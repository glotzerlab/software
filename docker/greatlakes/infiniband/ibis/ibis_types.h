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


#ifndef IBIS_TYPES_H_
#define IBIS_TYPES_H_

#include <stdlib.h>
#include <stdint.h>

#include "../ibutils/ibutils_common.h"
#include "../ibutils/ibis_ibdiagnet_plugin_common.h"

#include "packets/packets_layouts.h"


/****************************************************/
/* new types */
typedef struct direct_route {
    DirRPath_Block_Element path;
    u_int8_t length;
} direct_route_t;

typedef struct local_port {
    u_int64_t guid;
    u_int16_t lid;
    u_int8_t logical_state;
} local_port_t;


/****************************************************/
/* General Macros */
#ifndef CLEAR_STRUCT
    #define CLEAR_STRUCT(n) memset(&(n), 0, sizeof(n))
#endif

#define arrsize(a) (sizeof(a)/sizeof(a[0]))

#ifndef IN
    #define IN
#endif
#ifndef OUT
    #define OUT
#endif
#ifndef INOUT
    #define INOUT
#endif

/* defines */
#define MELLANOX_VEN_ID 0x000002c9
#define VOLTAIRE_VEN_ID 0x000008f1
#define BULL_VEN_ID     0x0000119f

/****************************************************/
/* Ibis defines + enums */
#define IBIS_TIMEOUT                500     /* 0.5 second */
#define IBIS_RETRIES                2       /* 2 tries */
#define IBIS_ERR_SIZE               4096    /* 4096 bytes */
#define IBIS_MAX_CAS                32
#define IBIS_MAX_PORTS_PER_CA       2
#define IBIS_MAX_LOCAL_PORTS        96      /* IBIS_MAX_CAS * (IBIS_MAX_PORTS_PER_CA + 1) = 96 */
#define IBIS_METHODS_MASK_LEN       4


/****************************************************/
/* Infiniband defines + enums */
#define IBIS_IB_BASE_VERSION                0x1
#define IBIS_IB_MAD_SIZE                    256
#define IBIS_IB_MAX_MAD_CLASSES             256
#define IBIS_IB_DEFAULT_QP1_QKEY            0x80010000

#define IBIS_IB_MAX_CLASS_VERSION_SUPP      2

#define IBIS_IB_MAD_SMP_LFT_NUM_BLOCKS          64
#define IBIS_IB_MAD_SMP_MFT_NUM_BLOCKS          32
#define IBIS_IB_MAD_SMP_MFT_PORT_MASK_SIZE      16
#define IBIS_IB_MAD_SMP_PKEY_TABLE_NUM_BLOCKS   32
#define IBIS_IB_MAD_SMP_GUIDS_TABLE_NUM_BLOCKS  8
#define IBIS_IB_MAD_PLFT_MAP_PORT_BLOCK_SIZE         4
#define IBIS_IB_MAD_SMP_AR_LFT_NUM_BLOCKS_SX      16
#define IBIS_IB_MAD_SMP_AR_GROUP_TABLE_BLOCK_SIZE      2
#define IBIS_IB_MAD_SMP_RN_SUB_GROUP_DIRECTION_BLOCK_SIZE 64
#define IBIS_IB_MAD_SMP_RN_GEN_STRING_TABLE_BLOCK_SIZE    32
#define IBIS_IB_MAD_SMP_RN_RCV_STRING_BLOCK_SIZE          16
#define IBIS_IB_MAD_SMP_RN_XMIT_PORT_MASK_BLOCK_SIZE      128

#define IBIS_IB_PORT_CAP_HAS_EXT_SPEEDS     0x00004000

#define IBIS_IB_PORT_PHY_STATE_ACTIVE       5

#define IBIS_IB_SM_STATE_NOT_ACTIVE         0
#define IBIS_IB_SM_STATE_DISCOVER           1
#define IBIS_IB_SM_STATE_STANDBY            2
#define IBIS_IB_SM_STATE_MASTER             3

//#define IBIS_IB_DEFAULT_SUBN_PREFIX  0xfe80000000000000ULL
//#define IBIS_IB_DEFAULT_QP1_QKEY 0x80010000
//#define IBIS_IB_VENDOR_RANGE1_DATA_OFFS  24
//#define IBIS_IB_VENDOR_RANGE1_DATA_SIZE  (IB_MAD_SIZE - IB_VENDOR_RANGE1_DATA_OFFS)
//#define IBIS_IB_VENDOR_RANGE2_DATA_OFFS  40
//#define IBIS_IB_VENDOR_RANGE2_DATA_SIZE  (IB_MAD_SIZE - IB_VENDOR_RANGE2_DATA_OFFS)

