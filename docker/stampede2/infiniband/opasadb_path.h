/* BEGIN_ICS_COPYRIGHT2 ****************************************

Copyright (c) 2015, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

** END_ICS_COPYRIGHT2   ****************************************/

/* [ICS VERSION STRING: @(#) ./opasadb/opasadb_path.h 10_6_1_0_2 [10/25/17 20:34] */

#if !defined(_OPA_SA_DB_PATH_H)

#define _OPA_SA_DB_PATH_H

#include <linux/types.h>
#include <verbs.h>
#include <errno.h>

#define OPA_SA_DB_PATH_API_VERSION 3
												
/*
 * Definitions for various bit fields used in the path record.
 */
#define OP_PATH_REC_SL_MASK                     0x000F
#define OP_PATH_REC_QOS_CLASS_MASK              0xFFF0
#define OP_PATH_REC_SELECTOR_MASK               0xC0
#define OP_PATH_REC_BASE_MASK                   0x3F
#define OP_PATH_RECORD_RATE_2_5_GBS             2
#define OP_PATH_RECORD_RATE_10_GBS              3
#define OP_PATH_RECORD_RATE_30_GBS              4
#define OP_PATH_RECORD_RATE_5_GBS               5
#define OP_PATH_RECORD_RATE_20_GBS              6
#define OP_PATH_RECORD_RATE_40_GBS              7
#define OP_PATH_RECORD_RATE_60_GBS              8
#define OP_PATH_RECORD_RATE_80_GBS              9
#define OP_PATH_RECORD_RATE_120_GBS             10
#define OP_MIN_RATE OP_PATH_RECORD_RATE_2_5_GBS
#define OP_MAX_RATE OP_PATH_RECORD_RATE_120_GBS

#define OP_PATH_REC_MTU(p_rec) ((uint8_t) (p_rec->mtu & OP_PATH_REC_BASE_MASK))
#define OP_PATH_REC_SL(p_rec) ((uint8_t)(ntohs(p_rec->qos_class_sl) & OP_PATH_REC_SL_MASK))
#define OP_PATH_REC_HOP_LIMIT(p_rec) ((uint8_t) (ntohl(p_rec->hop_flow_raw) & 0x000000FF))
#define OP_PATH_REC_FLOW_LBL(p_rec) (((ntohl(p_rec->hop_flow_raw) >> 8) & 0x000FFFFF))
#define OP_PATH_REC_NUM_PATH(p_rec) (p_rec->num_path & 0x7F)
#define OP_PATH_REC_QOS_CLASS(p_rec) (htons(p_rec->qos_class_sl) >> 4)
#define OP_PATH_REC_RATE(p_rec) ((uint8_t) (p_rec->rate & OP_PATH_REC_BASE_MASK))
#define OP_PATH_REC_PKT_LIFE(p_rec) ((uint8_t) (p_rec->pkt_life & OP_PATH_REC_BASE_MASK))

#ifndef ntoh64
	#define ntoh64( x ) ( (((x) & 0x00000000000000FF) << 56)  |     \
		(((x) & 0x000000000000FF00) << 40)  |   \
		(((x) & 0x0000000000FF0000) << 24)  |   \
		(((x) & 0x00000000FF000000) << 8 )  |   \
		(((x) & 0x000000FF00000000) >> 8 )  |   \
		(((x) & 0x0000FF0000000000) >> 24)  |   \
		(((x) & 0x00FF000000000000) >> 40)  |   \
		(((x) & 0xFF00000000000000) >> 56) )
	#define hton64              ntoh64
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Definition for a gid which is always maintained in network order (NO) */
typedef union _IB_GID_NO {
	uint8_t	Raw[16];
	union _IB_GID_TYPE_NO {
		struct {
			uint64_t SubnetPrefix;
			uint64_t InterfaceID;
		} Global;
	} Type;
}  __attribute__((packed)) IB_GID_NO;

