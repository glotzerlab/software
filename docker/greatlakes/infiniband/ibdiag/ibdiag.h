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


#ifndef IBDIAG_H
#define IBDIAG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string>
#include <list>
#include <map>
using namespace std;

#include <infiniband/ibdm/Fabric.h>
#include <ibis/ibis.h>

#include "ibdiag_ibdm_extended_info.h"
#include "ibdiag_fabric_errs.h"
#include "ibdiag_types.h"
#include "ibdiag_csv_out.h"
#include "ibdiag_fabric.h"

#define CHECK_EXT_SPEEDS_COUNTERS        0x01
#define CHECK_EXT_SPEEDS_COUNTERS_ON_HCA 0x02
#define PRINT_LLR_COUNTERS               0x04

#define VS_MLNX_CNTRS_PAGE0        0
#define VS_MLNX_CNTRS_PAGE1        1
#define VS_MLNX_CNTRS_PAGE255      255

#define PAGE255_NUM_FIELDS 17

#define PAGE0_LATEST_VER 2
#define PAGE1_LATEST_VER 4
#define PAGE255_LATEST_VER 3

//check that PortInfo.CapabilityMask's 'IsCapabilityMask2Supported' is set
#define IS_SUPPORT_PORT_INFO_CAP_MASK2(cap_mask) ((cap_mask & 0x8000))
//check that PortInfo.CapabilityMask2's IsPortInfoExtendedSupported is set
#define IS_SUPPORT_PORT_INFO_EXTENDED(cap_mask) ((cap_mask) & 0x2)
//K_FCODE - this is a coefficient to raw ber when RS-FEC is active
#define K_FCODE              2

#define VPORT_STATE_BLOCK_SIZE     128

#define DEFAULT_BER_THRESHOLD                       0xe8d4a51000ULL     /* pow(10,12) */
#define DEFAULT_BER_THRESHOLD_STR                   "10^-12"             /* pow(10,12) */

/****************PM PER SL/VL CNTRS******************/
#define PORT_RCV_DATA_VL_HEADER             "PortRcvDataVL"
#define PORT_RCV_DATA_VL_HEADER_CSV         "PORT_RCV_DATA_VL"

#define PORT_XMIT_DATA_VL_HEADER            "PortXmitDataVL"
#define PORT_XMIT_DATA_VL_HEADER_CSV        "PORT_XMIT_DATA_VL"

#define PORT_RCV_DATA_VL_EXT_HEADER         "PortRcvDataVLExt"
#define PORT_RCV_DATA_VL_EXT_HEADER_CSV     "PORT_RCV_DATA_VL_EXT"

#define PORT_XMIT_DATA_VL_EXT_HEADER        "PortXmitDataVLExt"
#define PORT_XMIT_DATA_VL_EXT_HEADER_CSV    "PORT_XMIT_DATA_VL_EXT"

#define PORT_RCV_PKT_VL_HEADER              "PortRcvPktVL"
#define PORT_RCV_PKT_VL_HEADER_CSV          "PORT_RCV_PKT_VL"

#define PORT_XMIT_PKT_VL_HEADER             "PortXmitPktVL"
#define PORT_XMIT_PKT_VL_HEADER_CSV         "PORT_XMIT_PKT_VL"

#define PORT_RCV_PKT_VL_EXT_HEADER          "PortRcvPktVLExt"
#define PORT_RCV_PKT_VL_EXT_HEADER_CSV      "PORT_RCV_PKT_VL_EXT"

#define PORT_XMIT_PKT_VL_EXT_HEADER         "PortXmitPktVLExt"
#define PORT_XMIT_PKT_VL_EXT_HEADER_CSV     "PORT_XMIT_PKT_VL_EXT"

#define PORT_XMIT_DATA_SL_HEADER            "PortXmitDataSL"
#define PORT_XMIT_DATA_SL_HEADER_CSV        "PORT_XMIT_DATA_SL"

#define PORT_RCV_DATA_SL_HEADER             "PortRcvDataSL"
#define PORT_RCV_DATA_SL_HEADER_CSV         "PORT_RCV_DATA_SL"

#define PORT_XMIT_DATA_SL_EXT_HEADER        "PortXmitDataSLExt"
#define PORT_XMIT_DATA_SL_EXT_HEADER_CSV    "PORT_XMIT_DATA_SL_EXT"

#define PORT_RCV_DATA_SL_EXT_HEADER         "PortRcvDataSLExt"
#define PORT_RCV_DATA_SL_EXT_HEADER_CSV     "PORT_RCV_DATA_SL_EXT"

//Capability check bit
#define NOT_SUPPORT_XMIT_WAIT                               0x1
#define NOT_SUPPORT_EXT_PORT_COUNTERS                       0x2
#define NOT_SUPPORT_EXT_SPEEDS_COUNTERS                     0x4
#define NOT_SUPPORT_LLR_COUNTERS                            0x8
#define NOT_SUPPORT_EXT_SPEEDS_RSFEC_COUNTERS               0x10
#define NOT_SUPPORT_PORT_INFO_EXTENDED                      0x20
#define PM_PER_SLVL_VS_CLASS_PORT_RCV_DATA_VL               0x40
#define PM_PER_SLVL_VS_CLASS_PORT_XMIT_DATA_VL              0x80
#define PM_PER_SLVL_VS_CLASS_PORT_RCV_PKTS_VL               0x100
#define PM_PER_SLVL_VS_CLASS_PORT_XMIT_PKTS_VL              0x200
#define PM_PER_SLVL_VS_CLASS_PORT_RCV_DATA_VL_EXT           0x400
#define PM_PER_SLVL_VS_CLASS_PORT_XMIT_DATA_VL_EXT          0x800
#define PM_PER_SLVL_VS_CLASS_PORT_RCV_PKTS_VL_EXT           0x1000
#define PM_PER_SLVL_VS_CLASS_PORT_XMIT_PKTS_VL_EXT          0x2000
#define PM_PER_SLVL_PM_CLASS_PORT_XMIT_DATA_SL              0x4000
#define PM_PER_SLVL_PM_CLASS_PORT_RCV_DATA_SL               0x8000
#define PM_PER_SLVL_PM_CLASS_PORT_XMIT_DATA_SL_EXT          0x10000
#define PM_PER_SLVL_PM_CLASS_PORT_RCV_DATA_SL_EXT           0x20000
#define NOT_SUPPORT_PORT_RCV_ERROR_DETAILS                  0x40000
#define NOT_SUPPORT_PORT_XMIT_DISCARD_DETAILS               0x80000
#define NOT_SUPPORT_SPECIAL_PORTS_MARKING_CHECKED           0x100000

#define IS_SUPPORT_EXT_PORT_FAILED(appData) \
    (appData & NOT_SUPPORT_EXT_PORT_COUNTERS)
#define IS_SUPPORT_EXT_SPEEDS_FAILED(appData) \
    (appData & NOT_SUPPORT_EXT_SPEEDS_COUNTERS)
