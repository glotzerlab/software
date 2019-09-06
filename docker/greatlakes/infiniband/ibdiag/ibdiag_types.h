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


#ifndef IBDIAG_TYPES_H_
#define IBDIAG_TYPES_H_

#include <stdlib.h>
#include <vector>
#include <list>
#include <map>

#include <infiniband/ibdm/Fabric.h>
#include <ibis/ibis_types.h>
#include <ibis/packets/packets_layouts.h>
#include <misc/tool_trace/tool_trace.h>


/****************************************************/
/* new types */
typedef struct progress_bar_nodes {
    u_int32_t nodes_found;
    u_int32_t sw_found;
    u_int32_t ca_found;
} progress_bar_nodes_t;
typedef void (*progress_func_discovered_t)(progress_bar_nodes_t *p_progress_discovered);
typedef void (*progress_func_nodes_t)(progress_bar_nodes_t *p_progress, progress_bar_nodes_t *p_target_result);

typedef struct progress_bar_ports {
    u_int64_t ports_found;
} progress_bar_ports_t;
typedef void (*progress_func_ports_t)(progress_bar_ports_t *p_progress, progress_bar_ports_t *p_target_result);
typedef void (*progress_func_ports_add_msg_t)(progress_bar_ports_t *, progress_bar_ports_t *,
                                              char const*);

typedef struct sm_info_obj {
    struct SMP_SMInfo smp_sm_info;
    IBPort *p_port;
} sm_info_obj_t;

// struct that holds different calculated counters based on pm counters
struct PM_PortCalcCounters {
    u_int64_t RetransmissionPerSec;
};

typedef struct vs_mlnx_cntrs_obj {
    struct VS_DiagnosticData *p_mlnx_cntrs_p0;
    struct VS_DiagnosticData *p_mlnx_cntrs_p1;
    struct VS_DiagnosticData *p_mlnx_cntrs_p255;
} vs_mlnx_cntrs_obj_t;

typedef struct index_line {
    string name;
    size_t offset;
    size_t size;
    size_t line;
    size_t rows;
} index_line_t;

typedef struct pm_info_obj {
    struct PM_PortCounters *p_port_counters;
    struct PM_PortCountersExtended *p_extended_port_counters;
    struct PM_PortExtendedSpeedsCounters *p_port_ext_speeds_counters;
    struct PM_PortExtendedSpeedsRSFECCounters *p_port_ext_speeds_rsfec_counters;
    struct VendorSpec_PortLLRStatistics *p_port_llr_statistics; //May need to move to vs_info_obj
    struct PM_PortCalcCounters *p_port_calc_counters;
    struct PM_PortRcvErrorDetails *p_port_rcv_error_details;
    struct PM_PortXmitDiscardDetails *p_port_xmit_discard_details;
} pm_info_obj_t;

typedef struct fw_version_obj {
    u_int32_t major;
    u_int32_t minor;
    u_int32_t sub_minor;

    fw_version_obj& operator=(const struct VendorSpec_GeneralInfo& other) {
        //extended fields != 0, then take them
        if (other.FWInfo.Extended_Major ||
            other.FWInfo.Extended_Minor ||
            other.FWInfo.Extended_SubMinor) {
            major = other.FWInfo.Extended_Major;
            minor = other.FWInfo.Extended_Minor;
            sub_minor = other.FWInfo.Extended_SubMinor;
        } else {
            major = other.FWInfo.Major;
            minor = other.FWInfo.Minor;
            sub_minor = other.FWInfo.SubMinor;
        }
        return *this;
    }
    int set(const char* fw_str) {
        if (!fw_str)
            return 1;
        unsigned int n = sscanf(fw_str, "%u.%u.%u", &major, &minor, &sub_minor);
        if (n == 3)
            return 0;
        return 1;
    }
    bool operator==(const struct fw_version_obj& other) const {
        return (major == other.major && minor == other.minor && sub_minor == other.sub_minor);
    }
    bool operator!=(const struct fw_version_obj& other) {
        return (!(*this == other));
    }
    bool operator>(const struct fw_version_obj& other) const {
        u_int32_t x[3] = {major, minor, sub_minor};
        const u_int32_t y[3] = {other.major, other.minor, other.sub_minor};
        for (int i = 0; i < 3; i++) {
            if (x[i] > y[i])
                return true;
            if (x[i] < y[i])
                return false;
        }
        return false;
    }
    bool operator<(const struct fw_version_obj& other) const {
        return (!((*this > other) || (*this == other)));
    }
} fw_version_obj_t;

