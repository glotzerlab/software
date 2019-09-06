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


#ifndef IBDIAG_IBDM_EXTENDED_INFO_H
#define IBDIAG_IBDM_EXTENDED_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <list>
#include <vector>
using namespace std;

#include <infiniband/ibdm/Fabric.h>
#include <ibis/packets/packets_layouts.h>

#include "ibdiag_types.h"



/*****************************************************/

//Go over speed's bits and add speed name
//regular speeds section at offset 0, first byte
//extended speeds section at offset 8, second byte
//mlnx speeds section at offset 16, third byte
static inline string supspeed2char(const u_int32_t speed)
{
    string speeds_str = "", section_speed_str = "";

    //check by speeds sections, as many bits are 0
    unsigned int check_offset[] = {0, 8, 16};
    u_int32_t offset = 0, mask = 0, speed_bit = 0;
    u_int8_t section = 0;

    //look at different speeds sections
    for (unsigned int i = 0; i < 3; i++) {
        speed_bit = 0;
        offset = check_offset[i];
        mask = 0xff << offset;
        section = (u_int8_t)((speed & mask) >> offset);
        while (section) {
            if (section & 0x1) {
                section_speed_str =
                    speed2char((IBLinkSpeed)(0x1 << (speed_bit + offset)));
                if (section_speed_str != IB_UNKNOWN_LINK_SPEED_STR)
                    speeds_str += (section_speed_str + " or ");
            }
            section = (u_int8_t)(section >> 1);
            speed_bit ++;
        }
    }
    //remove last " or "
    if (speeds_str.size() > 4)
        speeds_str.replace(speeds_str.size() - 4, string::npos, "");

    return speeds_str;
}

static inline const char * supwidth2char(const u_int8_t w)
{
    switch (w) {
    case 1:     return("1x");
    case 2:     return("4x");
    case 3:     return("1x or 4x");
    case 4:     return("8x");
    case 5:     return("1x or 8x");
    case 6:     return("4x or 8x");
    case 7:     return("1x or 4x or 8x");
    case 8:     return("12x");
    case 9:     return("1x or 12x");
    case 10:    return("4x or 12x");
    case 11:    return("1x or 4x or 12x");
    case 12:    return("8x or 12x");
    case 13:    return("1x or 8x or 12x");
    case 14:    return("4x or 8x or 12x");
    case 15:    return("1x or 4x or 8x or 12x");
    case 16:    return("2x");
    case 17:    return("1x or 2x");
    case 18:    return("2x or 4x");
    case 19:    return("1x or 2x or 4x");
    case 20:    return("2x or 8x");
    case 21:    return("1x or 2x or 8x");
    case 22:    return("2x or 4x or 8x");
    case 23:    return("1x or 2x or 4x or 8x");
    case 24:    return("2x or 12x");
    case 25:    return("1x or 2x or 12x");
    case 26:    return("2x or 4x or 12x");
    case 27:    return("1x or 2x or 4x or 12x");
    case 28:    return("2x or 8x or 12x");
    case 29:    return("1x or 2x or 8x or 12x");
    case 30:    return("2x or 4x or 8x or 12x");
    case 31:    return("1x or 2x or 4x or 8x or 12x");
    default:    return("UNKNOWN");
    }
};


IBLinkSpeed CalcFinalSpeed(u_int32_t speed1, u_int32_t speed2);
IBLinkWidth CalcFinalWidth(u_int8_t width1, u_int8_t width2);
u_int64_t CalcLinkRate(IBLinkWidth link_width, IBLinkSpeed link_speed);

// get the mlnx extended speeds | extended speeds | regular speeds
//for enabled supported and active
void GetTotalSpeeds(IN SMP_PortInfo *p_port_info,
                    IN SMP_MlnxExtPortInfo *p_mlnx_ext_port_info,
                    IN u_int32_t cap_mask,
                    OUT u_int32_t *sup_speed,
                    OUT u_int32_t *en_speed,
                    OUT u_int32_t *actv_speed);