#define IS_SUPPORT_EXT_SPEEDS_RSFEC_FAILED(appData)\
    (appData & NOT_SUPPORT_EXT_SPEEDS_RSFEC_COUNTERS)
#define IS_SUPPORT_LLR_FAILED(appData1) \
    (appData1 & NOT_SUPPORT_LLR_COUNTERS)
#define IS_SUPPORT_PORT_INFO_EXTENDED_FAILED(appData)\
    (appData & NOT_SUPPORT_PORT_INFO_EXTENDED)
#define IS_SUPPORT_PORT_RCV_ERROR_DETAILS(appData) \
    (appData & NOT_SUPPORT_PORT_RCV_ERROR_DETAILS)
#define IS_SUPPORT_PORT_XMIT_DISCARD_DETAILS(appData) \
    (appData & NOT_SUPPORT_PORT_XMIT_DISCARD_DETAILS)

//data1 set bit if not support cap
#define PM_PER_SLVL_ATTR_IS_NOT_SUPPORT_CAPABILTY(p_curr_node, attr_id_cap_bit) \
    IS_APP_DATA_BIT_SET(p_curr_node->appData1.val, attr_id_cap_bit)

//data2 set bit if support check
#define PM_PER_SLVL_ATTR_IS_SUPPORT_NOT_CHECKED_CAPABILTY(p_curr_node, attr_id_cap_bit) \
    !IS_APP_DATA_BIT_SET(p_curr_node->appData2.val, attr_id_cap_bit)

#define IS_APP_DATA_BIT_SET(appdata, attr_id_cap_bit) \
    ((appdata & attr_id_cap_bit) ? true : false)

/****************************************************/
struct slvl_data_sort {
        inline bool operator () (const pair_ibport_slvl_cntr_data_t &lsvd,
                                 const pair_ibport_slvl_cntr_data_t &rsvd) const {
            return (lsvd.first->createIndex < rsvd.first->createIndex);
        }
};

union IBDiagSLVLCntrsData {
       u_int32_t data32[16];
       struct uint64bit data64[16];
};

class CountersPerSLVL {
protected:
    u_int32_t m_attr_id;
    bool m_is_vs_class;
    bool m_is_per_vl;
    bool m_is_ext_cntrs;
    u_int32_t m_cap_bit;
    string m_header;
    string m_csv_header;

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) = 0;

    void Unpack32(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                  const uint8_t *buff) {
        struct RawData_PM_PortRcvXmitCntrsSlVl32 data32;
        CLEAR_STRUCT(data32);
        RawData_PM_PortRcvXmitCntrsSlVl32_unpack(&data32, buff);

        memcpy(ibdiag_slvl_cntrs_data.data32,
               data32.DataVLSL32,
               sizeof(ibdiag_slvl_cntrs_data.data32));
    }

    void Unpack64SL(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                    const uint8_t *buff) {
        struct RawData_PM_PortRcvXmitCntrsSl64 data64;
        CLEAR_STRUCT(data64);
        RawData_PM_PortRcvXmitCntrsSl64_unpack(&data64, buff);

        memcpy(ibdiag_slvl_cntrs_data.data64,
               data64.DataVLSL64,
               sizeof(ibdiag_slvl_cntrs_data.data64));
    }

    void Unpack64VL(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                    const uint8_t *buff) {
        struct RawData_PM_PortRcvXmitCntrsVl64 data64;
	CLEAR_STRUCT(data64);
        RawData_PM_PortRcvXmitCntrsVl64_unpack(&data64, buff);

        memcpy(ibdiag_slvl_cntrs_data.data64,
               data64.DataVLSL64,
               sizeof(ibdiag_slvl_cntrs_data.data64));
    }

    void Dump(u_int32_t data[], size_t arrsize, u_int8_t operationalVLs, stringstream &sstream);
    void Dump(struct uint64bit data[], size_t arrsize, u_int8_t operationalVLs, stringstream &sstream);

public:
    set_port_data_update_t m_set_port_data_update;

    CountersPerSLVL(u_int32_t attr_id, bool is_vs_class, bool is_per_vl,
                    bool is_ext_cntrs, u_int32_t cap_bit, string header, string csv_header) :
                        m_attr_id(attr_id), m_is_vs_class(is_vs_class), m_is_per_vl(is_vs_class),
                        m_is_ext_cntrs(is_ext_cntrs), m_cap_bit(cap_bit), m_header(header),
                        m_csv_header(csv_header) {}
    virtual ~CountersPerSLVL() {}

    inline u_int32_t GetAttrId() const { return m_attr_id; }
    inline bool IsVSClass() const { return m_is_vs_class; }
    inline bool IsExtCntrs() const {return m_is_ext_cntrs; }
    inline u_int32_t GetAttrCapBit() const { return m_cap_bit; }
    inline string GetCntrHeader() const { return m_header; }
    inline string GetCSVSectionHeader() const { return m_csv_header; }
    void DumpSLVLCntrsHeader(CSVOut &csv_out);
    void DumpSLVLCntrsData(CSVOut &csv_out, IBDMExtendedInfo &fabric_extended_info);
};