enum MAD_CLASSES {
    IBIS_IB_CLASS_SMI = 0x1,
    IBIS_IB_CLASS_SMI_DIRECT = 0x81,
    IBIS_IB_CLASS_SA = 0x3,
    IBIS_IB_CLASS_PERFORMANCE = 0x4,
    IBIS_IB_CLASS_BOARD_MGMT = 0x5,
    IBIS_IB_CLASS_DEVICE_MGMT = 0x6,
    IBIS_IB_CLASS_CM = 0x7,
    IBIS_IB_CLASS_SNMP = 0x8,
    IBIS_IB_CLASS_VENDOR_RANGE1_START = 0x9,
    IBIS_IB_CLASS_VENDOR_RANGE1_END = 0x0f,
    IBIS_IB_CLASS_CC= 0x21,
    IBIS_IB_CLASS_VENDOR_RANGE2_START = 0x30,
    IBIS_IB_CLASS_VENDOR_RANGE2_END = 0x4f,
    IBIS_IB_CLASS_VENDOR_MELLANOX = 0x0a,
    IBIS_IB_CLASS_AM = 0x0b
};


enum MAD_METHODS {
    IBIS_IB_MAD_METHOD_GET = 0x1,
    IBIS_IB_MAD_METHOD_SET = 0x2,
    IBIS_IB_MAD_METHOD_GET_RESPONSE = 0x81,
    IBIS_IB_MAD_METHOD_SEND = 0x3,
    IBIS_IB_MAD_METHOD_TRAP = 0x5,
    IBIS_IB_MAD_METHOD_TRAP_REPRESS = 0x7,
    IBIS_IB_MAD_METHOD_REPORT = 0x6,
    IBIS_IB_MAD_METHOD_REPORT_RESPONSE = 0x86,
    IBIS_IB_MAD_METHOD_GET_TABLE = 0x12,
    IBIS_IB_MAD_METHOD_GET_TABLE_RESPONSE = 0x92,
    IBIS_IB_MAD_METHOD_GET_TRACE_TABLE = 0x13,
    IBIS_IB_MAD_METHOD_GET_TRACE_TABLE_RESPONSE = 0x93,
    IBIS_IB_MAD_METHOD_GETMULTI = 0x14,
    IBIS_IB_MAD_METHOD_GETMULTI_RESPONSE = 0x94,
    IBIS_IB_MAD_METHOD_DELETE = 0x15,
    IBIS_IB_MAD_METHOD_DELETE_RESPONSE = 0x95,
    IBIS_IB_MAD_RESPONSE = 0x80
};


enum MAD_DATA_OFFSETS {
    IBIS_IB_DATA_OFFSET_SMP = 64,
    IBIS_IB_LOG_DATA_OFFSET_CC = 32,
	IBIS_IB_MGT_DATA_OFFSET_CC = 64,
	IBIS_IB_DATA_OFFSET_PERFORMANCE = 64,
    IBIS_IB_DATA_OFFSET_VENDOR_MELLANOX = 32,
    IBIS_IB_DATA_OFFSET_AM = 64
};

enum MAD_STATUS {
    IBIS_MAD_STATUS_SUCCESS = 0x0000,
    IBIS_MAD_STATUS_BUSY = 0x0001,
    IBIS_MAD_STATUS_REDIRECT = 0x0002,
    IBIS_MAD_STATUS_UNSUP_CLASS_VER = 0x0004,
    IBIS_MAD_STATUS_UNSUP_METHOD = 0x0008,
    IBIS_MAD_STATUS_UNSUP_METHOD_ATTR = 0x000C,
    IBIS_MAD_STATUS_INVALID_FIELD = 0x001C,
    IBIS_MAD_STATUS_SEND_FAILED = 0x00fc,       //umad_send failure
    IBIS_MAD_STATUS_RECV_FAILED = 0x00fd,       //umad_recv failure
    IBIS_MAD_STATUS_TIMEOUT = 0x00fe,           //timeout expired
    IBIS_MAD_STATUS_GENERAL_ERR = 0x00ff        //general error
};

enum RMPP_TYPE_ENUM {
    IBIS_IB_RMPP_TYPE_NONE,
    IBIS_IB_RMPP_TYPE_DATA,
    IBIS_IB_RMPP_TYPE_ACK,
    IBIS_IB_RMPP_TYPE_STOP,
    IBIS_IB_RMPP_TYPE_ABORT
};