static inline bool IsValidEnableSpeed(u_int32_t link_speed_en, u_int32_t link_speed_sup)
{
    return (((u_int32_t)link_speed_en | (u_int32_t)link_speed_sup) == (u_int32_t)link_speed_sup);
}
static inline bool IsValidEnableWidth(u_int8_t link_width_en, u_int8_t link_width_sup)
{
    return (((u_int8_t)link_width_en | (u_int8_t)link_width_sup) == (u_int8_t)link_width_sup);
}

static inline u_int8_t LinkWidthToLane(IBLinkWidth link_width)
{
    IBDIAG_ENTER;

    switch (link_width) {
    case IB_LINK_WIDTH_1X:  IBDIAG_RETURN(1); break;
    case IB_LINK_WIDTH_4X:  IBDIAG_RETURN(4); break;
    case IB_LINK_WIDTH_8X:  IBDIAG_RETURN(8); break;
    case IB_LINK_WIDTH_12X: IBDIAG_RETURN(12); break;
    case IB_LINK_WIDTH_2X:  IBDIAG_RETURN(2); break;
    default: IBDIAG_RETURN(0); break;
    }
}

typedef enum {
    IB_PORT_PHYS_STATE_UNKNOWN           = 0,
    IB_PORT_PHYS_STATE_SLEEP             = 1,
    IB_PORT_PHYS_STATE_POLLING           = 2,
    IB_PORT_PHYS_STATE_DISABLED          = 3,
    IB_PORT_PHYS_STATE_PORT_CONF_TRAIN   = 4,
    IB_PORT_PHYS_STATE_LINK_UP           = 5,
    IB_PORT_PHYS_STATE_LINK_ERR_RECOVERY = 6,
    IB_PORT_PHYS_STATE_PHY_TEST          = 7
    /* 8-15 reserved */
} IBPortPhysState;

static inline const char * portphysstate2char(const IBPortPhysState w)
{
    switch (w)
    {
    case IB_PORT_PHYS_STATE_SLEEP:             return("SLEEP");
    case IB_PORT_PHYS_STATE_POLLING:           return("POLL");
    case IB_PORT_PHYS_STATE_DISABLED:          return("DISABLE");
    case IB_PORT_PHYS_STATE_PORT_CONF_TRAIN:   return("PORT CONF TRAIN");
    case IB_PORT_PHYS_STATE_LINK_UP:           return("LINK UP");
    case IB_PORT_PHYS_STATE_LINK_ERR_RECOVERY: return("LINK ERR RECOVER");
    case IB_PORT_PHYS_STATE_PHY_TEST:          return("PHY TEST");
    case IB_PORT_PHYS_STATE_UNKNOWN: default:  return("UNKNOWN");
    }
};

/*****************************************************/
class IBDMExtendedInfo {
private:
    //members
    string last_error;

    vector_p_node   nodes_vector;
    vector_p_port   ports_vector;
    vector_p_vport  vports_vector;
    vector_p_vnode  vnodes_vector;

    list_p_sm_info_obj                  sm_info_obj_list;

    vector_p_smp_node_info              smp_node_info_vector;           // by node index
    vector_p_smp_switch_info            smp_switch_info_vector;         // by node index
    vector_p_smp_port_info              smp_port_info_vector;           // by port index
    vector_p_smp_port_info_ext          smp_port_info_ext_vector;       // by port index
    vector_p_smp_mlnx_ext_port_info     smp_mlnx_ext_port_info_vector;  // by port index
    vector_p_vs_general_info            vs_general_info_vector;         // by node index
    vector_p_pm_cap_mask                pm_cap_mask_vector;             // by node index
    vector_p_pm_info_obj                pm_info_obj_vector;             // by port index
    vector_p_pm_option_mask             pm_option_mask_vector;          // by port index
    vector_p_vs_mlnx_cntrs_obj          vs_mlnx_cntrs_obj_vector;       // by port index
    vector_p_smp_virtual_info           smp_virtual_info_vector;        // by port index
    vector_p_smp_vport_info             smp_vport_info_vector;          // by port index
    vector_p_smp_vnode_info             smp_vnode_info_vector;          // by vport index