//VS CLASS
class PortRcvDataVL: public CountersPerSLVL {
public:
    PortRcvDataVL(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_DATA_VL,
                                     true/*VS Class*/, true/*Per VL*/, false/*Not ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_RCV_DATA_VL,
                                     PORT_RCV_DATA_VL_HEADER,
                                     PORT_RCV_DATA_VL_HEADER_CSV) {}
    virtual ~PortRcvDataVL() {}

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortRcvDataVL Counter\n");
        Unpack32(ibdiag_slvl_cntrs_data, buff); }
};

class PortXmitDataVL: public CountersPerSLVL {
public:
    PortXmitDataVL(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_DATA_VL,
                                     true/*VS Class*/, true/*Per VL*/, false/*Not ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_XMIT_DATA_VL,
                                     PORT_XMIT_DATA_VL_HEADER,
                                     PORT_XMIT_DATA_VL_HEADER_CSV) {}
    virtual ~PortXmitDataVL() {}

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortXmitDataVL Counter\n");
        Unpack32(ibdiag_slvl_cntrs_data, buff); }
};

class PortRcvDataVLExt: public CountersPerSLVL {
public:
    PortRcvDataVLExt(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_DATA_VL_EXT,
                                     true/*VS Class*/, true/*Per VL*/, true/*Ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_RCV_DATA_VL_EXT,
                                     PORT_RCV_DATA_VL_EXT_HEADER,
                                     PORT_RCV_DATA_VL_EXT_HEADER_CSV) {}
    virtual ~PortRcvDataVLExt() {}

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortRcvDataVLExt Counter\n");
        Unpack64VL(ibdiag_slvl_cntrs_data, buff); }

};

class PortXmitDataVLExt: public CountersPerSLVL {
public:
    PortXmitDataVLExt(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_DATA_VL_EXT,
                                     true/*VS Class*/, true/*Per VL*/, true/*Ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_XMIT_DATA_VL_EXT,
                                     PORT_XMIT_DATA_VL_EXT_HEADER,
                                     PORT_XMIT_DATA_VL_EXT_HEADER_CSV) {}
    virtual ~PortXmitDataVLExt() {}

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortXmitDataVLExt Counter\n");
        Unpack64VL(ibdiag_slvl_cntrs_data, buff); }

};

class PortRcvPktVL: public CountersPerSLVL {
public:
    PortRcvPktVL(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_PKT_VL,
                                     true/*VS Class*/, true/*Per VL*/, false/*Not ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_RCV_PKTS_VL,
                                     PORT_RCV_PKT_VL_HEADER,
                                     PORT_RCV_PKT_VL_HEADER_CSV) {}
    virtual ~PortRcvPktVL() {}

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortRcvPktVL Counter\n");
        Unpack32(ibdiag_slvl_cntrs_data, buff); }
};

class PortXmitPktVL: public CountersPerSLVL {
public:
    PortXmitPktVL(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_PKT_VL,
                                     true/*VS Class*/, true/*Per VL*/, false/*Not ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_XMIT_PKTS_VL,
                                     PORT_XMIT_PKT_VL_HEADER,
                                     PORT_XMIT_PKT_VL_HEADER_CSV) {}
    virtual ~PortXmitPktVL() {}

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortXmitPktVL Counter\n");
        Unpack32(ibdiag_slvl_cntrs_data, buff); }
};

class PortRcvPktVLExt: public CountersPerSLVL {
public:
    PortRcvPktVLExt(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_PKT_VL_EXT,
                                     true/*VS Class*/, true/*Per VL*/, true/*Ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_RCV_PKTS_VL_EXT,
                                     PORT_RCV_PKT_VL_EXT_HEADER,
                                     PORT_RCV_PKT_VL_EXT_HEADER_CSV) {}
    virtual ~PortRcvPktVLExt() {}
    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortRcvPktVLExt Counter\n");
        Unpack64VL(ibdiag_slvl_cntrs_data, buff); }

};

class PortXmitPktVLExt: public CountersPerSLVL {
public:
    PortXmitPktVLExt(): CountersPerSLVL(IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_PKT_VL_EXT,
                                     true/*VS Class*/, true/*Per VL*/, true/*Ext cntrs*/,
                                     PM_PER_SLVL_VS_CLASS_PORT_XMIT_PKTS_VL_EXT,
                                     PORT_XMIT_PKT_VL_EXT_HEADER,
                                     PORT_XMIT_PKT_VL_EXT_HEADER_CSV) {}
    virtual ~PortXmitPktVLExt() {}
    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortXmitPktVLExt Counter\n");
        Unpack64VL(ibdiag_slvl_cntrs_data, buff); }

};

//PM CLASS
class PortXmitDataSL: public CountersPerSLVL {
public:
    PortXmitDataSL(): CountersPerSLVL(IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_XMIT_DATA_SL,
                                     false/*PM Class*/, false/*Per SL*/, false/*Not ext cntrs*/,
                                     PM_PER_SLVL_PM_CLASS_PORT_XMIT_DATA_SL,
                                     PORT_XMIT_DATA_SL_HEADER,
                                     PORT_XMIT_DATA_SL_HEADER_CSV) {}
    virtual ~PortXmitDataSL() {}

    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortXmitDataSL Counter\n");
        Unpack32(ibdiag_slvl_cntrs_data, buff); }
};

class PortRcvDataSL: public CountersPerSLVL {
public:
    PortRcvDataSL(): CountersPerSLVL(IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_RCV_DATA_SL,
                                     false/*PM Class*/, false/*Per SL*/, false/*Not ext cntrs*/,
                                     PM_PER_SLVL_PM_CLASS_PORT_RCV_DATA_SL,
                                     PORT_RCV_DATA_SL_HEADER,
                                     PORT_RCV_DATA_SL_HEADER_CSV) {}
    virtual ~PortRcvDataSL() {}
    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortRcvDataSL Counter\n");
        Unpack32(ibdiag_slvl_cntrs_data, buff); }
};


class PortXmitDataSLExt: public CountersPerSLVL {
public:
    PortXmitDataSLExt(): CountersPerSLVL(IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_XMIT_DATA_SL_EXT,
                                     false/*PM Class*/, false/*Per SL*/, true/*Ext cntrs*/,
                                     PM_PER_SLVL_PM_CLASS_PORT_XMIT_DATA_SL_EXT,
                                     PORT_XMIT_DATA_SL_EXT_HEADER,
                                     PORT_XMIT_DATA_SL_EXT_HEADER_CSV) {}
    virtual ~PortXmitDataSLExt() {}
    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortXmitDataSLExt Counter\n");
        Unpack64SL(ibdiag_slvl_cntrs_data, buff); }

};

class PortRcvDataSLExt: public CountersPerSLVL {
public:
    PortRcvDataSLExt(): CountersPerSLVL(IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_RCV_DATA_SL_EXT,
                                     false/*PM Class*/, false/*Per SL*/, true/*Ext cntrs*/,
                                     PM_PER_SLVL_PM_CLASS_PORT_RCV_DATA_SL_EXT,
                                     PORT_RCV_DATA_SL_EXT_HEADER,
                                     PORT_RCV_DATA_SL_EXT_HEADER_CSV) {}
    virtual ~PortRcvDataSLExt() {}
    virtual void Unpack(union IBDiagSLVLCntrsData &ibdiag_slvl_cntrs_data,
                        const uint8_t *buff) {
        IBDIAG_LOG(TT_LOG_LEVEL_INFO, "Unpack PM PortRcvDataSLExt Counter\n");
        Unpack64SL(ibdiag_slvl_cntrs_data, buff); }

};

/****************************************************/
string get_ibdiag_version();
u_int8_t get_operational_vl_num(u_int8_t opvl_code);
/****************************************************/

typedef vector<rn_gen_string_tbl > vec_rn_gen_string;
typedef vector<vec_rn_gen_string > vec_vec_rn_gen_string;


struct AdditionalRoutingData {

    IBNode *p_node;
    direct_route_t *p_direct_route;

    adaptive_routing_info ar_info;
    bool isRNSupported(){
        return (ar_info.is_arn_sup  && ar_info.is_frn_sup);
    }

    static bool dump_rn_data;
    static u_int16_t sw_supports_rn_count;

    //for each MAD vector
    //top is the max index for the current node
    //max is the max index in the fabric

    //// RNSubGroupDirectionTable
    u_int16_t top_sub_group_direction_block;
    static u_int16_t max_sub_group_direction_block;
    // index sub_group_direction_block
    vector <rn_sub_group_direction_tbl> sub_group_direction_table_vec;

    //// RNGenStringTable
    u_int8_t top_direction_block;
    static u_int8_t max_direction_block;
    static u_int8_t max_plft;
    //index: [pLFT][direction_block]
    vec_vec_rn_gen_string gen_string_table_vec;

    //// RNGenBySubGroupPriority
    rn_gen_by_sub_group_prio gen_by_sub_group_priority;