struct GreaterFwVerObjComparer{
    bool operator()(fw_version_obj_t const& x, fw_version_obj_t const& y) const{
        return x > y;
    }
};

// reasons for bad direct route
typedef enum {
    IBDIAG_BAD_DR_NONE = 0,
    IBDIAG_BAD_DR_NODE_FIRST,
    IBDIAG_BAD_DR_NODE_NODE_INFO = IBDIAG_BAD_DR_NODE_FIRST,
    IBDIAG_BAD_DR_NODE_DUPLICATE_CHECK,
    IBDIAG_BAD_DR_NODE_NODE_DESCRIPTION,
    IBDIAG_BAD_DR_NODE_INCONSISTENT, //data db inconsistency, no mem
    IBDIAG_BAD_DR_NODE_BAD_NODE_INFO, //received bad node info data
    IBDIAG_BAD_DR_NODE_LAST = IBDIAG_BAD_DR_NODE_BAD_NODE_INFO,
    IBDIAG_BAD_DR_PORT_FIRST,
    IBDIAG_BAD_DR_PORT_PORT_INFO = IBDIAG_BAD_DR_PORT_FIRST,
    IBDIAG_BAD_DR_PORT_INVALID_LID,
    IBDIAG_BAD_DR_PORT_INCONSISTENT,
    IBDIAG_BAD_DR_PORT_LAST = IBDIAG_BAD_DR_PORT_INCONSISTENT,
    IBDIAG_BAD_DR_MAX
} IbdiagBadDirectRouteReason_t;

extern const char* bad_direct_route_reasons [IBDIAG_BAD_DR_MAX];

// struct for more info on bad direct route
typedef struct IbdiagBadDirectRoute {
    direct_route_t              *direct_route;
    // more details on why it's bad
    IbdiagBadDirectRouteReason_t reason;
    int                          port_num;
    string                       message;
    void clear(void) {
        direct_route = NULL;
        reason = IBDIAG_BAD_DR_NONE;
        port_num = 0;
        message = "";
    }
} IbdiagBadDirectRoute_t;

#define NUM_CAPABILITY_FIELDS 4
//mask consists number of indexes. each filed size in bits
#define CAPABILITY_MASK_FIELD_SIZE (sizeof(u_int32_t)*8)

typedef struct capability_mask {
    u_int32_t mask[NUM_CAPABILITY_FIELDS];

    void clear() { memset(mask, 0, sizeof(mask)); }
    capability_mask() { clear(); }

    capability_mask& operator=(const struct GeneralInfoCapabilityMask& other) {
        mask[0] = other.capability0;
        mask[1] = other.capability1;
        mask[2] = other.capability2;
        mask[3] = other.capability3;
        return *this;
    }
    //bit is a number between 0 and 127
    //to set bit k in mask[w] -> bit=w*32+k
    int set(u_int8_t bit);
    void ntoh();
    void hton();
    friend std::ostream& operator<< (std::ostream& stream,
                                     const struct capability_mask& mask);
} capability_mask_t;

typedef struct query_or_mask {
    bool to_query; //if this true, then the 'mask' is irrelevant
    capability_mask_t mask;
    friend std::ostream& operator<< (std::ostream& stream,
                                     const struct query_or_mask& qmask);
} query_or_mask_t;