/* Definition for a pathrecord which is always maintained in network order (NO) */
typedef struct _IB_PATH_RECORD_NO {
	uint64_t      ServiceID;
	IB_GID_NO   DGID;				/* Destination GID */
	IB_GID_NO   SGID;				/* Source GID */
	uint16_t      DLID;				/* Destination LID */
	uint16_t      SLID;				/* Source LID */

	/* DO NOT ACCESS THESE FIELDS DIRECTLY ON LE SYSTEMS */
	union _u1 {
		uint32_t AsReg32;
		struct {
#if CPU_BE
			uint32_t      RawTraffic  :1; /* 0 for IB Packet (P_Key must be valid) */
                                        /* 1 for Raw Packet (No P_Key) */
			uint32_t      Reserved    :3;
			uint32_t      FlowLabel   :20;/* used in GRH		 */
			uint32_t      HopLimit    :8; /* Hop limit used in GRH */
#else
			uint32_t      HopLimit    :8; /* Hop limit used in GRH */
			uint32_t      FlowLabel   :20;/* used in GRH		 */
			uint32_t      Reserved    :3;
			uint32_t      RawTraffic  :1; /* 0 for IB Packet (P_Key must be valid) */
                                        /* 1 for Raw Packet (No P_Key) */
#endif
		} __attribute__((packed)) s;
	} u1;

	uint8_t       TClass;             /* Traffic Class used in GRH */
#if CPU_BE
	uint8_t       Reversible  :1;
	uint8_t       NumbPath    :7;     /* Max number of paths to (be) return(ed) */
#else /* CPU_BE */
	uint8_t       NumbPath    :7;     /* Max number of paths to (be) return(ed) */
	uint8_t       Reversible  :1;
#endif /* CPU_BE */
	uint16_t      P_Key;              /* Partition Key for this path */

	/* DO NOT ACCESS THESE FIELDS DIRECTLY ON LE SYSTEMS */
	union _u2 {
		uint16_t AsReg16;
		struct {
#if CPU_BE
			uint16_t      QosType     : 2;
			uint16_t      Reserved2   : 2;
			uint16_t      QosPriority : 8;
			uint16_t      SL          : 4;
#else
			uint16_t      SL          : 4;
			uint16_t      QosPriority : 8;
			uint16_t      Reserved2   : 2;
			uint16_t      QosType     : 2;
#endif
		} __attribute__((packed)) s;
	} u2;

#if CPU_BE
	uint8_t       MtuSelector :2;     /* enum IB_SELECTOR */
	uint8_t       Mtu         :6;     /* enum IB_MTU */
#else
	uint8_t       Mtu         :6;     /* enum IB_MTU */
	uint8_t       MtuSelector :2;     /* enum IB_SELECTOR */
#endif

#if CPU_BE
	uint8_t       RateSelector:2;     /* enum IB_SELECTOR */
	uint8_t       Rate        :6;     /* enum IB_STATIC_RATE */
#else
	uint8_t       Rate        :6;     /* enum IB_STATIC_RATE */
	uint8_t       RateSelector:2;     /* enum IB_SELECTOR */
#endif

	/* ***************************************** */
	/* *** User be aware that the CM LifeTime & */
	/* *** TimeOut values are only 5-bit wide. */
	/* ***************************************** */
	/* */
	/* Accumulated packet life time for the path specified by an enumeration  */
	/* deried from 4.096 usec * 2^PktLifeTime */
#if CPU_BE
	uint8_t       PktLifeTimeSelector:2;  /* enum IB_SELECTOR */
	uint8_t       PktLifeTime :6;
#else
	uint8_t       PktLifeTime :6;
	uint8_t       PktLifeTimeSelector:2;  /* enum IB_SELECTOR */
#endif

	uint8_t       Preference; /* 1.1 specific. see page 800 of volume 1 */
	uint8_t       Reserved2 [6];
} __attribute__((packed)) IB_PATH_RECORD_NO;

#if CPU_BE
#define RAW_TRAFFIC(x) x.s.RawTraffic
#define FLOW_LABEL(x) x.s.FlowLabel
#define HOP_LIMIT(x) x.s.HopLimit

#define QOS_TYPE(x) x.s.QosType
#define QOS_PRIORITY(x) x.s.QosPriority
#define SL(x) x.s.SL
#else
#define RAW_TRAFFIC(x) (((union _u1)(ntohl(x.AsReg32))).s.RawTraffic)
#define FLOW_LABEL(x) (htons(((union _u1)(ntohl(x.AsReg32))).s.FlowLabel))
#define HOP_LIMIT(x) (((union _u1)(ntohl(x.AsReg32))).s.HopLimit)

#define QOS_TYPE(x) (((union _u2)(ntohs(x.AsReg16))).s.QosType)
#define QOS_PRIORITY(x) (((union _u2)(ntohs(x.AsReg16))).s.QosPriority)
#define SL(x) (((union _u2)(ntohs(x.AsReg16))).s.SL)
#endif

/*
 * There's no "standard" place to define path records in OPENIB/OFED
 * so we do it here.
 *
 * All fields are assumed to be in network byte order.
 */
