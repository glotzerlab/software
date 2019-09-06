/*
 * Copyright (c) 2004-2015 Mellanox Technologies LTD. All rights reserved.
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


#ifndef IBIS_H_
#define IBIS_H_


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>      // std::ifstream
#include <stdexcept>
using namespace std;

#include "ibis_types.h"
#include "mkey_mngr.h"
#include "csv_parser.h"
#include "../ibutils/memory_pool.h"
#include "Regexp.h"

#define IB_SLT_UNASSIGNED 255

struct node_addr_t {
    direct_route_t m_direct_route;
    u_int16_t      m_lid;
    bool operator < (const node_addr_t& y) const
    {
        if (m_lid != y.m_lid)
            return m_lid < y.m_lid;
        if (m_direct_route.length != y.m_direct_route.length)
            return m_direct_route.length < y.m_direct_route.length;
        return memcmp(m_direct_route.path.BYTE, y.m_direct_route.path.BYTE,
                      m_direct_route.length) < 0;
    }
};

/*
struct less_node_addr {
  bool operator() (const node_addr_t* x, const node_addr_t* y) const
  {
      if (x->m_lid != y->m_lid)
          return x->m_lid < y->m_lid;
      if (x->m_direct_route.length != y->m_direct_route.length)
          return x->m_direct_route.length < y->m_direct_route.length;
      return memcmp(x->m_direct_route.path.BYTE, y->m_direct_route.path.BYTE,
                    x->m_direct_route.length) < 0;
  }
};
*/

struct transaction_data_t;

struct pending_mad_data_t {
    u_int8_t* m_umad;
    unsigned int m_umad_size;
    u_int8_t m_mgmt_class;
    transaction_data_t * m_transaction_data;

    pending_mad_data_t():m_umad(NULL),m_umad_size(0),
                         m_mgmt_class(0),
                         m_transaction_data(NULL) {}

    ~pending_mad_data_t() {
        delete[] m_umad;
    }

    int init();
};


struct ib_address_t {
    u_int16_t m_lid;
    u_int32_t m_qp;
    u_int32_t m_qkey;
    u_int8_t m_sl;

    ib_address_t(u_int16_t lid, u_int32_t qp, u_int32_t qkey, u_int8_t sl):
            m_lid(lid), m_qp(qp), m_qkey(qkey), m_sl(sl) {}
};


typedef void (*mad_handler_callback_func_t)
    (ib_address_t *p_ib_address, void *p_class_data, void *p_attribute_data,
     void *context);

struct mad_handler_t {
    unpack_data_func_t          m_unpack_class_data_func;
    dump_data_func_t            m_dump_class_data_func;
    unpack_data_func_t          m_unpack_attribute_data_func;
    dump_data_func_t            m_dump_attribute_data_func;
    mad_handler_callback_func_t m_callback_func;
    void                       *m_context;
    u_int8_t                     m_data_offset;
};

typedef std::map<pair<u_int16_t, u_int8_t>, mad_handler_t> attr_method_pair_to_handler_map_t;

typedef list<pending_mad_data_t *>  pending_mads_on_node_t;

struct transaction_data_t {
    u_int8_t           m_data_offset;
    unpack_data_func_t m_unpack_class_data_func;
    dump_data_func_t   m_dump_class_data_func;
    unpack_data_func_t m_unpack_attribute_data_func;
    dump_data_func_t   m_dump_attribute_data_func;
    bool               m_is_smp;
    clbck_data_t       m_clbck_data;
    pending_mads_on_node_t *m_pending_mads;

    transaction_data_t() :
            m_data_offset(0),
            m_unpack_class_data_func(NULL),
            m_dump_class_data_func(NULL),
            m_unpack_attribute_data_func(NULL),
            m_dump_attribute_data_func(NULL),
            m_is_smp(false),
            m_clbck_data(),
            m_pending_mads(NULL) {}

    int init(){return 0;} //for MemoryPool usage

    void Set(u_int8_t data_offset,
             const unpack_data_func_t unpack_class_data_func,
             const dump_data_func_t   dump_class_data_func,
             const unpack_data_func_t unpack_attribute_data_func,
             const dump_data_func_t   dump_attribute_data_func,
             bool is_smp,
             const clbck_data_t &clbck_data,
             pending_mads_on_node_t *pending_mads)
    {
        m_data_offset = data_offset;
        m_unpack_class_data_func = unpack_class_data_func;
        m_dump_class_data_func = dump_class_data_func;
        m_unpack_attribute_data_func = unpack_attribute_data_func;
        m_dump_attribute_data_func = dump_attribute_data_func;
        m_is_smp = is_smp;
        m_clbck_data = clbck_data;
        m_pending_mads = pending_mads;
    }



    /*
    transaction_data_t(
        u_int8_t data_offset,
        const unpack_data_func_t unpack_class_data_func,
        const dump_data_func_t   dump_class_data_func,
        const unpack_data_func_t unpack_attribute_data_func,
        const dump_data_func_t   dump_attribute_data_func,
        bool is_smp,
        const clbck_data_t &clbck_data,
        pending_mads_on_node_t *pending_mads) :
            m_data_offset(data_offset),
            m_unpack_class_data_func(unpack_class_data_func),
            m_dump_class_data_func(dump_class_data_func),
            m_unpack_attribute_data_func(unpack_attribute_data_func),
            m_dump_attribute_data_func(dump_attribute_data_func),
            m_is_smp(is_smp),
            m_clbck_data(clbck_data),
            m_pending_mads(pending_mads) {}
            */