typedef struct prefix_guid_data {
    u_int64_t        original_guid;
    query_or_mask_t  qmask;
    prefix_guid_data() { original_guid = 0; qmask.to_query = false; }
    friend std::ostream& operator<< (std::ostream& stream,
                                     const struct prefix_guid_data& guid_data);
} prefix_guid_data_t;

typedef vector < IBNode * >                                     vector_p_node;
typedef vector < IBPort * >                                     vector_p_port;
typedef vector < IBVPort * >                                    vector_p_vport;
typedef vector < IBVNode * >                                    vector_p_vnode;
typedef vector < struct SMP_NodeInfo * >                        vector_p_smp_node_info;
typedef vector < struct SMP_SwitchInfo * >                      vector_p_smp_switch_info;
typedef vector < struct SMP_PortInfo * >                        vector_p_smp_port_info;
typedef vector < struct SMP_PortInfoExtended * >                vector_p_smp_port_info_ext;
typedef vector < struct SMP_MlnxExtPortInfo * >                 vector_p_smp_mlnx_ext_port_info;
typedef vector < struct VendorSpec_GeneralInfo * >              vector_p_vs_general_info;
typedef vector < u_int16_t * >                                  vector_p_pm_cap_mask;
typedef vector < pm_info_obj_t * >                              vector_p_pm_info_obj;
typedef vector < struct PortSampleControlOptionMask * >         vector_p_pm_option_mask;
typedef vector < vs_mlnx_cntrs_obj_t * >                        vector_p_vs_mlnx_cntrs_obj;
typedef vector < struct SMP_VirtualizationInfo * >              vector_p_smp_virtual_info;
typedef vector < struct SMP_VPortInfo * >                       vector_p_smp_vport_info;
typedef vector < struct SMP_VNodeInfo * >                       vector_p_smp_vnode_info;
typedef vector < struct SMP_TempSensing * >                     vector_p_smp_temp_sensing;
typedef vector < struct SMP_QosConfigSL * >                     vector_p_smp_qos_config_sl;
typedef vector < struct SMP_RouterInfo * >                      vector_p_smp_router_info;
typedef vector < struct SMP_AdjSiteLocalSubnTbl * >             vector_p_smp_adj_router_tbl;
typedef vector < vector_p_smp_adj_router_tbl >                  vector_v_smp_adj_router_tbl;
typedef vector < struct SMP_NextHopTbl * >                      vector_p_smp_next_hop_router_tbl;
typedef vector < vector_p_smp_next_hop_router_tbl >             vector_v_smp_next_hop_router_tbl;
typedef list < IBNode * >                                       list_p_node;
typedef list < IBPort * >                                       list_p_port;
typedef list < sm_info_obj_t * >                                list_p_sm_info_obj;
typedef list < direct_route_t  * >                              list_p_direct_route;
typedef list < IbdiagBadDirectRoute * >                         list_p_bad_direct_route;
typedef list < string >                                         list_string;
typedef list < u_int8_t >                                       list_uint8;
typedef list < index_line_t >                                   list_index_line;
typedef map < u_int64_t, list_p_direct_route >                  map_guid_list_p_direct_route;
typedef map < u_int16_t, list_p_port >                          map_lid_list_p_port;
typedef map < string,  u_int64_t >                              map_str_uint64;
typedef map < u_int8_t,  u_int64_t >                            map_uint8_uint64;
typedef vector < struct SMP_VPortState * >                      vector_p_smp_vport_state;
typedef vector < vector_p_smp_vport_state >                     vector_v_smp_vport_state;
typedef vector < struct SMP_PKeyTable * >                       vector_p_smp_pkey_tbl;
typedef vector < vector_p_smp_pkey_tbl >                        vector_v_smp_pkey_tbl;
typedef vector < struct SMP_GUIDInfo * >                        vector_p_smp_guid_tbl;
typedef vector < vector_p_smp_guid_tbl >                        vector_v_smp_guid_tbl;
typedef vector < u_int64_t >                                    vec_guids;
typedef map<u_int64_t, fw_version_obj_t>                        map_uint64_fw_version_obj_t;
typedef map<u_int64_t, capability_mask_t>                       map_uint64_capability_mask_t;
typedef pair<uint32_t, device_id_t>                             pair_uint32_device_id_t;
typedef pair<device_id_t, string>                               pair_device_id_t_string;
typedef map<pair_uint32_device_id_t, capability_mask_t>         map_ven_dev_to_capability_mask_t;
typedef map<pair_device_id_t_string, struct VendorSpec_GeneralInfo * >     map_devid_psid_to_fw_version_obj_t;
typedef map<fw_version_obj_t, query_or_mask_t, GreaterFwVerObjComparer>    map_fw_to_query_or_mask_t;
typedef map<pair_uint32_device_id_t, map_fw_to_query_or_mask_t> map_ven_id_dev_id_2_fw_data_t;
typedef map<u_int64_t, prefix_guid_data_t>                      map_guid_to_prefix_data_t;
typedef map<u_int8_t, map_guid_to_prefix_data_t>                map_prefix_2_guids_data_t;