    vector_p_smp_qos_config_sl          smp_qos_config_sl_vector;       // by port index
    vector_p_smp_temp_sensing           smp_temp_sensing_vector;        // by node index
    vector_v_smp_vport_state            smp_vport_state_vector;         // by port index ,block index
    vector_v_smp_pkey_tbl               smp_vport_pkey_tbl_v_vector;    // by vport index, block index
    vector_v_smp_pkey_tbl               smp_pkey_tbl_v_vector;          // by port index, block index
    vector_v_smp_guid_tbl               smp_guid_tbl_v_vector;          // by port index, block index

    vector_p_smp_router_info            smp_router_info_vector;         //by node index
    vector_v_smp_adj_router_tbl         smp_adj_router_tbl_v_vector;    //by node index, block index
    vector_v_smp_next_hop_router_tbl    smp_nh_router_tbl_v_vector;     //by node index, block index

    //methods
    void SetLastError(const char *fmt, ...);

    template <class OBJ_VEC_TYPE, class OBJ_TYPE>
    void addPtrToVec(OBJ_VEC_TYPE& vector_obj, OBJ_TYPE *p_obj);

    int addPMObjectInfo(IBPort *p_port);
    int addMlnxCntrsObject(IBPort *p_port);

    template <class OBJ_VEC_TYPE, class OBJ_TYPE>
    OBJ_TYPE * getPtrFromVec(OBJ_VEC_TYPE& vector_obj, u_int32_t create_index);

    template <class OBJ_VEC_TYPE, class OBJ_TYPE, class DATA_VEC_TYPE, class DATA_TYPE>
    int addDataToVec(OBJ_VEC_TYPE& vector_obj,
            OBJ_TYPE *p_obj,
            DATA_VEC_TYPE& vector_data,
            DATA_TYPE& data);

    template <class OBJ_VEC_TYPE, class OBJ_TYPE, class DATA_VEC_TYPE, class DATA_TYPE>
    int addDataToVecInVec(OBJ_VEC_TYPE& vector_obj,
            OBJ_TYPE *p_obj,
            DATA_VEC_TYPE& vec_of_vectors,
            u_int32_t data_idx,
            DATA_TYPE& data);

    template <class OBJ_VEC_TYPE, class OBJ_TYPE>
    OBJ_TYPE * getPtrFromVecInVec(OBJ_VEC_TYPE& vec_of_vectors,
            u_int32_t idx1,
            u_int32_t idx2);

public:
    //methods
    void CleanUpInternalDB();

    IBDMExtendedInfo();
    ~IBDMExtendedInfo();

    const char* GetLastError();

    inline u_int32_t getNodesVectorSize() { return (u_int32_t)this->nodes_vector.size(); }
    inline u_int32_t getPortsVectorSize() { return (u_int32_t)this->ports_vector.size(); }
    inline u_int32_t getVPortsVectorSize() { return (u_int32_t)this->vports_vector.size(); }
    inline u_int32_t getVNodesVectorSize() { return (u_int32_t)this->vnodes_vector.size(); }

    IBNode * getNodePtr(u_int32_t node_index);
    IBPort * getPortPtr(u_int32_t port_index);
    IBVNode * getVNodePtr(u_int32_t vnode_index);
    IBVPort * getVPortPtr(u_int32_t vport_index);