enum SMP_ATTR_ID {
    IBIS_IB_ATTR_SMP_NODE_DESC = 0x10,
    IBIS_IB_ATTR_SMP_NODE_INFO = 0x11,
    IBIS_IB_ATTR_SMP_SWITCH_INFO = 0x12,
    IBIS_IB_ATTR_SMP_GUID_INFO = 0x14,
    IBIS_IB_ATTR_SMP_PORT_INFO = 0x15,
    IBIS_IB_ATTR_SMP_PKEY_TBL = 0x16,
    IBIS_IB_ATTR_SMP_SLVL_TABLE = 0x17,
    IBIS_IB_ATTR_SMP_VL_ARBITRATION = 0x18,
    IBIS_IB_ATTR_SMP_LINEARFORWTBL = 0x19,
    IBIS_IB_ATTR_SMP_MULTICASTFORWTBL = 0x1b,
    IBIS_IB_ATTR_SMP_LINKSPEEDWIDTHPAIRSTBL = 0x1c,
    IBIS_IB_ATTR_SMP_VENDORMADSTBL = 0x1d,
    IBIS_IB_ATTR_SMP_SMINFO = 0x20,
    IBIS_IB_ATTR_SMP_PORT_INFO_EXTENDED = 0x33,
    /* Mellanox vendor specific MADS */
    IBIS_IB_ATTR_SMP_PLFT_INFO = 0xff10,   /* PrivateLFTInfo attr */
    IBIS_IB_ATTR_SMP_PLFT_DEF = 0xff11,    /* PrivateLFTDef attr */
    IBIS_IB_ATTR_SMP_PLFT_MAP = 0xff12,    /* PrivateLFTMap attr */
    IBIS_IB_ATTR_SMP_PORT_SL_TO_PLFT_MAP = 0xff14,  /* PortSLToPrivateLFTMapT attr */
    IBIS_IB_ATTR_SMP_VS_GENERAL_INFO = 0xff17,  /*  General info */
    IBIS_IB_ATTR_SMP_AR_INFO = 0xff20,      /* AdaptiveRoutingInfo attr */
    IBIS_IB_ATTR_SMP_AR_GROUP_TABLE = 0xff21,  /* ARGroupTable attr */
    IBIS_IB_ATTR_SMP_AR_LINEAR_FORWARDING_TABLE = 0xff22, /* ARLinearFowardingTable attr */
    IBIS_IB_ATTR_SMP_AR_LINEAR_FORWARDING_TABLE_SX = 0xff23, /* ARLinearFowardingTableSX attr */
    IBIS_IB_ATTR_SMP_TEMP_SENSING = 0xff40,  /* TemperatureSensing attr */
    IBIS_IB_ATTR_SMP_QOS_CONFIG_SL = 0xff82,  /* QosConfigSL attr */
    IBIS_IB_ATTR_SMP_MLNXEXTPORTINFO = 0xff90,            /* Extended port info */
    IBIS_IB_ATTR_SMP_EXTENDED_SWITCH_INFO = 0xff91,  /* ExtendedSwitchInfo attr */
    IBIS_IB_ATTR_SMP_VIRTUALIZATION_INFO = 0xffb0,  /* ExtendedSwitchInfo attr */
    IBIS_IB_ATTR_SMP_VPORT_INFO = 0xffb1,  /* ExtendedSwitchInfo attr */
    IBIS_IB_ATTR_SMP_VPORT_STATE = 0xffb3,  /* ExtendedSwitchInfo attr */
    IBIS_IB_ATTR_SMP_VNODE_INFO = 0xffb2,
    IBIS_IB_ATTR_SMP_VNODE_DESC = 0xffb4,
    IBIS_IB_ATTR_SMP_VPORT_PKEY_TBL = 0xffb6,
    IBIS_IB_ATTR_SMP_RN_GEN_STRING_TABLE  = 0xffb8,       /* RNGenStringTable attr */
    IBIS_IB_ATTR_SMP_RN_RCV_STRING = 0xffb9,              /* RNRcvString attr */
    IBIS_IB_ATTR_SMP_RN_SUB_GROUP_DIRECTION_TABLE = 0xffba, /* RNSubGroupDirectionTable attr */
    IBIS_IB_ATTR_SMP_RN_XMIT_PORT_MASK = 0xffbc,          /* RNXmitPortMask attr */
    IBIS_IB_ATTR_SMP_AR_GROUP_TABLE_COPY = 0xffbd,        /* AdaptiveRoutingGroupTableCopy attr */
    IBIS_IB_ATTR_SMP_RN_GEN_BY_SUB_GROUP_PRIORITY = 0xffbe, /* RNGenBySubGroupPriority attr */
    IBIS_IB_ATTR_SMP_ROUTER_INFO = 0xffd0,                  /* RouterInfo attr */
    IBIS_IB_ATTR_SMP_RTR_NEXT_HOP_TABLE = 0xffd1,           /* Routers NextHopTable */
    IBIS_IB_ATTR_SMP_RTR_ADJ_SITE_LOCAL_SUBNETS_TABLE = 0xffd2, /* Routers AdjacentSiteLocalSubnetsTable */
    IBIS_IB_ATTR_SMP_LAST
};