typedef vector < class CountersPerSLVL * >                      vec_slvl_cntrs;

typedef pair< IBPort *, struct PM_PortRcvXmitCntrsSlVl >             pair_ibport_slvl_cntr_data_t;
typedef set < pair_ibport_slvl_cntr_data_t, struct slvl_data_sort >  set_port_data_update_t;

//SMP Capability Mask bits
//note: when adding new values, update the 'first' and the 'last'
typedef enum {
    EnSMPCapIsPrivateLinearForwardingSupported = 0,    //0
    EnSMPCapFirst = EnSMPCapIsPrivateLinearForwardingSupported,
    EnSMPCapIsAdaptiveRoutingSupported,                //1
    EnSMPCapIsAdaptiveRoutingRev1Supported,            //2
    EnSMPCapIsRemotePortMirroringSupported,            //3
    EnSMPCapIsTemperatureSensingSupported,             //4
    EnSMPCapIsConfigSpaceAccessSupported,              //5
    EnSMPCapIsCableInfoSupported,                      //6
    EnSMPCapIsSMPEyeOpenSupported,                     //7
    EnSMPCapIsLossyVLConfigSupported,                  //8
    EnSMPCapIsExtendedPortInfoSupported,               //9
    EnSMPCapIsAccessRegisterSupported,                 //10
    EnSMPCapIsInterProcessCommunicationSupported,      //11
    EnSMPCapIsPortSLToPrivateLFTMapSupported,          //12
    EnSMPCapIsExtendedSwitchInfoSupported,             //13
    EnSMPCapIsASlaveVirtualSwitch,                     //14
    EnSMPCapIsVirtualizationSupported,                 //15
    EnSMPCapIsAdvancedRetransAndFECModesSupported,     //16
    EnSMPCapIsSemaphoreLockSupported,                  //17
    EnSMPCapIsSHArPAggrNodeSupported,                  //18
    EnSMPCapIsCableInfoPasswordSupported,              //19
    EnSMPCapIsVL2VLPerSWIDSupported,                   //20
    EnSMPCapIsSpecialPortsMarkingSupported,            //21
    EnSMPCapIsVPortGUIDInfoSupported,                  //22
    EnSMPCapIsForcePLFTSubgroup0Supported,             //23
    EnSMPCapIsQoSConfigSLRateLimitSupported,           //24
    EnSMPCapIsQoSConfigSLVPortRateLimitSupported,      //25
    EnSMPCapIsQoSConfigSLAllocBWSupported,             //26
    EnSMPCapIsQoSConfigSLVPortAllocBWSupported,        //27
    EnSMPCapLast = EnSMPCapIsQoSConfigSLVPortAllocBWSupported
} EnSMPCapabilityMaskBit_t;