    //// RNRcvString
    u_int16_t top_string_block;
    static u_int16_t max_string_block;
    //index: string block
    vector<rn_rcv_string> rcv_string_vec;

    //// RNXmitPortMask
    u_int8_t top_ports_block;
    static u_int8_t max_ports_block;
    //index: ports block
    vector <rn_xmit_port_mask> xmit_port_mask_vec;

    ////VS_PortRNCounters
    static bool dump_rn_counters;
    static bool clear_rn_counters;
    static u_int8_t max_num_ports;
    //index: port number
    vector <port_rn_counters> port_rn_counters_vec;

    ////ib_ar_group_table
    static bool dump_full_ar;
    //index: group table block
    vector <ib_ar_group_table> group_table_vec;
    u_int16_t top_group_table_block;
    vector <ib_ar_linear_forwarding_table_sx> ar_lft_table_vec[MAX_PLFT_NUM];
    u_int16_t top_ar_lft_table_block;

    void AddGroupTable(u_int16_t group_table_block,
                       ib_ar_group_table *p_group_table){
        if (group_table_vec.size() <= group_table_block) {
            group_table_vec.resize(group_table_block + 100);
        }

        top_group_table_block = max(top_group_table_block, group_table_block);
        memcpy(&group_table_vec[group_table_block], p_group_table,
               sizeof (ib_ar_group_table));
    }
    void AddARLFT(u_int8_t pLFT,
                  u_int16_t block,
                  ib_ar_linear_forwarding_table_sx *p_ar_lft){
        if (ar_lft_table_vec[pLFT].size() <= block) {
            ar_lft_table_vec[pLFT].resize(block + 100);
        }

        top_ar_lft_table_block = max(top_ar_lft_table_block, block);
        memcpy(&ar_lft_table_vec[pLFT][block], p_ar_lft, sizeof (*p_ar_lft));
    }

};

struct AdditionalRoutingDataCompare {
    bool operator()(const IBNode *lhs, const IBNode *rhs) const {
        return lhs->guid_get() < rhs->guid_get();
    }
};

typedef map <IBNode *, AdditionalRoutingData, AdditionalRoutingDataCompare> AdditionalRoutingDataMap;
typedef AdditionalRoutingDataMap::iterator AdditionalRoutingDataMapIter;
typedef pair <AdditionalRoutingDataMapIter, bool> AdditionalRoutingDataMapInsertRes;


/*****************************************************/
class IBDiag {
private:
    ////////////////////
    //members
    ////////////////////
    IBFabric discovered_fabric;
    Ibis ibis_obj;
    IBDMExtendedInfo fabric_extended_info;

    enum {NOT_INITILIAZED, NOT_SET_PORT, READY} ibdiag_status;
    enum {DISCOVERY_SUCCESS, DISCOVERY_NOT_DONE, DISCOVERY_DUPLICATED_GUIDS} ibdiag_discovery_status;
    string last_error;
    bool check_duplicated_guids;

    ////////////////////
    //discovery members
    ////////////////////
    list_p_direct_route bfs_list;               //this list supposed to be empty at the end of discovery
    list_p_direct_route good_direct_routes;
    list_p_bad_direct_route bad_direct_routes;
    list_p_direct_route loop_direct_routes;
    list_string duplicated_guids_detection_errs;
    list_p_fabric_general_err errors; //MAYDO replace separete error per RetrieceInfo

    map_guid_list_p_direct_route bfs_known_node_guids;
    map_guid_list_p_direct_route bfs_known_port_guids;

    //this map is filled in alias guids stage with port guids and their alias guids.
    //If one wishes to use db for only aguids please use the PortByAGuids in
    //ibdm.
    map_guid_pport port_aguids;

    IBNode * root_node;
    u_int8_t root_port_num;
    progress_bar_nodes_t discover_progress_bar_nodes;
    progress_bar_ports_t discover_progress_bar_ports;

    bool no_mepi; // do not send SMPMlnxExtPortInfoMad
    u_int8_t llr_active_cell_size; //active LLR given by user

    int64_t ber_threshold;
    //capability mask module, responsible for what mad capabilities are supported
    CapabilityModule capability_module;

    ////////////////////
    //methods
    ////////////////////

    void CleanUpInternalDB();

    // Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int GetReverseDirectRoute(INOUT direct_route_t *p_reverse_direct_route, IN direct_route_t *p_direct_route);

    // Returns: SUCCESS_CODE / ERR_CODE_EXCEEDS_MAX_HOPS
    int ConcatDirectRoutes(IN direct_route_t *p_direct_route1,
            IN direct_route_t *p_direct_route2,
            OUT direct_route_t *p_direct_route_result);

    ////////////////////
    //duplicated guids  methods
    ////////////////////
    void AddDupGUIDDetectError(IN direct_route_t *p_direct_route_checked_node,
            IN u_int64_t checked_node_guid,
            IN u_int8_t checked_node_type,
            IN direct_route_t *p_direct_route_got_err,
            IN bool no_response_err,
            IN bool max_hops_err,
            IN string err_desc);

    // Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_DUPLICATED_GUID / ERR_CODE_FABRIC_ERROR
    int CheckIfSameCADevice(IN direct_route_t *p_new_direct_route,
            IN direct_route_t *p_old_direct_route,
            IN struct SMP_NodeInfo *p_new_node_info,
            OUT IbdiagBadDirectRoute_t *p_bad_direct_route_info);

    // Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_DUPLICATED_GUID / ERR_CODE_FABRIC_ERROR / ERR_CODE_EXCEEDS_MAX_HOPS
    int CheckIfSameSWDevice(IN direct_route_t *p_new_direct_route,
            IN direct_route_t *p_old_direct_route,
            IN struct SMP_NodeInfo *p_new_node_info,
            OUT IbdiagBadDirectRoute_t *p_bad_direct_route_info);

    // Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int IsDuplicatedGuids(IN direct_route_t *p_new_direct_route,
            IN struct SMP_NodeInfo *p_new_node_info,
            OUT bool *duplicated_node_guid,
            OUT bool *duplicated_port_guid,
            OUT bool *is_visited_node_already,
            OUT bool *is_visited_port_already,
            OUT direct_route_t **p_old_direct_route,
            OUT IbdiagBadDirectRoute_t *p_bad_direct_route_info);

    ////////////////////
    //discovery methods
    ////////////////////
    inline bool IsBFSKnownPortGuid(IN u_int64_t guid);
    inline bool IsBFSKnownNodeGuid(IN u_int64_t guid);
    inline void MarkNodeGuidAsBFSKnown(IN u_int64_t guid, IN direct_route_t *p_direct_route);
    inline void MarkPortGuidAsBFSKnown(IN u_int64_t guid, IN direct_route_t *p_direct_route);

    inline list_p_direct_route& GetDirectRoutesByNodeGuid(IN u_int64_t guid) { return this->bfs_known_node_guids[guid]; }
    inline list_p_direct_route& GetDirectRoutesByPortGuid(IN u_int64_t guid) { return this->bfs_known_port_guids[guid]; }

    inline void BFSPushPath(IN direct_route_t *p_direct_route);
    inline direct_route_t * BFSPopPath();

    inline void AddGoodPath(IN direct_route_t *p_direct_route);
    inline int  AddBadPath(IN IbdiagBadDirectRoute_t *bad_direct_route, IN direct_route_t *direct_route);
    inline void AddLoopPath(IN direct_route_t *p_direct_route);

    void PostDiscoverFabricProcess();

    // Returns: SUCCESS_CODE / ERR_CODE_FABRIC_ERROR / ERR_CODE_IBDM_ERR / ERR_CODE_INCORRECT_ARGS / ERR_CODE_NO_MEM
    int DiscoverFabricOpenCAPorts(IN IBNode *p_node,
            IN direct_route_t *p_direct_route,
            IN SMP_NodeInfo *p_node_info,
            IN bool is_root,
            OUT IbdiagBadDirectRoute_t *p_bad_direct_route_info,
            IN bool push_new_direct_route);
    int DiscoverFabricOpenSWPorts(IN IBNode *p_node,
            IN direct_route_t *p_direct_route,
            IN SMP_NodeInfo *p_node_info,
            IN bool is_root,
            OUT IbdiagBadDirectRoute_t *p_bad_direct_route_info,
            IN bool push_new_direct_route);
    int DiscoverFabricBFSOpenPorts(IN direct_route_t * p_direct_route,
            IN IBNode *p_node,
            IN struct SMP_NodeInfo *p_node_info,
            IN bool is_visited_node,
            IN bool is_root,
            OUT IbdiagBadDirectRoute_t *p_bad_direct_route_info,
            IN bool push_new_direct_route = true);

    int ApplySubCluster(IN vector_p_node sub_nodes,
                        IN vector_p_port sub_ports);

    u_int16_t GetPathNextNode(IN IBNode **p_node,
            IN lid_t dest_lid,
            INOUT direct_route_t **p_direct_route,
            IN direct_route_t *dr_path,
            IN struct SMP_NodeInfo &curr_node_info);

    // Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_IBDM_ERR / ERR_CODE_TRY_TO_DISCONNECT_CONNECTED_PORT
    int DiscoverFabricBFSCreateLink(IN direct_route_t * p_direct_route,
            IN IBPort * p_port);

    // Returns: SUCCESS_CODE / ERR_CODE_FABRIC_ERROR / ERR_CODE_IBDM_ERR / ERR_CODE_INCORRECT_ARGS / ERR_CODE_NO_MEM
    int DiscoverFabricBFSOpenNode(IN direct_route_t *p_direct_route,
            IN bool is_root,
            OUT IBNode **p_pnode,
            OUT struct SMP_NodeInfo *p_node_info,
            OUT bool *is_visited_node,
            IN progress_func_discovered_t discover_progress_func,
            OUT IbdiagBadDirectRoute_t *p_bad_direct_route_info);

    bool IsValidNodeInfoData(IN struct SMP_NodeInfo *p_node_info,
                             OUT string &additional_info);

    ////////////////////
    //db file methods
    ////////////////////
    void DumpCSVNodesTable(CSVOut &csv_out);
    void DumpCSVSwitchesTable(CSVOut &csv_out);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int DumpCSVPortsTable(CSVOut &csv_out, bool show_ports_data_extra);
    int DumpCSVLinksTable(CSVOut &csv_out);
    void DumpCSV_FECModeTable(CSVOut &csv_out);

    /////////////////////////////
    //network dump file methods
    /////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int DumpNetwork(ofstream &sout);

    ////////////////////
    //pm methods
    ////////////////////
    void DumpPortExtendedSpeedsCounters(ofstream &sout,
                                        bool en_per_lane_cnts,
                                        IBPort *p_curr_port,
                                        u_int32_t port_idx);

    void DumpPortCounters(ofstream &sout,
                          u_int32_t check_counters_bitset,
                          bool en_per_lane_cnts);
    int ReadCapMask(IBNode *p_node, IBPort *p_port,
                    u_int16_t &cap_mask, u_int32_t &port_info_cap_mask);
    int ReadPortInfoCapMask(IBNode *p_node,
                            IBPort *p_port,
                            u_int32_t &port_info_cap_mask,
                            u_int16_t *p_port_info_cap_mask2 = NULL);

    u_int8_t PMIsOptionalAttrSupported(IBNode * p_node, int attr_id);
    int BuildPortOptionMaskDB(list_p_fabric_general_err& pm_errors);
    ////////////////////
    //sm methods
    ////////////////////
    void DumpSMInfo(ofstream &sout);

    ////////////////////
    // vs methods
    ////////////////////
    void DumpNodesInfo(ofstream &sout);

    //Returns: SUCCESS_CODE / IBDIAG_ERR_CODE_FABRIC_ERROR
    int CheckVSGeneralInfo(IBNode *p_curr_node, struct VendorSpec_GeneralInfo *p_curr_general_info);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVsCapSmpFwInfo(list_p_fabric_general_err &vs_cap_smp_errors,
                            progress_func_nodes_t progress_func);
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVsCapSmpCapabilityMask(list_p_fabric_general_err &vs_cap_smp_errors,
                                        progress_func_nodes_t progress_func);
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVsCapGmpInfo(list_p_fabric_general_err &vs_cap_gmp_errors,
                          progress_func_nodes_t progress_func);

    ////////////////////
    //routing methods
    ////////////////////
    int ReportNonUpDownCa2CaPaths(IBFabric *p_fabric, list_pnode rootNodes, string& output);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int GetSwitchesDirectRouteList(direct_route_list &directRouteList);

    /// PLFT
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int RetrievePLFTInfo(list_p_fabric_general_err& retrieve_errors,
                         direct_route_list &directRouteList);
    int RetrievePLFTMapping(list_p_fabric_general_err& retrieve_errors,
                         direct_route_list &directRouteList);
    int RetrievePLFTTop(list_p_fabric_general_err& retrieve_errors,
                        direct_route_list &directRouteList);
    // AR
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    // removes sw entries from directRouteList if enable bit is false
    int RetrieveARInfo(list_p_fabric_general_err& retrieve_errors,
                       direct_route_list &directRouteList,
                       AdditionalRoutingDataMap *p_routing_data_map);
    int RetrieveARGroupTable(list_p_fabric_general_err& retrieve_errors,
                       direct_route_list & directRouteList);
    int RetrieveARLinearForwardingTable(
                        list_p_fabric_general_err& retrieve_errors,
                        direct_route_list & directRouteList);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int DumpUCFDBSInfo(ofstream &sout);
    int DumpMCFDBSInfo(ofstream &sout);
    int DumpSLVLFile(ofstream &sout,
                     list_p_fabric_general_err& retrieve_errors,
                     progress_func_nodes_t progress_func);
    int DumpPLFTInfo(ofstream &sout);
    int DumpARInfo(ofstream &sout);
    int DumpFARInfo(AdditionalRoutingDataMap *p_routing_data_map,
                    ofstream &sout);
    int DumpRNInfo(AdditionalRoutingDataMap *p_routing_data_map,
                   ofstream &sout);
    int DumpRNCountersInfo(AdditionalRoutingDataMap *p_routing_data_map,
                           ofstream &sout);
    int DumpVL2VLInfo(ofstream &sout);

    //helper for DumpFARInfo
    void DumpPortsBitset(u_int64_t pgSubBlockElement,
                         phys_port_t portOffset,
                         ofstream &sout);
    void DumpPortgroup(ib_portgroup_block_element &pgBlockElement,
                       ofstream &sout);

    //helper for DumpRNInfo
    const char *RNDecisionToStr(u_int8_t decision);

    //helper for DumpSLVLFile
    int ReadCASLVL(ofstream &sout,
                   clbck_data_t &clbck_data,
                   SMP_SLToVLMappingTable &slvl_mapping,
                   IBNode *p_node);
    bool HandleUnsupportedSLMapping(ofstream &sout,
                                    IBNode *p_node,
                                    phys_port_t port);

    ////////////////////
    ////pkey methods
    ////////////////////
    void DumpPartitionKeys(ofstream &sout);

    ////////////////////
    ////aguid methods
    ////////////////////
    void DumpAliasGUID(ofstream &sout);