enum PERFORMANCE_MANAGEMENT_ATTR_ID {
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_SAMPLES_CONTROL = 0x10,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_SAMPLES_RESULT = 0x11,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_COUNTERS = 0x12,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_RCV_ERROR_DETAILS = 0x15,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_XMIT_DISCARD_DETAILS = 0x16,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_COUNTERS_EXT = 0x1D,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_EXT_SPEEDS_COUNTERS = 0x1F,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_XMIT_DATA_SL = 0x36,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_RCV_DATA_SL = 0x37,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_XMIT_DATA_SL_EXT = 0x38,
    IBIS_IB_ATTR_PERF_MANAGEMENT_PORT_RCV_DATA_SL_EXT = 0x39,
    IBIS_IB_ATTR_PERF_MANAGEMENT_LAST
};

enum AGGREGATION_MANAGEMENT_ATTR_ID {
    IBIS_IB_ATTR_AM_AN_INFO = 0x20,
    IBIS_IB_ATTR_AM_QP_ALLOCATION = 0x21,
    IBIS_IB_ATTR_AM_QPC_CONFIG = 0x22,
    IBIS_IB_ATTR_AM_TREE_CONFIG = 0x23,
    IBIS_IB_ATTR_AM_QUOTA_CONFIG = 0x24,
    IBIS_IB_ATTR_AM_RESOURCE_CLEANUP = 0x40,
    IBIS_IB_ATTR_AM_PERFORMANCE_COUNTERS = 0x50
};

enum VENDOR_MELLANOX_ATTR_ID {
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_GENERAL_INFO = 0x17,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_DATA_VL = 0x60,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_DATA_VL = 0x61,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_PKT_VL = 0x62,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_PKT_VL = 0x63,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_LLR_STATISTICS = 0x68,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_DATA_VL_EXT = 0x73,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_DATA_VL_EXT = 0x74,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RCV_PKT_VL_EXT = 0x75,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_PKT_VL_EXT = 0x76,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_XMIT_WAIT_VL_EXT = 0x77,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_DIAGNOSTIC_COUNTERS = 0x78,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_PORT_RN_COUNTERS = 0x82,
    IBIS_IB_ATTR_VENDOR_SPEC_MELLANOX_LAST
};

enum CONGESTION_CONTROL_ATTR_ID {
    IBIS_IB_ATTR_CONGESTION_CONT_CONG_INFO = 0x11,
    IBIS_IB_ATTR_CONGESTION_CONT_CONG_KEY_INFO = 0x12,
	IBIS_IB_ATTR_CONGESTION_CONT_CONG_LOG = 0x13,
	IBIS_IB_ATTR_CONGESTION_CONT_SW_CONG_SETTING = 0x14,
	IBIS_IB_ATTR_CONGESTION_CONT_SW_PORT_CONG_SETTING = 0x15,
	IBIS_IB_ATTR_CONGESTION_CONT_CA_CONG_SETTING = 0x16,
	IBIS_IB_ATTR_CONGESTION_CONT_CC_TBL = 0x17,
	IBIS_IB_ATTR_CONGESTION_CONT_TIME_STAMP = 0x18,
	IBIS_IB_ATTR_CONGESTION_CONT_LAST
};

enum IB_ATTR_ID {
	IBIS_IB_ATTR_CLASS_PORT_INFO = 0x1,
	IBIS_IB_ATTR_NOTICE = 0x2,
	IBIS_IB_ATTR_LAST
};


/****************************************************/
/* log Macros */
#define IBIS_LOG_MSG_SEND_MAD       true
#define IBIS_LOG_MSG_RECEIVED_MAD   false

#define IBIS_LOG(level, fmt, ...) \
    Ibis::GetLogMsgFunction()(__FILE__, __LINE__, __FUNCTION__, \
                             level, fmt, ## __VA_ARGS__)

#define IBIS_ENTER  IBIS_LOG(TT_LOG_LEVEL_FUNCS, "%s: [\n", __FUNCTION__)
#define IBIS_EXIT   IBIS_LOG(TT_LOG_LEVEL_FUNCS, "%s: ]\n", __FUNCTION__)

#define IBIS_RETURN(rc)  { IBIS_EXIT; \
                           return (rc); }
#define IBIS_RETURN_VOID { IBIS_EXIT; \
                           return; }

#define CSV_LOG(level, fmt, ...) \
    CsvParser::GetLogMsgFunction()(__FILE__, __LINE__, __FUNCTION__, \
                             level, fmt, ## __VA_ARGS__)

#endif          /* not defined IBIS_TYPES_H_ */