//GMP Capability Mask bits
//note: when adding new values, update the 'first' and the 'last'
typedef enum {
    EnGMPCapIsPortPowerStateSupported = 0,
    EnGMPCapFirst = EnGMPCapIsPortPowerStateSupported,
    EnGMPCapIsDeviceSoftResetSupported,                //1
    EnGMPCapIsExtPortAccessSupported,                  //2
    EnGMPCapIsPhyConfigSupported,                      //3
    EnGMPCapIsVendSpecLedControlSupported,             //4
    EnGMPCapIsConfigSpaceAccessSupported,              //5
    EnGMPCapIsPerVLCountersSupported,                  //6
    EnGMPCapIsPerVLExtendedSupported,                  //7
    EnGMPCapIsPortLLRStatisticsSupported,              //8
    EnGMPCapIsCounterGroupsSupported,                  //9
    EnGMPCapIsEnhancedConfigSpaceAccessSupported,      //10
    EnGMPCapIsFlowMonitoringSupported,                 //11
    EnGMPCapIsCongestionNotificationSupported,         //12
    EnGMPCapIsVirtualSwitchSupported,                  //13
    EnGMPCapIsPortXmitQLengthSupported,                //14
    EnGMPCapIsMulticastForwardingTableSupported,       //15
    EnGMPCapIsPortXmitWaitVLExtendedSupported,         //16
    EnGMPCapIsExtI2CPortAccessSupported,               //17
    EnGMPCapIsDiagnosticDataSupported,                 //18
    EnGMPCapIsMaxRetransmissionRateSupported,          //19
    EnGMPCapIsAccessRegisterSupported,                 //20
    EnGMPCapLast = EnGMPCapIsAccessRegisterSupported
} EnGMPCapabilityMaskBit_t;

typedef enum {
    EnSPCapSL2VL_VL2VL_Capability,
    EnSPCapAR_supported,
    EnSPCapIsPerVLCountersSupported,
    EnSPCapCC_supported,
    EnSPCapIsPerVLExtendedSupported,
    EnSPCapIsPortXmitWaitVLExtendedSupported,
    EnSPCapIsDiagnosticDataSupported
} EnSpecialPortsCapabilityMaskBit_t;

class CapabilityModule;
class Ibis;

class CapabilityMaskConfig {
    friend class CapabilityModule;
protected:
    u_int8_t                         m_mask_first_bit; //first bit number
    u_int8_t                         m_mask_last_bit; //last bit number

    //devices that don't support the capability mask mad
    map_ven_dev_to_capability_mask_t m_unsupported_mad_devices;
    //devices that have different mask per fw
    map_ven_id_dev_id_2_fw_data_t    m_fw_devices;
    //guids with prefixes to query or mask map
    map_prefix_2_guids_data_t        m_prefix_guids_2_mask;

    ////////////////////////////////////////
    //auxiliary data
    ////////////////////////////////////////

    //node guid to fw map
    map_uint64_fw_version_obj_t      m_guid_2_fw;
    //node guid to capability mask. guids that we already checked, and cached their mask
    map_uint64_capability_mask_t     m_guid_2_mask;

    string                           m_what_mask;
    string                           m_section_header;
    string                           m_section_footer;
    string                           m_unsupported_mad_devs_header;
    string                           m_fw_devs_header;
    string                           m_prefix_guids_2_mask_header;
public:
    CapabilityMaskConfig(u_int8_t mask_first_bit, u_int8_t mask_last_bit):
        m_mask_first_bit(mask_first_bit), m_mask_last_bit(mask_last_bit) {};
    virtual ~CapabilityMaskConfig() {};

    virtual int Init(Ibis* ibis_obj);
    //Init mask for SwitchX, ConnectX3, Golan.
    //These devices have old fw that doesn't support capability mask,
    //so store the mask for them, that tells what capabilities are supported
    virtual void InitMask(capability_mask_t &mask) = 0;

    //Init FW version, from which connectX3 supports capability mask
    virtual void InitFWConnectX3(fw_version_obj_t &fw) = 0;
    //Init FW version, from which connectIB supports capability mask
    virtual void InitFWConnectIB(fw_version_obj_t &fw) = 0;