    /*
    transaction_data_t& operator=(const transaction_data_t& transaction_data)
    {
        m_data_offset = transaction_data.m_data_offset;
        m_unpack_class_data_func = transaction_data.m_unpack_class_data_func;
        m_dump_class_data_func = transaction_data.m_dump_class_data_func;
        m_unpack_attribute_data_func = transaction_data.m_unpack_attribute_data_func;
        m_dump_attribute_data_func = transaction_data.m_dump_attribute_data_func;
        m_is_smp = transaction_data.m_is_smp;
        m_handle_data_func = transaction_data.m_handle_data_func;
        m_p_obj = transaction_data.m_p_obj;
        m_p_key = transaction_data.m_p_key;
        return *this;
    }
    */

};

struct port_properties_t {
    uint16_t base_lid;
    uint16_t sm_lid;
    uint64_t port_guid;
    uint64_t subnet_prefix;

    port_properties_t(): base_lid(0), sm_lid(0), port_guid(0), subnet_prefix(0) {}
};

typedef map < u_int32_t, transaction_data_t *>  transactions_map_t;
typedef map < node_addr_t, pending_mads_on_node_t >  mads_on_node_map_t;
typedef list < transaction_data_t *>  transactions_queue_t;
typedef list < u_int8_t > methods_list_t;
typedef vector < u_int8_t > class_versions_vec_t;

typedef list < u_int16_t > device_id_list_t;

typedef void(*ibis_log_msg_function_t)(const char *file_name, unsigned line_num,
                                       const char *function_name, int level,
                                       const char *format, ...);

typedef void(*ibis_log_mad_function_t)(dump_data_func_t dump_func,
                                       void *mad_obj, bool msg_send_mad);


/****************************************************/
const char * get_ibis_version();


/****************************************************/
class Ibis {
private:
    ////////////////////
    //members
    ////////////////////
    string dev_name;
    phys_port_t port_num;

    enum {NOT_INITILIAZED, NOT_SET_PORT, READY} ibis_status;
    string last_error;

    void *p_umad_buffer_send;       /* buffer for send mad - sync buffer */
    void *p_umad_buffer_recv;       /* buffer for recv mad - sync buffer */
    u_int8_t *p_pkt_send;           /* mad pkt to send */
    u_int8_t *p_pkt_recv;           /* mad pkt was received */
    u_int64_t mads_counter;         /* number of mads we sent already */

    MKeyManager *p_mkeymngr;
    int umad_port_id;									/* file descriptor returned by umad_open() */
    int umad_agents_by_class[IBIS_IB_MAX_MAD_CLASSES]
                            [IBIS_IB_MAX_CLASS_VERSION_SUPP + 1]; /* array to map class --> agent */

    // class version to register
    class_versions_vec_t class_versions_by_class[IBIS_IB_MAX_MAD_CLASSES];

    // Methods to register as replier
    methods_list_t replier_methods_list_by_class[IBIS_IB_MAX_MAD_CLASSES];
    int timeout;
    int retries;

    // Unsolicited MADs handler
    attr_method_pair_to_handler_map_t m_mad_handlers_by_class[IBIS_IB_MAX_MAD_CLASSES];

    vector<uint8_t > PSL;          /* PSL table (dlid->SL mapping) of this node */
    bool usePSL;

    //asynchronouse invocation
    MemoryPool<transaction_data_t> m_transaction_data_pool;
    transactions_map_t transactions_map;
    u_int32_t m_pending_gmps;
    u_int32_t m_pending_smps;
    u_int32_t m_max_gmps_on_wire;
    u_int32_t m_max_smps_on_wire;

    MemoryPool<pending_mad_data_t> m_pending_mads_pool;
    mads_on_node_map_t      m_mads_on_node_map;
    transactions_queue_t m_pending_nodes_transactions;
    bool suppressMadSending;       /* Indicator for Ibis to void sending MADs */


    ////////////////////
    //methods
    ////////////////////
    void SetLastError(const char *fmt, ...);

    // Returns: 0 - success / 1 - error
    int Bind();
    void CalculateMethodMaskByClass(u_int8_t mgmt_class, long (&method_mask)[4]);

    /*
     * Add methods to class for IBIS to register as a replier.
     * This method should be called before calling SetPort.
     */
    int AddMethodToClass(uint8_t mgmt_class, u_int8_t methods);

    int RecvMad(u_int8_t mgmt_class, int umad_timeout);
    int SendMad(u_int8_t mgmt_class, int umad_timeout, int umad_retries);
    int RecvAsyncMad(int umad_timeout);

    int AsyncRec(bool &retry, pending_mad_data_t *&next_pending_mad_data);
    void MadRecTimeoutAll();
    void MadRecTimeoutAll(transaction_data_t *p_transaction_data);
    void TimeoutAllPendingMads();

    /*
     * Checks if method is of a request MAD
     * Returns true if the method is of a request, otherwise false
     */
    bool IsRequestMad(uint8_t method);

    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR / IBIS_MAD_STATUS_SUCCESS
     */
    int DoRPC(u_int8_t mgmt_class);

    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_GENERAL_ERR
     *  IBIS_MAD_STATUS_SUCCESS
     */
    int DoAsyncSend(u_int8_t mgmt_class);

    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR / IBIS_MAD_STATUS_SUCCESS
     */
    int DoAsyncRec();

    /*
     * remove the current pending mad data from the list and free it
     * set next_pending_mad_data to the next element in the list.
     *
     * Returns: IBIS_MAD_STATUS_GENERAL_ERR / IBIS_MAD_STATUS_SUCCESS
     */
    int GetNextPendingData(transaction_data_t * p_transaction_data,
                           pending_mad_data_t *&next_pending_mad_data);

