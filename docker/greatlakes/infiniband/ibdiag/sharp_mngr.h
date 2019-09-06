/*
 * Copyright (c) 2004-2012 Mellanox Technologies LTD. All rights reserved.
 *
 * This software is available to you under the terms of the
 * OpenIB.org BSD license included below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */


#ifndef SHARP_MNGR_H
#define SHARP_MNGR_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <list>
#include <map>
using namespace std;

#include <infiniband/ibdm/Fabric.h>
#include <ibis/ibis.h>

#include <infiniband/ibdiag/ibdiag_ibdm_extended_info.h>
#include <infiniband/ibdiag/ibdiag_fabric_errs.h>
#include <infiniband/ibdiag/ibdiag_types.h>

#define DEFAULT_SL  0
#define DEFAULT_AM_KEY  0
#define DEFAULT_AM_CLASS_VERSION  1
#define MAX_TREE_ID 63
#define MAX_CHILD_IDX_IN_TREE_CONFIG_MAD    44
#define ALL_COUNTERS_SELECT 0xffff
typedef enum {
    QP_STATE_DISABLED = 0,
    QP_STATE_ACTIVE,
    QP_STATE_ERROR
} qp_state;

typedef list < IBNode * > vector_ibnodes;
typedef list < class SharpAggNode * > list_sharp_an;
typedef vector < class SharpTreeEdge * > vector_p_sharp_tree_edge;
typedef vector < class SharpTreeNode * > vector_p_sharp_tree_node;
typedef map < lid_t, class SharpAggNode * ,less<lid_t> > map_lid_to_sharpagg_node;
typedef vector < class SharpTree * > vector_sharp_root_node;
typedef map < u_int32_t, struct AM_QPCConfig * ,less<u_int16_t> > map_qpn_to_qpc_config;
typedef map < u_int32_t, u_int16_t > map_qpn_to_treeid;

class IBDiag;
class SharpMngr {
private:
    u_int16_t                       m_fabric_max_trees_idx;
    IBDiag *                        m_ibdiag;

    map_lid_to_sharpagg_node        m_lid_to_sharp_agg_node;
    vector_sharp_root_node          m_sharp_root_nodes;
    list_sharp_an                   m_sharp_an;
    vector_ibnodes                  m_sharp_supported_nodes; //all IBNodes that supports Sharp

    int DiscoverSharpAggNodes(list_p_fabric_general_err& sharp_discovery_errors);
    int BuildTreeConfigDB(list_p_fabric_general_err& sharp_discovery_errors);
    int BuildQPCConfigDB(list_p_fabric_general_err& sharp_discovery_errors);
    int BuildANInfoDB(list_p_fabric_general_err& sharp_discovery_errors);

    int SharpMngrDumpCounters(ofstream &sout);
public:
    SharpMngr(IBDiag * ibdiag);
    ~SharpMngr(){}

    inline void UpdateFabricMaxTreeIdx(u_int16_t tree_index) {
        if (tree_index > this->m_fabric_max_trees_idx)
            m_fabric_max_trees_idx = tree_index;
    }
    void AddSharpSupportedNodes(IBNode * p_ibnode) {
        m_sharp_supported_nodes.push_back(p_ibnode);
    }

    int BuildSharpConfigurationDB(
        list_p_fabric_general_err &sharp_discovery_errors,
        progress_func_nodes_t progress_func);

    int BuildPerformanceCountersDB(list_p_fabric_general_err& sharp_discovery_errors);
    int ResetPerformanceCounters(list_p_fabric_general_err &sharp_discovery_errors);

    int ConnectTreeEdges(list_p_fabric_general_err &sharp_discovery_errors);
    int CheckSharpTrees(list_p_fabric_general_err &sharp_discovery_errors);

    int WriteSharpFile(const char *file_name);
    int WriteSharpPMFile(const char *file_name);
    void SharpMngrDumpAllTrees(ofstream &sout);

    int AddTreeRoot(u_int16_t tree_idx,
                    SharpTreeNode *p_sharp_tree_node);
    SharpTree * GetTree(u_int16_t tree_idx);