    //Returns: SUCCESS_CODE / ERR_CODE_INCORRECT_ARGS / ERR_CODE_NO_MEM
    int addSMPSMInfoObj(IBPort *p_port, struct SMP_SMInfo &smpSMInfo);
    int addSMPNodeInfo(IBNode *p_node, struct SMP_NodeInfo &smpNodeInfo);
    int addSMPSwitchInfo(IBNode *p_node, struct SMP_SwitchInfo &smpSwitchInfo);
    int addSMPPortInfo(IBPort *p_port, struct SMP_PortInfo &smpPortInfo);
    int addSMPPortInfoExtended(IBPort *p_port, struct SMP_PortInfoExtended &smpPortInfoExt);
    int addSMPMlnxExtPortInfo(IBPort *p_port, struct SMP_MlnxExtPortInfo &smpMlnxExtPortInfo);
    int addVSGeneralInfo(IBNode *p_node, struct VendorSpec_GeneralInfo &vsGeneralInfo);
    int addPMCapMask(IBNode *p_node, u_int16_t pm_cap_mask);
    int addPMPortCounters(IBPort *p_port, struct PM_PortCounters &pmPortCounters);
    int addPMPortCountersExtended(IBPort *p_port, struct PM_PortCountersExtended &pmPortCountersExtended);
    int addPMPortExtSpeedsCounters(IBPort *p_port, struct PM_PortExtendedSpeedsCounters &pmPortExtendedSpeedsCounters);
    int addPMPortExtSpeedsRSFECCounters(IBPort *p_port,
    struct PM_PortExtendedSpeedsRSFECCounters &pmPortExtSpeedsRSFECCounters);
    int addVSPortLLRStatistics(IBPort *p_port, struct VendorSpec_PortLLRStatistics &vsPortLLRCounters);
    int addPMPortCalculatedCounters(IBPort *p_port, struct PM_PortCalcCounters &pmPortCalcCounters);
    int addPMOptionMask(IBNode *p_node, struct PortSampleControlOptionMask &pm_option_mask);
    int addSMPPKeyTable(IBPort *p_port, struct SMP_PKeyTable &smpPKeyTable, u_int32_t block_idx);
    int addSMPGUIDInfo(IBPort *p_port, struct SMP_GUIDInfo &smpGUIDInfo, u_int32_t block_idx);
    int addVSDiagnosticCountersPage0(IBPort *p_port, struct VS_DiagnosticData &vs_mlnx_cntrs_p0);
    int addVSDiagnosticCountersPage1(IBPort *p_port, struct VS_DiagnosticData &vs_mlnx_cntrs_p1);
    int addVSDiagnosticCountersPage255(IBPort *p_port, struct VS_DiagnosticData &vs_mlnx_cntrs_p255);
    int applySubCluster();
    int addSMPVirtualizationInfo(IBPort *p_port,
                                 struct SMP_VirtualizationInfo &virtual_info);
    int addSMPVPortState(IBPort *p_port, struct SMP_VPortState &smpVPortState, u_int32_t block_idx);
    int addSMPVPortInfo(IBVPort *p_vport, struct SMP_VPortInfo &smpVPortInfo);
    int addSMPVNodeInfo(IBVNode *p_vnode, struct SMP_VNodeInfo &smpVNodeInfo);
    int addSMPVNodeDescription(IBVNode *p_vnode,
                               struct SMP_NodeDesc &smpVNodeDescription);
    int addSMPVPortPKeyTable(IBVPort *p_vport, struct SMP_PKeyTable &smpVPortPKeyTable, u_int16_t block_idx);
    int addSMPRouterInfo(IBNode *p_node, struct SMP_RouterInfo &smpRouterInfo);
    int addSMPAdjSiteLocalSubnTbl(IBNode *p_node, struct SMP_AdjSiteLocalSubnTbl &smpRouterTbl, u_int8_t block_idx);
    int addSMPNextHopTbl(IBNode *p_node, struct SMP_NextHopTbl &smpRouterTbl, u_int32_t block_idx);

    // PortRcvErrorDetails and PortXmitDiscardDetails
    int addPMPortRcvErrorDetails(IBPort *p_port,
                                 struct PM_PortRcvErrorDetails &pmPortRcvErrorDetails);
    int addPMPortXmitDiscardDetails(IBPort *p_port,
                                    struct PM_PortXmitDiscardDetails &pmPortXmitDiscardDetails);