    int AddFw(u_int64_t guid, fw_version_obj_t &fw);
    int GetFw(u_int64_t guid, fw_version_obj_t &fw);
    int AddCapabilityMask(u_int64_t guid, capability_mask_t &mask);
    void AddFwDevice(u_int32_t ven_id, device_id_t dev_id,
                     fw_version_obj_t &fw, query_or_mask_t &query_or_mask);
    void RemoveFwDevice(u_int32_t ven_id, device_id_t dev_id);
    int GetFwConfiguredMask(uint32_t ven_id, device_id_t dev_id,
                            fw_version_obj_t &fw, capability_mask_t &mask,
                            bool *is_only_fw = NULL);
    void AddUnsupportMadDevice(u_int32_t ven_id, device_id_t dev_id,
                               capability_mask_t &mask);
    void RemoveUnsupportMadDevice(u_int32_t ven_id, device_id_t dev_id);
    int AddPrefixGuid(u_int8_t prefix_len, u_int64_t guid,
                      query_or_mask_t &qmask, string &output);

    bool IsUnsupportedMadDevice(uint32_t ven_id, device_id_t dev_id,
                                capability_mask_t &mask);

    bool IsMaskKnown(u_int64_t guid);

    bool IsSupportedCapability(IBNode *node, u_int8_t cap_bit);
    bool IsLongestPrefixMatch(u_int64_t guid, u_int8_t &prefix_len,
                              u_int64_t &matched_guid, query_or_mask &qmask);
    int DumpCapabilityMaskFile(ofstream& sout);

    int DumpGuid2Mask(ofstream& sout, IBFabric *p_discovered_fabric);

    int GetCapability(IBNode *node, capability_mask_t& mask);
};

class SmpMask: public CapabilityMaskConfig {
    friend class CapabilityModule;
public:
    SmpMask();
    virtual ~SmpMask() {}
    virtual void InitMask(capability_mask_t &mask);
    //Init FW version, from which connectX3 supports SMP capability mask
    virtual void InitFWConnectX3(fw_version_obj_t &fw);
    //Init FW version, from which connectIB supports SMP capability mask
    virtual void InitFWConnectIB(fw_version_obj_t &fw);
    virtual int Init(Ibis* ibis_obj);
};

class GmpMask: public CapabilityMaskConfig {
    friend class CapabilityModule;
public:
    GmpMask();
    virtual ~GmpMask() {}
    virtual void InitMask(capability_mask_t &mask);
    //Init FW version, from which connectX3 supports GMP capability mask
    virtual void InitFWConnectX3(fw_version_obj_t &fw);
    //Init FW version, from which connectIB supports GMP capability mask
    virtual void InitFWConnectIB(fw_version_obj_t &fw);
    virtual int Init(Ibis* ibis_obj);
};

class CapabilityModule {
    SmpMask smp_mask;
    GmpMask gmp_mask;
public:
    CapabilityModule() {}
    ~CapabilityModule() {}
    int Init(Ibis *ibis_obj);

    int DumpCapabilityMaskFile(const char *file_name);
    //for debug purposes
    int DumpGuid2Mask(const char *file_name, IBFabric *p_discovered_fabric);
    int ParseCapabilityMaskFile(const char *file_name);

    int AddSMPFw(u_int64_t guid, fw_version_obj_t &fw);
    int GetSMPFw(u_int64_t guid, fw_version_obj_t &fw);
    int AddSMPCapabilityMask(u_int64_t guid, capability_mask_t &mask);
    void AddSMPFwDevice(u_int32_t ven_id, device_id_t dev_id, fw_version_obj_t &fw, query_or_mask_t &query_or_mask);

    bool IsSMPUnsupportedMadDevice(uint32_t ven_id, device_id_t dev_id,
                                   capability_mask_t &mask);
    bool IsSMPMaskKnown(u_int64_t guid);
    bool IsSupportedSMPCapability(IBNode *node, u_int8_t cap_bit);