public:
    ////////////////////
    //methods
    ////////////////////
    IBDiag();
    ~IBDiag();

    void ResetAppData(bool force = false);

    inline string ConvertDirPathToStr(direct_route_t *p_direct_route) { return (this->ibis_obj.ConvertDirPathToStr(p_direct_route)); }

    //Returns: SUCCESS_CODE / ERR_CODE_IO_ERR
    int OpenFile(const char *file_name, ofstream& sout, bool to_append = false, bool add_header = false);

    inline bool IsInit() { return (this->ibdiag_status != NOT_INITILIAZED); };
    inline bool IsReady() { return (this->ibdiag_status == READY); };
    inline bool IsDiscoveryDone() { return this->ibdiag_discovery_status == DISCOVERY_SUCCESS; }
    inline bool IsDuplicatedGuidsFound() { return this->ibdiag_discovery_status == DISCOVERY_DUPLICATED_GUIDS; }

    list_p_fabric_general_err &GetErrors() {return errors;}

    inline IBFabric * GetDiscoverFabricPtr() { return &(this->discovered_fabric); }
    inline Ibis * GetIbisPtr() { return &(this->ibis_obj); }
    inline CapabilityModule* GetCapabilityModulePtr() { return &(this->capability_module); }
    inline IBDMExtendedInfo* GetIBDMExtendedInfoPtr() { return &(this->fabric_extended_info); }

    inline progress_bar_nodes_t * GetDiscoverProgressBarNodesPtr() { return &this->discover_progress_bar_nodes; }
    inline progress_bar_ports_t * GetDiscoverProgressBarPortsPtr() { return &this->discover_progress_bar_ports; }

    inline list_string& GetRefToDupGuidsDetectionErrors() {return this->duplicated_guids_detection_errs; }
    inline bool& GetRefToCheckDupGuids() { return this->check_duplicated_guids; }

    void SetLastError(const char *fmt, ...);
    const char* GetLastError();
    inline bool IsLastErrorEmpty() { return last_error.empty();}

    // Returns: SUCCESS_CODE / ERR_CODE_INIT_FAILED
    int Init();
    int SetPort(const char* device_name, phys_port_t port_num);
    int SetPort(u_int64_t port_guid);

    // Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int GetLocalPortState(OUT u_int8_t& state);

    IBNode * GetNodeByDirectRoute(IN const direct_route_t *p_direct_route);
    direct_route_t * GetDirectRouteByNodeGuid(IN u_int64_t guid);
    direct_route_t * GetDirectRouteByPortGuid(IN u_int64_t guid);
    IBPort * GetRootPort();
    int GetAllLocalPortGUIDs(OUT local_port_t local_ports_array[IBIS_MAX_LOCAL_PORTS],
            OUT u_int32_t *p_local_ports_num);

    int getLatestSupportedVersion(int page_number,
                                  unsigned int &latest_version);

    inline void SetBERThreshold(int64_t ber) {
        if (ber_threshold == 0) {   /* ZERO is considered as overflow value ==> print all calculations */
            this->ber_threshold = OVERFLOW_VAL_64_BIT;
            return;
        }
        this->ber_threshold = ber_threshold;
    }

    inline int64_t GetBERThreshold() {return ber_threshold;}

    ////////////////////
    //duplicated guids methods
    ////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_CHECK_FAILED / ERR_CODE_NO_MEM / ERR_CODE_DB_ERR
    int CheckDuplicatedGUIDs(list_p_fabric_general_err& guids_errors);

    // Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int PrintNodesDuplicatedGuids();
    int PrintPortsDuplicatedGuids();

    void PrintDupGuidsDetectionErrors();

    ////////////////////
    //discovery methods
    ////////////////////
    void GetGoodDirectRoutes(OUT list_string& good_direct_routes);
    void GetLoopDirectRoutes(OUT list_string& loop_direct_routes);
    void GetBadDirectRoutes(OUT list_string& bad_direct_routes);
    void PrintAllRoutes();
    void PrintAllDirectRoutes();

    // Returns: SUCCESS_CODE / ERR_CODE_FABRIC_ERROR / ERR_CODE_IBDM_ERR / ERR_CODE_INCORRECT_ARGS / ERR_CODE_NO_MEM / ERR_CODE_DB_ERR / ERR_CODE_TRY_TO_DISCONNECT_CONNECTED_PORT / ERR_CODE_INCORRECT_ARGS
    int DiscoverPath(IN progress_func_discovered_t discover_progress_func,
            IN u_int8_t max_hops, IN lid_t src_lid, IN lid_t dest_lid,
            direct_route_t &dr_path, OUT stringstream *pss);

    bool IsVirtualLidForNode(IBNode *p_node,
                            lid_t lid,
                            stringstream *pss);
    int DiscoverFabric(IN progress_func_discovered_t discover_progress_func = NULL,
            IN u_int8_t max_hops = IBDIAG_MAX_HOPS);

    // for 'load from file' mode
    int DiscoverFabricFromFile(IN const string &csv_file,
            IN progress_func_discovered_t discover_progress_func = NULL);
    int BuildDirectRoutesDB();

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildSwitchInfoDB(list_p_fabric_general_err& retrieve_errors, progress_func_nodes_t progress_func);
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR
    // ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildPortInfoExtendedDB(list_p_fabric_general_err& retrieve_errors,
                                progress_func_nodes_t progress_func);

    int ParsePSLFile(const string & file_name, string& output);
    int ParseSADumpFile(const string & file_name, string& output);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_IBDM_ERR
    int DumpCapabilityMaskFile(const char* file_name, string& output);
    //for debug purposes
    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_IBDM_ERR
    int DumpGuid2Mask(const char *file_name, string& output);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int ParseCapabilityMaskFile(const char* file_name, string& output);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int ParseNodeNameMapFile(const char* file_name, string& output);

    inline void SetNoMEPI() {
        this->no_mepi = true;
    }

    inline void SetLLRActiveCell(const string &active_cell_size) {
        unsigned long int cell_size = strtoul(active_cell_size.c_str(), NULL, 10);

        switch (cell_size) {
        case 128:
            this->llr_active_cell_size = RETRANS_LLR_ACTIVE_CELL_128;
            break;
        case 64: default:
            this->llr_active_cell_size = RETRANS_LLR_ACTIVE_CELL_64;
            break;
        }
    }

    inline u_int8_t GetLLRActiveCellSize() {
        return this->llr_active_cell_size;
    }

    ////////////////////
    //checks methods
    ////////////////////
    //Return: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_INCORRECT_ARGS / ERR_CODE_NO_MEM / ERR_CODE_CHECK_FAILED / ERR_CODE_DB_ERR
    int CheckLinkWidth(list_p_fabric_general_err& width_errors, string expected_link_width_str = "");
    int CheckLinkSpeed(list_p_fabric_general_err& speed_errors, string expected_link_speed = "");

    //Return: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_NO_MEM / ERR_CODE_CHECK_FAILED
    int CheckDuplicatedNodeDescription(list_p_fabric_general_err& nodes_errors);
    int CheckLinks(list_p_fabric_general_err& links_errors);
    int CheckLids(list_p_fabric_general_err& lids_errors);
    int CheckAndSetVPortLid(list_p_fabric_general_err &vport_errors);

    ////////////////////
    //db file methods
    ////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR / ERR_CODE_DB_ERR
    int DumpInternalDBCSVTable(CSVOut &csv_out, bool show_ports_data_extra, bool to_dump_fec_mode);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IBDM_ERR
    int WriteLSTFile(const char *file_path, bool write_with_lmc);

    int WriteNetDumpFile(const char* file_path);

    ////////////////////
    //pm methods
    ////////////////////
    void CopyPMInfoObjVector(OUT vector_p_pm_info_obj& new_pm_obj_info_vector);
    void CleanPMInfoObjVector(IN vector_p_pm_info_obj& curr_pm_obj_info_vector);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildClassPortInfoDB(list_p_fabric_general_err& pm_errors);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildPortCountersDB(list_p_fabric_general_err& pm_errors,
                            progress_func_nodes_t progress_func,
                            u_int32_t check_counters_bitset);
    int ResetPortCounters(list_p_fabric_general_err& ports_errors,
                          progress_func_nodes_t progress_func,
                          u_int32_t check_counters_bitset);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpPortCountersCSVTable(CSVOut &csv_out, u_int32_t check_counters_bitset);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpDiagnosticCountersCSVTable(CSVOut &csv_out);

    void DumpDiagnosticCounters(ofstream &sout);

    void DumpDiagnosticCountersDescriptionP1(ofstream &sout);
    void DumpDiagnosticCountersDescriptionP0(ofstream &sout);

    void DumpDiagnosticCountersP1(ofstream &sout,
                                    struct VS_DiagnosticData *p_p1);

    void DumpDiagnosticCountersP0(ofstream &sout,
                                    struct VS_DiagnosticData *p_p0);

    void DumpDiagnosticCountersP255(ofstream &sout, struct VS_DiagnosticData *p_p255);

    //Returns: SUCCESS_CODE / IBDIAG_ERR_CODE_NO_MEM / ERR_CODE_INCORRECT_ARGS / IBDIAG_ERR_CODE_CHECK_FAILED
    int CalcCounters(vector_p_pm_info_obj& prev_pm_info_obj_vec,
                     double diff_time_between_samples,
                     list_p_fabric_general_err& pm_errors);

    //Returns: SUCCESS_CODE / IBDIAG_ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_CHECK_FAILED / ERR_CODE_INCORRECT_ARGS
    int CheckAllPMValues(list_p_fabric_general_err& pm_errors,
                         map_str_uint64& counters_to_threshold_map,
                         u_int32_t check_counters_bitset);

    //Returns: SUCCESS_CODE / ERR_CODE_NO_MEM / ERR_CODE_CHECK_FAILED / ERR_CODE_INCORRECT_ARGS
    int CheckCountersDiff(vector_p_pm_info_obj& prev_pm_info_obj_vec,
            list_p_fabric_general_err& pm_errors);

    int CalcBER(IBPort *p_curr_port,
                double time,
                u_int64_t symbol_error,
                long double &ber_value_reciprocal_val);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_CHECK_FAILED / ERR_CODE_FABRIC_ERROR
    int CalcBERErrors(vector_p_pm_info_obj& prev_pm_info_obj_vec,
            u_int64_t ber_threshold_opposite_val,
            double sec_between_samples,
            list_p_fabric_general_err& ber_errors,
            CSVOut &csv_out);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR
    int CalcPhyTest(vector_p_pm_info_obj& prev_pm_info_obj_vec,
                    double sec_between_samples,
                    CSVOut &csv_out);

    list_string GetListOFPMNames();

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WritePMFile(const char *file_name,
                    u_int32_t check_counters_bitset,
                    bool en_per_lane_cnts);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WriteMlnxCntrsFile(const char *file_name);

    int BuildCapabilityCache(string& output);

    ////////////////////
    //sm methods
    ////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildSMInfoDB(list_p_fabric_general_err& ports_errors);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_NO_MEM / ERR_CODE_CHECK_FAILED
    int CheckSMInfo(list_p_fabric_general_err& sm_errors);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WriteSMFile(const char *file_name);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpSMInfoCSVTable(CSVOut &csv_out);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpCSVVNodesTable(CSVOut &csv_out);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpCSVVPortsTable(CSVOut &csv_out);
    ////////////////////
    //vs methods
    ////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WriteNodesInfoFile(const char *file_name);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpNodesInfoCSVTable(CSVOut &csv_out);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_CHECK_FAILED
    int CheckFWVersion(list_p_fabric_general_err& fw_errors);

    ////////////////////
    //routing methods
    ////////////////////
    void SetDefaultSL(u_int8_t sl) {
        discovered_fabric.SetDefaultSL(sl);
    }

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int RetrieveUCFDBSInfo(list_p_fabric_general_err& retrieve_errors, progress_func_nodes_t progress_func);
    int RetrieveMCFDBSInfo(list_p_fabric_general_err& retrieve_errors, progress_func_nodes_t progress_func);
    int RetrieveExtendedSwitchInfo(list_p_fabric_general_err& retrieve_errors);
    int RetrievePLFTData(list_p_fabric_general_err& retrieve_errors, unsigned int &supportedDev);
    int RetrieveARData(list_p_fabric_general_err& retrieve_errors,
                       unsigned int &supportedDev,
                       AdditionalRoutingDataMap *p_routing_data_map);

    int RetrieveRNData(list_p_fabric_general_err& retrieve_errors,
                       AdditionalRoutingDataMap *p_routing_data_map);
    //Clear and/or get RN counters
    int ClearAndGetRNCounters(list_p_fabric_general_err& retrieve_errors,
                       AdditionalRoutingDataMap *p_routing_data_map);
    int AddRNDataMapEntry(AdditionalRoutingDataMap *p_routing_data_map,
                          IBNode *p_node,
                          direct_route_t *p_direct_route,
                          adaptive_routing_info *p_ar_info);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR / ERR_CODE_DB_ERR
    int WriteUCFDBSFile(const char *file_name);
    int WriteMCFDBSFile(const char *file_name);
    int WriteSLVLFile(const char *file_name,
                      list_p_fabric_general_err& retrieve_errors,
                      progress_func_nodes_t progress_func);
    int WritePLFTFile(const char *file_name);
    int WriteARFile(const char *file_name);
    int WriteFARFile(AdditionalRoutingDataMap *p_routing_data_map,
                    const char *file_name);
    int WriteRNFile(AdditionalRoutingDataMap *p_routing_data_map,
                    const char *file_name);
    int WriteRNCountersFile(AdditionalRoutingDataMap *p_routing_data_map,
                    const char *file_name);

    int WriteVL2VLFile(const char *file_name);

    int ParseSLVLFile(const string & file_name, string& output);


    //Returns: SUCCESS_CODE / ERR_CODE_IBDM_ERR / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int ReportFabricQualities(string& output, const char *outDir);
    int ReportCreditLoops(string& output, bool is_fat_tree, bool checkAR = false);
    //AR Tests
    int ReportFabricARConnectivity(string& output);
    int CheckSL2VLTables(string& output);

        ////////////////////
        ////pkey methods
        ////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildPartitionKeysDB(list_p_fabric_general_err &pkey_errors,
            progress_func_nodes_t progress_func);

    //Returns: SUCCESS_CODE / ERR_CODE_NO_MEM / ERR_CODE_CHECK_FAILED
    int CheckPartitionKeys(list_p_fabric_general_err& pkey_errors);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WritePKeyFile(const char *file_name);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpPartitionKeysCSVTable(CSVOut &csv_out);

        ////////////////////
        ////aguid methods
        ////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildAliasGuidsDB(list_p_fabric_general_err &aguid_errors,
            progress_func_nodes_t progress_func);

    //Returns: SUCCESS_CODE / ERR_CODE_NO_MEM / ERR_CODE_CHECK_FAILED
    int CheckDuplicatedAliasGuids(list_p_fabric_general_err& aguid_errors);
    int CheckVPortDuplicatedGuids(list_p_fabric_general_err& vguid_errors);


    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WriteAliasGUIDFile(const char *file_name);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS
    int DumpAliasGUIDCSVTable(CSVOut &csv_out);

    ////////////////////////////////
    ////VS Capability SMP methods
    ////////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVsCapSmpDB(list_p_fabric_general_err &vs_cap_smp_errors, progress_func_nodes_t progress_func);

    ////////////////////////////////
    ////VS Capability GMP methods
    ////////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVsCapGmpDB(list_p_fabric_general_err &vs_cap_smp_errors, progress_func_nodes_t progress_func);


    ////////////////////////////////////////
    ////Collect VS ExtendedPortInfo MADs
    ////////////////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildExtendedPortInfo(list_p_fabric_general_err &vs_ext_pi_errors,
                              progress_func_nodes_t progress_func);
    ////////////////////////////////////////
    ////Mellanox Diagnostic Counters methods
    ////////////////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVsDiagnosticCounters(list_p_fabric_general_err &mlnx_cntrs_errors,
                                  progress_func_nodes_t progress_func);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int ResetDiagnosticCounters(list_p_fabric_general_err& mlnx_cntrs_errors,
                                progress_func_nodes_t progress_func);

    ////////////////////////////////////////
    ///Scope methods
    ////////////////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / IBDIAG_ERR_CODE_IBDM_ERR
    //Parses file and applies the scope on the fabric
    //if include_in_scope is true, applies data in file as scope on the fabric
    //else applies as excluded scope.
    int ParseScopePortGuidsFile(const string & file_name,
                                string& output,
                                bool include_in_scope);


    ////Virtualization Ports methods
    ////////////////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVirtualizationDB(list_p_fabric_general_err &vport_errors,
                     progress_func_nodes_t progress_func);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVirtualizationInfoDB(IBNode *p_node);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVPortStateDB(IBNode *p_node);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVPortInfoDB(IBNode *p_node);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVNodeInfoDB(IBNode *p_node);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVNodeDescriptionDB(IBNode *p_node);

    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / ERR_CODE_NO_MEM / ERR_CODE_FABRIC_ERROR
    int BuildVPortPKeyTableDB(IBNode *p_node);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WriteVPortsFile(const char *file_name);
    void DumpVPorts(ofstream &sout);

    //Returns: SUCCESS_CODE / ERR_CODE_DISCOVERY_NOT_SUCCESS / ERR_CODE_IO_ERR
    int WriteVPortsPKeyTblFile(const char *file_name);
    void DumpVPortsPKeyTbl(ofstream &sout);

    ////////////////////////////////////////
    ///Temperature Sensing methods
    ////////////////////////////////////////
    //Returns: SUCCESS_CODE / ERR_CODE_DB_ERR / IBDIAG_ERR_CODE_IBDM_ERR
    int BuildSMPTempSensing(
            list_p_fabric_general_err& temp_sensing_errors,
            progress_func_nodes_t progress_func);

    int DumpTempSensingCSVTable(CSVOut &csv_out);

    int BuildRouterInfoDB(list_p_fabric_general_err& errors,
                          progress_func_nodes_t progress_func);
    int BuildRouterTable(list_p_fabric_general_err& errors,
                         progress_func_nodes_t progress_func);
    int DumpRoutersInfoCSVTable(CSVOut &csv_out);
    int DumpRoutersAdjSiteLocalSubnetCSVTable(CSVOut &csv_out);
    int DumpRoutersNextHopCSVTable(CSVOut &csv_out);

    bool HandleSpecialPorts(CountersPerSLVL * cntrs_per_slvl,
                            SMP_MlnxExtPortInfo *p_curr_mepi,
                            IBPort *p_curr_port,
                            int &rc,
                            list_p_fabric_general_err &cntrs_per_slvl_errors);

    int BuildDBOrResetSLVLCntrs(
            list_p_fabric_general_err &vs_ext_pi_errors,
            progress_func_ports_t progress_func,
            bool is_reset_cntr,
            CountersPerSLVL * cntrs_per_slvl);
    int DumpPerSLVLPortCntrsCSVTable(CSVOut &csv_out, vec_slvl_cntrs  &slvl_cntrs_vec);

    // QoS config SL
    int BuildSMPQoSConfigSL(list_p_fabric_general_err& qos_config_sl_errors,
                            progress_func_nodes_t progress_func);

    int DumpQoSConfigSLCSVTable(CSVOut &csv_out);

};


#endif          /* IBDIAG_H */