    SMP_NodeInfo*               getSMPNodeInfo(u_int32_t node_index);
    SMP_SwitchInfo*             getSMPSwitchInfo(u_int32_t node_index);
    SMP_PortInfo*               getSMPPortInfo(u_int32_t port_index);
    SMP_PortInfoExtended *      getSMPPortInfoExtended(u_int32_t port_index);
    SMP_MlnxExtPortInfo*        getSMPMlnxExtPortInfo(u_int32_t port_index);
    VendorSpec_GeneralInfo*     getVSGeneralInfo(u_int32_t node_index);
    u_int16_t*                  getPMCapMask(u_int32_t node_index);
    PM_PortCounters*            getPMPortCounters(u_int32_t port_index);
    PM_PortCountersExtended*    getPMPortCountersExtended(u_int32_t port_index);
    PM_PortExtendedSpeedsCounters * getPMPortExtSpeedsCounters(u_int32_t port_index);
    PM_PortExtendedSpeedsRSFECCounters *
        getPMPortExtSpeedsRSFECCounters(u_int32_t port_index);
    VendorSpec_PortLLRStatistics * getVSPortLLRStatistics(u_int32_t port_index);
    // PortRcvErrorDetails and PortXmitDiscardDetails
    PM_PortRcvErrorDetails* getPMPortRcvErrorDetails(u_int32_t port_index);
    PM_PortXmitDiscardDetails* getPMPortXmitDiscardDetails(u_int32_t port_index);
    PM_PortCalcCounters *       getPMPortCalcCounters(u_int32_t port_index);
    struct PortSampleControlOptionMask * getPMOptionMask(u_int32_t node_index);
    SMP_PKeyTable *             getSMPPKeyTable(u_int32_t port_index, u_int32_t block_idx);
    SMP_GUIDInfo *              getSMPGUIDInfo(u_int32_t port_index, u_int32_t block_idx);
    VS_DiagnosticData *         getVSDiagnosticCountersPage0(u_int32_t port_index);
    VS_DiagnosticData *         getVSDiagnosticCountersPage1(u_int32_t port_index);
    VS_DiagnosticData *         getVSDiagnosticCountersPage255(u_int32_t port_index);
    SMP_VirtualizationInfo *    getSMPVirtualizationInfo(u_int32_t port_index);
    SMP_VPortState * getSMPVPortState(u_int32_t port_index, u_int32_t block_idx);
    SMP_VPortInfo * getSMPVPortInfo(u_int32_t port_index);
    SMP_VNodeInfo * getSMPVNodeInfo(u_int32_t vnode_index);
    SMP_RouterInfo *            getSMPRouterInfo(u_int32_t node_index);
    SMP_AdjSiteLocalSubnTbl *   getSMPAdjSiteLocalSubnTbl(u_int32_t node_index,
                                                          u_int8_t block_idx);
    SMP_NextHopTbl *            getSMPNextHopTbl(u_int32_t node_index,
                                                 u_int32_t block_idx);

    struct SMP_NodeDesc * getSMPVNodeDescription(u_int32_t vnode_index);
    SMP_PKeyTable * getSMPVPortPKeyTable(u_int32_t vport_index, u_int16_t block_idx);

    int addSMPQosConfigSL(IBPort *p_port, SMP_QosConfigSL &qos_config_sl);
    struct SMP_QosConfigSL* getSMPQosConfigSL(u_int32_t port_index);

    int addSMPTempSensing(IBNode *p_node, SMP_TempSensing &p_temp_sense);
    struct SMP_TempSensing * getSMPTempSensing(u_int32_t node_index);

    uint8_t getSMPVPortStateVectorSize(u_int32_t port_index);

    inline list_p_sm_info_obj& getSMPSMInfoListRef() { return this->sm_info_obj_list; }
    inline vector_p_smp_node_info& getSMPNodeInfoVectorRef() { return this->smp_node_info_vector; }
    inline vector_p_smp_switch_info& getSMPSwitchInfoVectorRef() { return this->smp_switch_info_vector; }
    inline vector_p_smp_port_info& getSMPPortInfoVectorRef() { return this->smp_port_info_vector; }
    inline vector_p_vs_general_info& getVSGeneralInfoVectorRef() { return this->vs_general_info_vector; }
    inline vector_p_pm_cap_mask& getPMCapMaskVectorRef() { return this->pm_cap_mask_vector; }
    inline vector_p_pm_info_obj& getPMInfoObjVectorRef() { return this->pm_info_obj_vector; }
};

typedef SMP_PKeyTable* (IBDMExtendedInfo::*get_pkey_table_func_t)(u_int32_t, u_int16_t);

#endif          /* IBDIAG_IBDM_EXTENDED_INFO_H */