    bool IsLongestSMPPrefixMatch(u_int64_t guid, u_int8_t &prefix_len,
                                 u_int64_t &matched_guid,
                                 query_or_mask &qmask);
    int  GetSMPFwConfiguredMask(uint32_t ven_id, device_id_t dev_id,
                                fw_version_obj_t &fw, capability_mask_t &mask,
                                bool *is_only_fw = NULL);

    int AddGMPFw(u_int64_t guid, fw_version_obj_t &fw);
    int GetGMPFw(u_int64_t guid, fw_version_obj_t &fw);
    int AddGMPCapabilityMask(u_int64_t guid, capability_mask_t &mask);
    bool IsGMPUnsupportedMadDevice(uint32_t ven_id, device_id_t dev_id,
                                   capability_mask_t &mask);
    bool IsGMPMaskKnown(u_int64_t guid);
    bool IsLongestGMPPrefixMatch(u_int64_t guid, u_int8_t &prefix_len,
                                 u_int64_t &matched_guid,
                                 query_or_mask &qmask);
    int GetGMPFwConfiguredMask(uint32_t ven_id, device_id_t dev_id,
                               fw_version_obj_t &fw, capability_mask_t &mask,
                               bool *is_only_fw = NULL);
    bool IsSupportedGMPCapability(IBNode *node, u_int8_t cap_bit);

    int GetFw(u_int64_t guid, fw_version_obj_t &fw);

    int GetCapability(IBNode *node, bool is_gmp, capability_mask_t& mask);
};

/****************************************************/
/* sections defines */
#define SECTION_NODES                "NODES"
#define SECTION_PORTS                "PORTS"
#define SECTION_SWITCHES             "SWITCHES"
#define SECTION_FEC_MODE             "FEC_MODE"
#define SECTION_LINKS                "LINKS"
#define SECTION_PM_INFO              "PM_INFO"
#define SECTION_SM_INFO              "SM_INFO"
#define SECTION_NODES_INFO           "NODES_INFO"
#define SECTION_AGUID                "AGUID"
#define SECTION_PKEY                 "PKEY"
#define SECTION_MLNX_CNTRS_INFO      "MLNX_CNTRS_INFO"
#define SECTION_VNODES               "VNODES"
#define SECTION_VPORTS               "VPORTS"
#define SECTION_QOS_CONFIG_SL        "QOS_CONFIG_SL"
#define SECTION_TEMP_SENSING         "TEMP_SENSING"
#define SECTION_BER_TEST             "BER_TEST"
#define SECTION_PHY_TEST             "PHY_TEST"
#define SECTION_ROUTERS_INFO         "ROUTERS_INFO"
#define SECTION_ROUTERS_ADJ_TBL      "ROUTERS_ADJ_SITE_LOCAL_SUBNETS_TABLE"
#define SECTION_ROUTERS_NEXT_HOP_TBL "ROUTERS_NEXT_HOP_TABLE"

/****************************************************/
/* defines */

/*
 * As the ttlog buffer size is 4096 and if 'ibdiag.last_error' buffer will
 * be copied to ttlog buffer it will cause to overflow.
 * So the last_IBDIAG_ERR_SIZE should be less than the ttlog buffer because
 * the ttlog function add to the last_error buffer some overhead of info of
 * the function/error_level and then copy it to the ttlog buffer.
 * */
#define IBDIAG_ERR_SIZE                             3840            /* 3840 bytes */


#define IBDIAG_MAX_HOPS                             64              /* maximum hops for discovery BFS */
#define IBDIAG_MAX_SUPPORTED_NODE_PORTS             254             /* for lft and mft retrieve */
#define IBDIAG_BER_THRESHOLD_OPPOSITE_VAL           0xe8d4a51000    /* 10^12 */