    int SharpMngrDumpAllQPs(ofstream &sout);

    void DumpQPC(ofstream &sout, struct AM_QPCConfig *qpconfig);
};

class SharpAggNode {
private:
    IBPort *                        m_port;
    AM_ANInfo                       m_an_info;
    AM_PerformanceCounters          m_perf_cntr;
    vector_p_sharp_tree_node        m_trees;

public:
    SharpAggNode(IBPort * port);
    ~SharpAggNode();

    inline u_int16_t GetMaxNumQps() const { return m_an_info.max_num_qps; }
    inline u_int16_t GetTreesSize() { return (u_int16_t)this->m_trees.size(); };
    inline IBPort * GetIBPort() const { return m_port; }

    inline void SetPerfCounters(AM_PerformanceCounters  *perf_cntr) {
        m_perf_cntr = *perf_cntr;
    }
    inline const AM_PerformanceCounters & GetPerfCounters() const {
        return m_perf_cntr;
    }

    void SetANInfo(AM_ANInfo *an_info);
    inline const AM_ANInfo & GetANInfo() const { return m_an_info; }

    int AddSharpTreeNode(SharpTreeNode *p_sharp_tree_node,
                         u_int16_t tree_index);
    SharpTreeNode * GetSharpTreeNode(u_int16_t tree_index);
};

class SharpTree {
private:
    SharpTreeNode *         m_root;
    uint32_t                m_max_radix;

public:
    SharpTree(SharpTreeNode *root);
    ~SharpTree(){}

    inline uint32_t GetMaxRadix() const { return m_max_radix; }
    inline void SetMaxRadix(uint32_t max_radix) { m_max_radix = max_radix; }
    inline SharpTreeNode * GetRoot() const { return m_root; }
};

class SharpTreeNode {
private:
    u_int16_t                   m_tree_id;
    int                         m_child_idx;
    SharpAggNode *              m_agg_node;
    SharpTreeEdge *             m_parent;
    vector_p_sharp_tree_edge    m_children;

public:
    SharpTreeNode(SharpAggNode *aggNode,
                  u_int16_t treeid);
    ~SharpTreeNode(){}

    inline u_int16_t GetTreeId() const { return m_tree_id; }

    inline void SetChildIdx(int child_idx) { m_child_idx = child_idx; }

    inline SharpTreeEdge * GetSharpParentTreeEdge() const { return m_parent; }
    inline void SetSharpParentTreeEdge(SharpTreeEdge * parent) { m_parent = parent; }

    inline u_int8_t GetChildrenSize() const { return (u_int8_t)this->m_children.size(); };

    int AddSharpTreeEdge(SharpTreeEdge *p_sharp_tree_eage,
                         u_int8_t db_index);
    SharpTreeEdge * GetSharpTreeEdge(u_int8_t db_index);

    void DumpTree(int indent_level, ofstream &sout);
};

class SharpTreeEdge {
private:
    SharpTreeNode * m_remote_tree_node;
    u_int32_t m_qpn;
    u_int8_t m_child_idx;
    struct AM_QPCConfig  m_qpc_config;

public:
    SharpTreeEdge(u_int32_t qp_num, u_int8_t qp_idx);
    ~SharpTreeEdge(){}

   inline SharpTreeNode * GetRemoteTreeNode() const { return m_remote_tree_node; }
   //TODO remove this
   inline void SetRemoteTreeNode(SharpTreeNode * remote_tree_node) {
       m_remote_tree_node = remote_tree_node;
   }

   inline u_int32_t GetQpn() const { return m_qpn; }
   inline u_int8_t GetChildIdx() const { return m_child_idx; }

   inline struct AM_QPCConfig GetQPCConfig() const { return m_qpc_config; }
   inline void SetQPCConfig(struct AM_QPCConfig  qpc_config) { m_qpc_config = qpc_config; }

   void AddToQpcMap(map_qpn_to_qpc_config &qpc_map) {
       qpc_map.insert(pair<u_int32_t, struct AM_QPCConfig *> (m_qpn, &m_qpc_config));
   }
};


#endif  /* SHARP_MNGR_H */