    /*
     * Send the current mad
     * May recive mad and send pending mad on the received mad address
     * Returns: IBIS_MAD_STATUS_GENERAL_ERR / IBIS_MAD_STATUS_SUCCESS
     */
    int AsyncSendAndRec(u_int8_t mgmt_class,
                        transaction_data_t *p_transaction_data,
                        pending_mad_data_t *pending_mad_data);

    /*
     * Invoke call back function
     */
    void InvokeCallbackFunction(const clbck_data_t &clbck_data, int rec_status,
                                void *p_attribute_data);

    ////////////////////
    //methods mads
    ////////////////////
    void DumpReceivedMAD();
    void DumpMadData(dump_data_func_t dump_func, void *mad_obj,
                     bool msg_send_mad);
    void CommonMadHeaderBuild(struct MAD_Header_Common *mad_header,
            u_int8_t mgmt_class,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            u_int8_t class_version = 0);

    u_int8_t GetDefaultMgmtClassVersion(u_int8_t mgmt_class);

    ////////////////////
    //smp class methods
    ////////////////////
    void SMPHeaderDirectRoutedBuild(struct MAD_Header_SMP_Direct_Routed *smp_direct_route_header,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            u_int8_t direct_path_len);

    ////////////////////
    //mellanox methods
    ////////////////////
    bool IsSupportIB(void *type);
    bool IsIBDevice(void *arr, unsigned arr_size, u_int16_t dev_id);

    // Pointer to logging function
    static ibis_log_msg_function_t m_log_msg_function;
    static ibis_log_mad_function_t m_log_mad_function;

    void InitClassVersionsDB();
    int RegisterClassVersionToUmad(u_int8_t mgmt_class);

    inline int GetAgentId(u_int8_t mgmt_class, uint8_t class_version);
    inline int CheckValidAgentIdForClass(int recv_agent_id, u_int8_t mgmt_class,
                                         uint8_t class_version);
public:

    ////////////////////
    //methods
    ////////////////////
    Ibis();
    ~Ibis();

    inline bool IsInit() { return (this->ibis_status != NOT_INITILIAZED); };
    inline bool IsReady() { return (this->ibis_status == READY); };
    inline void SetTimeout(int timeout_value) { this->timeout = timeout_value; };
    inline void SetNumOfRetries(int retries_value) { this->retries = retries_value; };
    inline u_int64_t GetNewTID() { return ++this->mads_counter;	}
    //this function is for ibdiagnet's plugins
    inline void SetMADsCounter(u_int64_t mads_cnt) { this->mads_counter = mads_cnt; }
    inline u_int8_t *GetSendMadPktPtr() { return this->p_pkt_send; };
    inline u_int8_t *GetRecvMadPktPtr() { return this->p_pkt_recv; };

    const char* GetLastError();
    void ClearLastError() {last_error.clear();}
    bool IsFailed() {return !last_error.empty();}

    string ConvertDirPathToStr(direct_route_t *p_curr_direct_route);
    string ConvertMadStatusToStr(u_int16_t status);

    static ibis_log_msg_function_t GetLogMsgFunction() {
        return m_log_msg_function;
    }

    void SetLogMsgFunction(ibis_log_msg_function_t log_msg_function) {
        m_log_msg_function = log_msg_function;
    }

    static ibis_log_mad_function_t GetLogMadFunction() {
        return m_log_mad_function;
    }

    void SetLogMadFunction(ibis_log_mad_function_t log_mad_function) {
        m_log_mad_function = log_mad_function;
    }

    // Returns: 0 - success / 1 - error
    int Init();
    int SetPort(const char* device_name, phys_port_t port_num);
    int SetPort(u_int64_t port_guid);   //guid is BE

    int SetSendMadAddr(int d_lid, int d_qp, int sl, int qkey);
    int GetAllLocalPortGUIDs(OUT local_port_t local_ports_array[IBIS_MAX_LOCAL_PORTS],
            OUT u_int32_t *p_local_ports_num);

    // Returns: 0 - success / 1 - error
    int GetLocalPortProperties(OUT port_properties_t *p_port_properties);

    int SetPSLTable(const vector<uint8_t > &PSLTable);
    uint8_t getPSLForLid(u_int16_t lid);
    void setPSLForLid(u_int16_t lid, u_int16_t maxLid, uint8_t sl);

    void SetMaxMadsOnWire(u_int16_t max_gmps_on_wire, u_int8_t max_smps_on_wire)
    {
        m_max_gmps_on_wire = max_gmps_on_wire;
        m_max_smps_on_wire = max_smps_on_wire;
    }

    inline void SetMKeyManager(MKeyManager *ptr_mkeymngr){p_mkeymngr = ptr_mkeymngr;};
    inline MKeyManager * GetMKeyManager() {return p_mkeymngr;};