typedef union _op_gid {
    uint8_t raw[16];
    struct _op_gid_unicast {
        uint64_t prefix;
        uint64_t interface_id;

    } __attribute__((packed)) unicast;

    struct _op_gid_multicast {
        uint8_t header[2];
        uint8_t raw_group_id[14];

    } __attribute__((packed)) multicast;

} __attribute__((packed)) op_gid_t;

typedef struct _op_path_rec {
    uint64_t service_id;
    op_gid_t dgid;
    op_gid_t sgid;
    uint16_t dlid;
    uint16_t slid;
    uint32_t hop_flow_raw;
    uint8_t tclass;
    uint8_t num_path;
    uint16_t pkey;
    uint16_t qos_class_sl;
    uint8_t mtu;
    uint8_t rate;
    uint8_t pkt_life;
    uint8_t preference;
    uint8_t resv2[6];

} __attribute__((packed)) op_path_rec_t;

/*
 * Convenience function. Given the name of an HFI,
 * returns the ibv_device structure associated with it.
 * Returns NULL if the HFI could not be found.
 *
 * OPENS THE HFI! Use ibv_close_device() to release it.
 *
 * Input:
 * name: the name of the HFI, or NULL.
 *
 * Output:
 * Returns a pointer to the opened HFI. Use ibv_close_device() to free it.
 * device: will contain a pointer to the info structure for the device.
 * DO NOT FREE THIS - it will be freed when op_path_close() is called.
 *
 * Sets errno on failure.
 */ 
struct ibv_context *op_path_find_hfi(const char *name, 
								    struct ibv_device **device);

/*
 * Opens the interface to the opp module.
 * Must be called before any use of the path functions.
 *
 * device       The verbs context for the HFI.
 *              Can be acquired via op_path_find_hfi.
 *
 * port_num     The port to use for sending queries.
 *
 * This information is used for querying pkeys and
 * calculating timeouts.
 *
 * Returns a pointer to the USA context on success, or returns NULL 
 * and sets errno if the device could not be opened.
 */
void *op_path_open(struct ibv_device *device, int port_num);

/*
 * Closes the interface to the opp module.
 * No path functions will work after calling this function.
 */
void op_path_close(void *context);

/*
 * Retrieves an IB Path Record given a particular query.
 *
 * context		A handle to the interface to query over.
 *
 * query		The path record to use for asking the query.
 *				All fields should be zero'ed out except for
 *				those being used to query! For example,
 *				a simple query might specify the source lid,
 *				the destination lid and a pkey. All fields should
 *				be in network byte order.
 * 
 * response		The path record where the completed path will
 *				be written. All fields are in network byte order.
 *
 * RETURN VAL:	This function will return a value of 0 on success,
 *				or non-zero on error.
 */
int op_path_get_path_by_rec(void *context,
					op_path_rec_t *query, 
					op_path_rec_t *response);

/*
 * Retrieves an IB Path Record to a given destination.
 *
 * op_path_context	A handle to the interface to query over.
 *
 * hfi_context	A handle to the HFI that will be used for
 *				this path. 
 *
 * port			The local port number that will be used 
 *				for this path. (not the lid.)
 *
 * dgid			The destination GID.
 *
 * pkey			The desired pkey. This should be zero to
 *				accept the default.
 *
 * response		The path record where the completed path will
 *				be written. All fields are in network byte order.
 *
 * RETURN VAL:	This function will return a value of 0 on success,
 *				or non-zero on error.
 */
int op_path_get_path_to_dgid(void *op_path_context,
							uint16_t pkey,
							union ibv_gid dgid,
							op_path_rec_t *response);

/*
 * Converts a pkey to a pkey index, which is needed by the queue pairs.
 *
 * Returns 0 on success, non-zero on error.
 */
int op_path_find_pkey(void *op_path_context, uint16_t pkey, uint16_t *pkey_index);

/*
 * Given an HFI and the packet life time from a path record, compute the packet lifetime
 * for a queue pair.
 */
uint8_t op_path_compute_timeout(struct ibv_context *hfi_context, 
								uint8_t pkt_life);

/*
 * Fills out a qp_attr structure and its mask based on the contents
 * of a path record and an optional alternate path.
 *
 * alt_path	and alt_context can be null. In that case, no alternate path 
 * will be set.
 *
 * Returns a mask listing the attributes that have been set. Returns 0 
 * on error and sets errno.
 */
unsigned op_path_qp_attr(struct ibv_qp_attr *qp_attr,
						void *context,
					    op_path_rec_t *primary_path,
						void *alt_context,
					    op_path_rec_t *alt_path);

/*
 * Returns the API version the path functions.
 */
unsigned op_path_check_version(void);

#ifdef __cplusplus
};
#endif

#endif /* _OPA_SA_DB_PATH_H */