enum OVERFLOW_VALUES {
    OVERFLOW_VAL_NONE   = 0x0,
    OVERFLOW_VAL_4_BIT  = 0xf,
    OVERFLOW_VAL_8_BIT  = 0xff,
    OVERFLOW_VAL_16_BIT = 0xffff,
    OVERFLOW_VAL_32_BIT = 0xffffffff,
    OVERFLOW_VAL_64_BIT = 0xffffffffffffffffULL
};

enum IBDIAG_RETURN_CODES {
    IBDIAG_SUCCESS_CODE = 0x0,
    IBDIAG_ERR_CODE_FABRIC_ERROR = 0x1,
    IBDIAG_ERR_CODE_NO_MEM = 0x3,
    IBDIAG_ERR_CODE_DB_ERR = 0x4,
    IBDIAG_ERR_CODE_IBDM_ERR = 0x5,
    IBDIAG_ERR_CODE_INIT_FAILED = 0x6,
    IBDIAG_ERR_CODE_NOT_READY = 0x7,
    IBDIAG_ERR_CODE_IO_ERR = 0x8,
    IBDIAG_ERR_CODE_CHECK_FAILED = 0x9,
    IBDIAG_ERR_CODE_PARSE_FILE_FAILED = 0xA,
    IBDIAG_ERR_CODE_EXCEEDS_MAX_HOPS = 0x10,
    IBDIAG_ERR_CODE_DUPLICATED_GUID = 0x11,
    IBDIAG_ERR_CODE_INCORRECT_ARGS = 0x12,
    IBDIAG_ERR_CODE_DISCOVERY_NOT_SUCCESS = 0x13,
    IBDIAG_ERR_CODE_TRY_TO_DISCONNECT_CONNECTED_PORT = 0x14,
    IBDIAG_ERR_CODE_ILLEGAL_FUNCTION_CALL = 0x15,
    IBDIAG_ERR_CODE_LAST
};

#define PATH_INFO_PREFIX_SEFIX "-I- --------------------------------------"\
                               "--------\n"
#define  TRAVERSE_SRC_TO_DEST PATH_INFO_PREFIX_SEFIX  \
    "-I- Traversing the path from source to destination\n" \
    PATH_INFO_PREFIX_SEFIX

#define  TRAVERSE_LOCAL_TO_SRC PATH_INFO_PREFIX_SEFIX \
    "-I- Traversing the path from local to source\n"   \
        PATH_INFO_PREFIX_SEFIX

/****************************************************/
/* general defines */
#ifndef CLEAR_STRUCT
    #define CLEAR_STRUCT(n) memset(&(n), 0, sizeof(n))
#endif
#define OFFSET_OF(type, field) ((unsigned long) &(((type *) 0)->field))

#ifndef IN
    #define IN
#endif
#ifndef OUT
    #define OUT
#endif
#ifndef INOUT
    #define INOUT
#endif


/****************************************************/
/* log Macros */
#ifdef DEBUG
    #define IBDIAG_LOG(level, fmt, ...) TT_LOG(TT_LOG_MODULE_IBDIAG, level, fmt, ## __VA_ARGS__);
    #define IBDIAG_ENTER TT_ENTER( TT_LOG_MODULE_IBDIAG );
    #define IBDIAG_RETURN(rc) { TT_EXIT( TT_LOG_MODULE_IBDIAG );  \
                                return (rc); }
    #define IBDIAG_RETURN_VOID { TT_EXIT( TT_LOG_MODULE_IBDIAG );   \
                                    return; }
#else           /*def DEBUG */
    #define IBDIAG_LOG(level, fmt, ...)
    #define IBDIAG_ENTER
    #define IBDIAG_RETURN(rc) return (rc);
    #define IBDIAG_RETURN_VOID return;
#endif          /*def DEBUG */

#ifndef WIN32
    #define IBDIAG_LOG_NAME "/tmp/ibutils2_ibdiag.log"
#else
    #define IBDIAG_LOG_NAME "\\tmp\\ibutils2_ibdiag.log"
#endif      /* ndef WIN32 */

#endif          /* not defined IBDIAG_TYPES_H_ */