    ////////////////////
    //methods mads
    ////////////////////

    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int MadGetSet(ib_address_t *p_ib_address,
        u_int8_t mgmt_class,
        u_int8_t method,
        u_int8_t data_offset,
        void *p_class_data,
        void *p_attribute_data,
        const pack_data_func_t pack_class_data_func,
        const unpack_data_func_t unpack_class_data_func,
        const dump_data_func_t dump_class_data_func,
        const pack_data_func_t pack_attribute_data_func,
        const unpack_data_func_t unpack_attribute_data_func,
        const dump_data_func_t dump_attribute_data_func,
        const clbck_data_t *p_clbck_data);

    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int MadGetSet(u_int16_t lid,
            u_int32_t d_qp,
            u_int8_t sl,
            u_int32_t qkey,
            u_int8_t mgmt_class,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            u_int8_t data_offset,
            void *p_class_data,
            void *p_attribute_data,
            const pack_data_func_t pack_class_data_func,
            const unpack_data_func_t unpack_class_data_func,
            const dump_data_func_t dump_class_data_func,
            const pack_data_func_t pack_attribute_data_func,
            const unpack_data_func_t unpack_attribute_data_func,
            const dump_data_func_t dump_attribute_data_func,
            const clbck_data_t *p_clbck_data = NULL);

    void MadRecAll();

    //////////////////////
    // IBIS Server methods
    //////////////////////

    int ReceiveUnsolicitedMad(int timeout_ms);

    // Register MAD handler
    // Returns: 0 - success / 1 - error
    int RegisterMadHandler(u_int8_t mgmt_class, u_int16_t attribute_id,
                           u_int8_t method,
                           u_int8_t data_offset,
                           unpack_data_func_t unpack_class_data_func,
                           dump_data_func_t   dump_class_data_func,
                           unpack_data_func_t unpack_attribute_data_func,
                           dump_data_func_t dump_attribute_data_func,
                           mad_handler_callback_func_t callback_func,
                           void *context);

    ////////////////////
    //smp class methods
    ////////////////////
    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int SMPMadGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            void *p_smp_attribute_data,
            const pack_data_func_t smp_pack_attribute_data_func,
            const unpack_data_func_t smp_unpack_attribute_data_func,
            const dump_data_func_t smp_dump_attribute_data_func,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPMadGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            void *p_smp_attribute_data,
            const pack_data_func_t smp_pack_attribute_data_func,
            const unpack_data_func_t smp_unpack_attribute_data_func,
            const dump_data_func_t smp_dump_attribute_data_func,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int SMPPortInfoMadGetByLid(u_int16_t lid,
            phys_port_t port_number,
            struct SMP_PortInfo *p_port_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPortInfoExtMadGetByLid(u_int16_t lid,
                                  phys_port_t port_number,
                                  struct SMP_PortInfoExtended *p_port_info_ext,
                                  const clbck_data_t *p_clbck_data = NULL);
    int SMPMlnxExtPortInfoMadGetByLid(u_int16_t lid,
            phys_port_t port_number,
            struct SMP_MlnxExtPortInfo *p_mlnx_ext_port_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPSwitchInfoMadGetByLid(u_int16_t lid,
            struct SMP_SwitchInfo *p_switch_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPNodeInfoMadGetByLid(u_int16_t lid,
            struct SMP_NodeInfo *p_node_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPNodeDescMadGetByLid(u_int16_t lid,
            struct SMP_NodeDesc *p_node_desc,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPSMInfoMadGetByLid(u_int16_t lid,
            struct SMP_SMInfo *p_sm_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPLinearForwardingTableGetByLid(u_int16_t lid,
            u_int32_t lid_to_port_block_num,
            struct SMP_LinearForwardingTable *p_linear_forwarding_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPMulticastForwardingTableGetByLid(u_int16_t lid,
            u_int8_t port_group,
            u_int32_t lid_to_port_block_num,
            struct SMP_MulticastForwardingTable *p_multicast_forwarding_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPkeyTableGetByLid(u_int16_t lid,
            u_int16_t port_num,
            u_int16_t block_num,
            struct SMP_PKeyTable *p_pkey_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPGUIDInfoTableGetByLid(u_int16_t lid,
            u_int32_t block_num,
            struct SMP_GUIDInfo *p_guid_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPSLToVLMappingTableGetByLid(u_int16_t lid,
            phys_port_t out_port_number,
            phys_port_t in_port_number,
            struct SMP_SLToVLMappingTable *p_slvl_mapping,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPLFTInfoMadGetSetByLid(u_int16_t lid,
            u_int8_t method,
            ib_private_lft_info *p_plft_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPLFTDefMadGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int8_t plft_block,
            struct ib_private_lft_def *p_plft_def,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPLFTMapMadGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int8_t pLFTID,
            struct ib_private_lft_map *p_plft_map,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPortSLToPrivateLFTMapGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int8_t port_block,
            struct ib_port_sl_to_private_lft_map *p_plft_map,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPARInfoGetSetByLid(u_int16_t lid,
            u_int8_t method,
            bool get_cap,
            struct adaptive_routing_info *p_ar_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPARGroupTableGetSetByLid(u_int16_t lid,
            u_int8_t  method,
            u_int16_t group_block,
            u_int8_t  group_table,
            u_int8_t  pLFTID,
            struct ib_ar_group_table *p_ar_group_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPARLinearForwardingTableGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int32_t lid_block,
            u_int8_t pLFTID,
            struct ib_ar_linear_forwarding_table_sx *p_ar_linear_forwarding_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPExtendedSwitchInfoMadGetSetByLid(u_int16_t lid,
            u_int8_t method,
            struct ib_extended_switch_info *p_ext_sw_info,
            const clbck_data_t *p_clbck_data);


    int SMPRNSubGroupDirectionTableGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int16_t block_num,
            struct rn_sub_group_direction_tbl *p_sub_group_direction_table,
            const clbck_data_t *p_clbck_data);
    int SMPRNGenStringTableGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int8_t direction_block,
            u_int8_t pLFTID,
            struct rn_gen_string_tbl *p_gen_string_table,
            const clbck_data_t *p_clbck_data);
    int SMPRNGenBySubGroupPriorityMadGetSetByLid(u_int16_t lid,
            u_int8_t method,
            struct rn_gen_by_sub_group_prio *p_gen_by_sg_priority,
            const clbck_data_t *p_clbck_data);
    int SMPRNRcvStringGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int8_t string_block,
            struct rn_rcv_string *p_rcv_string,
            const clbck_data_t *p_clbck_data);
    int SMPRNXmitPortMaskGetSetByLid(u_int16_t lid,
            u_int8_t method,
            u_int8_t ports_block,
            struct rn_xmit_port_mask *p_xmit_port_mask,
            const clbck_data_t *p_clbck_data);
    int SMPARGroupTableCopySetByLid(u_int16_t lid,
            u_int16_t group_to_copy,
            bool copy_direction,
            struct adaptive_routing_group_table_copy *p_group_table_copy,
            const clbck_data_t *p_clbck_data);

    int SMPPortInfoMadGetByDirect(direct_route_t *p_direct_route,
            phys_port_t port_number,
            struct SMP_PortInfo *p_port_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPortInfoExtMadGetByDirect(direct_route_t *p_direct_route,
            phys_port_t port_number,
            struct SMP_PortInfoExtended *p_port_info_ext,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPMlnxExtPortInfoMadGetByDirect(direct_route_t *p_direct_route,
            phys_port_t port_number,
            struct SMP_MlnxExtPortInfo *p_mlnx_ext_port_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPVSGeneralInfoFwInfoMadGetByDirect(direct_route_t *p_direct_route,
                                             struct FWInfo_Block_Element *p_general_info,
                                             const clbck_data_t *p_clbck_data = NULL);
    int SMPVSGeneralInfoCapabilityMaskMadGetByDirect(direct_route_t *p_direct_route,
                                                     struct GeneralInfoCapabilityMask *p_general_info,
                                                     const clbck_data_t *p_clbck_data = NULL);
    int SMPSwitchInfoMadGetByDirect(direct_route_t *p_direct_route,
            struct SMP_SwitchInfo *p_switch_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPNodeInfoMadGetByDirect(direct_route_t *p_direct_route,
            struct SMP_NodeInfo *p_node_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPNodeDescMadGetByDirect(direct_route_t *p_direct_route,
            struct SMP_NodeDesc *p_node_desc,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPSMInfoMadGetByDirect(direct_route_t *p_direct_route,
            struct SMP_SMInfo *p_sm_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPLinearForwardingTableGetByDirect(direct_route_t *p_direct_route,
            u_int32_t lid_to_port_block_num,
            struct SMP_LinearForwardingTable *p_linear_forwarding_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPMulticastForwardingTableGetByDirect(direct_route_t *p_direct_route,
            u_int8_t port_group,
            u_int32_t lid_to_port_block_num,
            struct SMP_MulticastForwardingTable *p_multicast_forwarding_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPKeyTableGetByDirect(direct_route_t *p_direct_route,
            u_int16_t port_num,
            u_int16_t block_num,
            struct SMP_PKeyTable *p_pkey_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPGUIDInfoTableGetByDirect(direct_route_t *p_direct_route,
            u_int32_t block_num,
            struct SMP_GUIDInfo *p_guid_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPSLToVLMappingTableGetByDirect(direct_route_t *p_direct_route,
            phys_port_t out_port_number,
            phys_port_t in_port_number,
            struct SMP_SLToVLMappingTable *p_slvl_mapping,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPLFTInfoMadGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            ib_private_lft_info *p_plft_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPLFTDefMadGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int8_t plft_block,
            struct ib_private_lft_def *p_plft_def,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPLFTMapMadGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int8_t pLFTID,
            struct ib_private_lft_map *p_plft_map,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPPortSLToPrivateLFTMapGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int8_t port_block,
            struct ib_port_sl_to_private_lft_map *p_plft_map,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPARInfoGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            bool get_cap,
            struct adaptive_routing_info *p_ar_info,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPARGroupTableGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t  method,
            u_int16_t group_block,
            u_int8_t  group_table,
            u_int8_t  pLFTID,
            struct ib_ar_group_table *p_ar_group_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPARLinearForwardingTableGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int32_t lid_block,
            u_int8_t pLFTID,
            struct ib_ar_linear_forwarding_table_sx *p_ar_linear_forwarding_table,
            const clbck_data_t *p_clbck_data = NULL);
    int SMPExtendedSwitchInfoMadGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            struct ib_extended_switch_info *p_ext_sw_info,
            const clbck_data_t *p_clbck_data);

    int SMPRNSubGroupDirectionTableGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int16_t block_num,
            struct rn_sub_group_direction_tbl *p_sub_group_direction_table,
            const clbck_data_t *p_clbck_data);
    int SMPRNGenStringTableGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int8_t direction_block,
            u_int8_t pLFTID,
            struct rn_gen_string_tbl *p_gen_string_table,
            const clbck_data_t *p_clbck_data);
    int SMPRNGenBySubGroupPriorityMadGetSetByDirect(
            direct_route_t *p_direct_route,
            u_int8_t method,
            struct rn_gen_by_sub_group_prio *p_gen_by_sg_priority,
            const clbck_data_t *p_clbck_data);
    int SMPRNRcvStringGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int16_t string_block,
            struct rn_rcv_string *p_rcv_string,
            const clbck_data_t *p_clbck_data);
    int SMPRNXmitPortMaskGetSetByDirect(direct_route_t *p_direct_route,
            u_int8_t method,
            u_int8_t ports_block,
            struct rn_xmit_port_mask *p_xmit_port_mask,
            const clbck_data_t *p_clbck_data);
    int SMPARGroupTableCopySetByDirect(direct_route_t *p_direct_route,
            u_int16_t group_to_copy,
            bool copy_direction,
            struct adaptive_routing_group_table_copy *p_group_table_copy,
            const clbck_data_t *p_clbck_data);

    int SMPVirtualizationInfoMadGetByLid(u_int16_t lid,
            struct SMP_VirtualizationInfo *p_virtual_info,
            const clbck_data_t *p_clbck_data);
    int SMPVPortInfoMadGetByLid(u_int16_t lid,
            virtual_port_t vport_num,
            struct SMP_VPortInfo *p_vport_info,
            const clbck_data_t *p_clbck_data);
    int SMPVPortStateMadGetByLid(u_int16_t lid,
            u_int16_t block_num,
            struct SMP_VPortState *p_vport_state,
            const clbck_data_t *p_clbck_data);
    int SMPVNodeInfoMadGetByLid(u_int16_t lid,
            virtual_port_t vport_num,
            struct SMP_VNodeInfo *p_vnode_info,
            const clbck_data_t *p_clbck_data);
    int SMPVNodeDescriptionMadGetByLid(u_int16_t lid,
            virtual_port_t vport_num,
            struct SMP_NodeDesc *p_vnode_description,
            const clbck_data_t *p_clbck_data);
    int SMPVPortPKeyTblMadGetByLid(u_int16_t lid,
            virtual_port_t vport_num,
            u_int16_t block_num,
            struct SMP_PKeyTable *p_vport_pkey_tbl,
            const clbck_data_t *p_clbck_data);
    int SMPTempSensingDataGetByDirect(direct_route_t *p_direct_route,
            struct SMP_TempSensing *p_tempsens,
            const clbck_data_t *p_clbck_data);
    int SMPQosConfigSLGetByDirect(direct_route_t *p_direct_route,
            struct SMP_QosConfigSL *p_qos_config_sl,
            const clbck_data_t *p_clbck_data,
            phys_port_t port_num);
    int SMPRouterInfoGetByDirect(direct_route_t *p_direct_route,
            struct SMP_RouterInfo *p_router_info,
            const clbck_data_t *p_clbck_data);
    int SMPAdjRouterTableGetByDirect(direct_route_t *p_direct_route,
            u_int8_t block_num,
            struct SMP_AdjSiteLocalSubnTbl *p_router_tbl,
            const clbck_data_t *p_clbck_data);
    int SMPNextHopRouterTableGetByDirect(direct_route_t *p_direct_route,
            u_int32_t block_num,
            struct SMP_NextHopTbl *p_router_tbl,
            const clbck_data_t *p_clbck_data);

    ////////////////////
    //pm class methods
    ////////////////////
    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int PMMadGetSet(u_int16_t lid,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            void *p_pm_attribute_data,
            const pack_data_func_t pm_pack_attribute_data_func,
            const unpack_data_func_t pm_unpack_attribute_data_func,
            const dump_data_func_t pm_dump_attribute_data_func,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int PMClassPortInfoGet(u_int16_t lid,
            struct IB_ClassPortInfo *p_ib_class_port_info,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortSampleControlGet(u_int16_t lid,
        phys_port_t port_number,
        struct PM_PortSamplesControl *p_sample_control,
        const clbck_data_t *p_clbck_data);
    int PMPortCountersGet(u_int16_t lid,
            phys_port_t port_number,
            struct PM_PortCounters *p_port_counters,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortCountersSet(u_int16_t lid,
            struct PM_PortCounters *p_port_counters,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortCountersClear(u_int16_t lid,
            phys_port_t port_number,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortCountersExtendedGet(u_int16_t lid,
            phys_port_t port_number,
            struct PM_PortCountersExtended *p_port_counters,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortCountersExtendedSet(u_int16_t lid,
            struct PM_PortCountersExtended *p_port_counters,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortCountersExtendedClear(u_int16_t lid,
            phys_port_t port_number,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortExtendedSpeedsCountersGet(u_int16_t lid,
            phys_port_t port_number,
            struct PM_PortExtendedSpeedsCounters *p_port_counters,
            const clbck_data_t *p_clbck_data = NULL);
    //undefined behavior
    //int PMPortExtendedSpeedsCountersSet(u_int16_t lid,
    //    struct PM_PortExtendedSpeedsCounters *p_port_counters);
    int PMPortExtendedSpeedsCountersClear(u_int16_t lid,
            phys_port_t port_number,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortExtendedSpeedsRSFECCountersGet(u_int16_t lid,
            phys_port_t port_number,
            struct PM_PortExtendedSpeedsRSFECCounters *p_port_counters,
            const clbck_data_t *p_clbck_data = NULL);
    int PMPortExtendedSpeedsRSFECCountersClear(u_int16_t lid,
            phys_port_t port_number,
            const clbck_data_t *p_clbck_data = NULL);
   /*
    * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
    *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
    */
    int PMPerSLVLCounters(bool is_reset_cntr,
            u_int16_t lid,
            phys_port_t port_number,
            u_int32_t attr_id,
            struct PM_PortRcvXmitCntrsSlVl *p_pm_port_rcvxmit_data_slvl,
            const clbck_data_t *p_clbck_data);

    //PortRcvErrorDetails and PortXmitDiscardDetails

    int PMPortRcvErrorDetailsGet(u_int16_t lid,
                                 phys_port_t port_number,
                                 struct PM_PortRcvErrorDetails *p_pm_port_rcv_error_details,
                                 const clbck_data_t *p_clbck_data = NULL);

    int PMPortRcvErrorDetailsClear(u_int16_t lid,
                                   phys_port_t port_number,
                                   const clbck_data_t *p_clbck_data = NULL);

    int PMPortXmitDiscardDetailsGet(u_int16_t lid,
                                    phys_port_t port_number,
                                    struct PM_PortXmitDiscardDetails *p_pm_port_xmit_discard_details,
                                    const clbck_data_t *p_clbck_data = NULL);

    int PMPortXmitDiscardDetailsClear(u_int16_t lid,
                                      phys_port_t port_number,
                                      const clbck_data_t *p_clbck_data = NULL);

    ////////////////////
    //vs class methods
    ////////////////////
    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int VSMadGetSet(u_int16_t lid,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            void *p_vs_attribute_data,
            const pack_data_func_t vs_pack_attribute_data_func,
            const unpack_data_func_t vs_unpack_attribute_data_func,
            const dump_data_func_t vs_dump_attribute_data_func,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int VSGeneralInfoGet(u_int16_t lid, struct VendorSpec_GeneralInfo *p_general_info,
                         const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int VSPortLLRStatisticsGet(u_int16_t lid,
            phys_port_t port_number,
            struct VendorSpec_PortLLRStatistics *p_port_llr_statistics,
            bool get_symbol_errors,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int VSPortLLRStatisticsClear(u_int16_t lid,
        phys_port_t port_number,
        bool clear_symbol_errors,
        const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int VSPortLLRStatisticsSet(u_int16_t lid,
        phys_port_t port_number,
        struct VendorSpec_PortLLRStatistics *p_port_llr_statistics,
        bool set_symbol_errors,
        const clbck_data_t *p_clbck_data = NULL);

    int VSDiagnosticDataGet(u_int16_t lid,
        phys_port_t port_number,
        u_int8_t page_number,
        struct VS_DiagnosticData *p_dc,
        const clbck_data_t *p_clbck_data);

    int VSDiagnosticDataPageClear(u_int16_t lid,
        phys_port_t port_number,
        u_int8_t page_number,
        struct VS_DiagnosticData *p_dc,
        const clbck_data_t *p_clbck_data);

    int VSPortRNCountersClear(u_int16_t lid,
            phys_port_t port_number,
            const clbck_data_t *p_clbck_data);

    int VSPortRNCountersGet(u_int16_t lid,
            phys_port_t port_number,
            struct port_rn_counters *p_rn_counters,
            const clbck_data_t *p_clbck_data);

   /*
    * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
    *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
    */
    int VSPerVLCounters(bool is_reset_cntr,
            u_int16_t lid,
            phys_port_t port_number,
            u_int32_t attr_id,
            struct PM_PortRcvXmitCntrsSlVl *p_pm_port_rcvxmit_data_slvl,
            const clbck_data_t *p_clbck_data);
    ////////////////////
    //cc class methods
    ////////////////////
    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int CCMadGetSet(u_int16_t lid,
            u_int8_t sl,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            u_int64_t cc_key,
            void *p_cc_log_attribute_data,
            void *p_cc_mgt_attribute_data,
            const pack_data_func_t cc_pack_attribute_data_func,
            const unpack_data_func_t cc_unpack_attribute_data_func,
            const dump_data_func_t cc_dump_attribute_data_func,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int CCClassPortInfoGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct IB_ClassPortInfo *p_ib_class_port_info,
            const clbck_data_t *p_clbck_data = NULL);
    int CCClassPortInfoSet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct IB_ClassPortInfo *p_ib_class_port_info,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCongestionInfoGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_CongestionInfo *p_cc_congestion_info,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCongestionKeyInfoGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_CongestionKeyInfo *p_cc_congestion_key_info,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCongestionKeyInfoSet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_CongestionKeyInfo *p_cc_congestion_key_info,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCongestionLogSwitchGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_CongestionLogSwitch *p_cc_congestion_log_sw,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCongestionLogCAGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_CongestionLogCA *p_cc_congestion_log_ca,
            const clbck_data_t *p_clbck_data = NULL);
    int CCSwitchCongestionSettingGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_SwitchCongestionSetting *p_cc_sw_congestion_setting,
            const clbck_data_t *p_clbck_data = NULL);
    int CCSwitchCongestionSettingSet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_SwitchCongestionSetting *p_cc_sw_congestion_setting,
            const clbck_data_t *p_clbck_data = NULL);
    int CCSwitchPortCongestionSettingGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            u_int8_t block_idx,
            struct CC_SwitchPortCongestionSetting *p_cc_sw_port_congestion_setting,
            const clbck_data_t *p_clbck_data = NULL);
    int CCSwitchPortCongestionSettingSet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            u_int8_t block_idx,
            struct CC_SwitchPortCongestionSetting *p_cc_sw_port_congestion_setting,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCACongestionSettingGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_CACongestionSetting *p_cc_ca_congestion_setting,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCACongestionSettingSet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_CACongestionSetting *p_cc_ca_congestion_setting,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCongestionControlTableGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            u_int8_t block_idx,
            struct CC_CongestionControlTable *p_cc_congestion_control_table,
            const clbck_data_t *p_clbck_data = NULL);
    int CCCongestionControlTableSet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            u_int8_t block_idx,
            struct CC_CongestionControlTable *p_cc_congestion_control_table,
            const clbck_data_t *p_clbck_data = NULL);
    int CCTimeStampGet(u_int16_t lid,
            u_int8_t sl,
            u_int64_t cc_key,
            struct CC_TimeStamp *p_cc_time_stamp,
            const clbck_data_t *p_clbck_data = NULL);

    ////////////////////
    //AM class methods
    ////////////////////
    /*
     * Returns: mad status[bits: 0-15] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMMadGetSet(u_int16_t lid,
            u_int8_t sl,
            u_int8_t method,
            u_int16_t attribute_id,
            u_int32_t attribute_modifier,
            u_int64_t am_key,
            u_int8_t class_version,
            void *p_am_attribute_data,
            const pack_data_func_t am_pack_attribute_data_func,
            const unpack_data_func_t am_unpack_attribute_data_func,
            const dump_data_func_t am_dump_attribute_data_func,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMClassPortInfoGet(u_int16_t lid,
            u_int8_t sl,
            struct IB_ClassPortInfo *p_ib_class_port_info,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMClassPortInfoSet(u_int16_t lid,
            u_int8_t sl,
            struct IB_ClassPortInfo *p_ib_class_port_info,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMANInfoGet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_ANInfo *p_an_info,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMANInfoSet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_ANInfo *p_an_info,
            const clbck_data_t *p_clbck_data = NULL);
    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMResourceCleanupSet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_ResourceCleanup_V2 *p_resource_cleanup,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMResourceCleanupSet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_ResourceCleanup *p_resource_cleanup,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMQPAllocationSet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_QPAllocation *p_qp_allocation,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMQPCConfigSet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_QPCConfig *p_qpc_config,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMQPCConfigGet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_QPCConfig *p_qpc_config,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMTreeConfigSet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_TreeConfig *p_tree_config,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMPerformanceCountersGet(u_int16_t lid,
        uint8_t sl,
        uint64_t am_key,
        uint8_t class_version,
        struct AM_PerformanceCounters *p_perf_cntr,
        const clbck_data_t *p_clbck_data);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMPerformanceCountersSet(u_int16_t lid,
        uint8_t sl,
        uint64_t am_key,
        uint8_t class_version,
        struct AM_PerformanceCounters *p_perf_cntr,
        const clbck_data_t *p_clbck_data);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMTreeConfigGet(u_int16_t lid,
        uint8_t sl,
        uint64_t am_key,
        uint8_t class_version,
        struct AM_TreeConfig *p_tree_config,
        const clbck_data_t *p_clbck_data);

    /*
     * Returns: mad status[bits: 0-7] / IBIS_MAD_STATUS_SEND_FAILED / IBIS_MAD_STATUS_RECV_FAILED /
     *  IBIS_MAD_STATUS_TIMEOUT / IBIS_MAD_STATUS_GENERAL_ERR
     */
    int AMQuotaConfigSet(u_int16_t lid,
            uint8_t sl,
            uint64_t am_key,
            uint8_t class_version,
            struct AM_QuotaConfig *p_tree_config,
            const clbck_data_t *p_clbck_data = NULL);

    /*
     * Register AM traps handler
     * Returns: 0 - success / 1 - error
     */
    int RegisterAmTrapsHandler(mad_handler_callback_func_t callback_func,
                               void *context);

    /*
     * Send TrapRepress for AM trap
     */
    int RepressAmTrap(ib_address_t *p_ib_address,
                      MAD_AggregationManagement *p_am_mad,
                      Notice *p_notice);

    ////////////////////
    //mellanox methods
    ////////////////////
    bool IsVenMellanox(u_int32_t vendor_id);
    //switch
    bool IsDevAnafa(u_int16_t dev_id);
    bool IsDevPelican(u_int16_t dev_id);
    bool IsDevShaldag(u_int16_t dev_id);
    bool IsDevSwitchXIB(u_int16_t dev_id);
    void GetSwitchXIBDevIds(device_id_list_t& mlnx_dev_ids_list,
                            device_id_list_t& bull_dev_ids_list);
    void GetAnafaDevIds(device_id_list_t& dev_ids_list);
    void GetShaldagDevIds(device_id_list_t& mlnx_dev_ids_list,
                          device_id_list_t& volt_dev_ids_list);
    //bridge
    bool IsDevBridgeXIB(u_int16_t dev_id);
    void GetBridgeXIBDevIds(device_id_list_t& dev_ids_list);
    //hca
    bool IsDevTavor(u_int16_t dev_id);
    bool IsDevSinai(u_int16_t dev_id);
    bool IsDevArbel(u_int16_t dev_id);
    bool IsDevConnectX_1IB(u_int16_t dev_id);
    bool IsDevConnectX_2IB(u_int16_t dev_id);
    bool IsDevConnectX_3IB(u_int16_t dev_id);
    bool IsDevConnectXIB(u_int16_t dev_id);
    bool IsDevGolan(u_int16_t dev_id);
    void GetConnectX_3IBDevIds(device_id_list_t& mlnx_dev_ids_list,
                               device_id_list_t& bull_dev_ids_list);
    void GetGolanDevIds(device_id_list_t& dev_ids_list);
    void GetTavorDevIds(device_id_list_t& dev_ids_list);
    void GetSinaiDevIds(device_id_list_t& dev_ids_list);
    void GetArbelDevIds(device_id_list_t& dev_ids_list);
    void GetConnectXDevIds(device_id_list_t& dev_ids_list);
    void GetConnectX_2DevIds(device_id_list_t& dev_ids_list);
    void GetConnectX_2_ENtDevIds(device_id_list_t& dev_ids_list);
    void GetConnectX_2_LxDevIds(device_id_list_t& dev_ids_list);
};

#endif	/* IBIS_H_ */

