
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2010-2011, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */
 

/***
         *** This file was generated at "2018-10-14 17:18:55"
         *** by:
         ***    > /mswg/release/tools/a-me/a-me-1.0.96/adabe_plugins/adb2c/adb2pack.py --input adb/packets.adb --file-prefix packets
         ***/
#ifndef PACKETS_LAYOUTS_H
#define PACKETS_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 52 */
struct AM_ANInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Endianness, Controls the aggregation node endianness: 1: BIG_ENDIAN 0: LITTLE_ENDIAN */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t endianness;
	/* Description - Enable bit for per job endianess: 0: GLOBAL_MODE 1: PER_JOB */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t enable_endianness_per_job;
	/* Description - Reproducibilty, 0: ENABLED, 1: DISABLED */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t reproducibility_disable;
	/* Description - Enable bit for per job reproducibility: 0: GLOBAL_MODE 1: PER_JOB */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t enable_reproducibility_per_job;
	/* Description - Allowed class version for all MADs in mgmt class 0xB */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t active_class_version;
	/* Description - When set, the device supports half buffer line optimization. Halfbuffer line optimization is for case when data size is less than or equal to half of the buffer line size which results in half the buffer to be utilized */
	/* 0x0.24 - 0x0.24 */
	 u_int8_t half_buffer_line_optimization_supported;
	/* Description - When set, the device supports sharp reproducibility per job option */
	/* 0x0.25 - 0x0.25 */
	 u_int8_t reproducibility_per_job_supported;
	/* Description - When set, the device supports the ability to disable reproducibility */
	/* 0x0.26 - 0x0.26 */
	 u_int8_t reproducibility_disable_supported;
	/* Description - capability bit. if set, the root gid is used in group join flow */
	/* 0x0.27 - 0x0.27 */
	 u_int8_t root_gid_group_join;
	/* Description - When set, the device supports the option for both requester/responder packet_based_credits */
	/* 0x0.28 - 0x0.28 */
	 u_int8_t packet_based_credits_supported;
	/* Description - When set, the device supports endianess per job option */
	/* 0x0.29 - 0x0.29 */
	 u_int8_t endianess_per_job_supported;
	/* Description - When set, the device supports more than 1 active SHArP version at a time */
	/* 0x0.30 - 0x0.30 */
	 u_int8_t multiple_sver_active_supported;
	/* Description - When set, the device supports streaming aggregation */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t streaming_aggregation_supported;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Tree Table Size
Maximum number of trees supported by the aggregation node */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t tree_table_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Tree Radix
Maximum number of children in a tree */
	/* 0x8.0 - 0x8.7 */
	 u_int8_t tree_radix;
	/* Description - Tree Radix Used
The maximum radix used in the system. Used to calculate buffer 
utilization per operation. (Default = 
tree_radix
) */
	/* 0x8.16 - 0x8.23 */
	 u_int8_t tree_radix_used;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - SHArP version supprted bit mask: Bit 0 - sver[0] is not supported; Bit k[1-15] - sver[k] is supported */
	/* 0xc.0 - 0xc.15 */
	 u_int16_t sharp_version_supported_bit_mask;
	/* Description - SHArP version active bit mask: Bit 0 - sver[0] is not active; Bit k[1-15] - sver[k] is active */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t active_sharp_version_bit_mask;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Group Table Size
Maximum number of groups supported by the aggregation node */
	/* 0x10.0 - 0x10.23 */
	 u_int32_t group_table_size;
	/* Description - Group Table Mode Support
Bit 0: TABLE
Bit 1: CACHE */
	/* 0x10.28 - 0x10.31 */
	 u_int8_t gt_mode;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Maximum valid group number. Value of 0 is 0xffff */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t max_group_num;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Outstanding Operation Table Size
Maximum number of outstanding operations supported by the 
aggregation node */
	/* 0x18.0 - 0x18.15 */
	 u_int16_t outstanding_operation_table_size;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Num of demaphores supported by AN for streaming aggregation */
	/* 0x1c.0 - 0x1c.7 */
	 u_int8_t num_semaphores;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Operation Buffer Size */
	/* 0x20.0 - 0x20.23 */
	 u_int32_t operation_buffer_size;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Number of jobs supported by the aggregation node. Value of 0 is equal to 256 */
	/* 0x24.0 - 0x24.23 */
	 u_int32_t num_of_jobs;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Maximum number of QPs supported by the Aggregation Node */
	/* 0x28.0 - 0x28.15 */
	 u_int16_t max_num_qps;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Line size in bytes. Value of 0 means 32 bytes */
	/* 0x2c.0 - 0x2c.15 */
	 u_int16_t line_size;
	/* Description - Non aligned operand tag effected number of lines in worst case. Value of 0 means no penalty */
	/* 0x2c.16 - 0x2c.23 */
	 u_int8_t worst_case_num_lines;
	/* Description - Number of buffer lines in chunk mode
0: tree_radix / 2, rounded up to an even value. Minimum value is 8 regardless of tree_radix.
1: 2 lines
2-15: Reserved */
	/* 0x2c.28 - 0x2c.31 */
	 u_int8_t num_lines_chunk_mode;
};

/* Description -   */
/* Size in bytes - 16 */
struct AM_GroupJoin {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tree Identifier */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t tree_id;
	/* Description - Operation
0: GROUP_JOIN
1: GROUP_LEAVE */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Group ID */
	/* 0x4.0 - 0x4.23 */
	 u_int32_t group_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - QP Number (remote QP number <parent QPn>)
The QP Number to add / remove from the group */
	/* 0xc.0 - 0xc.23 */
	 u_int32_t qpn;
};

/* Description -   */
/* Size in bytes - 64 */
struct AM_QPCConfig {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - QP Number */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t qpn;
	/* Description - QP State
0: 
DISABLED
 - QP is disabled.
1: 
ACTIVE
 - QP is active and ready to send and receive packets
2: 
ERROR */
	/* 0x0.28 - 0x0.31 */
	 u_int8_t state;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - QP bit of credit mode of requester side to support streaming aggregation */
	/* 0x4.0 - 0x4.0 */
	 u_int8_t packet_based_credit_req_en;
	/* Description - QP bit of credit mode of responder side to support streaming aggregation */
	/* 0x4.1 - 0x4.1 */
	 u_int8_t packet_based_credit_resp_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Global Header Exists */
	/* 0x8.16 - 0x8.16 */
	 u_int8_t g;
	/* Description - Transport Service
0: RC - Reliable Connection
1: UC - Unreliable Connection
 
2: RD - Reliable Datagram
 
3: UD - Unreliable Datagram
4: DC - Dynamically Connected */
	/* 0x8.24 - 0x8.27 */
	 u_int8_t ts;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.15 */
	 u_int16_t rlid;
	/* Description - Service Level */
	/* 0xc.20 - 0xc.23 */
	 u_int8_t sl;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Hop Limit */
	/* 0x10.0 - 0x10.7 */
	 u_int8_t hop_limit;
	/* Description -  */
	/* 0x10.20 - 0x10.27 */
	 u_int8_t traffic_class;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Remote GID */
	/* 0x14.0 - 0x20.31 */
	 u_int32_t rgid[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The transport Packet Sequence Number at which the remote node (rela
tive to the receiver of the QPCConfig message) shall begin transmitting
over the newly established channel. This value should be chosen to min
imize the chance that a packet from a previous connection could fall 
within the valid PSN window. */
	/* 0x24.0 - 0x24.23 */
	 u_int32_t rq_psn;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The transport Packet Sequence Number at which the local node (relative 
to the receiver of the QPCConfig message) shall begin transmitting
over the newly established channel. This value should be chosen to min
imize the chance that a packet from a previous connection could fall 
within the valid PSN window. */
	/* 0x28.0 - 0x28.23 */
	 u_int32_t sq_psn;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - P_Key */
	/* 0x2c.0 - 0x2c.15 */
	 u_int16_t pkey;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Remote QPn */
	/* 0x30.0 - 0x30.23 */
	 u_int32_t rqpn;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - RNR Retry Limit
The total number of times that the sender wishes the receiver to retry 
RNR NAK errors before posting a completion error. */
	/* 0x38.0 - 0x38.7 */
	 u_int8_t rnr_retry_limit;
	/* Description - RNR Mode
0: SHArP level resources does not apply for RNR. If a SHArP level 
resource is missing, the request will be acknowledged at the IB transport 
layer (but will not be handled at the SHArP layer). 
1: SHArP level resources apply to the IB transport RNR NACK. If 
SHArP resources are missing, the responder will discard the request and 
send an RNR NACK to the requester. */
	/* 0x38.28 - 0x38.29 */
	 u_int8_t rnr_mode;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Timeout Retry Limit
The total number of times that the sender wishes the receiver to retry 
timeout, packet sequence, etc. errors before posting a completion error. */
	/* 0x3c.0 - 0x3c.7 */
	 u_int8_t timeout_retry_limit;
	/* Description - Timeout Retry Limit
Value representing the transport (ACK) timeout for use by the remote, 
expressed as (4.096   S*2Local ACK Timeout). */
	/* 0x3c.16 - 0x3c.23 */
	 u_int8_t local_ack_timeout;
};

/* Description -   */
/* Size in bytes - 48 */
struct AM_QuotaConfig {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Job Identifier
Unique identifier of a job. */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t job_id;
	/* Description - Opcod
e
1
: SET_QUOTA - Set a quota for the job
2: EDIT_QUOTA - Edit job's quota. Reducing job's quota might 
fail if resources are currently in use
. */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t opcode;
	/* Description - Controls the aggregation node endianness for this job
0: default global configuration
1:LITTLE ENDIAN
2:BIG ENDIAN
Must be zero when ANInfo:enable_endianness_per_job is 0 */
	/* 0x0.29 - 0x0.30 */
	 u_int8_t endianness;
	/* Description - Root
Indicates this aggregation node is the root of the tree for a spe
cific job. This bit is used for GroupJoin operations, to save going 
all the way to the tree root. */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t r;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Tree Identifier
Note that in Switch-IB2, the quotas are configured globaly and 
not per tree. Quota must be valid for all tree IDs and should not 
change unless editing the quota. */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t tree_id;
	/* Description - Controls the AN reproducibility mode for this job, valid only when ANInfo reproducibility_per_job is 1 */
	/* 0x4.24 - 0x4.24 */
	 u_int8_t job_is_reproducible;
	/* Description - Prevent streaming aggregation lock per job */
	/* 0x4.31 - 0x4.31 */
	 u_int8_t prevent_lock;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Max OST
Maximum Outstanding Operations allowed for the specific job */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t max_ost;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Max Buffer */
	/* 0x10.0 - 0x10.23 */
	 u_int32_t max_buffer;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Maximum Groups
The maximum number of groups allowed for the job */
	/* 0x18.0 - 0x18.15 */
	 u_int16_t max_groups;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Unreliable Datagram QP Number - A UD QP allocated for     the job to enable unreliable Multicast distribution of the result */
	/* 0x24.0 - 0x24.23 */
	 u_int32_t ud_qpn;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Maximum Groups
The maximum number of 
QPs a
llowed for the job */
	/* 0x28.0 - 0x28.15 */
	 u_int16_t max_qps;
};

/* Description -   */
/* Size in bytes - 16 */
struct AM_ResourceCleanup {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tree Identifier */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t tree_id;
	/* Description - Operatio
n
1
: 
CLEAN_JOB - Clean all resources used by the job.
2: CLEAN_TREE - Clean all resources used on the tree (for all 
jobs)
3: CLEAN_JOB_TREE - Clean all resources used on the tree that 
belongs to the job including QPs (leaf), quota etc.
5: CLEAN_ALL - Resets the Aggregation Node (including all 
QPs) */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Group ID */
	/* 0x4.0 - 0x4.23 */
	 u_int32_t group_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Job I
D */
	/* 0x8.0 - 0x8.7 */
	 u_int8_t job_id;
};

/* Description -   */
/* Size in bytes - 16 */
struct AM_ResourceCleanup_V2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tree Identifier */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t tree_id;
	/* Description - Operatio
n
1
: 
CLEAN_JOB - Clean all resources used by the job.
2: CLEAN_TREE - Clean all resources used on the tree (for all 
jobs)
3: CLEAN_JOB_TREE - Clean all resources used on the tree that 
belongs to the job including QPs (leaf), quota etc.
5: CLEAN_ALL - Resets the Aggregation Node (including all 
QPs) */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Group Num */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t group_num;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Job ID */
	/* 0x8.0 - 0x8.23 */
	 u_int32_t job_id;
};

/* Description -   */
/* Size in bytes - 8 */
struct AdjSiteLocalSubnetRecord {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t SubnetPrefix;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t Pkey;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t MasterSMLID;
};

/* Description -   */
/* Size in bytes - 192 */
struct AggregationManagement_MAD_Data_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xbc.31 */
	 u_int32_t DWORD[48];
};

/* Description -   */
/* Size in bytes - 4 */
struct BandwidthPerSL {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.19 */
	 u_int32_t RateLimit;
	/* Description -  */
	/* 0x0.20 - 0x0.31 */
	 u_int16_t BandwidthShare;
};

/* Description -   */
/* Size in bytes - 8 */
struct CACongestionEntryListElement {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When the CCTI is equal to this value, an event is logged in the CAs cyclic event log. */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t Trigger_Threshold;
	/* Description - The number to be added to the table Index (CCTI) on the receipt of a BECN. */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t CCTI_Increase;
	/* Description - When the timer expires it will be reset to its specified value, and 1 will be decremented from the CCTI. */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t CCTI_Timer;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The minimum value permitted for the CCTI. */
	/* 0x4.24 - 0x4.31 */
	 u_int8_t CCTI_Min;
};

/* Description -   */
/* Size in bytes - 2 */
struct CCTI_Entry_ListElement {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - This is the multiplier used when calculating the injection rate delay */
	/* 0x0.0 - 0x0.13 */
	 u_int16_t CCT_Multiplier;
	/* Description - This is the shift value used when calculating the injection rate delay */
	/* 0x0.14 - 0x0.15 */
	 u_int8_t CCT_Shift;
};

/* Description -   */
/* Size in bytes - 4 */
struct CC_CongestionInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - CA only - Number of 64 entry block in CCT  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t ControlTableCap;
	/* Description - Bit0 - 1: Switch support Creadit Starvation, Bit0 - 0: Switch doesn't support CS */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t CongestionInfo;
};

/* Description -   */
/* Size in bytes - 32 */
struct CC_Log_Data_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	 u_int32_t DWORD[8];
};

/* Description -   */
/* Size in bytes - 192 */
struct CC_Mgt_Data_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xbc.31 */
	 u_int32_t DWORD[48];
};

/* Description -   */
/* Size in bytes - 4 */
struct CC_SwitchCongestionSetting_Control_Map {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t Marking_RateIsValid;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t CS_ThresholdAndCS_ReturnDelayIsValid;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t ThresholdAndPacket_SizeIsValid;
	/* Description -  */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t Credit_MaskIsValid;
	/* Description -  */
	/* 0x0.4 - 0x0.4 */
	 u_int8_t Victim_MaskIsValid;
};

/* Description -   */
/* Size in bytes - 4 */
struct CC_TimeStamp {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Free running clock that provieds relative time infomation for a device. Time is kept in 1.024 usec units. */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t TimeStamp;
};

/* Description -   */
/* Size in bytes - 12 */
struct CongestionEntryListSwitchElement {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Destination lid of congestion event */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t DLID;
	/* Description - Source lid of congestion event */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t SLID;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Service level of congestion event */
	/* 0x4.28 - 0x4.31 */
	 u_int8_t SL;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Time stamp of congestion event */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t Timestamp;
};

/* Description -   */
/* Size in bytes - 16 */
struct CongestionLogEventListCAElement {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local QP that reached CN Threshold. Set to zero if port threshold reached. */
	/* 0x0.8 - 0x0.31 */
	 u_int32_t Local_QP_CN_Entry;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Service Type of local QP: 0 - RC, 1 - UC, 2 - RD, 3 - UD */
	/* 0x4.0 - 0x4.3 */
	 u_int8_t Service_Type_CN_Entry;
	/* Description - Service Level associated with local QP */
	/* 0x4.4 - 0x4.7 */
	 u_int8_t SL_CN_Entry;
	/* Description - Remote QP that is connected to local QP. Set to zero for datagram QPs. */
	/* 0x4.8 - 0x4.31 */
	 u_int32_t Remote_QP_Number_CN_Entry;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - LID of remote port that is connected to local QP. Set to zero for datagram service. */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t Remote_LID_CN_Entry;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Time stamp of congestion event */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t Timestamp;
};

/* Description -  generic buffer */
/* Size in bytes - 216 */
struct DataBuffer {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xd8.23 */
	 u_int8_t data[216];
};

/* Description -   */
/* Size in bytes - 64 */
struct DirRPath_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x40.23 */
	 u_int8_t BYTE[64];
};

/* Description -   */
/* Size in bytes - 16 */
struct GID_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	 u_int32_t DWord[4];
};

/* Description -  General Info Capability Mask field set */
/* Size in bytes - 16 */
struct GeneralInfoCapabilityMask {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t capability0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t capability1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t capability2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t capability3;
};

/* Description -  HW Info */
/* Size in bytes - 32 */
struct HWInfo_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t DeviceID;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t DeviceHWRevision;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reserved */
	/* 0x4.0 - 0x18.31 */
	 u_int32_t Reserved_Dword[6];
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time (in sec) since last reset */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t UpTime;
};

/* Description -  ACK Extended Transport Header */
/* Size in bytes - 4 */
struct IB_AETH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicates the sequence number of the last message completed at the responder. Remote Key that authorizes access to the remote virtual address */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t MSN;
	/* Description - Indicates if this is an ACK or NAK packet plus additional information about the ACK or NAKRemote virtual address */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Syndrome;
};

/* Description -  Datagram Extended Transport Header */
/* Size in bytes - 8 */
struct IB_DETH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Queue Key */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t Q_Key;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Source QP */
	/* 0x4.0 - 0x4.23 */
	 u_int32_t SrcQP;
	/* Description - TX - 0, RX - ignore */
	/* 0x4.24 - 0x4.31 */
	 u_int8_t Rsv8;
};

/* Description -  Invalidate Extended Transport Header */
/* Size in bytes - 4 */
struct IB_IETH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Remote Key */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t R_Key;
};

/* Description -  Immediate Extended Transport Header */
/* Size in bytes - 4 */
struct IB_ImmDt {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Immediate Extended Transport Header */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t Immediate_Data;
};

/* Description -  Local Routed Header */
/* Size in bytes - 8 */
struct IB_LRH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Destination Local Identifier */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t DLID;
	/* Description - Link Next Header (3-IBA/GRH, 2-IBA/BTH, 1-Raw/IPv6, 0-Raw/RWH) */
	/* 0x0.16 - 0x0.17 */
	 u_int8_t LNH;
	/* Description - The 2 -bit Reserve field, shall be transmited as 00 and ignored on receive */
	/* 0x0.18 - 0x0.19 */
	 u_int8_t Rsv2;
	/* Description - Service Level  */
	/* 0x0.20 - 0x0.23 */
	 u_int8_t Sl;
	/* Description - Link Version (shall be set to 0x0) */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t LVer;
	/* Description - Virtual Lane */
	/* 0x0.28 - 0x0.31 */
	 u_int8_t Vl;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Source Local Identifier */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t SLID;
	/* Description - Packet Length (from LRH upto Variant CRC in 4 byte words) */
	/* 0x4.16 - 0x4.26 */
	 u_int16_t PktLen;
	/* Description - The 5 - bit Reserve shall be transmited as 0x0 and ignored on receive */
	/* 0x4.27 - 0x4.31 */
	 u_int8_t Rsv5;
};

/* Description -  Reliable Datagram Extended Transport Header */
/* Size in bytes - 4 */
struct IB_RDETH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - This field indicates which End-to-End Context should be used for this Reliable Datagram packet */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t EECnxt;
	/* Description - TX - 0, RX - ignore */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Rsv8;
};

/* Description -  Raw Header */
/* Size in bytes - 4 */
struct IB_RWH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t EtherType;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t HW_Reserved;
};

/* Description -  ICRC of IB Packet */
/* Size in bytes - 4 */
struct ICRC {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Invariant CRC */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t ICRC;
};

/* Description -   */
/* Size in bytes - 4 */
struct LID_Port_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t LID;
	/* Description -  */
	/* 0x0.16 - 0x0.16 */
	 u_int8_t Valid;
	/* Description -  */
	/* 0x0.17 - 0x0.19 */
	 u_int8_t LMC;
	/* Description -  */
	/* 0x0.20 - 0x0.23 */
	 u_int8_t Reserved;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Port;
};

/* Description -  0x40 */
/* Size in bytes - 192 */
struct PM_PortSamplesResult {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Read-only copy of PortSamplesControl:SampleStatus. */
	/* 0x0.0 - 0x0.1 */
	 u_int8_t SampleStatus;
	/* Description - Read-only copy of PortSamplesControl:Tag. */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t Tag;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t Counter0;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t Counter1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t Counter2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t Counter3;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t Counter4;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t Counter5;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t Counter6;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t Counter7;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.31 */
	 u_int32_t Counter8;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	 u_int32_t Counter9;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.31 */
	 u_int32_t Counter10;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.31 */
	 u_int32_t Counter11;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.31 */
	 u_int32_t Counter12;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x38.31 */
	 u_int32_t Counter13;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description -  */
	/* 0x3c.0 - 0x3c.31 */
	 u_int32_t Counter14;
};

/* Description -   */
/* Size in bytes - 16 */
struct PSID_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PS - ID */
	/* 0x0.24 - 0x10.23 */
	 u_int8_t PSID[16];
};

/* Description -  Partition Key */
/* Size in bytes - 2 */
struct P_Key_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.14 */
	 u_int16_t P_KeyBase;
	/* Description -  */
	/* 0x0.15 - 0x0.15 */
	 u_int8_t Membership_Type;
};

/* Description -   */
/* Size in bytes - 192 */
struct PerfManagement_MAD_Data_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xbc.31 */
	 u_int32_t DWORD[48];
};

/* Description -   */
/* Size in bytes - 2 */
struct PortCountersExtended_Mask_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t SetPortXmitData;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t SetPortRcvData;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t SetPortXmitPkts;
	/* Description -  */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t SetPortRcvPkts;
	/* Description -  */
	/* 0x0.4 - 0x0.4 */
	 u_int8_t SetPortUnicastXmitPkts;
	/* Description -  */
	/* 0x0.5 - 0x0.5 */
	 u_int8_t SetPortUnicastRcvPkts;
	/* Description -  */
	/* 0x0.6 - 0x0.6 */
	 u_int8_t SetPortMulticastXmitPkts;
	/* Description -  */
	/* 0x0.7 - 0x0.7 */
	 u_int8_t SetPortMulticastRcvPkts;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t Reserved;
};

/* Description -   */
/* Size in bytes - 1 */
struct PortCounters_Mask2_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t SetPortXmitWait;
};

/* Description -   */
/* Size in bytes - 2 */
struct PortCounters_Mask_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t SetSymbolErrorCounter;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t SetLinkErrorRecoveryCounter;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t SetLinkDownedCounter;
	/* Description -  */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t SetPortRcvErrors;
	/* Description -  */
	/* 0x0.4 - 0x0.4 */
	 u_int8_t SetPortRcvRemotePhysicalErrors;
	/* Description -  */
	/* 0x0.5 - 0x0.5 */
	 u_int8_t SetPortRcvSwitchRelayErrors;
	/* Description -  */
	/* 0x0.6 - 0x0.6 */
	 u_int8_t SetPortXmitDiscards;
	/* Description -  */
	/* 0x0.7 - 0x0.7 */
	 u_int8_t SetPortXmitConstraintErrors;
	/* Description -  */
	/* 0x0.8 - 0x0.8 */
	 u_int8_t SetPortRcvConstraintErrors;
	/* Description -  */
	/* 0x0.9 - 0x0.9 */
	 u_int8_t SetLocalLinkIntegrityErrors;
	/* Description -  */
	/* 0x0.10 - 0x0.10 */
	 u_int8_t SetExcessiveBufferOverrunErrors;
	/* Description -  */
	/* 0x0.11 - 0x0.11 */
	 u_int8_t SetVL15Dropped;
	/* Description -  */
	/* 0x0.12 - 0x0.12 */
	 u_int8_t SetPortXmitData;
	/* Description -  */
	/* 0x0.13 - 0x0.13 */
	 u_int8_t SetPortRcvData;
	/* Description -  */
	/* 0x0.14 - 0x0.14 */
	 u_int8_t SetPortXmitPkts;
	/* Description -  */
	/* 0x0.15 - 0x0.15 */
	 u_int8_t SetPortRcvPkts;
};

/* Description -   */
/* Size in bytes - 2 */
struct PortRcvErrorDetails_Mask_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t SetPortLocalPhysicalErrors;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t SetPortMalformedPacketErrors;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t SetPortBufferOverrunErrors;
	/* Description -  */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t SetPortDLIDMappingErrors;
	/* Description -  */
	/* 0x0.4 - 0x0.4 */
	 u_int8_t SetPortVLMappingErrors;
	/* Description -  */
	/* 0x0.5 - 0x0.5 */
	 u_int8_t SetPortLoopingErrors;
	/* Description -  */
	/* 0x0.6 - 0x0.15 */
	 u_int16_t Reserved;
};

/* Description -   */
/* Size in bytes - 8 */
struct PortSampleControlOptionMask {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t PlaceHolder;
	/* Description -  */
	/* 0x0.16 - 0x0.16 */
	 u_int8_t SwPortVLCongestion_SWPortVLCongestion_n;
	/* Description -  */
	/* 0x0.17 - 0x0.17 */
	 u_int8_t PortRcvConCtrl_PortPktRcvFECN;
	/* Description -  */
	/* 0x0.18 - 0x0.18 */
	 u_int8_t PortRcvConCtrl_PortPktRcvBECN;
	/* Description -  */
	/* 0x0.19 - 0x0.19 */
	 u_int8_t PortSLRcvFECN_PortSLRcvFECN_n;
	/* Description -  */
	/* 0x0.20 - 0x0.20 */
	 u_int8_t PortSLRcvBECN_PortSLRcvBECN_n;
	/* Description -  */
	/* 0x0.21 - 0x0.21 */
	 u_int8_t PortXmitConCtrl_PortXmitTimeCong;
	/* Description -  */
	/* 0x0.22 - 0x0.22 */
	 u_int8_t PortVLXmitTimeCong_PortVLXmitTimeCong_n;
	/* Description -  */
	/* 0x0.23 - 0x0.23 */
	 u_int8_t PortXmitDataSL_n;
	/* Description -  */
	/* 0x0.24 - 0x0.24 */
	 u_int8_t PortRcvDataSL_n;
	/* Description -  */
	/* 0x0.25 - 0x0.25 */
	 u_int8_t PortXmitDataSLExt_n;
	/* Description -  */
	/* 0x0.26 - 0x0.26 */
	 u_int8_t PortRcvDataSLExt_n;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.1 - 0x4.1 */
	 u_int8_t PortXmitQueue_n;
	/* Description -  */
	/* 0x4.2 - 0x4.2 */
	 u_int8_t PortXmitDataVl_n;
	/* Description -  */
	/* 0x4.3 - 0x4.3 */
	 u_int8_t PortRcvDataVl_n;
	/* Description -  */
	/* 0x4.4 - 0x4.4 */
	 u_int8_t PortXmitPktVl_n;
	/* Description -  */
	/* 0x4.5 - 0x4.5 */
	 u_int8_t PortRcvPktVl_n;
	/* Description -  */
	/* 0x4.6 - 0x4.6 */
	 u_int8_t PortRcvErrorDetails_PortLocalPhysicalErrors;
	/* Description -  */
	/* 0x4.7 - 0x4.7 */
	 u_int8_t PortRcvErrorDetails_PortMalformedPacketErrors;
	/* Description -  */
	/* 0x4.8 - 0x4.8 */
	 u_int8_t PortRcvErrorDetails_PortBufferOverrunErrors;
	/* Description -  */
	/* 0x4.9 - 0x4.9 */
	 u_int8_t PortRcvErrorsDetails_PortDLIDMappingErrors;
	/* Description -  */
	/* 0x4.10 - 0x4.10 */
	 u_int8_t PortRcvErrorsDetails_PortVlMappingErrors;
	/* Description -  */
	/* 0x4.11 - 0x4.11 */
	 u_int8_t PortRcvErrorDetails_PortLoopingErrors;
	/* Description -  */
	/* 0x4.12 - 0x4.12 */
	 u_int8_t PortXmitDiscardDetails_PortInactiveDiscards;
	/* Description -  */
	/* 0x4.13 - 0x4.13 */
	 u_int8_t PortXmitDiscardsDetails_PortNeighborMTUDiscards;
	/* Description -  */
	/* 0x4.14 - 0x4.14 */
	 u_int8_t PortXmitDiscardDetails_PortSwLifetimeLimitDiscards;
	/* Description -  */
	/* 0x4.15 - 0x4.15 */
	 u_int8_t PortXmitDiscardDetails_PortSwHOQLifeLimitDiscards;
	/* Description -  */
	/* 0x4.16 - 0x4.16 */
	 u_int8_t PortOpRcvCounters_PortOpRcvPkts;
	/* Description -  */
	/* 0x4.17 - 0x4.17 */
	 u_int8_t PortOpRcvCounters_PortOpRcvData;
	/* Description -  */
	/* 0x4.18 - 0x4.18 */
	 u_int8_t PortFlowCtlCounters_PortXmitFlowPkts;
	/* Description -  */
	/* 0x4.19 - 0x4.19 */
	 u_int8_t PortFlowCtlCounters_PortRcvFlowPkts;
	/* Description -  */
	/* 0x4.20 - 0x4.20 */
	 u_int8_t PortVLOpPackets_PortVLOpPackets_n;
	/* Description -  */
	/* 0x4.21 - 0x4.21 */
	 u_int8_t PortVLOpData_PortVLOpData_n;
	/* Description -  */
	/* 0x4.22 - 0x4.22 */
	 u_int8_t PortVlXmitFlowCtlUpdateErrors_PortVLXmitCtlUpdateErrors_n;
	/* Description -  */
	/* 0x4.23 - 0x4.23 */
	 u_int8_t PortVLXmitWaitCounters_PortVLXmitWait_n;
	/* Description -  */
	/* 0x4.28 - 0x4.28 */
	 u_int8_t PortExtendedSpeedsCounter;
};

/* Description -   */
/* Size in bytes - 2 */
struct PortXmitDiscardDetails_Mask_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t SetPortInactiveDiscards;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t SetPortNeighborMTUDiscards;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t SetPortSwLifetimeLimitDiscards;
	/* Description -  */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t SetPortSwHOQLifetimeLimitDiscards;
	/* Description -  */
	/* 0x0.4 - 0x0.15 */
	 u_int16_t Reserved;
};

/* Description -   */
/* Size in bytes - 132 */
struct RawData_PM_PortRcvXmitCntrsSlVl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x84.23 */
	 u_int8_t data[132];
};

/* Description -   */
/* Size in bytes - 64 */
struct RawData_PM_PortRcvXmitCntrsSlVl32 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 u_int32_t DataVLSL32[16];
};

/* Description -  generic buffer for NoticeDataDetails */
/* Size in bytes - 56 */
struct RawNoticeDataDetails {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x38.23 */
	 u_int8_t data[56];
};

/* Description -   */
/* Size in bytes - 4 */
struct SMP_LedInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t LedMask;
	/* Description -  */
	/* 0x0.1 - 0x0.31 */
	 u_int32_t Reserved;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_LinearForwardingTable {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x40.23 */
	 u_int8_t Port[64];
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_MAD_Data_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 u_int32_t DWORD[16];
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_MlnxExtPortInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t StateChangeEnable;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t AME;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t LinkSpeedSupported;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	 u_int8_t LinkSpeedEnabled;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.7 */
	 u_int8_t LinkSpeedActive;
	/* Description - The active RS-FEC parity size in Symbols, 0 - RS-FEC disabled */
	/* 0xc.8 - 0xc.19 */
	 u_int16_t ActiveRSFECParity;
	/* Description - The active RS-FEC data size in Symbols, 0 - RS-FEC disabled */
	/* 0xc.20 - 0xc.31 */
	 u_int16_t ActiveRSFECData;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t CapabilityMask;
	/* Description -  */
	/* 0x10.20 - 0x10.23 */
	 u_int8_t FECModeActive;
	/* Description -  */
	/* 0x10.28 - 0x10.31 */
	 u_int8_t RetransMode;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.15 */
	 u_int16_t FDR10FECModeSupported;
	/* Description -  */
	/* 0x14.16 - 0x14.31 */
	 u_int16_t FDR10FECModeEnabled;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.15 */
	 u_int16_t FDRFECModeSupported;
	/* Description -  */
	/* 0x18.16 - 0x18.31 */
	 u_int16_t FDRFECModeEnabled;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	 u_int16_t EDR20FECModeSupported;
	/* Description -  */
	/* 0x1c.16 - 0x1c.31 */
	 u_int16_t EDR20FECModeEnabled;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.15 */
	 u_int16_t EDRFECModeSupported;
	/* Description -  */
	/* 0x20.16 - 0x20.31 */
	 u_int16_t EDRFECModeEnabled;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.7 */
	 u_int8_t FDR10RetranSupported;
	/* Description -  */
	/* 0x24.8 - 0x24.15 */
	 u_int8_t FDR10RetranEnabled;
	/* Description -  */
	/* 0x24.16 - 0x24.23 */
	 u_int8_t FDRRetranSupported;
	/* Description -  */
	/* 0x24.24 - 0x24.31 */
	 u_int8_t FDRRetranEnabled;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.7 */
	 u_int8_t EDR20RetranSupported;
	/* Description -  */
	/* 0x28.8 - 0x28.15 */
	 u_int8_t EDR20RetranEnabled;
	/* Description -  */
	/* 0x28.16 - 0x28.23 */
	 u_int8_t EDRRetranSupported;
	/* Description -  */
	/* 0x28.24 - 0x28.31 */
	 u_int8_t EDRRetranEnabled;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.3 */
	 u_int8_t SpecialPortType;
	/* Description -  */
	/* 0x2c.7 - 0x2c.7 */
	 u_int8_t IsSpecialPort;
	/* Description -  */
	/* 0x2c.8 - 0x2c.15 */
	 u_int8_t SpecialPortCapabilityMask;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.15 */
	 u_int16_t HDRFECModeSupported;
	/* Description -  */
	/* 0x30.16 - 0x30.31 */
	 u_int16_t HDRFECModeEnabled;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_MulticastForwardingTable {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x40.15 */
	 u_int16_t PortMask[32];
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_NodeDesc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - UTF-8 encoded string to describe node in text format */
	/* 0x0.24 - 0x40.23 */
	 char Byte[65];
};

/* Description -   */
/* Size in bytes - 20 */
struct SMP_PortInfoExtended {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - offset 0 */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t CapMsk;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - offset 48 */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t FDRFECModeSupported;
	/* Description - offset 32 */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t FECModeActive;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - offset 80 */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t EDRFECModeSupported;
	/* Description - offset 64 */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t FDRFECModeEnabled;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - offset 112 */
	/* 0xc.0 - 0xc.15 */
	 u_int16_t HDRFECModeSupported;
	/* Description - offset 96 */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t EDRFECModeEnabled;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - offset 128 */
	/* 0x10.16 - 0x10.31 */
	 u_int16_t HDRFECModeEnabled;
};

/* Description -  Router Info MAD */
/* Size in bytes - 64 */
struct SMP_RouterInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t CapabilityMask;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t NextHopTableCap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t NextHopTableTop;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.7 */
	 u_int8_t AdjSiteLocalSubnetsTblCap;
	/* Description -  */
	/* 0xc.8 - 0xc.15 */
	 u_int8_t AdjSiteLocalSubnetsTblTop;
	/* Description -  */
	/* 0xc.29 - 0xc.29 */
	 u_int8_t IsGlbSA;
	/* Description -  */
	/* 0xc.30 - 0xc.30 */
	 u_int8_t NHChange;
	/* Description -  */
	/* 0xc.31 - 0xc.31 */
	 u_int8_t AdjChange;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.7 */
	 u_int8_t MaxMulticastTTL;
};

/* Description -   */
/* Size in bytes - 8 */
struct SMP_SLToVLMappingTable {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.3 */
	 u_int8_t SL7ToVL;
	/* Description -  */
	/* 0x0.4 - 0x0.7 */
	 u_int8_t SL6ToVL;
	/* Description -  */
	/* 0x0.8 - 0x0.11 */
	 u_int8_t SL5ToVL;
	/* Description -  */
	/* 0x0.12 - 0x0.15 */
	 u_int8_t SL4ToVL;
	/* Description -  */
	/* 0x0.16 - 0x0.19 */
	 u_int8_t SL3ToVL;
	/* Description -  */
	/* 0x0.20 - 0x0.23 */
	 u_int8_t SL2ToVL;
	/* Description -  */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t SL1ToVL;
	/* Description -  */
	/* 0x0.28 - 0x0.31 */
	 u_int8_t SL0ToVL;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.3 */
	 u_int8_t SL15ToVL;
	/* Description -  */
	/* 0x4.4 - 0x4.7 */
	 u_int8_t SL14ToVL;
	/* Description -  */
	/* 0x4.8 - 0x4.11 */
	 u_int8_t SL13ToVL;
	/* Description -  */
	/* 0x4.12 - 0x4.15 */
	 u_int8_t SL12ToVL;
	/* Description -  */
	/* 0x4.16 - 0x4.19 */
	 u_int8_t SL11ToVL;
	/* Description -  */
	/* 0x4.20 - 0x4.23 */
	 u_int8_t SL10ToVL;
	/* Description -  */
	/* 0x4.24 - 0x4.27 */
	 u_int8_t SL9ToVL;
	/* Description -  */
	/* 0x4.28 - 0x4.31 */
	 u_int8_t SL8ToVL;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_SwitchInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t RandomFDBCap;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t LinearFDBCap;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t LinearFDBTop;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t MCastFDBCap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - bit[0] when set indicate switch support optimized SLtoVL Mapping
bit[1] - reserve */
	/* 0x8.0 - 0x8.1 */
	 u_int8_t OptimizedSLVLMapping;
	/* Description -  */
	/* 0x8.2 - 0x8.2 */
	 u_int8_t PortStateChange;
	/* Description -  */
	/* 0x8.3 - 0x8.7 */
	 u_int8_t LifeTimeValue;
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	 u_int8_t DefMCastNotPriPort;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	 u_int8_t DefMCastPriPort;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	 u_int8_t DefPort;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.15 */
	 u_int16_t PartEnfCap;
	/* Description -  */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t LidsPerPort;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t MCastFDBTop;
	/* Description -  */
	/* 0x10.27 - 0x10.27 */
	 u_int8_t ENP0;
	/* Description -  */
	/* 0x10.28 - 0x10.28 */
	 u_int8_t FilterRawOutbCap;
	/* Description -  */
	/* 0x10.29 - 0x10.29 */
	 u_int8_t FilterRawInbCap;
	/* Description -  */
	/* 0x10.30 - 0x10.30 */
	 u_int8_t OutbEnfCap;
	/* Description -  */
	/* 0x10.31 - 0x10.31 */
	 u_int8_t InbEnfCap;
};

/* Description -   */
/* Size in bytes - 16 */
struct SMP_TempSensing {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t tss;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t stgs;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t stge;
	/* Description -  */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t wtts;
	/* Description -  */
	/* 0x0.4 - 0x0.4 */
	 u_int8_t wtte;
	/* Description -  */
	/* 0x0.5 - 0x0.5 */
	 u_int8_t wtgs;
	/* Description -  */
	/* 0x0.6 - 0x0.6 */
	 u_int8_t wtge;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.10 */
	 u_int16_t current_temp;
	/* Description -  */
	/* 0x4.16 - 0x4.26 */
	 u_int16_t max_temp;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.10 */
	 u_int16_t overtemp_warning_threshold_hi;
	/* Description -  */
	/* 0x8.16 - 0x8.26 */
	 u_int16_t overtemp_warning_threshold_lo;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.0 */
	 u_int8_t wts;
	/* Description -  */
	/* 0xc.1 - 0xc.1 */
	 u_int8_t wtga;
	/* Description -  */
	/* 0xc.2 - 0xc.2 */
	 u_int8_t wtgp;
	/* Description -  */
	/* 0xc.3 - 0xc.4 */
	 u_int8_t wtgm;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_VPortState {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - VPortState associated with the VPort where VPort index. */
	/* 0x0.28 - 0x40.27 */
	 u_int8_t vport_state[128];
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_VirtualizationInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicates the top index of VPort with VPortInfo:VPortEnable = True. */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t vport_index_top;
	/* Description - indicates the maximal supported VPort index on that port. */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t vport_cap;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Optional Virtualization capabilities. 0-7: Reserved */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t capability_mask;
	/* Description - Local SMA virtualization revision. SM should check whether it supports that revision. */
	/* 0x4.8 - 0x4.15 */
	 u_int8_t virtualization_revision;
	/* Description -  */
	/* 0x4.29 - 0x4.29 */
	 u_int8_t vportstate_change;
	/* Description - optional: shall be 0 if not implemented
(PortInfo:CapabilityMask.IsClientReregistrationSupported = 0). Used by SM to request endnode clients on all VPorts of that physical port reregistration of SA subscriptions. */
	/* 0x4.30 - 0x4.30 */
	 u_int8_t vclient_reregister;
	/* Description - Indicates support of optional Virtualization. If set to 0, virtualization is disabled; VPort0 refers to the physical port and tracks its PortState. If set to 1, virtualization is enabled and VPort 0 has an independent PortState. */
	/* 0x4.31 - 0x4.31 */
	 u_int8_t virtualization_enable;
};

/* Description -  SW Info */
/* Size in bytes - 32 */
struct SWInfo_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t SubMinor;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t Minor;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t Major;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Reserved8;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x1c.31 */
	 u_int32_t Reserved_Dword[7];
};

/* Description -   */
/* Size in bytes - 200 */
struct SubnetAdministartion_MAD_Data_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc4.31 */
	 u_int32_t DWORD[50];
};

/* Description -   */
/* Size in bytes - 4 */
struct SwitchPortCongestionSettingElement {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When control_type=0 this field contains the port marking_rate. When control_type=1 this field is reserved */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t Cong_Parm;
	/* Description - When control_type=0 this field contains the minimum size of packets that may be marked with a FECN. When control_type=1 this field is reserved. */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t Packet_Size;
	/* Description - When control_type=0 this field contains the congestion threshold value (Threshold) for this port. When Control Type is 1, contains the credit starvation threshold (CS_Threshold) value for this port. */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t Threshold;
	/* Description - Indicates which type of attribute is being set: 0b = Congestion Control parameters are being set. 1b = Credit Starvation parameters are being set. */
	/* 0x0.30 - 0x0.30 */
	 u_int8_t Control_Type;
	/* Description - When set to 1, indicates this switch port congestion setting element is valid. */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t Valid;
};

/* Description -   */
/* Size in bytes - 8 */
struct TID_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t High;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t Low;
};

/* Description -   */
/* Size in bytes - 32 */
struct UINT256 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t Mask_255_224;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t Mask_223_192;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t Mask_191_160;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t Mask_159_128;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t Mask_127_96;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t Mask_95_64;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t Mask_63_32;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - bit0: port 0, bit1: port1... bit254: port 254, bit255: reserved */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t Mask_31_0;
};

/* Description -  VCRC of IB Packet */
/* Size in bytes - 4 */
struct VCRC {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Variant CRC */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t VCRC;
	/* Description - Reserved */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t Rsrvd;
};

/* Description -  VL Weight */
/* Size in bytes - 2 */
struct VL_Weight_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.3 */
	 u_int8_t Reserved;
	/* Description -  */
	/* 0x0.4 - 0x0.7 */
	 u_int8_t VL;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t Weight;
};

/* Description -  page 1 v3 in Vendor Specific DiagnosticCounters mad */
/* Size in bytes - 104 */
struct VS_DC_Page1LatestVersion {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t rq_num_sig_err;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t sq_num_sig_err;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t sq_num_cnak;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t sq_reconnect;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t sq_reconnect_ack;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t rq_open_gb;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  Responder-number of loopback Connects which got no DCRs */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t rq_num_no_dcrs;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  Responder-number of loopback Connects which got no DCRs and sent a CNAK */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t rq_num_cnak_sent;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  Requester-number of DC reconnect acks dropped */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t sq_reconnect_ack_bad;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  Responder-number of DC ghost busters open required/connect while connect with ghost buster - but no DCRs available */
	/* 0x24.0 - 0x24.31 */
	 u_int32_t rq_open_gb_cnak;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  Responder-number of cnaks sent on connect packet trapped at ghost buster */
	/* 0x28.0 - 0x28.31 */
	 u_int32_t rq_gb_trap_cnak;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  Responder-connect while connected, no ghost buster involved (dropped disconnect) */
	/* 0x2c.0 - 0x2c.31 */
	 u_int32_t rq_not_gb_connect;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  Responder-reconnect without ghost buster received = ghost buster installer  */
	/* 0x30.0 - 0x30.31 */
	 u_int32_t rq_not_gb_reconnect;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  Responder-connect received trapped by ghost buster */
	/* 0x34.0 - 0x34.31 */
	 u_int32_t rq_curr_gb_connect;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  Responder-ghost buster reactivated (ghost buster installer while ghost buster exists) */
	/* 0x38.0 - 0x38.31 */
	 u_int32_t rq_curr_gb_reconnect;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description -  Responder-number of regular DCRs closed due to garbage collection */
	/* 0x3c.0 - 0x3c.31 */
	 u_int32_t rq_close_non_gb_gc;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  Responder-number of DCR inhale events triggered */
	/* 0x40.0 - 0x40.31 */
	 u_int32_t rq_dcr_inhale_events;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description -  Responder-number of currently open ghost busters */
	/* 0x44.0 - 0x44.31 */
	 u_int32_t rq_state_active_gb;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  Responder-number of currently available DCRs */
	/* 0x48.0 - 0x48.31 */
	 u_int32_t rq_state_avail_dcrs;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description -  Responder-current DCR stack size */
	/* 0x4c.0 - 0x4c.31 */
	 u_int32_t rq_state_dcr_lifo_size;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x50.31 */
	 u_int32_t sq_cnak_drop;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description -  */
	/* 0x54.0 - 0x54.31 */
	 u_int32_t minimum_dcrs;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x58.31 */
	 u_int32_t maximum_dcrs;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description -  */
	/* 0x5c.0 - 0x5c.31 */
	 u_int32_t max_cnak_fifo_size;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x60.31 */
	 u_int32_t rq_num_dc_cacks;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description -  */
	/* 0x64.0 - 0x64.31 */
	 u_int32_t sq_num_dc_cacks;
};

/* Description -  page 255 in Vendor Specific DiagnosticCounters mad */
/* Size in bytes - 68 */
struct VS_DC_Page255LatestVersion {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t num_cqovf;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t num_eqovf;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t sq_num_ds_ex_pi_retry;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t rq_next_gb_connect;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t rq_next_gb_reconnect;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t rq_psn_close_gb;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t rq_psn_close_gb_cwc;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t rq_close_gb_gc;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t rq_cwc_ghost_discard_connect;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.31 */
	 u_int32_t rq_cwc_ghost_discard_reconnect;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	 u_int32_t rq_cwc_reconnect_stale_connection;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.31 */
	 u_int32_t rq_cwc_reconnect_probable_current_connection;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.31 */
	 u_int32_t rq_cwc_uncertainty_discard;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.31 */
	 u_int32_t rq_num_dc_cacks_full_hash;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x38.31 */
	 u_int32_t rq_num_dc_cacks_collision;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description -  */
	/* 0x3c.0 - 0x3c.31 */
	 u_int32_t dc_hash_curr_used_lines;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x40.31 */
	 u_int32_t dc_has_max_used_entries_in_line;
};

/* Description -  page 0 in Vendor Specific DiagnosticCounters mad   */
/* Size in bytes - 124 */
struct VS_DC_TransportErrorsAndFlowsV2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t rq_num_lle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t sq_num_lle;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t rq_num_lqpoe;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t sq_num_lqpoe;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t rq_num_leeoe;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t sq_num_leeoe;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t rq_num_lpe;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t sq_num_lpe;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t rq_num_wrfe;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.31 */
	 u_int32_t sq_num_wrfe;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	 u_int32_t sq_num_mwbe;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.31 */
	 u_int32_t sq_num_bre;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.31 */
	 u_int32_t rq_num_lae;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.31 */
	 u_int32_t rq_num_rire;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x38.31 */
	 u_int32_t sq_num_rire;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description -  */
	/* 0x3c.0 - 0x3c.31 */
	 u_int32_t rq_num_rae;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x40.31 */
	 u_int32_t sq_num_rae;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description -  */
	/* 0x44.0 - 0x44.31 */
	 u_int32_t rq_num_roe;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x48.31 */
	 u_int32_t sq_num_roe;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description -  */
	/* 0x4c.0 - 0x4c.31 */
	 u_int32_t sq_num_rnr;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x50.31 */
	 u_int32_t rq_num_oos;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description -  */
	/* 0x54.0 - 0x54.31 */
	 u_int32_t sq_num_oos;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x58.31 */
	 u_int32_t rq_num_dup;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description -  */
	/* 0x5c.0 - 0x5c.31 */
	 u_int32_t sq_num_to;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x60.31 */
	 u_int32_t sq_num_tree;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description -  */
	/* 0x64.0 - 0x64.31 */
	 u_int32_t sq_num_rree;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x68.31 */
	 u_int32_t sq_num_rabrte;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description -  */
	/* 0x6c.0 - 0x6c.31 */
	 u_int32_t rq_num_mce;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.0 - 0x70.31 */
	 u_int32_t rq_num_retrans_rsync;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description -  */
	/* 0x74.0 - 0x74.31 */
	 u_int32_t sq_num_retrans_rsync;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description -  */
	/* 0x78.0 - 0x78.31 */
	 u_int32_t sq_num_ldb_drops;
};

/* Description -   */
/* Size in bytes - 224 */
struct VendorSpecific_MAD_Data_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xdc.31 */
	 u_int32_t DWORD[56];
};

/* Description -  generic register */
/* Size in bytes - 44 */
struct acc_register {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x2c.23 */
	 u_int8_t data[44];
};

/* Description -  generic register */
/* Size in bytes - 220 */
struct acc_register_gmp {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xdc.23 */
	 u_int8_t data[220];
};

/* Description -   */
/* Size in bytes - 4 */
struct adaptive_routing_group_table_copy_element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - First index of the AdaptiveRoutingGroupTable to be copied to. */
	/* 0x0.0 - 0x0.11 */
	 u_int16_t copy_from_index;
	/* Description - Last index of the AdaptiveRoutingGroupTable to be copied to. */
	/* 0x0.16 - 0x0.27 */
	 u_int16_t copy_to_index;
};

/* Description -   */
/* Size in bytes - 20 */
struct adaptive_routing_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1 indicates that Adaptive Routing mechanism is enabled.
0 indicates that Adaptive Routing is disabled. */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t e;
	/* Description - 1 indicates that ARN is supported.
0 indicates that ARN is not supported. */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t is_arn_sup;
	/* Description - 1 indicates that FRN is supported.
0 indicates that FRN is not supported. */
	/* 0x0.2 - 0x0.2 */
	 u_int8_t is_frn_sup;
	/* Description - 1 indicates that Fallback Routing is supported.
0 indicates that Fallback Routing is not supported. */
	/* 0x0.3 - 0x0.3 */
	 u_int8_t is_fr_sup;
	/* Description - 1 indicates that Fallback Routing mechanism is enabled.
0 indicates that Fallback Routing is disabled. */
	/* 0x0.4 - 0x0.4 */
	 u_int8_t fr_enabled;
	/* Description - 1 indicates that the device will be able to generate and pass on RN packets.i
0 indicates that the device won't generate or pass-on RNs and RNXmitPortMask for all ports will be 0. */
	/* 0x0.5 - 0x0.5 */
	 u_int8_t rn_xmit_enabled;
	/* Description - The number of ARSubGroups to be used within each ARGroup. */
	/* 0x0.8 - 0x0.11 */
	 u_int8_t sub_grps_active;
	/* Description - Indicates the number of AaptiveRoutingGroups that can be copied by AdaptiveRoutingGroupTableCopy attribute. */
	/* 0x0.12 - 0x0.15 */
	 u_int8_t group_table_copy_sup;
	/* Description - Number of supported directions. */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t direction_num_sup;
	/* Description - When a standard LFT mad is processed it should check no_fallback state : 
        0 - it should disable adaptive_routing (SET_AR_INFO with enable == 0).
        1 - return error.
Default for both is 0. */
	/* 0x0.24 - 0x0.24 */
	 u_int8_t no_fallback;
	/* Description - 0 - Shaldag mode (1 TQs)
1 - Baz mode (3 TQs) */
	/* 0x0.25 - 0x0.25 */
	 u_int8_t is4_mode;
	/* Description - 1 - ARGroups are stored in a global resources.
0 - Groups can be associated with each pLFT */
	/* 0x0.26 - 0x0.26 */
	 u_int8_t glb_groups;
	/* Description - If set to 1 declares the device supports EnableBySLMask field */
	/* 0x0.27 - 0x0.27 */
	 u_int8_t by_sl_cap;
	/* Description - If set to 1 enable the use of EnableBySLMask field. When set to 0 AR is applied to all SLs. */
	/* 0x0.28 - 0x0.28 */
	 u_int8_t by_sl_en;
	/* Description - If set to 1 declares the device supports applying AR by transport as defined by the ByTransportDisable field. */
	/* 0x0.29 - 0x0.29 */
	 u_int8_t by_transp_cap;
	/* Description - If set to 1 declares the device supports and demands recalculating this attribute Capability fields based on user provided selection of other fields. */
	/* 0x0.30 - 0x0.30 */
	 u_int8_t dyn_cap_calc_sup;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Indicates the number of ARGroups supported by each ARGroupsTable.
AdaptiveRoutingGroupCap = 0 indicates that Adaptive routing is not supported. */
	/* 0x4.0 - 0x4.11 */
	 u_int16_t group_cap;
	/* Description - Index of the maximal enabled group. */
	/* 0x4.12 - 0x4.23 */
	 u_int16_t group_top;
	/* Description - Indicates the number of different AR Group Tables supported */
	/* 0x4.24 - 0x4.27 */
	 u_int8_t group_table_cap;
	/* Description - Capability of the String Width bits. Values 0-15. */
	/* 0x4.28 - 0x4.31 */
	 u_int8_t string_width_cap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Indicates the latest Adaptive Routing Version supported by the device */
	/* 0x8.0 - 0x8.3 */
	 u_int8_t ar_version_cap;
	/* Description - Indicates the latest Routing Notification Version supported by the device. */
	/* 0x8.4 - 0x8.7 */
	 u_int8_t rn_version_cap;
	/* Description - Indicates the supported number of ARSubGroups in each ARGroup. */
	/* 0x8.8 - 0x8.15 */
	 u_int8_t sub_grps_supported;
	/* Description - If BySLEn is set to 1 this field provides the set of SLs that AR is applied to.
Other SLs (their mask bit set to 0) are not subject to AR */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t enable_by_sl_mask;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Bit 0 = UD
Bit 1 = RC
Bit 2 = UC
Bit 3 = DCT
Bits 4-7 are reserved */
	/* 0xc.0 - 0xc.7 */
	 u_int8_t by_transport_disable;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - In one microsecond granularity.
*Write permission depends on the value of GeneralInfoSMP:CapabilityMask.IsASlaveVirtualSwitch being 0 */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t ageing_time_value;
};

/* Description -   */
/* Size in bytes - 4 */
struct child_qp {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Child QP Number */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t child_qpn;
	/* Description - Child index */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t child_index;
};

/* Description -   */
/* Size in bytes - 4 */
struct child_qpn {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t child_qpn;
};

/* Description -  This element defines the connection between lid to port group and table in FDB for SX dev */
/* Size in bytes - 4 */
struct ib_ar_lft_block_element_sx {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Group number for this LID, if LID state indicates Static Routing this filed indicates port number. */
	/* 0x0.0 - 0x0.11 */
	 u_int16_t GroupNumber;
	/* Description -  */
	/* 0x0.12 - 0x0.15 */
	 u_int8_t Reserved_1;
	/* Description - The default port to be used for packets classified as Legacy Routing.
For AR enabled has to contain the Legacy Routing port */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t DefaultPort;
	/* Description - Table number for this LID, non applicable if LID state is Static Routing. */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t TableNumber;
	/* Description -  */
	/* 0x0.28 - 0x0.29 */
	 u_int8_t Reserved_2;
	/* Description - 00 - Bounded adaptive routing.
01 - Free adaptive routing.
10 - Static Routing.
11 - Reserved. */
	/* 0x0.30 - 0x0.31 */
	 u_int8_t LidState;
};

/* Description -   */
/* Size in bytes - 2 */
struct ib_description_mode {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.3 */
	 u_int8_t NumOfLFTables;
	/* Description -  */
	/* 0x0.8 - 0x0.13 */
	 u_int8_t LFTableSize;
};

/* Description -   */
/* Size in bytes - 4 */
struct ib_extended_switch_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.1 */
	 u_int8_t sl2vl_cap;
	/* Description -  */
	/* 0x0.8 - 0x0.9 */
	 u_int8_t sl2vl_act;
};

/* Description -   */
/* Size in bytes - 4 */
struct ib_lft_def {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.6 */
	 u_int8_t FDB_LID_Offset;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t FDB_LID_Space;
	/* Description - Internal Table index */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t FDB_Table_IX;
};

/* Description -   */
/* Size in bytes - 16 */
struct ib_port_sl_to_plft {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t PLFTToPortSL3;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t PLFTToPortSL2;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PLFTToPortSL1;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t PLFTToPortSL0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t PLFTToPortSL7;
	/* Description -  */
	/* 0x4.8 - 0x4.15 */
	 u_int8_t PLFTToPortSL6;
	/* Description -  */
	/* 0x4.16 - 0x4.23 */
	 u_int8_t PLFTToPortSL5;
	/* Description -  */
	/* 0x4.24 - 0x4.31 */
	 u_int8_t PLFTToPortSL4;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	 u_int8_t PLFTToPortSL11;
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	 u_int8_t PLFTToPortSL10;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	 u_int8_t PLFTToPortSL9;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	 u_int8_t PLFTToPortSL8;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.7 */
	 u_int8_t PLFTToPortSL15;
	/* Description -  */
	/* 0xc.8 - 0xc.15 */
	 u_int8_t PLFTToPortSL14;
	/* Description -  */
	/* 0xc.16 - 0xc.23 */
	 u_int8_t PLFTToPortSL13;
	/* Description -  */
	/* 0xc.24 - 0xc.31 */
	 u_int8_t PLFTToPortSL12;
};

/* Description -   */
/* Size in bytes - 40 */
struct ib_private_lft_map {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t Port_MaskEn;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t LFT_TopEn;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x20.31 */
	 u_int32_t FDB_Port_Group_Mask[8];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.15 */
	 u_int16_t LFT_Top;
};

/* Description -   */
/* Size in bytes - 4 */
struct qpn {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t qpn;
};

/* Description -   */
/* Size in bytes - 4 */
struct rn_gen_by_sub_group_prio_element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1 if ARN should be generated. 0 otherwise. */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t gen_arn;
	/* Description - 1 if FRN should be generated. 0 otherwise. */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t gen_frn;
};

/* Description -   */
/* Size in bytes - 4 */
struct rn_gen_by_sub_group_priority_element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	 u_int8_t gen_arn;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	 u_int8_t gen_frn;
};

/* Description -   */
/* Size in bytes - 2 */
struct rn_gen_string_element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - RNGenString to be set when generating ARN or FRN. */
	/* 0x0.0 - 0x0.14 */
	 u_int16_t rn_gen_string;
};

/* Description -   */
/* Size in bytes - 4 */
struct rn_rcv_string_element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: Discard
1: Consume ARN
2: Consume ARN/FRN
3: Pass-on */
	/* 0x0.0 - 0x0.1 */
	 u_int8_t decision;
	/* Description - PrivateLFTID to be used for consume or pass-on. */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t plft_id;
	/* Description - New String to be assigned to the RN. Relevant only if decision is Pass-on. */
	/* 0x0.16 - 0x0.30 */
	 u_int16_t string2string;
};

/* Description -   */
/* Size in bytes - 64 */
struct rn_sub_group_direction_tbl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Direction of the sub-group. */
	/* 0x0.24 - 0x40.23 */
	 u_int8_t direction_of_sub_group[64];
};

/* Description -   */
/* Size in bytes - 64 */
struct rn_xmit_port_mask {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.28 - 0x40.27 */
	 u_int8_t element[128];
};

/* Description -   */
/* Size in bytes - 8 */
struct uint64bit {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t High;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t Low;
};

/* Description -   */
/* Size in bytes - 12 */
struct AM_AMKeyInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Aggregation Node Key
The 8-byte AN_Key used in all AggregationManagement MADs 
by all valid AggMgrs. A value of 0 means that no AN_Key check 
is ever performed by the AMMgtA */
	/* 0x0.0 - 0x4.31 */
	 struct uint64bit am_key;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Timer value used to indicate how long the AM_KeyProtectBit is
to remain non zero after a AMMgtSet(AMKeyInfo) MAD that
failed a AM_Key check is dropped. The value of the timer indi
cates the number of seconds for the lease period. With a 16 bit
counter, the period can range from 1 second to approximately 18
hours. 0 shall mean infinite. */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t am_key_lease_period;
	/* Description - Aggregation Management Key Protect Bit
For details, see TBD */
	/* 0x8.31 - 0x8.31 */
	 u_int8_t am_key_protect_bit;
};

/* Description -   */
/* Size in bytes - 80 */
struct AM_PerformanceCounters {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t counter_select;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t packet_sent;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	 u_int64_t ack_packet_sent;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t retry_packet_sent;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	 u_int64_t rnr_event;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	 u_int64_t timeout_event;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	 u_int64_t oos_nack_rcv;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	 u_int64_t rnr_nack_rcv;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x44.31 */
	 u_int64_t packet_discard_transport;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x4c.31 */
	 u_int64_t packet_discard_sharp;
};

/* Description -   */
/* Size in bytes - 144 */
struct AM_QPAllocation {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Job ID
For the tree related QPs, use Job-ID=0
bits [8:23] are reserved for class version 1 */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t job_id;
	/* Description - 1: ALLOCATE_QP
2: RELEASE_QP
3: CONFIRM_ALLOCATION */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of QPs. 
Maximum supported
 
for a single allocate operation is 32.
On request - number of QPs to allocate
on response - number of QPs actually allocated. Might be equal 
or smaller than the requested number of QPs. */
	/* 0x4.0 - 0x4.5 */
	 u_int8_t num_of_qps;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - List of 
Q
P Number
s allocated */
	/* 0x10.0 - 0x8c.31 */
	 struct qpn qpn[32];
};

/* Description -   */
/* Size in bytes - 56 */
struct AM_TrapQPAllocationTime {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t data_valid;
	/* Description -  */
	/* 0x0.16 - 0x0.30 */
	 u_int16_t notice_count;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t notice_toggle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t lid1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	 u_int8_t job_id;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x20.31 */
	 struct GID_Block_Element gid1;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x34.31 */
	 u_int32_t padding[5];
};

/* Description -   */
/* Size in bytes - 56 */
struct AM_TrapQPAllocationTime_V2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t data_valid;
	/* Description -  */
	/* 0x0.16 - 0x0.30 */
	 u_int16_t notice_count;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t notice_toggle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t lid1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.23 */
	 u_int32_t job_id;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x20.31 */
	 struct GID_Block_Element gid1;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x34.31 */
	 u_int32_t padding[5];
};

/* Description -   */
/* Size in bytes - 56 */
struct AM_TrapQPError {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t data_valid;
	/* Description -  */
	/* 0x0.16 - 0x0.30 */
	 u_int16_t notice_count;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t notice_toggle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t lid2;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t lid1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t tree_id;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	 u_int8_t job_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.23 */
	 u_int32_t qp1;
	/* Description -  */
	/* 0xc.24 - 0xc.31 */
	 u_int8_t syndrom;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.23 */
	 u_int32_t qp2;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x20.31 */
	 struct uint64bit gid1[2];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x30.31 */
	 struct uint64bit gid2[2];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.31 */
	 u_int32_t padding;
};

/* Description -   */
/* Size in bytes - 56 */
struct AM_TrapQPError_V2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t data_valid;
	/* Description -  */
	/* 0x0.16 - 0x0.30 */
	 u_int16_t notice_count;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t notice_toggle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t lid2;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t lid1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t tree_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.23 */
	 u_int32_t qp1;
	/* Description -  */
	/* 0xc.24 - 0xc.31 */
	 u_int8_t syndrom;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.23 */
	 u_int32_t qp2;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x20.31 */
	 struct uint64bit gid1[2];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x30.31 */
	 struct uint64bit gid2[2];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.23 */
	 u_int32_t job_id;
};

/* Description -   */
/* Size in bytes - 56 */
struct AM_TrapSharpInvalidRequest {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t data_valid;
	/* Description -  */
	/* 0x0.16 - 0x0.30 */
	 u_int16_t notice_count;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t notice_toggle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t lid2;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t lid1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t tree_id;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	 u_int8_t job_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.23 */
	 u_int32_t qp1;
	/* Description -  */
	/* 0xc.24 - 0xc.31 */
	 u_int8_t syndrom;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.23 */
	 u_int32_t qp2;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x20.31 */
	 struct uint64bit gid1[2];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x30.31 */
	 struct uint64bit gid2[2];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.23 */
	 u_int32_t group_id;
};

/* Description -   */
/* Size in bytes - 56 */
struct AM_TrapSharpInvalidRequest_V2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t data_valid;
	/* Description -  */
	/* 0x0.16 - 0x0.30 */
	 u_int16_t notice_count;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t notice_toggle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t lid2;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t lid1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t tree_id;
	/* Description -  */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t job_id_lo;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.23 */
	 u_int32_t qp1;
	/* Description -  */
	/* 0xc.24 - 0xc.31 */
	 u_int8_t syndrom;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.23 */
	 u_int32_t qp2;
	/* Description -  */
	/* 0x10.24 - 0x10.31 */
	 u_int8_t job_id_hi;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x20.31 */
	 struct uint64bit gid1[2];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x30.31 */
	 struct uint64bit gid2[2];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.31 */
	 u_int32_t group_num;
};

/* Description -   */
/* Size in bytes - 192 */
struct AM_TreeConfig {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tree Identifier
Supported range is 0 ..(MAX_TREES_SUPPORTED-1) */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t tree_id;
	/* Description - TreeState
0: DISABLED
 - all children and parents are removed
1: ENABLED
2: ERROR
Reserved for opcodes ADD_CHILDREN, REMOVE_CHIL
DREN */
	/* 0x0.24 - 0x0.27 */
	 u_int8_t tree_state;
	/* Description - 0: ADD_CHILDREN - Add the list of children QP numbers to 
the tree database.
1: REMOVE_CHILDREN - Remove the list of children QP 
numbers to the tree database
2: WRITE_TREE - Write the parent QPn as well as the list of 
children QP numbers
3: SET_PARENT - Set the tree parent. */
	/* 0x0.28 - 0x0.31 */
	 u_int8_t opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Small data tree_id used for big data lock operation of this tree. Valid only if tree_mode == 1  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t small_data_tree_id;
	/* Description - Maximal value for B2B credits in HBA SLP operation is 2^log_max_streaming_op. log_max_streaming_op = 0 indicates single HBA operation (B2B credits = 1) */
	/* 0x4.16 - 0x4.19 */
	 u_int8_t log_max_streaming_op;
	/* Description - Operation mode for the streaming aggregation semaphore
0: lock is performed using llt. No limitation for number of credits
1: lock is performed using llt. Number of operations for a single lock is limited by log_max_streaming_op
2: Semaphore is constantly locked. */
	/* 0x4.24 - 0x4.27 */
	 u_int8_t streaming_lock_mode;
	/* Description - 0: small data / packets aggregation, 1: big data aggregation. Valid only in WRITE_TREE */
	/* 0x4.28 - 0x4.31 */
	 u_int8_t tree_mode;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Parent QP Number
parent_qpn = 0 indicates NULL QP, for tree root.
Reserved for opcodes ADD_CHILDREN, REMOVE_CHIL
DREN */
	/* 0x8.0 - 0x8.23 */
	 u_int32_t parent_qpn;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Number of 
entries in the children list */
	/* 0xc.0 - 0xc.7 */
	 u_int8_t num_of_children;
	/* Description - Used for querying the trees children QP table. Use record_locator=0 to initiate the query. When a record is returned, a new record_locator is returned to be used in the subsequent query. This field is reserved for Set() operations. */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t record_locator;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - List of childs */
	/* 0x10.0 - 0xbc.31 */
	 struct child_qp child_qp[44];
};

/* Description -   */
/* Size in bytes - 128 */
struct CACongestionEntryList {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - List of sixteen CACongestionEntries, one per service level. (See Table 519 on Page 1684.) */
	/* 0x0.0 - 0x7c.31 */
	 struct CACongestionEntryListElement CACongestionEntryListElement[16];
};

/* Description -   */
/* Size in bytes - 128 */
struct CCTI_Entry_List {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - List of up to 64 CongestionControlTableEntries. see table 521 p1686 for data format */
	/* 0x0.16 - 0x80.15 */
	 struct CCTI_Entry_ListElement CCTI_Entry_ListElement[64];
};

/* Description -   */
/* Size in bytes - 16 */
struct CC_CongestionKeyInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Congestion Control key, is used to validate the source of Congestion Control Mads. A value of 0 means that no CC_Key checks is ever performed by the CCMgrA. */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t CC_Key;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - How long the CC Key protect bit is to remain non-zero. */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t CC_KeyLeasePeriod;
	/* Description -  */
	/* 0x8.31 - 0x8.31 */
	 u_int8_t CC_KeyProtectBit;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Number of received MADs that violated CC Key. */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t CC_KeyViolations;
};

/* Description -   */
/* Size in bytes - 56 */
struct CC_KeyViolation {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t Method;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t SourceLID;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t ArrtibuteID;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t AttributeModifier;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.8 - 0xc.31 */
	 u_int32_t QP;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Congestion Control key, is used to validate the source of Congestion Control Mads. */
	/* 0x10.0 - 0x14.31 */
	 u_int64_t CC_Key;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x24.31 */
	 struct GID_Block_Element SourceGID;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.24 - 0x38.23 */
	 u_int8_t Padding[16];
};

/* Description -   */
/* Size in bytes - 76 */
struct CC_SwitchCongestionSetting {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct CC_SwitchCongestionSetting_Control_Map Control_Map;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - If the bit is set to 1, then the port corresponding to that bit shall mark packets that enconter congestion with a FECN, wheter they are the source or victim of congestion. */
	/* 0x4.0 - 0x20.31 */
	 struct UINT256 Victim_Mask;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - If the bit is set to 1, then the port corresponding to that bit shall apply Credit Starvation. */
	/* 0x24.0 - 0x40.31 */
	 struct UINT256 Credit_Mask;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description -  */
	/* 0x44.12 - 0x44.15 */
	 u_int8_t CS_Threshold;
	/* Description -  */
	/* 0x44.16 - 0x44.23 */
	 u_int8_t Packet_Size;
	/* Description -  */
	/* 0x44.28 - 0x44.31 */
	 u_int8_t Threshold;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x48.15 */
	 u_int16_t Marking_Rate;
	/* Description -  */
	/* 0x48.16 - 0x48.31 */
	 u_int16_t CS_ReturnDelay;
};

/* Description -   */
/* Size in bytes - 128 */
struct CC_SwitchPortCongestionSetting {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - see table 516 and table 517 p1681 for data format */
	/* 0x0.0 - 0x7c.31 */
	 struct SwitchPortCongestionSettingElement SwitchPortCongestionSettingElement[32];
};

/* Description -  array of at most 15 recent events */
/* Size in bytes - 180 */
struct CongestionEntryListSwitch {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xb0.31 */
	 struct CongestionEntryListSwitchElement CongestionEntryListSwitchElement[15];
};

/* Description -  array of at most 13 recent events */
/* Size in bytes - 208 */
struct CongestionLogEventListCA {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xcc.31 */
	 struct CongestionLogEventListCAElement CongestionLogEventListCAElement[13];
};

/* Description -   */
/* Size in bytes - 216 */
union DD_set {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	 struct VS_DC_TransportErrorsAndFlowsV2 TransportErrorsAndFlowsV2;
	/* Description -  */
	/* 0x0.0 - 0x64.31 */
	 struct VS_DC_Page1LatestVersion Page1LatestVersion;
	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	 struct VS_DC_Page255LatestVersion Page255LatestVersion;
	/* Description -  */
	/* 0x0.0 - 0xd4.31 */
	 struct DataBuffer gen_set;
};

/* Description -  FW Info */
/* Size in bytes - 64 */
struct FWInfo_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t SubMinor;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t Minor;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t Major;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Reserved8;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t BuildID;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t Year;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	 u_int8_t Day;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	 u_int8_t Month;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.15 */
	 u_int16_t Hour;
	/* Description -  */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t Reserved16;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x1c.31 */
	 struct PSID_Block_Element PSID;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t INI_File_Version;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.31 */
	 u_int32_t Extended_Major;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	 u_int32_t Extended_Minor;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.31 */
	 u_int32_t Extended_SubMinor;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x3c.31 */
	 u_int32_t Reserved[4];
};

/* Description -   */
/* Size in bytes - 224 */
struct GMP_AccessRegister {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.3 */
	 u_int8_t reg_current_rev;
	/* Description -  */
	/* 0x0.8 - 0x0.11 */
	 u_int8_t reg_backward_rev;
	/* Description -  */
	/* 0x0.16 - 0x0.19 */
	 u_int8_t block;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0xdc.31 */
	 struct acc_register_gmp reg;
};

/* Description -   */
/* Size in bytes - 64 */
struct GUID_Block_Element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct uint64bit GUID[8];
};

/* Description -  Atomic ACK Extended Transport Header */
/* Size in bytes - 8 */
struct IB_AtomicAckETH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Return operand in atomic operations and contains the data in the remote memory location before the atomic operationIndicates if this is an ACK or NAK packet plus additional information about the ACK or NAKRemote virtual address */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t OrigRemDt;
};

/* Description -  Atomic Extended Transport Header */
/* Size in bytes - 28 */
struct IB_AtomicETH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Remote virtual address */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t VA;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Remote Key that authorizes access to the remote virtual address */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t R_Key;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Operand in atomic operations */
	/* 0xc.0 - 0x10.31 */
	 u_int64_t SwapDt;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Operand in CmpSwap atomic operation */
	/* 0x14.0 - 0x18.31 */
	 u_int64_t CmpDt;
};

/* Description -  Base Transport Header */
/* Size in bytes - 12 */
struct IB_BTH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 struct P_Key_Block_Element P_Key;
	/* Description - Transport Header Version (is set to 0x0) */
	/* 0x0.16 - 0x0.19 */
	 u_int8_t TVer;
	/* Description - Pad Count */
	/* 0x0.20 - 0x0.21 */
	 u_int8_t PadCnt;
	/* Description - If zero, it means there is no change in current migration state */
	/* 0x0.22 - 0x0.22 */
	 u_int8_t MigReq;
	/* Description - Solicited Event */
	/* 0x0.23 - 0x0.23 */
	 u_int8_t SE;
	/* Description - operation code (011_00100 - UD_SEND_only) */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t OpCode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Destination QP */
	/* 0x4.0 - 0x4.23 */
	 u_int32_t DestQP;
	/* Description - Reserved(variant) - 8 bits. TX - 0, RX - ignore. Not included in ICRC */
	/* 0x4.24 - 0x4.31 */
	 u_int8_t Rsv8;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Packet Sequence Number */
	/* 0x8.0 - 0x8.23 */
	 u_int32_t PSN;
	/* Description - TX - 0, RX - ignore. This field is included in the ICRC */
	/* 0x8.24 - 0x8.30 */
	 u_int8_t Rsv7;
	/* Description - Requests responder to schedule an ACK on the associated QP */
	/* 0x8.31 - 0x8.31 */
	 u_int8_t AckReq;
};

/* Description -  Base Transport Header for CNP */
/* Size in bytes - 12 */
struct IB_BTH_CNP {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 struct P_Key_Block_Element P_Key;
	/* Description - Transport Header Version (is set to 0x0) */
	/* 0x0.16 - 0x0.19 */
	 u_int8_t TVer;
	/* Description - Pad Count */
	/* 0x0.20 - 0x0.21 */
	 u_int8_t PadCnt;
	/* Description - If zero, it means there is no change in current migration state */
	/* 0x0.22 - 0x0.22 */
	 u_int8_t MigReq;
	/* Description - Solicited Event */
	/* 0x0.23 - 0x0.23 */
	 u_int8_t SE;
	/* Description - operation code (011_00100 - UD_SEND_only) */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t OpCode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Destination QP */
	/* 0x4.0 - 0x4.23 */
	 u_int32_t DestQP;
	/* Description - Reserved(variant) - 6 bits. TX - 0, RX - ignore. Not included in ICRC */
	/* 0x4.24 - 0x4.29 */
	 u_int8_t Rsv6;
	/* Description -  */
	/* 0x4.30 - 0x4.30 */
	 u_int8_t Becn;
	/* Description -  */
	/* 0x4.31 - 0x4.31 */
	 u_int8_t Fecn;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Packet Sequence Number */
	/* 0x8.0 - 0x8.23 */
	 u_int32_t PSN;
	/* Description - TX - 0, RX - ignore. This field is included in the ICRC */
	/* 0x8.24 - 0x8.30 */
	 u_int8_t Rsv7;
	/* Description - Requests responder to schedule an ACK on the associated QP */
	/* 0x8.31 - 0x8.31 */
	 u_int8_t AckReq;
};

/* Description -   */
/* Size in bytes - 72 */
struct IB_ClassPortInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Supported capabilities of this management class, 
Bit set to 1 for affirmation of management support. 
Bit 0 - If 1, the management class generates Trap() MADs Bit 1 - If 1, the management class implements Get(Notice) and Set(Notice) 
Bit 2-7: reserved 
Bit 8: Switch only - set if the EnhancedPort0 supports CA Congestion Control. (Note a switch can support Congestion control on data ports without supporting it on EnhancedPort0) 
Bit 9-15: class-specific capabilities. */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t CapMsk;
	/* Description - Current supported management class version. 
Indicates that this channel adapter, switch, or router supports up to and including this version. */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t ClassVersion;
	/* Description - Current supported MAD Base Version. 
Indicates that this channel adapter, switch, or router supports up to and including this version. */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t BaseVersion;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - See 13.4.6.2 Timers and Timeouts . */
	/* 0x4.0 - 0x4.4 */
	 u_int8_t RespTimeValue;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The GID a requester shall use as the destination GID in the GRH of messages used to access redirected class services. */
	/* 0x8.0 - 0x14.31 */
	 struct uint64bit RedirectGID[2];
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The Flow Label a requester shall use in the GRH of messages used to access redirected class services. */
	/* 0x18.0 - 0x18.19 */
	 u_int32_t RedirectFL;
	/* Description - The SL a requester shall use to access the class services. */
	/* 0x18.20 - 0x18.23 */
	 u_int8_t RedirectSL;
	/* Description - The Traffic Class a requester shall use in the GRH of messages used to access redirected class services. */
	/* 0x18.24 - 0x18.31 */
	 u_int8_t RedirectTC;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - The P_Key a requester shall use to access the class services. */
	/* 0x1c.0 - 0x1c.15 */
	 u_int16_t RedirectPKey;
	/* Description - If this value is non-zero, it is the DLID a requester shall use to access the class services. */
	/* 0x1c.16 - 0x1c.31 */
	 u_int16_t RedirectLID;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The QP a requester shall use to access the class services. Zero is illegal. */
	/* 0x20.0 - 0x20.23 */
	 u_int32_t RedirectQP;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The Q_Key associated with the RedirectQP. This Q_Key shall be set to the well known Q_Key. */
	/* 0x24.0 - 0x24.31 */
	 u_int32_t RedirectQKey;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The GID to be used as the destination GID in the GRH of Trap() messages originated by this service. */
	/* 0x28.0 - 0x34.31 */
	 u_int32_t TrapGID[4];
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - The Flow Label to be placed in the GRH of Trap() messages originated by this service. */
	/* 0x38.0 - 0x38.19 */
	 u_int32_t TrapFL;
	/* Description - The SL that shall be used when sending Trap() messages originated by this service. */
	/* 0x38.20 - 0x38.23 */
	 u_int8_t TrapSL;
	/* Description - The Traffic Class to be placed in the GRH of Trap() messages originated by this service. */
	/* 0x38.24 - 0x38.31 */
	 u_int8_t TrapTC;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - The P_Key to be placed in the header for traps originated by this service. */
	/* 0x3c.0 - 0x3c.15 */
	 u_int16_t TrapPKey;
	/* Description - The DLID to where Trap() messages shall be sent by this service. */
	/* 0x3c.16 - 0x3c.31 */
	 u_int16_t TrapLID;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - The QP to which Trap() messages originated by this service shall be sent. The value shall not be zero. */
	/* 0x40.0 - 0x40.23 */
	 u_int32_t TrapQP;
	/* Description - The Hop Limit to be placed in the GRH of Trap() messages originated by this service. The default value is 255. */
	/* 0x40.24 - 0x40.31 */
	 u_int8_t TrapHL;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - The Q_Key associated with the TrapQP. */
	/* 0x44.0 - 0x44.31 */
	 u_int32_t TrapQKey;
};

/* Description -  Global Routing Header */
/* Size in bytes - 40 */
struct IB_GRH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  This field identifies sequences of packets requiring special handling. */
	/* 0x0.0 - 0x0.19 */
	 u_int32_t FlowLabel;
	/* Description - This field is used by IBA to communicate global service level. */
	/* 0x0.20 - 0x0.27 */
	 u_int8_t TClass;
	/* Description - This field indicates version of the GRH */
	/* 0x0.28 - 0x0.31 */
	 u_int8_t IPVer;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This field sets a strict bound on the number of hops
between subnets a packet can make before being discarded.
This is enforced only by routers. */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t HopLmt;
	/* Description - This field identifies the header following the GRH.
This field is included for compatibility with IPV6 headers.
It should indicate IBA transport. */
	/* 0x4.8 - 0x4.15 */
	 u_int8_t NxtHdr;
	/* Description - For an IBA packet this field specifies the number of bytes
starting from the first byte after the GRH,
up to and including the last byte of the ICRC.
For a raw IPv6 datagram this field specifies the number
of bytes starting from the first byte after the GRH,
up to but not including either the VCRC or any padding,
to achieve a multiple of 4 byte packet length.
For raw IPv6 datagrams padding is determined
from the lower 2 bits of this GRH:PayLen field.
Note: GRH:PayLen is different from LRH:PkyLen. */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t PayLen;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x14.31 */
	 struct GID_Block_Element SGID;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x24.31 */
	 struct GID_Block_Element DGID;
};

/* Description -  RDMA Extended Transport Header Fields */
/* Size in bytes - 16 */
struct IB_RETH {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Virtual Address of the RDMA operation */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t VA;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Remote Key that authorizes access for the RDMA operation */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t R_Key;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Indicates the length (in Bytes) of the DMA operation */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t DMALen;
};

/* Description -  MAD Header Common */
/* Size in bytes - 24 */
struct MAD_Header_Common {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Method to perform Based on Management Class */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t Method;
	/* Description - Version of MAD class-specific format */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t ClassVersion;
	/* Description - Class of operation */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t MgmtClass;
	/* Description - Version of MAD base format */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t BaseVersion;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This field is reserved except for the Subnet Management Class */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t ClassSpecific;
	/* Description - Code indicating status of operation */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t Status;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t TID_Block_Element;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t Rsv16;
	/* Description - Defines objects being operated by a management class (Page 658) */
	/* 0x10.16 - 0x10.31 */
	 u_int16_t AttributeID;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Provides further scope to the attributes */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t AttributeModifier;
};

/* Description -  MAD Header Common With RMPP */
/* Size in bytes - 36 */
struct MAD_Header_Common_With_RMPP {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Method to perform Based on Management Class */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t Method;
	/* Description - Version of MAD class-specific format */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t ClassVersion;
	/* Description - Class of operation */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t MgmtClass;
	/* Description - Version of MAD base format */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t BaseVersion;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This field is reserved except for the Subnet Management Class */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t ClassSpecific;
	/* Description - Code indicating status of operation */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t Status;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t TID_Block_Element;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t Rsv16;
	/* Description - Defines objects being operated by a management class (Page 658) */
	/* 0x10.16 - 0x10.31 */
	 u_int16_t AttributeID;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Provides further scope to the attributes */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t AttributeModifier;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.7 */
	 u_int8_t RMPPStatus;
	/* Description -  */
	/* 0x18.8 - 0x18.11 */
	 u_int8_t RMPPFlags;
	/* Description -  */
	/* 0x18.12 - 0x18.15 */
	 u_int8_t RRespTime;
	/* Description - Indicates the type of RMPP packet being transferred. */
	/* 0x18.16 - 0x18.23 */
	 u_int8_t RMPPType;
	/* Description - Version of RMPP. Shall be set to the version of RMPP implemented. */
	/* 0x18.24 - 0x18.31 */
	 u_int8_t RMPPVersion;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t Data1;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t Data2;
};

/* Description -  MAD Header for SMP Direct Routed  */
/* Size in bytes - 24 */
struct MAD_Header_SMP_Direct_Routed {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Method to perform Based on Management Class */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t Method;
	/* Description - Version of MAD class-specific format */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t ClassVersion;
	/* Description - Class of operation */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t MgmtClass;
	/* Description - Version of MAD base format */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t BaseVersion;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Used in The direct route */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t HopCounter;
	/* Description - Used in The direct route */
	/* 0x4.8 - 0x4.15 */
	 u_int8_t HopPointer;
	/* Description - Code indicating status of operation */
	/* 0x4.16 - 0x4.30 */
	 u_int16_t Status;
	/* Description - direction of direct route packet */
	/* 0x4.31 - 0x4.31 */
	 u_int8_t D;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t TID_Block_Element;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t Rsv16;
	/* Description - Defines objects being operated by a management class (Page 658) */
	/* 0x10.16 - 0x10.31 */
	 u_int16_t AttributeID;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Provides further scope to the attributes */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t AttributeModifier;
};

/* Description -   */
/* Size in bytes - 16 */
struct NextHopRecord {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t SubnetPrefix;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t Pkey;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	 u_int8_t Weight;
};

/* Description -   */
/* Size in bytes - 44 */
struct PM_PortCounters {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 struct PortCounters_Mask_Block_Element CounterSelect;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Reserved0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t LinkDownedCounter;
	/* Description -  */
	/* 0x4.8 - 0x4.15 */
	 u_int8_t LinkErrorRecoveryCounter;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t SymbolErrorCounter;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t PortRcvRemotePhysicalErrors;
	/* Description -  */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t PortRcvErrors;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.15 */
	 u_int16_t PortXmitDiscards;
	/* Description -  */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t PortRcvSwitchRelayErrors;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.3 */
	 u_int8_t ExcessiveBufferOverrunErrors;
	/* Description -  */
	/* 0x10.4 - 0x10.7 */
	 u_int8_t LocalLinkIntegrityErrors;
	/* Description -  */
	/* 0x10.8 - 0x10.15 */
	 struct PortCounters_Mask2_Block_Element CounterSelect2;
	/* Description -  */
	/* 0x10.16 - 0x10.23 */
	 u_int8_t PortRcvConstraintErrors;
	/* Description -  */
	/* 0x10.24 - 0x10.31 */
	 u_int8_t PortXmitConstraintErrors;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.15 */
	 u_int16_t VL15Dropped;
	/* Description -  */
	/* 0x14.16 - 0x14.31 */
	 u_int16_t Reserved2;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t PortXmitData;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t PortRcvData;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t PortXmitPkts;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.31 */
	 u_int32_t PortRcvPkts;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	 u_int32_t PortXmitWait;
};

/* Description -   */
/* Size in bytes - 72 */
struct PM_PortCountersExtended {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 struct PortCountersExtended_Mask_Block_Element CounterSelect;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Reserved0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t Reserved1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of data octets, divided by 4, transmitted on all VLs from the port. This includes all octets between (and not including) the start of packet delimiter and the VCRC, and may include packets containing errors. */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t PortXmitData;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of data octets, divided by 4, received on all VLs at the port. This includes all octets between (and not including) the start of packet delimiter and the VCRC, and may include packets containing errors. */
	/* 0x10.0 - 0x14.31 */
	 u_int64_t PortRcvData;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of packets transmitted on all VLs from the port. */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t PortXmitPkts;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of packets, including packets containing errors */
	/* 0x20.0 - 0x24.31 */
	 u_int64_t PortRcvPkts;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of packets, including packets containing errors */
	/* 0x28.0 - 0x2c.31 */
	 u_int64_t PortUniCastXmitPkts;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of packets, including packets containing errors */
	/* 0x30.0 - 0x34.31 */
	 u_int64_t PortUniCastRcvPkts;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of packets, including packets containing errors */
	/* 0x38.0 - 0x3c.31 */
	 u_int64_t PortMultiCastXmitPkts;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Optional; shall be zero if not implemented. Total number of packets, including packets containing errors */
	/* 0x40.0 - 0x44.31 */
	 u_int64_t PortMultiCastRcvPkts;
};

/* Description -   */
/* Size in bytes - 140 */
struct PM_PortExtendedSpeedsCounters {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bit 0 - SyncHeaderErrorCounter
Bit 1 - UnknownBlockCounter
Bit 2 - ErrorDetectionCounterLane0
Bit 3 ErrorDetectionCounterLane1
Bit 4 ErrorDetectionCounterLane2
Bit 5 ErrorDetectionCounterLane3
Bit 6 ErrorDetectionCounterLane4
Bit 7 ErrorDetectionCounterLane5
Bit 8 ErrorDetectionCounterLane6
Bit 9 ErrorDetectionCounterLane7
Bit 10 ErrorDetectionCounterLane8
Bit 11 ErrorDetectionCounterLane9
Bit 12 ErrorDetectionCounterLane10
Bit 13 ErrorDetectionCounterLane11
Bit 14 FECCorrectableBlockCounterLane0
Bit 15 FECCorrectableBlockCounterLane1
Bit 16 FECCorrectableBlockCounterLane2
Bit 17 FECCorrectableBlockCounterLane3
Bit 18 FECCorrectableBlockCounterLane4
Bit 19 FECCorrectableBlockCounterLane5
Bit 20 FECCorrectableBlockCounterLane6
Bit 21 FECCorrectableBlockCounterLane7
Bit 22 FECCorrectableBlockCounterLane8
Bit 23 FECCorrectableBlockCounterLane9
Bit 24 FECCorrectableBlockCounterLane10
Bit 25 FECCorrectableBlockCounterLane11
Bit 26 FECUncorrectableBlockCounterLane0
Bit 27 FECUncorrectableBlockCounterLane1
Bit 28 FECUncorrectableBlockCounterLane2
Bit 29 FECUncorrectableBlockCounterLane3
Bit 30 FECUncorrectableBlockCounterLane4
Bit 31 FECUncorrectableBlockCounterLane5
Bit 32 FECUncorrectableBlockCounterLane6
Bit 33 FECUncorrectableBlockCounterLane7
Bit 34 FECUncorrectableBlockCounterLane8
Bit 35 FECUncorrectableBlockCounterLane9
Bit 36 FECUncorrectableBlockCounterLane10
Bit 37 FECUncorrectableBlockCounterLane11
Bits 38-63 - Reserved

 */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t CounterSelect;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t UnknownBlockCounter;
	/* Description -  */
	/* 0x10.16 - 0x10.31 */
	 u_int16_t SyncHeaderErrorCounter;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.16 - 0x2c.15 */
	 u_int16_t ErrorDetectionCounterLane[12];
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x58.31 */
	 u_int32_t FECCorrectableBlockCountrLane[12];
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description -  */
	/* 0x5c.0 - 0x88.31 */
	 u_int32_t FECUncorrectableBlockCounterLane[12];
};

/* Description -   */
/* Size in bytes - 152 */
struct PM_PortExtendedSpeedsRSFECCounters {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bit 0 - SyncHeaderErrorCounter
Bit 1 - UnknownBlockCounter
Bit 2 - ErrorDetectionCounterLane0
Bit 3 ErrorDetectionCounterLane1
Bit 4 ErrorDetectionCounterLane2
Bit 5 ErrorDetectionCounterLane3
Bit 6 ErrorDetectionCounterLane4
Bit 7 ErrorDetectionCounterLane5
Bit 8 ErrorDetectionCounterLane6
Bit 9 ErrorDetectionCounterLane7
Bit 10 ErrorDetectionCounterLane8
Bit 11 ErrorDetectionCounterLane9
Bit 12 ErrorDetectionCounterLane10
Bit 13 ErrorDetectionCounterLane11
Bit 14 FECCorrectedSymbolCounterLane0
Bit 15 FECCorrectedSymbolCounterLane1
Bit 16 FECCorrectedSymbolCounterLane2
Bit 17 FECCorrectedSymbolCounterLane3
Bit 18 FECCorrectedSymbolCounterLane4
Bit 19 FECCorrectedSymbolCounterLane5
Bit 20 FECCorrectedSymbolCounterLane6
Bit 21 FECCorrectedSymbolCounterLane7
Bit 22 FECCorrectedSymbolCounterLane8
Bit 23 FECCorrectedSymbolCounterLane9
Bit 24 FECCorrectedSymbolCounterLane10
Bit 25 FECCorrectedSymbolCounterLane11
Bits 26-37 - Reserved
Bit 38 PortFECCorrectableBlockCounter
Bit 39 PortFECUncorrectableBlockCounter
Bit 40 PortFECCorrectedSymbolCounter

 */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t CounterSelect;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t UnknownBlockCounter;
	/* Description -  */
	/* 0x10.16 - 0x10.31 */
	 u_int16_t SyncHeaderErrorCounter;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x58.31 */
	 u_int32_t FECCorrectedSymbolCounterLane[12];
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description -  */
	/* 0x8c.0 - 0x8c.31 */
	 u_int32_t PortFECCorrectableBlockCounter;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description -  */
	/* 0x90.0 - 0x90.31 */
	 u_int32_t PortFECUncorrectableBlockCounter;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description -  */
	/* 0x94.0 - 0x94.31 */
	 u_int32_t PortFECCorrectedSymbolCounter;
};

/* Description -   */
/* Size in bytes - 64 */
struct PM_PortRcvErrorDetails {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 struct PortRcvErrorDetails_Mask_Block_Element CounterSelect;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
	/* Description - Reserved */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Reserved;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t PortMalformedPacketErrors;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t PortLocalPhysicalErrors;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t PortDLIDMappingErrors;
	/* Description -  */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t PortBufferOverrunErrors;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.15 */
	 u_int16_t PortLoopingErrors;
	/* Description -  */
	/* 0xc.16 - 0xc.31 */
	 u_int16_t PortVLMappingErrors;
};

/* Description -   */
/* Size in bytes - 104 */
struct PM_PortSamplesControl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.2 */
	 u_int8_t CounterWidth;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t Tick;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t OpCode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.26 */
	 u_int32_t CounterMasks1to9;
	/* Description -  */
	/* 0x4.27 - 0x4.29 */
	 u_int8_t CounterMask0;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.1 */
	 u_int8_t SampleStatus;
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	 u_int8_t SampleMechanisms;
	/* Description -  */
	/* 0x8.16 - 0x8.30 */
	 u_int16_t CounterMasks10to14;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0x10.31 */
	 struct PortSampleControlOptionMask PortSampleControlOptionMask;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x18.31 */
	 u_int64_t VendorMask;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	 u_int32_t SampleStart;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t SampleInterval;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x40.15 */
	 u_int16_t CounterSelect[15];
	/* Description -  */
	/* 0x24.16 - 0x24.31 */
	 u_int16_t Tag;
};

/* Description -   */
/* Size in bytes - 64 */
struct PM_PortXmitDiscardDetails {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 struct PortXmitDiscardDetails_Mask_Block_Element CounterSelect;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
	/* Description - Reserved */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Reserved;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t PortNeighborMTUDiscards;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t PortInactiveDiscards;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t PortSwHOQLifetimeLimitDiscards;
	/* Description -  */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t PortSwLifetimeLimitDiscards;
};

/* Description -   */
/* Size in bytes - 132 */
struct RawData_PM_PortRcvXmitCntrsSl64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t reserved;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x80.31 */
	 struct uint64bit DataVLSL64[16];
};

/* Description -   */
/* Size in bytes - 128 */
struct RawData_PM_PortRcvXmitCntrsVl64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	 struct uint64bit DataVLSL64[16];
};

/* Description -   */
/* Size in bytes - 52 */
struct SA_MCMMemberRecord {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	 struct GID_Block_Element MGID;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x1c.31 */
	 struct GID_Block_Element PortGID;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t Q_key;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.7 */
	 u_int8_t TClass;
	/* Description -  */
	/* 0x24.8 - 0x24.13 */
	 u_int8_t MTU;
	/* Description -  */
	/* 0x24.14 - 0x24.15 */
	 u_int8_t MTUSelector;
	/* Description -  */
	/* 0x24.16 - 0x24.31 */
	 u_int16_t MLID;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.5 */
	 u_int8_t PacketLifeTime;
	/* Description -  */
	/* 0x28.6 - 0x28.7 */
	 u_int8_t PacketLifeTimeSelector;
	/* Description -  */
	/* 0x28.8 - 0x28.13 */
	 u_int8_t Rate;
	/* Description -  */
	/* 0x28.14 - 0x28.15 */
	 u_int8_t RateSelector;
	/* Description -  */
	/* 0x28.16 - 0x28.31 */
	 u_int16_t P_Key;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.7 */
	 u_int8_t HopLimit;
	/* Description -  */
	/* 0x2c.8 - 0x2c.27 */
	 u_int32_t FlowLabel;
	/* Description -  */
	/* 0x2c.28 - 0x2c.31 */
	 u_int8_t SL;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.22 */
	 u_int32_t Reserved;
	/* Description -  */
	/* 0x30.23 - 0x30.23 */
	 u_int8_t ProxyJoin;
	/* Description -  */
	/* 0x30.24 - 0x30.27 */
	 u_int8_t JoinState;
	/* Description -  */
	/* 0x30.28 - 0x30.31 */
	 u_int8_t Scope;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_AccessRegister {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.8 - 0x0.14 */
	 u_int8_t status;
	/* Description -  */
	/* 0x0.15 - 0x0.15 */
	 u_int8_t dr;
	/* Description -  */
	/* 0x0.16 - 0x0.26 */
	 u_int16_t len_op;
	/* Description -  */
	/* 0x0.27 - 0x0.31 */
	 u_int8_t type_op;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t class_op;
	/* Description -  */
	/* 0x4.8 - 0x4.14 */
	 u_int8_t method;
	/* Description -  */
	/* 0x4.15 - 0x4.15 */
	 u_int8_t r;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t register_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t tid_hi;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t tid_lo;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.16 - 0x10.26 */
	 u_int16_t len_reg;
	/* Description -  */
	/* 0x10.27 - 0x10.31 */
	 u_int8_t type_reg;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x3c.31 */
	 struct acc_register reg;
};

/* Description -  Router Adjacent Site Local Subnets Table */
/* Size in bytes - 64 */
struct SMP_AdjSiteLocalSubnTbl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct AdjSiteLocalSubnetRecord Record[8];
};

/* Description -  0x28 */
/* Size in bytes - 40 */
struct SMP_NodeInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of physical ports on this node. */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t NumPorts;
	/* Description - 1: Channel Adapter 2: Switch 3: Router 0, 4 - 255: Reserved
 */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t NodeType;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t ClassVersion;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t BaseVersion;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x8.31 */
	 u_int64_t SystemImageGUID;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0x10.31 */
	 u_int64_t NodeGUID;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x18.31 */
	 u_int64_t PortGUID;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Device ID information as assigned by device manufacturer. */
	/* 0x1c.0 - 0x1c.15 */
	 u_int16_t DeviceID;
	/* Description - Number of entries in the Partition Table for CA, router, and the switch management port. This is at a minimum set to 1 for all nodes including switches. */
	/* 0x1c.16 - 0x1c.31 */
	 u_int16_t PartitionCap;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Device revision, assigned by manufacturer. */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t revision;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.23 */
	 u_int32_t VendorID;
	/* Description - Number of the link port which received this SMP. */
	/* 0x24.24 - 0x24.31 */
	 u_int8_t LocalPortNum;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_PKeyTable {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x40.15 */
	 struct P_Key_Block_Element PKey_Entry[32];
};

/* Description -  0x38 */
/* Size in bytes - 64 */
struct SMP_PortInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t MKey;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t GIDPrfx;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	 u_int16_t MSMLID;
	/* Description - offset  128 */
	/* 0x10.16 - 0x10.31 */
	 u_int16_t LID;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - offset  160 */
	/* 0x14.0 - 0x14.31 */
	 u_int32_t CapMsk;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.15 */
	 u_int16_t M_KeyLeasePeriod;
	/* Description - offset  192 */
	/* 0x18.16 - 0x18.31 */
	 u_int16_t DiagCode;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.7 */
	 u_int8_t LinkWidthActv;
	/* Description -  */
	/* 0x1c.8 - 0x1c.15 */
	 u_int8_t LinkWidthSup;
	/* Description -  */
	/* 0x1c.16 - 0x1c.23 */
	 u_int8_t LinkWidthEn;
	/* Description - offset  224 */
	/* 0x1c.24 - 0x1c.31 */
	 u_int8_t LocalPortNum;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.3 */
	 u_int8_t LinkSpeedEn;
	/* Description -  */
	/* 0x20.4 - 0x20.7 */
	 u_int8_t LinkSpeedActv;
	/* Description -  */
	/* 0x20.8 - 0x20.10 */
	 u_int8_t LMC;
	/* Description -  */
	/* 0x20.14 - 0x20.15 */
	 u_int8_t MKeyProtBits;
	/* Description -  */
	/* 0x20.16 - 0x20.19 */
	 u_int8_t LinkDownDefState;
	/* Description -  */
	/* 0x20.20 - 0x20.23 */
	 u_int8_t PortPhyState;
	/* Description -  */
	/* 0x20.24 - 0x20.27 */
	 u_int8_t PortState;
	/* Description - offset 256 */
	/* 0x20.28 - 0x20.31 */
	 u_int8_t LinkSpeedSup;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.7 */
	 u_int8_t VLArbHighCap;
	/* Description -  */
	/* 0x24.8 - 0x24.15 */
	 u_int8_t VLHighLimit;
	/* Description -  */
	/* 0x24.16 - 0x24.19 */
	 u_int8_t InitType;
	/* Description -  */
	/* 0x24.20 - 0x24.23 */
	 u_int8_t VLCap;
	/* Description -  */
	/* 0x24.24 - 0x24.27 */
	 u_int8_t MSMSL;
	/* Description - offset 288 */
	/* 0x24.28 - 0x24.31 */
	 u_int8_t NMTU;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.0 */
	 u_int8_t FilterRawOutb;
	/* Description -  */
	/* 0x28.1 - 0x28.1 */
	 u_int8_t FilterRawInb;
	/* Description -  */
	/* 0x28.2 - 0x28.2 */
	 u_int8_t PartEnfOutb;
	/* Description -  */
	/* 0x28.3 - 0x28.3 */
	 u_int8_t PartEnfInb;
	/* Description -  */
	/* 0x28.4 - 0x28.7 */
	 u_int8_t OpVLs;
	/* Description -  */
	/* 0x28.8 - 0x28.12 */
	 u_int8_t HoQLife;
	/* Description -  */
	/* 0x28.13 - 0x28.15 */
	 u_int8_t VLStallCnt;
	/* Description -  */
	/* 0x28.16 - 0x28.19 */
	 u_int8_t MTUCap;
	/* Description -  */
	/* 0x28.20 - 0x28.23 */
	 u_int8_t InitTypeReply;
	/* Description - offset 320 */
	/* 0x28.24 - 0x28.31 */
	 u_int8_t VLArbLowCap;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.15 */
	 u_int16_t PKeyViolations;
	/* Description -  */
	/* 0x2c.16 - 0x2c.31 */
	 u_int16_t MKeyViolations;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.4 */
	 u_int8_t SubnTmo;
	/* Description -  */
	/* 0x30.7 - 0x30.7 */
	 u_int8_t ClientReregister;
	/* Description -  */
	/* 0x30.8 - 0x30.15 */
	 u_int8_t GUIDCap;
	/* Description -  */
	/* 0x30.16 - 0x30.31 */
	 u_int16_t QKeyViolations;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.15 */
	 u_int16_t MaxCreditHint;
	/* Description -  */
	/* 0x34.16 - 0x34.19 */
	 u_int8_t OverrunErrs;
	/* Description -  */
	/* 0x34.20 - 0x34.23 */
	 u_int8_t LocalPhyError;
	/* Description -  */
	/* 0x34.24 - 0x34.28 */
	 u_int8_t RespTimeValue;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x38.23 */
	 u_int32_t LinkRoundTripLatency;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - offset 507 */
	/* 0x3c.0 - 0x3c.4 */
	 u_int8_t LinkSpeedExtEn;
	/* Description - offset 500 */
	/* 0x3c.8 - 0x3c.11 */
	 u_int8_t LinkSpeedExtSup;
	/* Description - offset 496 */
	/* 0x3c.12 - 0x3c.15 */
	 u_int8_t LinkSpeedExtActv;
	/* Description - offset 480 */
	/* 0x3c.16 - 0x3c.31 */
	 u_int16_t CapMsk2;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_QosConfigSL {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct BandwidthPerSL BandwidthPerSL[16];
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_RandomForwardingTable {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct LID_Port_Block_Element LID_Port_Block_Element[16];
};

/* Description -   */
/* Size in bytes - 24 */
struct SMP_SMInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t GUID;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t Sm_Key;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t ActCount;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.24 - 0x14.27 */
	 u_int8_t SmState;
	/* Description -  */
	/* 0x14.28 - 0x14.31 */
	 u_int8_t Priority;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_VLArbitrationTable {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x40.15 */
	 struct VL_Weight_Block_Element VLArb[32];
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_VNodeInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t vnum_ports;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t vlocal_port_num;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t vpartition_cap;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x8.31 */
	 u_int64_t vnode_guid;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_VPortInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Supported capabilities of this port. A bit set to 1 for affirmation of supported capability.0: IsCommunicationManagementSupported 1: IsSNMPTunnelingSupported 2: IsDeviceManagementSupported 3: IsVendorClassSupported 4: IsBootManagementSupported 5-15: Reserved */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t vport_capability_mask;
	/* Description - Number of GUID entries supported in the VPortGUIDInfo attribute for this virtual VPort. */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t vguid_cap;
	/* Description -  */
	/* 0x0.26 - 0x0.26 */
	 u_int8_t lid_required;
	/* Description - Optional: shall be 0 if not implemeneted(PortInfo:CapabilityMask.IsClientReregistrationSupported = 0). Used by SMto request VPort endnode clients reregistration of SA subscriptions. */
	/* 0x0.27 - 0x0.27 */
	 u_int8_t vport_client_reregister;
	/* Description - VPortState. Enumerated as: 0:No State Change;valid only on Set(). 1:Down(includes VPortEnable=False. 2:Initialize. 3:Armed. 4:Active. 5-15:Reserved. When writing this field, only legal transactions are valid. */
	/* 0x0.28 - 0x0.31 */
	 u_int8_t vport_state;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Counts the number of packets that have been received at this port that have had invalid Q_Keys, since power-on or reset. Increments till count reaches all 1s and then shall be set back to zero to re-enable incrementing. Setting this component to any value other than zero results in undefined behavior; however, it is recommended that any attempt to set the counter to a non-zero value results in it being left unchanged. */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t qkey_violations;
	/* Description - Counts the number of packets that have been received at this VPort that have had invalid P_Keys, since power-on or reset. Increments till count reaches all 1s and then shall be set back to zero to re-enable incrementing. Setting this component to any value other than zero results in undefined behavior; however, it is recommended that any attempt to set the counter to a non-zero value results in it being left unchanged. */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t pkey_violations;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t lid_by_vport_idx;
	/* Description -  */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t vport_lid;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0x10.31 */
	 u_int64_t vport_guid;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x18.31 */
	 u_int64_t vport_profile;
};

/* Description -   */
/* Size in bytes - 96 */
struct VendorSpec_PortLLRStatistics {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t Reserved1;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t PortSelect;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t Reserved2;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x8.31 */
	 u_int64_t PortRcvCells;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0x10.31 */
	 u_int64_t PortRcvCellForRetry;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x18.31 */
	 u_int64_t PortRcvRetry;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x20.31 */
	 u_int64_t PortXmitCells;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x28.31 */
	 u_int64_t PortXmitRetryCells;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x30.31 */
	 u_int64_t PortXmitRetry;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x38.31 */
	 u_int64_t PortSymbolError;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description -  */
	/* 0x3c.0 - 0x40.31 */
	 u_int64_t PortErrorDetectionCounterLane0;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description -  */
	/* 0x44.0 - 0x48.31 */
	 u_int64_t PortErrorDetectionCounterLane1;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description -  */
	/* 0x4c.0 - 0x50.31 */
	 u_int64_t PortErrorDetectionCounterLane2;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description -  */
	/* 0x54.0 - 0x58.31 */
	 u_int64_t PortErrorDetectionCounterLane3;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description -  */
	/* 0x5c.0 - 0x5c.15 */
	 u_int16_t MaxRetransmissionRate;
};

/* Description -   */
/* Size in bytes - 64 */
struct adaptive_routing_group_table_copy {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct adaptive_routing_group_table_copy_element element[16];
};

/* Description -   */
/* Size in bytes - 64 */
struct ib_ar_linear_forwarding_table_sx {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_ar_lft_block_element_sx LidEntry[16];
};

/* Description -   */
/* Size in bytes - 64 */
struct ib_port_sl_to_private_lft_map {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_port_sl_to_plft PortSLToPLFT[4];
};

/* Description -   */
/* Size in bytes - 32 */
struct ib_portgroup_block_element {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 u_int64_t SubGroup_3;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t SubGroup_2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	 u_int64_t SubGroup_1;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t SubGroup_0;
};

/* Description -   */
/* Size in bytes - 64 */
struct ib_private_lft_def {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_lft_def LFT[16];
};

/* Description -   */
/* Size in bytes - 64 */
struct ib_private_lft_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.2 */
	 u_int8_t Active_Mode;
	/* Description -  */
	/* 0x0.8 - 0x0.10 */
	 u_int8_t ModeCap;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t NumPLFTs;
	/* Description - When a standard LFT mad is processed it should check no_fallback state :
     0 - it should disable private lft. Erase all tables and reset port_base (SET_PRIVATE_LFT_INFO with active_mode == 0).
         1 - return error. */
	/* 0x0.24 - 0x0.24 */
	 u_int8_t NoFallback;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.16 - 0xc.15 */
	 struct ib_description_mode Description_Mode[4];
};

/* Description -   */
/* Size in bytes - 192 */
struct port_rn_counters {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t counter_select;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t port_select;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x8.31 */
	 u_int64_t port_rcv_rn_pkt;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0x10.31 */
	 u_int64_t port_xmit_rn_pkt;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x18.31 */
	 u_int64_t port_rcv_rn_error;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x20.31 */
	 u_int64_t port_rcv_switch_relay_rn_error;
};

/* Description -   */
/* Size in bytes - 64 */
struct rn_gen_by_sub_group_prio {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_gen_by_sub_group_prio_element element[16];
};

/* Description -   */
/* Size in bytes - 64 */
struct rn_gen_by_sub_group_priority {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_gen_by_sub_group_priority_element sub_group_priority_element[16];
};

/* Description -   */
/* Size in bytes - 64 */
struct rn_gen_string_tbl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x40.15 */
	 struct rn_gen_string_element element[32];
};

/* Description -   */
/* Size in bytes - 64 */
struct rn_rcv_string {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_rcv_string_element element[16];
};

/* Description -   */
/* Size in bytes - 132 */
struct CC_CACongestionSetting {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - List of sixteen CACongestionEntries, one per service level. */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t Control_Map;
	/* Description - Congestion attributes for this port: bit0 = 0: QP based CC; bit0 = 1: SL/Port based CC; All other bits are reserved. */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t Port_Control;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x80.31 */
	 struct CACongestionEntryList CACongestionEntryList;
};

/* Description -   */
/* Size in bytes - 132 */
struct CC_CongestionControlTable {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Maximum valid CCTI for this table. */
	/* 0x0.16 - 0x0.31 */
	 u_int16_t CCTI_Limit;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - List of up to 64 CongestionControlTableEntries. */
	/* 0x4.0 - 0x80.31 */
	 struct CCTI_Entry_List CCTI_Entry_List;
};

/* Description -   */
/* Size in bytes - 220 */
struct CC_CongestionLogCA {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of CongestionLogEvents since log last sent */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t ThresholdEventCounter;
	/* Description - Bit0 - 1: - CC_Key lease period timer active, Bit0 - 0: lease timer incative */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t CongestionFlags;
	/* Description - 0x1 - switch , 0x2 - CA */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t LogType;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - List of sixteen entries, one per service level. */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t ThresholdCongestionEventMap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 2^CurrentTimeStamp*1.24uSec = time stamp, wrap around ~1.22hr */
	/* 0x8.0 - 0x8.31 */
	 u_int32_t CurrentTimeStamp;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - for data format see spec 1.2.1 vol 1 p.1678 */
	/* 0xc.0 - 0xd8.31 */
	 struct CongestionLogEventListCA CongestionLogEvent;
};

/* Description -   */
/* Size in bytes - 220 */
struct CC_CongestionLogSwitch {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of CongestionLogEvents since log last sent */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t LogEventsCounter;
	/* Description - Bit0 - 1: CC_Key lease period timer active, Bit0 - 0: lease timer incative */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t CongestionFlags;
	/* Description - 0x1 - switch , 0x2 - CA */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t LogType;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 2^CurrentTimeStamp*1.24uSec = time stamp, wrap around ~1.22hr */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t CurrentTimeStamp;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - If a bit is set then the corresponding port has marked packets with FECN, bit 0 - reserve, bit 1 - port 1 */
	/* 0x8.0 - 0x24.31 */
	 struct UINT256 PortMap;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - for data format see spec 1.2.1 vol 1 p.1678 */
	/* 0x28.0 - 0xd8.31 */
	 struct CongestionEntryListSwitch CongestionEntryList;
};

/* Description -   */
/* Size in bytes - 80 */
struct CC_Notice {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t ProducerType_VendorID;
	/* Description -  */
	/* 0x0.24 - 0x0.30 */
	 u_int8_t Type;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t IsGeneric;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t IssuerLID;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t TrapNumber;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x3c.31 */
	 struct CC_KeyViolation CC_KeyViolation;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x4c.31 */
	 struct GID_Block_Element IssuerGID;
};

/* Description -  MAD Aggregation management Data Format */
/* Size in bytes - 256 */
struct MAD_AggregationManagement {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_Common MAD_Header_Common;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t am_key;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x3c.31 */
	 u_int32_t Reserved_Dword[8];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0xfc.31 */
	 struct AggregationManagement_MAD_Data_Block_Element Data;
};

/* Description -  MAD Performance management Data Format */
/* Size in bytes - 256 */
struct MAD_CongestionControl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_Common MAD_Header_Common;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Congestion Control key, is used to validate the source of Congestion Control Mads. */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t CC_Key;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x3c.31 */
	 struct CC_Log_Data_Block_Element CC_LogData;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0xfc.31 */
	 struct CC_Mgt_Data_Block_Element CC_MgtData;
};

/* Description -  MAD Performance management Data Format */
/* Size in bytes - 256 */
struct MAD_PerformanceManagement {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_Common MAD_Header_Common;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x3c.31 */
	 u_int32_t Reserved_Dword[10];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0xfc.31 */
	 struct PerfManagement_MAD_Data_Block_Element Data;
};

/* Description -  MAD SMP Data Format - Direct Routed */
/* Size in bytes - 256 */
struct MAD_SMP_Direct_Routed {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_SMP_Direct_Routed MAD_Header_SMP_Direct_Routed;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t M_Key;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Directed route destination LID. Used in directed routing. */
	/* 0x20.0 - 0x20.15 */
	 u_int16_t DrDLID;
	/* Description - Directed route source LID. Used in directed routing. */
	/* 0x20.16 - 0x20.31 */
	 u_int16_t DrSLID;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Reserved 28 bytes */
	/* 0x24.0 - 0x3c.31 */
	 u_int32_t Reserved[7];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x7c.31 */
	 struct SMP_MAD_Data_Block_Element Data;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description -  */
	/* 0x80.0 - 0xbc.31 */
	 struct DirRPath_Block_Element InitPath;
/*---------------- DWORD[48] (Offset 0xc0) ----------------*/
	/* Description -  */
	/* 0xc0.0 - 0xfc.31 */
	 struct DirRPath_Block_Element RetPath;
};

/* Description -  MAD SMP Data Format - Lid Routed */
/* Size in bytes - 256 */
struct MAD_SMP_LID_Routed {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_Common MAD_Header_Common;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t M_Key;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Reserved 32 bytes. */
	/* 0x20.0 - 0x3c.31 */
	 u_int32_t Reserved1[8];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x7c.31 */
	 struct SMP_MAD_Data_Block_Element Data;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Reserved 128 bytes. */
	/* 0x80.0 - 0xfc.31 */
	 u_int32_t Reserved2[32];
};

/* Description -  MAD Subnet Administration Data Format */
/* Size in bytes - 256 */
struct MAD_SubnetAdministartion {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	 struct MAD_Header_Common_With_RMPP MAD_Header_Common_With_RMPP;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x28.31 */
	 u_int64_t Sm_Key;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.15 */
	 u_int16_t Reserved;
	/* Description -  */
	/* 0x2c.16 - 0x2c.31 */
	 u_int16_t AttributeOffset;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	 u_int64_t ComponentMask;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0xfc.31 */
	 struct SubnetAdministartion_MAD_Data_Block_Element Data;
};

/* Description -  MAD Vendor Specific Data Format */
/* Size in bytes - 256 */
struct MAD_VendorSpec {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_Common MAD_Header_Common;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 u_int64_t V_Key;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0xfc.31 */
	 struct VendorSpecific_MAD_Data_Block_Element Data;
};

/* Description -   */
/* Size in bytes - 56 */
union NoticeDataDetails {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x34.31 */
	 struct AM_TrapQPError TrapQPError;
	/* Description -  */
	/* 0x0.0 - 0x34.31 */
	 struct AM_TrapQPError_V2 TrapQPError_V2;
	/* Description -  */
	/* 0x0.0 - 0x34.31 */
	 struct AM_TrapQPAllocationTime TrapQPAllocationTime;
	/* Description -  */
	/* 0x0.0 - 0x34.31 */
	 struct AM_TrapQPAllocationTime_V2 TrapQPAllocationTime_V2;
	/* Description -  */
	/* 0x0.0 - 0x34.31 */
	 struct AM_TrapSharpInvalidRequest TrapSharpInvalidRequest;
	/* Description -  */
	/* 0x0.0 - 0x34.31 */
	 struct AM_TrapSharpInvalidRequest_V2 TrapSharpInvalidRequest_V2;
	/* Description -  */
	/* 0x0.0 - 0x34.31 */
	 struct RawNoticeDataDetails RawData;
};

/* Description -   */
/* Size in bytes - 132 */
union PM_PortRcvXmitCntrsSlVlData {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct RawData_PM_PortRcvXmitCntrsSlVl32 Cntrs32Bit;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	 struct RawData_PM_PortRcvXmitCntrsVl64 CntrsVL64Bit;
	/* Description -  */
	/* 0x0.0 - 0x80.31 */
	 struct RawData_PM_PortRcvXmitCntrsSl64 CntrsSL64Bit;
	/* Description -  */
	/* 0x0.0 - 0x80.31 */
	 struct RawData_PM_PortRcvXmitCntrsSlVl RawData_8x132_array;
};

/* Description -   */
/* Size in bytes - 64 */
struct SMP_GUIDInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct GUID_Block_Element GUIDBlock;
};

/* Description -  Router Next Hop Table */
/* Size in bytes - 64 */
struct SMP_NextHopTbl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct NextHopRecord Record[4];
};

/* Description -   */
/* Size in bytes - 224 */
struct VS_DiagnosticData {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.3 */
	 u_int8_t CurrentRevision;
	/* Description -  */
	/* 0x0.8 - 0x0.11 */
	 u_int8_t BackwardRevision;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xdc.31 */
	 union DD_set data_set;
};

/* Description -   */
/* Size in bytes - 144 */
struct VendorSpec_GeneralInfo {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	 struct HWInfo_Block_Element HWInfo;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	 struct FWInfo_Block_Element FWInfo;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x7c.31 */
	 struct SWInfo_Block_Element SWInfo;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description -  */
	/* 0x80.0 - 0x8c.31 */
	 struct GeneralInfoCapabilityMask CapabilityMask;
};

/* Description -   */
/* Size in bytes - 64 */
struct ib_ar_group_table {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bit mask that represent the member of the group as indicated by attribute modifier */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_portgroup_block_element Group[2];
};

/* Description -   */
/* Size in bytes - 131072 */
union CONGESTION_CONTOL {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct CC_CongestionInfo CC_CongestionInfo;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	 struct CC_CongestionKeyInfo CC_CongestionKeyInfo;
	/* Description -  */
	/* 0x0.0 - 0xd8.31 */
	 struct CC_CongestionLogSwitch CC_CongestionLogSwitch;
	/* Description -  */
	/* 0x0.0 - 0xd8.31 */
	 struct CC_CongestionLogCA CC_CongestionLogCA;
	/* Description -  */
	/* 0x0.0 - 0x48.31 */
	 struct CC_SwitchCongestionSetting CC_SwitchCongestionSetting;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	 struct CC_SwitchPortCongestionSetting CC_SwitchPortCongestionSetting;
	/* Description -  */
	/* 0x0.0 - 0x80.31 */
	 struct CC_CACongestionSetting CC_CACongestionSetting;
	/* Description -  */
	/* 0x0.0 - 0x80.31 */
	 struct CC_CongestionControlTable CC_CongestionControlTable;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct CC_TimeStamp CC_TimeStamp;
	/* Description -  */
	/* 0x0.0 - 0x4c.31 */
	 struct CC_Notice CC_Notice;
};

/* Description -  Notice */
/* Size in bytes - 64 */
struct Notice {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - ProducerType/VendorID
If generic, indicates the type of the events producer:
1 - Channel Adapter
2 - Switch
3 - Router
4 - Class Manager
0, 5-0xFFFFFF - Reserved
If not generic, indicates the 24 bit IEEE OUI assigned to the vendor. */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t producer_type;
	/* Description - Enumeration indicating type of Trap()/notice:
0 - Fatal
1 - Urgent
2 - Security
3 - Subnet Management
4 - Informational
5-0x7E - Reserved
0x7F - Empty notice. All other fields are meaningless. */
	/* 0x0.24 - 0x0.30 */
	 u_int8_t type;
	/* Description - If set to 1, notice is generic, else is vendor specific */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t is_generic;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Issuer LID */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t issuer_lid;
	/* Description - If generic, indicates a class-defined trap number. Number 0xFFFF is reserved.
If not generic, this is Device ID information as assigned by device manufacturer. */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t trap_number;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Data details - 54 bytes */
	/* 0x8.0 - 0x3c.31 */
	 union NoticeDataDetails data_details;
};

/* Description -   */
/* Size in bytes - 136 */
struct PM_PortRcvXmitCntrsSlVl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t counter_select;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t port_select;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x84.31 */
	 union PM_PortRcvXmitCntrsSlVlData Data;
};

/* Description -   */
/* Size in bytes - 131072 */
union SMP_MADS {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_NodeDesc SMP_NodeDesc;
	/* Description -  */
	/* 0x0.0 - 0x24.31 */
	 struct SMP_NodeInfo SMP_NodeInfo;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_SwitchInfo SMP_SwitchInfo;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_GUIDInfo SMP_GUIDInfo;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_PortInfo SMP_PortInfo;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	 struct SMP_PortInfoExtended SMP_PortInfoExtended;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_PKeyTable SMP_PKeyTable;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 struct SMP_SLToVLMappingTable SMP_SLToVLMappingTable;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_VLArbitrationTable SMP_VLArbitrationTable;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_LinearForwardingTable SMP_LinearForwardingTable;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_RandomForwardingTable SMP_RandomForwardingTable;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_MulticastForwardingTable SMP_MulticastForwardingTable;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct SMP_SMInfo SMP_SMInfo;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct SMP_LedInfo SMP_LedInfo;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_MlnxExtPortInfo SMP_MlnxExtPortInfo;
	/* Description - General Info Capability Mask field set */
	/* 0x0.0 - 0xc.31 */
	 struct GeneralInfoCapabilityMask GeneralInfoCapabilityMask;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_private_lft_info private_lft_info;
	/* Description -  */
	/* 0x0.0 - 0x24.31 */
	 struct ib_private_lft_map private_lft_map;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_private_lft_def private_lft_def;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_port_sl_to_private_lft_map port_sl_to_private_lft_map;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct ib_extended_switch_info extended_switch_info;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	 struct adaptive_routing_info ar_info;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_ar_linear_forwarding_table_sx ar_linear_forwarding_table_sx;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct ib_ar_group_table ar_group_table;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct adaptive_routing_group_table_copy ar_group_table_copy;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_sub_group_direction_tbl rn_sub_group_direction_tbl;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_gen_string_tbl rn_gen_string_tbl;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_gen_by_sub_group_prio rn_gen_by_sub_group_prio;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_rcv_string rn_rcv_string;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct rn_xmit_port_mask rn_xmit_port_mask;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_VPortState SMP_VPortState;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_VPortInfo SMP_VPortInfo;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_VirtualizationInfo SMP_VirtualizationInfo;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_VNodeInfo SMP_VNodeInfo;
	/* Description - Router Info MAD */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_RouterInfo SMP_RouterInfo;
	/* Description - Router Adjacent Site Local Subnets Table */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_AdjSiteLocalSubnTbl SMP_AdjSiteLocalSubnTbl;
	/* Description - Router Next Hop Table */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_NextHopTbl SMP_NextHopTbl;
};

/* Description -   */
/* Size in bytes - 131072 */
union VENDOR_SPECS {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8c.31 */
	 struct VendorSpec_GeneralInfo VendorSpec_GeneralInfo;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	 struct VendorSpec_PortLLRStatistics VendorSpec_PortLLRStatistics;
	/* Description -  */
	/* 0x0.0 - 0xdc.31 */
	 struct VS_DiagnosticData VS_DiagnosticData;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_AccessRegister SMP_AccessRegister;
	/* Description -  */
	/* 0x0.0 - 0xdc.31 */
	 struct GMP_AccessRegister GMP_AccessRegister;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	 struct SMP_TempSensing SMP_TempSensing;
	/* Description -  */
	/* 0x0.0 - 0xbc.31 */
	 struct port_rn_counters VS_PortRNCounters;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct SMP_QosConfigSL SMP_QosConfigSL;
};

/* Description -   */
/* Size in bytes - 256 */
union AGGREGATION_MADS {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Table 114 - QPAllocation MAD Layout */
	/* 0x0.0 - 0x8c.31 */
	 struct AM_QPAllocation AM_QPAllocation;
	/* Description - Table 110 - AMKeyInfo MAD Layout */
	/* 0x0.0 - 0x8.31 */
	 struct AM_AMKeyInfo AM_AMKeyInfo;
	/* Description - Table 112 - ANInfo MAD Layout */
	/* 0x0.0 - 0x30.31 */
	 struct AM_ANInfo AM_ANInfo;
	/* Description - Table 120 - child_qp Layout */
	/* 0x0.0 - 0x0.31 */
	 struct child_qp child_qp;
	/* Description - Table 124 - GroupJoin MAD Layout */
	/* 0x0.0 - 0xc.31 */
	 struct AM_GroupJoin AM_GroupJoin;
	/* Description - Table 116 - QPCConfig MAD Layout */
	/* 0x0.0 - 0x3c.31 */
	 struct AM_QPCConfig AM_QPCConfig;
	/* Description - Table 122 - AggQuota MAD Layout */
	/* 0x0.0 - 0x2c.31 */
	 struct AM_QuotaConfig AM_QuotaConfig;
	/* Description - Table 126 - ResourceCleanup MAD Layout */
	/* 0x0.0 - 0xc.31 */
	 struct AM_ResourceCleanup AM_ResourceCleanup;
	/* Description - Table 126 - ResourceCleanup MAD Layout */
	/* 0x0.0 - 0xc.31 */
	 struct AM_ResourceCleanup_V2 AM_ResourceCleanup_V2;
	/* Description - Table 118 - TreeConfig MAD Layout */
	/* 0x0.0 - 0xbc.31 */
	 struct AM_TreeConfig AM_TreeConfig;
	/* Description - Section B.7 - Aggregation Management Notice */
	/* 0x0.0 - 0x3c.31 */
	 struct Notice AM_Notice;
	/* Description -  */
	/* 0x0.0 - 0x4c.31 */
	 struct AM_PerformanceCounters AM_PerformanceCounters;
};

/* Description -   */
/* Size in bytes - 131072 */
union PERFORMANCE_MADS {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x28.31 */
	 struct PM_PortCounters PM_PortCounters;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	 struct PM_PortCountersExtended PM_PortCountersExtended;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct PM_PortXmitDiscardDetails PM_PortXmitDiscardDetails;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct PM_PortRcvErrorDetails PM_PortRcvErrorDetails;
	/* Description -  */
	/* 0x0.0 - 0xbc.31 */
	 struct PM_PortSamplesResult PM_PortSamplesResult;
	/* Description -  */
	/* 0x0.0 - 0x64.31 */
	 struct PM_PortSamplesControl PM_PortSamplesControl;
	/* Description -  */
	/* 0x0.0 - 0x88.31 */
	 struct PM_PortExtendedSpeedsCounters PM_PortExtendedSpeedsCounters;
	/* Description -  */
	/* 0x0.0 - 0x94.31 */
	 struct PM_PortExtendedSpeedsRSFECCounters PM_PortExtendedSpeedsRSFECCounters;
	/* Description -  */
	/* 0x0.0 - 0x84.31 */
	 struct PM_PortRcvXmitCntrsSlVl PM_PortRcvXmitCntrsSlVl;
};

/* Description -   */
/* Size in bytes - 16777216 */
union PACKETS_EXTERNAL {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 struct IB_LRH IB_LRH;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct IB_RWH IB_RWH;
	/* Description -  */
	/* 0x0.0 - 0x24.31 */
	 struct IB_GRH IB_GRH;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	 struct IB_BTH IB_BTH;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	 struct IB_BTH_CNP IB_BTH_CNP;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct IB_RDETH IB_RDETH;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 struct IB_DETH IB_DETH;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	 struct IB_RETH IB_RETH;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	 struct IB_AtomicETH IB_AtomicETH;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct IB_AETH IB_AETH;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 struct IB_AtomicAckETH IB_AtomicAckETH;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct IB_ImmDt IB_ImmDt;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct IB_IETH IB_IETH;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct ICRC ICRC;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct VCRC VCRC;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_Common MAD_Header_Common;
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	 struct MAD_Header_Common_With_RMPP MAD_Header_Common_With_RMPP;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	 struct MAD_Header_SMP_Direct_Routed MAD_Header_SMP_Direct_Routed;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 struct MAD_SMP_Direct_Routed MAD_SMP_Direct_Routed;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 struct MAD_SMP_LID_Routed MAD_SMP_LID_Routed;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 struct MAD_PerformanceManagement MAD_PerformanceManagement;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 struct MAD_SubnetAdministartion MAD_SubnetAdministartion;
	/* Description -  */
	/* 0x0.0 - 0x30.31 */
	 struct SA_MCMMemberRecord SA_MCMMemberRecord;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 struct MAD_VendorSpec MAD_VendorSpec;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 struct MAD_CongestionControl MAD_CongestionControl;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	 struct IB_ClassPortInfo IB_ClassPortInfo;
	/* Description -  */
	/* 0x0.0 - 0x1fffc.31 */
	 union SMP_MADS SMP_MADS;
	/* Description -  */
	/* 0x0.0 - 0x1fffc.31 */
	 union PERFORMANCE_MADS PERFORMANCE_MADS;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 union AGGREGATION_MADS AGGREGATION_MADS;
	/* Description -  */
	/* 0x0.0 - 0x1fffc.31 */
	 union CONGESTION_CONTOL CONGESTION_CONTOL;
	/* Description -  */
	/* 0x0.0 - 0x1fffc.31 */
	 union VENDOR_SPECS VENDOR_SPECS;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* AM_ANInfo */
void AM_ANInfo_pack(const struct AM_ANInfo *ptr_struct, u_int8_t* ptr_buff);
void AM_ANInfo_unpack(struct AM_ANInfo *ptr_struct, const u_int8_t* ptr_buff);
void AM_ANInfo_print(const struct AM_ANInfo *ptr_struct, FILE* file, int indent_level);
int AM_ANInfo_size(void);
#define AM_ANINFO_SIZE    (0x34)
void AM_ANInfo_dump(const struct AM_ANInfo *ptr_struct, FILE* file);
/* AM_GroupJoin */
void AM_GroupJoin_pack(const struct AM_GroupJoin *ptr_struct, u_int8_t* ptr_buff);
void AM_GroupJoin_unpack(struct AM_GroupJoin *ptr_struct, const u_int8_t* ptr_buff);
void AM_GroupJoin_print(const struct AM_GroupJoin *ptr_struct, FILE* file, int indent_level);
int AM_GroupJoin_size(void);
#define AM_GROUPJOIN_SIZE    (0x10)
void AM_GroupJoin_dump(const struct AM_GroupJoin *ptr_struct, FILE* file);
/* AM_QPCConfig */
void AM_QPCConfig_pack(const struct AM_QPCConfig *ptr_struct, u_int8_t* ptr_buff);
void AM_QPCConfig_unpack(struct AM_QPCConfig *ptr_struct, const u_int8_t* ptr_buff);
void AM_QPCConfig_print(const struct AM_QPCConfig *ptr_struct, FILE* file, int indent_level);
int AM_QPCConfig_size(void);
#define AM_QPCCONFIG_SIZE    (0x40)
void AM_QPCConfig_dump(const struct AM_QPCConfig *ptr_struct, FILE* file);
/* AM_QuotaConfig */
void AM_QuotaConfig_pack(const struct AM_QuotaConfig *ptr_struct, u_int8_t* ptr_buff);
void AM_QuotaConfig_unpack(struct AM_QuotaConfig *ptr_struct, const u_int8_t* ptr_buff);
void AM_QuotaConfig_print(const struct AM_QuotaConfig *ptr_struct, FILE* file, int indent_level);
int AM_QuotaConfig_size(void);
#define AM_QUOTACONFIG_SIZE    (0x30)
void AM_QuotaConfig_dump(const struct AM_QuotaConfig *ptr_struct, FILE* file);
/* AM_ResourceCleanup */
void AM_ResourceCleanup_pack(const struct AM_ResourceCleanup *ptr_struct, u_int8_t* ptr_buff);
void AM_ResourceCleanup_unpack(struct AM_ResourceCleanup *ptr_struct, const u_int8_t* ptr_buff);
void AM_ResourceCleanup_print(const struct AM_ResourceCleanup *ptr_struct, FILE* file, int indent_level);
int AM_ResourceCleanup_size(void);
#define AM_RESOURCECLEANUP_SIZE    (0x10)
void AM_ResourceCleanup_dump(const struct AM_ResourceCleanup *ptr_struct, FILE* file);
/* AM_ResourceCleanup_V2 */
void AM_ResourceCleanup_V2_pack(const struct AM_ResourceCleanup_V2 *ptr_struct, u_int8_t* ptr_buff);
void AM_ResourceCleanup_V2_unpack(struct AM_ResourceCleanup_V2 *ptr_struct, const u_int8_t* ptr_buff);
void AM_ResourceCleanup_V2_print(const struct AM_ResourceCleanup_V2 *ptr_struct, FILE* file, int indent_level);
int AM_ResourceCleanup_V2_size(void);
#define AM_RESOURCECLEANUP_V2_SIZE    (0x10)
void AM_ResourceCleanup_V2_dump(const struct AM_ResourceCleanup_V2 *ptr_struct, FILE* file);
/* AdjSiteLocalSubnetRecord */
void AdjSiteLocalSubnetRecord_pack(const struct AdjSiteLocalSubnetRecord *ptr_struct, u_int8_t* ptr_buff);
void AdjSiteLocalSubnetRecord_unpack(struct AdjSiteLocalSubnetRecord *ptr_struct, const u_int8_t* ptr_buff);
void AdjSiteLocalSubnetRecord_print(const struct AdjSiteLocalSubnetRecord *ptr_struct, FILE* file, int indent_level);
int AdjSiteLocalSubnetRecord_size(void);
#define ADJSITELOCALSUBNETRECORD_SIZE    (0x8)
void AdjSiteLocalSubnetRecord_dump(const struct AdjSiteLocalSubnetRecord *ptr_struct, FILE* file);
/* AggregationManagement_MAD_Data_Block_Element */
void AggregationManagement_MAD_Data_Block_Element_pack(const struct AggregationManagement_MAD_Data_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void AggregationManagement_MAD_Data_Block_Element_unpack(struct AggregationManagement_MAD_Data_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void AggregationManagement_MAD_Data_Block_Element_print(const struct AggregationManagement_MAD_Data_Block_Element *ptr_struct, FILE* file, int indent_level);
int AggregationManagement_MAD_Data_Block_Element_size(void);
#define AGGREGATIONMANAGEMENT_MAD_DATA_BLOCK_ELEMENT_SIZE    (0xc0)
void AggregationManagement_MAD_Data_Block_Element_dump(const struct AggregationManagement_MAD_Data_Block_Element *ptr_struct, FILE* file);
/* BandwidthPerSL */
void BandwidthPerSL_pack(const struct BandwidthPerSL *ptr_struct, u_int8_t* ptr_buff);
void BandwidthPerSL_unpack(struct BandwidthPerSL *ptr_struct, const u_int8_t* ptr_buff);
void BandwidthPerSL_print(const struct BandwidthPerSL *ptr_struct, FILE* file, int indent_level);
int BandwidthPerSL_size(void);
#define BANDWIDTHPERSL_SIZE    (0x4)
void BandwidthPerSL_dump(const struct BandwidthPerSL *ptr_struct, FILE* file);
/* CACongestionEntryListElement */
void CACongestionEntryListElement_pack(const struct CACongestionEntryListElement *ptr_struct, u_int8_t* ptr_buff);
void CACongestionEntryListElement_unpack(struct CACongestionEntryListElement *ptr_struct, const u_int8_t* ptr_buff);
void CACongestionEntryListElement_print(const struct CACongestionEntryListElement *ptr_struct, FILE* file, int indent_level);
int CACongestionEntryListElement_size(void);
#define CACONGESTIONENTRYLISTELEMENT_SIZE    (0x8)
void CACongestionEntryListElement_dump(const struct CACongestionEntryListElement *ptr_struct, FILE* file);
/* CCTI_Entry_ListElement */
void CCTI_Entry_ListElement_pack(const struct CCTI_Entry_ListElement *ptr_struct, u_int8_t* ptr_buff);
void CCTI_Entry_ListElement_unpack(struct CCTI_Entry_ListElement *ptr_struct, const u_int8_t* ptr_buff);
void CCTI_Entry_ListElement_print(const struct CCTI_Entry_ListElement *ptr_struct, FILE* file, int indent_level);
int CCTI_Entry_ListElement_size(void);
#define CCTI_ENTRY_LISTELEMENT_SIZE    (0x2)
void CCTI_Entry_ListElement_dump(const struct CCTI_Entry_ListElement *ptr_struct, FILE* file);
/* CC_CongestionInfo */
void CC_CongestionInfo_pack(const struct CC_CongestionInfo *ptr_struct, u_int8_t* ptr_buff);
void CC_CongestionInfo_unpack(struct CC_CongestionInfo *ptr_struct, const u_int8_t* ptr_buff);
void CC_CongestionInfo_print(const struct CC_CongestionInfo *ptr_struct, FILE* file, int indent_level);
int CC_CongestionInfo_size(void);
#define CC_CONGESTIONINFO_SIZE    (0x4)
void CC_CongestionInfo_dump(const struct CC_CongestionInfo *ptr_struct, FILE* file);
/* CC_Log_Data_Block_Element */
void CC_Log_Data_Block_Element_pack(const struct CC_Log_Data_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void CC_Log_Data_Block_Element_unpack(struct CC_Log_Data_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void CC_Log_Data_Block_Element_print(const struct CC_Log_Data_Block_Element *ptr_struct, FILE* file, int indent_level);
int CC_Log_Data_Block_Element_size(void);
#define CC_LOG_DATA_BLOCK_ELEMENT_SIZE    (0x20)
void CC_Log_Data_Block_Element_dump(const struct CC_Log_Data_Block_Element *ptr_struct, FILE* file);
/* CC_Mgt_Data_Block_Element */
void CC_Mgt_Data_Block_Element_pack(const struct CC_Mgt_Data_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void CC_Mgt_Data_Block_Element_unpack(struct CC_Mgt_Data_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void CC_Mgt_Data_Block_Element_print(const struct CC_Mgt_Data_Block_Element *ptr_struct, FILE* file, int indent_level);
int CC_Mgt_Data_Block_Element_size(void);
#define CC_MGT_DATA_BLOCK_ELEMENT_SIZE    (0xc0)
void CC_Mgt_Data_Block_Element_dump(const struct CC_Mgt_Data_Block_Element *ptr_struct, FILE* file);
/* CC_SwitchCongestionSetting_Control_Map */
void CC_SwitchCongestionSetting_Control_Map_pack(const struct CC_SwitchCongestionSetting_Control_Map *ptr_struct, u_int8_t* ptr_buff);
void CC_SwitchCongestionSetting_Control_Map_unpack(struct CC_SwitchCongestionSetting_Control_Map *ptr_struct, const u_int8_t* ptr_buff);
void CC_SwitchCongestionSetting_Control_Map_print(const struct CC_SwitchCongestionSetting_Control_Map *ptr_struct, FILE* file, int indent_level);
int CC_SwitchCongestionSetting_Control_Map_size(void);
#define CC_SWITCHCONGESTIONSETTING_CONTROL_MAP_SIZE    (0x4)
void CC_SwitchCongestionSetting_Control_Map_dump(const struct CC_SwitchCongestionSetting_Control_Map *ptr_struct, FILE* file);
/* CC_TimeStamp */
void CC_TimeStamp_pack(const struct CC_TimeStamp *ptr_struct, u_int8_t* ptr_buff);
void CC_TimeStamp_unpack(struct CC_TimeStamp *ptr_struct, const u_int8_t* ptr_buff);
void CC_TimeStamp_print(const struct CC_TimeStamp *ptr_struct, FILE* file, int indent_level);
int CC_TimeStamp_size(void);
#define CC_TIMESTAMP_SIZE    (0x4)
void CC_TimeStamp_dump(const struct CC_TimeStamp *ptr_struct, FILE* file);
/* CongestionEntryListSwitchElement */
void CongestionEntryListSwitchElement_pack(const struct CongestionEntryListSwitchElement *ptr_struct, u_int8_t* ptr_buff);
void CongestionEntryListSwitchElement_unpack(struct CongestionEntryListSwitchElement *ptr_struct, const u_int8_t* ptr_buff);
void CongestionEntryListSwitchElement_print(const struct CongestionEntryListSwitchElement *ptr_struct, FILE* file, int indent_level);
int CongestionEntryListSwitchElement_size(void);
#define CONGESTIONENTRYLISTSWITCHELEMENT_SIZE    (0xc)
void CongestionEntryListSwitchElement_dump(const struct CongestionEntryListSwitchElement *ptr_struct, FILE* file);
/* CongestionLogEventListCAElement */
void CongestionLogEventListCAElement_pack(const struct CongestionLogEventListCAElement *ptr_struct, u_int8_t* ptr_buff);
void CongestionLogEventListCAElement_unpack(struct CongestionLogEventListCAElement *ptr_struct, const u_int8_t* ptr_buff);
void CongestionLogEventListCAElement_print(const struct CongestionLogEventListCAElement *ptr_struct, FILE* file, int indent_level);
int CongestionLogEventListCAElement_size(void);
#define CONGESTIONLOGEVENTLISTCAELEMENT_SIZE    (0x10)
void CongestionLogEventListCAElement_dump(const struct CongestionLogEventListCAElement *ptr_struct, FILE* file);
/* DataBuffer */
void DataBuffer_pack(const struct DataBuffer *ptr_struct, u_int8_t* ptr_buff);
void DataBuffer_unpack(struct DataBuffer *ptr_struct, const u_int8_t* ptr_buff);
void DataBuffer_print(const struct DataBuffer *ptr_struct, FILE* file, int indent_level);
int DataBuffer_size(void);
#define DATABUFFER_SIZE    (0xd8)
void DataBuffer_dump(const struct DataBuffer *ptr_struct, FILE* file);
/* DirRPath_Block_Element */
void DirRPath_Block_Element_pack(const struct DirRPath_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void DirRPath_Block_Element_unpack(struct DirRPath_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void DirRPath_Block_Element_print(const struct DirRPath_Block_Element *ptr_struct, FILE* file, int indent_level);
int DirRPath_Block_Element_size(void);
#define DIRRPATH_BLOCK_ELEMENT_SIZE    (0x40)
void DirRPath_Block_Element_dump(const struct DirRPath_Block_Element *ptr_struct, FILE* file);
/* GID_Block_Element */
void GID_Block_Element_pack(const struct GID_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void GID_Block_Element_unpack(struct GID_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void GID_Block_Element_print(const struct GID_Block_Element *ptr_struct, FILE* file, int indent_level);
int GID_Block_Element_size(void);
#define GID_BLOCK_ELEMENT_SIZE    (0x10)
void GID_Block_Element_dump(const struct GID_Block_Element *ptr_struct, FILE* file);
/* GeneralInfoCapabilityMask */
void GeneralInfoCapabilityMask_pack(const struct GeneralInfoCapabilityMask *ptr_struct, u_int8_t* ptr_buff);
void GeneralInfoCapabilityMask_unpack(struct GeneralInfoCapabilityMask *ptr_struct, const u_int8_t* ptr_buff);
void GeneralInfoCapabilityMask_print(const struct GeneralInfoCapabilityMask *ptr_struct, FILE* file, int indent_level);
int GeneralInfoCapabilityMask_size(void);
#define GENERALINFOCAPABILITYMASK_SIZE    (0x10)
void GeneralInfoCapabilityMask_dump(const struct GeneralInfoCapabilityMask *ptr_struct, FILE* file);
/* HWInfo_Block_Element */
void HWInfo_Block_Element_pack(const struct HWInfo_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void HWInfo_Block_Element_unpack(struct HWInfo_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void HWInfo_Block_Element_print(const struct HWInfo_Block_Element *ptr_struct, FILE* file, int indent_level);
int HWInfo_Block_Element_size(void);
#define HWINFO_BLOCK_ELEMENT_SIZE    (0x20)
void HWInfo_Block_Element_dump(const struct HWInfo_Block_Element *ptr_struct, FILE* file);
/* IB_AETH */
void IB_AETH_pack(const struct IB_AETH *ptr_struct, u_int8_t* ptr_buff);
void IB_AETH_unpack(struct IB_AETH *ptr_struct, const u_int8_t* ptr_buff);
void IB_AETH_print(const struct IB_AETH *ptr_struct, FILE* file, int indent_level);
int IB_AETH_size(void);
#define IB_AETH_SIZE    (0x4)
void IB_AETH_dump(const struct IB_AETH *ptr_struct, FILE* file);
/* IB_DETH */
void IB_DETH_pack(const struct IB_DETH *ptr_struct, u_int8_t* ptr_buff);
void IB_DETH_unpack(struct IB_DETH *ptr_struct, const u_int8_t* ptr_buff);
void IB_DETH_print(const struct IB_DETH *ptr_struct, FILE* file, int indent_level);
int IB_DETH_size(void);
#define IB_DETH_SIZE    (0x8)
void IB_DETH_dump(const struct IB_DETH *ptr_struct, FILE* file);
/* IB_IETH */
void IB_IETH_pack(const struct IB_IETH *ptr_struct, u_int8_t* ptr_buff);
void IB_IETH_unpack(struct IB_IETH *ptr_struct, const u_int8_t* ptr_buff);
void IB_IETH_print(const struct IB_IETH *ptr_struct, FILE* file, int indent_level);
int IB_IETH_size(void);
#define IB_IETH_SIZE    (0x4)
void IB_IETH_dump(const struct IB_IETH *ptr_struct, FILE* file);
/* IB_ImmDt */
void IB_ImmDt_pack(const struct IB_ImmDt *ptr_struct, u_int8_t* ptr_buff);
void IB_ImmDt_unpack(struct IB_ImmDt *ptr_struct, const u_int8_t* ptr_buff);
void IB_ImmDt_print(const struct IB_ImmDt *ptr_struct, FILE* file, int indent_level);
int IB_ImmDt_size(void);
#define IB_IMMDT_SIZE    (0x4)
void IB_ImmDt_dump(const struct IB_ImmDt *ptr_struct, FILE* file);
/* IB_LRH */
void IB_LRH_pack(const struct IB_LRH *ptr_struct, u_int8_t* ptr_buff);
void IB_LRH_unpack(struct IB_LRH *ptr_struct, const u_int8_t* ptr_buff);
void IB_LRH_print(const struct IB_LRH *ptr_struct, FILE* file, int indent_level);
int IB_LRH_size(void);
#define IB_LRH_SIZE    (0x8)
void IB_LRH_dump(const struct IB_LRH *ptr_struct, FILE* file);
/* IB_RDETH */
void IB_RDETH_pack(const struct IB_RDETH *ptr_struct, u_int8_t* ptr_buff);
void IB_RDETH_unpack(struct IB_RDETH *ptr_struct, const u_int8_t* ptr_buff);
void IB_RDETH_print(const struct IB_RDETH *ptr_struct, FILE* file, int indent_level);
int IB_RDETH_size(void);
#define IB_RDETH_SIZE    (0x4)
void IB_RDETH_dump(const struct IB_RDETH *ptr_struct, FILE* file);
/* IB_RWH */
void IB_RWH_pack(const struct IB_RWH *ptr_struct, u_int8_t* ptr_buff);
void IB_RWH_unpack(struct IB_RWH *ptr_struct, const u_int8_t* ptr_buff);
void IB_RWH_print(const struct IB_RWH *ptr_struct, FILE* file, int indent_level);
int IB_RWH_size(void);
#define IB_RWH_SIZE    (0x4)
void IB_RWH_dump(const struct IB_RWH *ptr_struct, FILE* file);
/* ICRC */
void ICRC_pack(const struct ICRC *ptr_struct, u_int8_t* ptr_buff);
void ICRC_unpack(struct ICRC *ptr_struct, const u_int8_t* ptr_buff);
void ICRC_print(const struct ICRC *ptr_struct, FILE* file, int indent_level);
int ICRC_size(void);
#define ICRC_SIZE    (0x4)
void ICRC_dump(const struct ICRC *ptr_struct, FILE* file);
/* LID_Port_Block_Element */
void LID_Port_Block_Element_pack(const struct LID_Port_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void LID_Port_Block_Element_unpack(struct LID_Port_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void LID_Port_Block_Element_print(const struct LID_Port_Block_Element *ptr_struct, FILE* file, int indent_level);
int LID_Port_Block_Element_size(void);
#define LID_PORT_BLOCK_ELEMENT_SIZE    (0x4)
void LID_Port_Block_Element_dump(const struct LID_Port_Block_Element *ptr_struct, FILE* file);
/* PM_PortSamplesResult */
void PM_PortSamplesResult_pack(const struct PM_PortSamplesResult *ptr_struct, u_int8_t* ptr_buff);
void PM_PortSamplesResult_unpack(struct PM_PortSamplesResult *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortSamplesResult_print(const struct PM_PortSamplesResult *ptr_struct, FILE* file, int indent_level);
int PM_PortSamplesResult_size(void);
#define PM_PORTSAMPLESRESULT_SIZE    (0xc0)
void PM_PortSamplesResult_dump(const struct PM_PortSamplesResult *ptr_struct, FILE* file);
/* PSID_Block_Element */
void PSID_Block_Element_pack(const struct PSID_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void PSID_Block_Element_unpack(struct PSID_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void PSID_Block_Element_print(const struct PSID_Block_Element *ptr_struct, FILE* file, int indent_level);
int PSID_Block_Element_size(void);
#define PSID_BLOCK_ELEMENT_SIZE    (0x10)
void PSID_Block_Element_dump(const struct PSID_Block_Element *ptr_struct, FILE* file);
/* P_Key_Block_Element */
void P_Key_Block_Element_pack(const struct P_Key_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void P_Key_Block_Element_unpack(struct P_Key_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void P_Key_Block_Element_print(const struct P_Key_Block_Element *ptr_struct, FILE* file, int indent_level);
int P_Key_Block_Element_size(void);
#define P_KEY_BLOCK_ELEMENT_SIZE    (0x2)
void P_Key_Block_Element_dump(const struct P_Key_Block_Element *ptr_struct, FILE* file);
/* PerfManagement_MAD_Data_Block_Element */
void PerfManagement_MAD_Data_Block_Element_pack(const struct PerfManagement_MAD_Data_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void PerfManagement_MAD_Data_Block_Element_unpack(struct PerfManagement_MAD_Data_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void PerfManagement_MAD_Data_Block_Element_print(const struct PerfManagement_MAD_Data_Block_Element *ptr_struct, FILE* file, int indent_level);
int PerfManagement_MAD_Data_Block_Element_size(void);
#define PERFMANAGEMENT_MAD_DATA_BLOCK_ELEMENT_SIZE    (0xc0)
void PerfManagement_MAD_Data_Block_Element_dump(const struct PerfManagement_MAD_Data_Block_Element *ptr_struct, FILE* file);
/* PortCountersExtended_Mask_Block_Element */
void PortCountersExtended_Mask_Block_Element_pack(const struct PortCountersExtended_Mask_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void PortCountersExtended_Mask_Block_Element_unpack(struct PortCountersExtended_Mask_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void PortCountersExtended_Mask_Block_Element_print(const struct PortCountersExtended_Mask_Block_Element *ptr_struct, FILE* file, int indent_level);
int PortCountersExtended_Mask_Block_Element_size(void);
#define PORTCOUNTERSEXTENDED_MASK_BLOCK_ELEMENT_SIZE    (0x2)
void PortCountersExtended_Mask_Block_Element_dump(const struct PortCountersExtended_Mask_Block_Element *ptr_struct, FILE* file);
/* PortCounters_Mask2_Block_Element */
void PortCounters_Mask2_Block_Element_pack(const struct PortCounters_Mask2_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void PortCounters_Mask2_Block_Element_unpack(struct PortCounters_Mask2_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void PortCounters_Mask2_Block_Element_print(const struct PortCounters_Mask2_Block_Element *ptr_struct, FILE* file, int indent_level);
int PortCounters_Mask2_Block_Element_size(void);
#define PORTCOUNTERS_MASK2_BLOCK_ELEMENT_SIZE    (0x1)
void PortCounters_Mask2_Block_Element_dump(const struct PortCounters_Mask2_Block_Element *ptr_struct, FILE* file);
/* PortCounters_Mask_Block_Element */
void PortCounters_Mask_Block_Element_pack(const struct PortCounters_Mask_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void PortCounters_Mask_Block_Element_unpack(struct PortCounters_Mask_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void PortCounters_Mask_Block_Element_print(const struct PortCounters_Mask_Block_Element *ptr_struct, FILE* file, int indent_level);
int PortCounters_Mask_Block_Element_size(void);
#define PORTCOUNTERS_MASK_BLOCK_ELEMENT_SIZE    (0x2)
void PortCounters_Mask_Block_Element_dump(const struct PortCounters_Mask_Block_Element *ptr_struct, FILE* file);
/* PortRcvErrorDetails_Mask_Block_Element */
void PortRcvErrorDetails_Mask_Block_Element_pack(const struct PortRcvErrorDetails_Mask_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void PortRcvErrorDetails_Mask_Block_Element_unpack(struct PortRcvErrorDetails_Mask_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void PortRcvErrorDetails_Mask_Block_Element_print(const struct PortRcvErrorDetails_Mask_Block_Element *ptr_struct, FILE* file, int indent_level);
int PortRcvErrorDetails_Mask_Block_Element_size(void);
#define PORTRCVERRORDETAILS_MASK_BLOCK_ELEMENT_SIZE    (0x2)
void PortRcvErrorDetails_Mask_Block_Element_dump(const struct PortRcvErrorDetails_Mask_Block_Element *ptr_struct, FILE* file);
/* PortSampleControlOptionMask */
void PortSampleControlOptionMask_pack(const struct PortSampleControlOptionMask *ptr_struct, u_int8_t* ptr_buff);
void PortSampleControlOptionMask_unpack(struct PortSampleControlOptionMask *ptr_struct, const u_int8_t* ptr_buff);
void PortSampleControlOptionMask_print(const struct PortSampleControlOptionMask *ptr_struct, FILE* file, int indent_level);
int PortSampleControlOptionMask_size(void);
#define PORTSAMPLECONTROLOPTIONMASK_SIZE    (0x8)
void PortSampleControlOptionMask_dump(const struct PortSampleControlOptionMask *ptr_struct, FILE* file);
/* PortXmitDiscardDetails_Mask_Block_Element */
void PortXmitDiscardDetails_Mask_Block_Element_pack(const struct PortXmitDiscardDetails_Mask_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void PortXmitDiscardDetails_Mask_Block_Element_unpack(struct PortXmitDiscardDetails_Mask_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void PortXmitDiscardDetails_Mask_Block_Element_print(const struct PortXmitDiscardDetails_Mask_Block_Element *ptr_struct, FILE* file, int indent_level);
int PortXmitDiscardDetails_Mask_Block_Element_size(void);
#define PORTXMITDISCARDDETAILS_MASK_BLOCK_ELEMENT_SIZE    (0x2)
void PortXmitDiscardDetails_Mask_Block_Element_dump(const struct PortXmitDiscardDetails_Mask_Block_Element *ptr_struct, FILE* file);
/* RawData_PM_PortRcvXmitCntrsSlVl */
void RawData_PM_PortRcvXmitCntrsSlVl_pack(const struct RawData_PM_PortRcvXmitCntrsSlVl *ptr_struct, u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsSlVl_unpack(struct RawData_PM_PortRcvXmitCntrsSlVl *ptr_struct, const u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsSlVl_print(const struct RawData_PM_PortRcvXmitCntrsSlVl *ptr_struct, FILE* file, int indent_level);
int RawData_PM_PortRcvXmitCntrsSlVl_size(void);
#define RAWDATA_PM_PORTRCVXMITCNTRSSLVL_SIZE    (0x84)
void RawData_PM_PortRcvXmitCntrsSlVl_dump(const struct RawData_PM_PortRcvXmitCntrsSlVl *ptr_struct, FILE* file);
/* RawData_PM_PortRcvXmitCntrsSlVl32 */
void RawData_PM_PortRcvXmitCntrsSlVl32_pack(const struct RawData_PM_PortRcvXmitCntrsSlVl32 *ptr_struct, u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsSlVl32_unpack(struct RawData_PM_PortRcvXmitCntrsSlVl32 *ptr_struct, const u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsSlVl32_print(const struct RawData_PM_PortRcvXmitCntrsSlVl32 *ptr_struct, FILE* file, int indent_level);
int RawData_PM_PortRcvXmitCntrsSlVl32_size(void);
#define RAWDATA_PM_PORTRCVXMITCNTRSSLVL32_SIZE    (0x40)
void RawData_PM_PortRcvXmitCntrsSlVl32_dump(const struct RawData_PM_PortRcvXmitCntrsSlVl32 *ptr_struct, FILE* file);
/* RawNoticeDataDetails */
void RawNoticeDataDetails_pack(const struct RawNoticeDataDetails *ptr_struct, u_int8_t* ptr_buff);
void RawNoticeDataDetails_unpack(struct RawNoticeDataDetails *ptr_struct, const u_int8_t* ptr_buff);
void RawNoticeDataDetails_print(const struct RawNoticeDataDetails *ptr_struct, FILE* file, int indent_level);
int RawNoticeDataDetails_size(void);
#define RAWNOTICEDATADETAILS_SIZE    (0x38)
void RawNoticeDataDetails_dump(const struct RawNoticeDataDetails *ptr_struct, FILE* file);
/* SMP_LedInfo */
void SMP_LedInfo_pack(const struct SMP_LedInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_LedInfo_unpack(struct SMP_LedInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_LedInfo_print(const struct SMP_LedInfo *ptr_struct, FILE* file, int indent_level);
int SMP_LedInfo_size(void);
#define SMP_LEDINFO_SIZE    (0x4)
void SMP_LedInfo_dump(const struct SMP_LedInfo *ptr_struct, FILE* file);
/* SMP_LinearForwardingTable */
void SMP_LinearForwardingTable_pack(const struct SMP_LinearForwardingTable *ptr_struct, u_int8_t* ptr_buff);
void SMP_LinearForwardingTable_unpack(struct SMP_LinearForwardingTable *ptr_struct, const u_int8_t* ptr_buff);
void SMP_LinearForwardingTable_print(const struct SMP_LinearForwardingTable *ptr_struct, FILE* file, int indent_level);
int SMP_LinearForwardingTable_size(void);
#define SMP_LINEARFORWARDINGTABLE_SIZE    (0x40)
void SMP_LinearForwardingTable_dump(const struct SMP_LinearForwardingTable *ptr_struct, FILE* file);
/* SMP_MAD_Data_Block_Element */
void SMP_MAD_Data_Block_Element_pack(const struct SMP_MAD_Data_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void SMP_MAD_Data_Block_Element_unpack(struct SMP_MAD_Data_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void SMP_MAD_Data_Block_Element_print(const struct SMP_MAD_Data_Block_Element *ptr_struct, FILE* file, int indent_level);
int SMP_MAD_Data_Block_Element_size(void);
#define SMP_MAD_DATA_BLOCK_ELEMENT_SIZE    (0x40)
void SMP_MAD_Data_Block_Element_dump(const struct SMP_MAD_Data_Block_Element *ptr_struct, FILE* file);
/* SMP_MlnxExtPortInfo */
void SMP_MlnxExtPortInfo_pack(const struct SMP_MlnxExtPortInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_MlnxExtPortInfo_unpack(struct SMP_MlnxExtPortInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_MlnxExtPortInfo_print(const struct SMP_MlnxExtPortInfo *ptr_struct, FILE* file, int indent_level);
int SMP_MlnxExtPortInfo_size(void);
#define SMP_MLNXEXTPORTINFO_SIZE    (0x40)
void SMP_MlnxExtPortInfo_dump(const struct SMP_MlnxExtPortInfo *ptr_struct, FILE* file);
/* SMP_MulticastForwardingTable */
void SMP_MulticastForwardingTable_pack(const struct SMP_MulticastForwardingTable *ptr_struct, u_int8_t* ptr_buff);
void SMP_MulticastForwardingTable_unpack(struct SMP_MulticastForwardingTable *ptr_struct, const u_int8_t* ptr_buff);
void SMP_MulticastForwardingTable_print(const struct SMP_MulticastForwardingTable *ptr_struct, FILE* file, int indent_level);
int SMP_MulticastForwardingTable_size(void);
#define SMP_MULTICASTFORWARDINGTABLE_SIZE    (0x40)
void SMP_MulticastForwardingTable_dump(const struct SMP_MulticastForwardingTable *ptr_struct, FILE* file);
/* SMP_NodeDesc */
void SMP_NodeDesc_pack(const struct SMP_NodeDesc *ptr_struct, u_int8_t* ptr_buff);
void SMP_NodeDesc_unpack(struct SMP_NodeDesc *ptr_struct, const u_int8_t* ptr_buff);
void SMP_NodeDesc_print(const struct SMP_NodeDesc *ptr_struct, FILE* file, int indent_level);
int SMP_NodeDesc_size(void);
#define SMP_NODEDESC_SIZE    (0x40)
void SMP_NodeDesc_dump(const struct SMP_NodeDesc *ptr_struct, FILE* file);
/* SMP_PortInfoExtended */
void SMP_PortInfoExtended_pack(const struct SMP_PortInfoExtended *ptr_struct, u_int8_t* ptr_buff);
void SMP_PortInfoExtended_unpack(struct SMP_PortInfoExtended *ptr_struct, const u_int8_t* ptr_buff);
void SMP_PortInfoExtended_print(const struct SMP_PortInfoExtended *ptr_struct, FILE* file, int indent_level);
int SMP_PortInfoExtended_size(void);
#define SMP_PORTINFOEXTENDED_SIZE    (0x14)
void SMP_PortInfoExtended_dump(const struct SMP_PortInfoExtended *ptr_struct, FILE* file);
/* SMP_RouterInfo */
void SMP_RouterInfo_pack(const struct SMP_RouterInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_RouterInfo_unpack(struct SMP_RouterInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_RouterInfo_print(const struct SMP_RouterInfo *ptr_struct, FILE* file, int indent_level);
int SMP_RouterInfo_size(void);
#define SMP_ROUTERINFO_SIZE    (0x40)
void SMP_RouterInfo_dump(const struct SMP_RouterInfo *ptr_struct, FILE* file);
/* SMP_SLToVLMappingTable */
void SMP_SLToVLMappingTable_pack(const struct SMP_SLToVLMappingTable *ptr_struct, u_int8_t* ptr_buff);
void SMP_SLToVLMappingTable_unpack(struct SMP_SLToVLMappingTable *ptr_struct, const u_int8_t* ptr_buff);
void SMP_SLToVLMappingTable_print(const struct SMP_SLToVLMappingTable *ptr_struct, FILE* file, int indent_level);
int SMP_SLToVLMappingTable_size(void);
#define SMP_SLTOVLMAPPINGTABLE_SIZE    (0x8)
void SMP_SLToVLMappingTable_dump(const struct SMP_SLToVLMappingTable *ptr_struct, FILE* file);
/* SMP_SwitchInfo */
void SMP_SwitchInfo_pack(const struct SMP_SwitchInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_SwitchInfo_unpack(struct SMP_SwitchInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_SwitchInfo_print(const struct SMP_SwitchInfo *ptr_struct, FILE* file, int indent_level);
int SMP_SwitchInfo_size(void);
#define SMP_SWITCHINFO_SIZE    (0x40)
void SMP_SwitchInfo_dump(const struct SMP_SwitchInfo *ptr_struct, FILE* file);
/* SMP_TempSensing */
void SMP_TempSensing_pack(const struct SMP_TempSensing *ptr_struct, u_int8_t* ptr_buff);
void SMP_TempSensing_unpack(struct SMP_TempSensing *ptr_struct, const u_int8_t* ptr_buff);
void SMP_TempSensing_print(const struct SMP_TempSensing *ptr_struct, FILE* file, int indent_level);
int SMP_TempSensing_size(void);
#define SMP_TEMPSENSING_SIZE    (0x10)
void SMP_TempSensing_dump(const struct SMP_TempSensing *ptr_struct, FILE* file);
/* SMP_VPortState */
void SMP_VPortState_pack(const struct SMP_VPortState *ptr_struct, u_int8_t* ptr_buff);
void SMP_VPortState_unpack(struct SMP_VPortState *ptr_struct, const u_int8_t* ptr_buff);
void SMP_VPortState_print(const struct SMP_VPortState *ptr_struct, FILE* file, int indent_level);
int SMP_VPortState_size(void);
#define SMP_VPORTSTATE_SIZE    (0x40)
void SMP_VPortState_dump(const struct SMP_VPortState *ptr_struct, FILE* file);
/* SMP_VirtualizationInfo */
void SMP_VirtualizationInfo_pack(const struct SMP_VirtualizationInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_VirtualizationInfo_unpack(struct SMP_VirtualizationInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_VirtualizationInfo_print(const struct SMP_VirtualizationInfo *ptr_struct, FILE* file, int indent_level);
int SMP_VirtualizationInfo_size(void);
#define SMP_VIRTUALIZATIONINFO_SIZE    (0x40)
void SMP_VirtualizationInfo_dump(const struct SMP_VirtualizationInfo *ptr_struct, FILE* file);
/* SWInfo_Block_Element */
void SWInfo_Block_Element_pack(const struct SWInfo_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void SWInfo_Block_Element_unpack(struct SWInfo_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void SWInfo_Block_Element_print(const struct SWInfo_Block_Element *ptr_struct, FILE* file, int indent_level);
int SWInfo_Block_Element_size(void);
#define SWINFO_BLOCK_ELEMENT_SIZE    (0x20)
void SWInfo_Block_Element_dump(const struct SWInfo_Block_Element *ptr_struct, FILE* file);
/* SubnetAdministartion_MAD_Data_Block_Element */
void SubnetAdministartion_MAD_Data_Block_Element_pack(const struct SubnetAdministartion_MAD_Data_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void SubnetAdministartion_MAD_Data_Block_Element_unpack(struct SubnetAdministartion_MAD_Data_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void SubnetAdministartion_MAD_Data_Block_Element_print(const struct SubnetAdministartion_MAD_Data_Block_Element *ptr_struct, FILE* file, int indent_level);
int SubnetAdministartion_MAD_Data_Block_Element_size(void);
#define SUBNETADMINISTARTION_MAD_DATA_BLOCK_ELEMENT_SIZE    (0xc8)
void SubnetAdministartion_MAD_Data_Block_Element_dump(const struct SubnetAdministartion_MAD_Data_Block_Element *ptr_struct, FILE* file);
/* SwitchPortCongestionSettingElement */
void SwitchPortCongestionSettingElement_pack(const struct SwitchPortCongestionSettingElement *ptr_struct, u_int8_t* ptr_buff);
void SwitchPortCongestionSettingElement_unpack(struct SwitchPortCongestionSettingElement *ptr_struct, const u_int8_t* ptr_buff);
void SwitchPortCongestionSettingElement_print(const struct SwitchPortCongestionSettingElement *ptr_struct, FILE* file, int indent_level);
int SwitchPortCongestionSettingElement_size(void);
#define SWITCHPORTCONGESTIONSETTINGELEMENT_SIZE    (0x4)
void SwitchPortCongestionSettingElement_dump(const struct SwitchPortCongestionSettingElement *ptr_struct, FILE* file);
/* TID_Block_Element */
void TID_Block_Element_pack(const struct TID_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void TID_Block_Element_unpack(struct TID_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void TID_Block_Element_print(const struct TID_Block_Element *ptr_struct, FILE* file, int indent_level);
int TID_Block_Element_size(void);
#define TID_BLOCK_ELEMENT_SIZE    (0x8)
void TID_Block_Element_dump(const struct TID_Block_Element *ptr_struct, FILE* file);
/* UINT256 */
void UINT256_pack(const struct UINT256 *ptr_struct, u_int8_t* ptr_buff);
void UINT256_unpack(struct UINT256 *ptr_struct, const u_int8_t* ptr_buff);
void UINT256_print(const struct UINT256 *ptr_struct, FILE* file, int indent_level);
int UINT256_size(void);
#define UINT256_SIZE    (0x20)
void UINT256_dump(const struct UINT256 *ptr_struct, FILE* file);
/* VCRC */
void VCRC_pack(const struct VCRC *ptr_struct, u_int8_t* ptr_buff);
void VCRC_unpack(struct VCRC *ptr_struct, const u_int8_t* ptr_buff);
void VCRC_print(const struct VCRC *ptr_struct, FILE* file, int indent_level);
int VCRC_size(void);
#define VCRC_SIZE    (0x4)
void VCRC_dump(const struct VCRC *ptr_struct, FILE* file);
/* VL_Weight_Block_Element */
void VL_Weight_Block_Element_pack(const struct VL_Weight_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void VL_Weight_Block_Element_unpack(struct VL_Weight_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void VL_Weight_Block_Element_print(const struct VL_Weight_Block_Element *ptr_struct, FILE* file, int indent_level);
int VL_Weight_Block_Element_size(void);
#define VL_WEIGHT_BLOCK_ELEMENT_SIZE    (0x2)
void VL_Weight_Block_Element_dump(const struct VL_Weight_Block_Element *ptr_struct, FILE* file);
/* VS_DC_Page1LatestVersion */
void VS_DC_Page1LatestVersion_pack(const struct VS_DC_Page1LatestVersion *ptr_struct, u_int8_t* ptr_buff);
void VS_DC_Page1LatestVersion_unpack(struct VS_DC_Page1LatestVersion *ptr_struct, const u_int8_t* ptr_buff);
void VS_DC_Page1LatestVersion_print(const struct VS_DC_Page1LatestVersion *ptr_struct, FILE* file, int indent_level);
int VS_DC_Page1LatestVersion_size(void);
#define VS_DC_PAGE1LATESTVERSION_SIZE    (0x68)
void VS_DC_Page1LatestVersion_dump(const struct VS_DC_Page1LatestVersion *ptr_struct, FILE* file);
/* VS_DC_Page255LatestVersion */
void VS_DC_Page255LatestVersion_pack(const struct VS_DC_Page255LatestVersion *ptr_struct, u_int8_t* ptr_buff);
void VS_DC_Page255LatestVersion_unpack(struct VS_DC_Page255LatestVersion *ptr_struct, const u_int8_t* ptr_buff);
void VS_DC_Page255LatestVersion_print(const struct VS_DC_Page255LatestVersion *ptr_struct, FILE* file, int indent_level);
int VS_DC_Page255LatestVersion_size(void);
#define VS_DC_PAGE255LATESTVERSION_SIZE    (0x44)
void VS_DC_Page255LatestVersion_dump(const struct VS_DC_Page255LatestVersion *ptr_struct, FILE* file);
/* VS_DC_TransportErrorsAndFlowsV2 */
void VS_DC_TransportErrorsAndFlowsV2_pack(const struct VS_DC_TransportErrorsAndFlowsV2 *ptr_struct, u_int8_t* ptr_buff);
void VS_DC_TransportErrorsAndFlowsV2_unpack(struct VS_DC_TransportErrorsAndFlowsV2 *ptr_struct, const u_int8_t* ptr_buff);
void VS_DC_TransportErrorsAndFlowsV2_print(const struct VS_DC_TransportErrorsAndFlowsV2 *ptr_struct, FILE* file, int indent_level);
int VS_DC_TransportErrorsAndFlowsV2_size(void);
#define VS_DC_TRANSPORTERRORSANDFLOWSV2_SIZE    (0x7c)
void VS_DC_TransportErrorsAndFlowsV2_dump(const struct VS_DC_TransportErrorsAndFlowsV2 *ptr_struct, FILE* file);
/* VendorSpecific_MAD_Data_Block_Element */
void VendorSpecific_MAD_Data_Block_Element_pack(const struct VendorSpecific_MAD_Data_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void VendorSpecific_MAD_Data_Block_Element_unpack(struct VendorSpecific_MAD_Data_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void VendorSpecific_MAD_Data_Block_Element_print(const struct VendorSpecific_MAD_Data_Block_Element *ptr_struct, FILE* file, int indent_level);
int VendorSpecific_MAD_Data_Block_Element_size(void);
#define VENDORSPECIFIC_MAD_DATA_BLOCK_ELEMENT_SIZE    (0xe0)
void VendorSpecific_MAD_Data_Block_Element_dump(const struct VendorSpecific_MAD_Data_Block_Element *ptr_struct, FILE* file);
/* acc_register */
void acc_register_pack(const struct acc_register *ptr_struct, u_int8_t* ptr_buff);
void acc_register_unpack(struct acc_register *ptr_struct, const u_int8_t* ptr_buff);
void acc_register_print(const struct acc_register *ptr_struct, FILE* file, int indent_level);
int acc_register_size(void);
#define ACC_REGISTER_SIZE    (0x2c)
void acc_register_dump(const struct acc_register *ptr_struct, FILE* file);
/* acc_register_gmp */
void acc_register_gmp_pack(const struct acc_register_gmp *ptr_struct, u_int8_t* ptr_buff);
void acc_register_gmp_unpack(struct acc_register_gmp *ptr_struct, const u_int8_t* ptr_buff);
void acc_register_gmp_print(const struct acc_register_gmp *ptr_struct, FILE* file, int indent_level);
int acc_register_gmp_size(void);
#define ACC_REGISTER_GMP_SIZE    (0xdc)
void acc_register_gmp_dump(const struct acc_register_gmp *ptr_struct, FILE* file);
/* adaptive_routing_group_table_copy_element */
void adaptive_routing_group_table_copy_element_pack(const struct adaptive_routing_group_table_copy_element *ptr_struct, u_int8_t* ptr_buff);
void adaptive_routing_group_table_copy_element_unpack(struct adaptive_routing_group_table_copy_element *ptr_struct, const u_int8_t* ptr_buff);
void adaptive_routing_group_table_copy_element_print(const struct adaptive_routing_group_table_copy_element *ptr_struct, FILE* file, int indent_level);
int adaptive_routing_group_table_copy_element_size(void);
#define ADAPTIVE_ROUTING_GROUP_TABLE_COPY_ELEMENT_SIZE    (0x4)
void adaptive_routing_group_table_copy_element_dump(const struct adaptive_routing_group_table_copy_element *ptr_struct, FILE* file);
/* adaptive_routing_info */
void adaptive_routing_info_pack(const struct adaptive_routing_info *ptr_struct, u_int8_t* ptr_buff);
void adaptive_routing_info_unpack(struct adaptive_routing_info *ptr_struct, const u_int8_t* ptr_buff);
void adaptive_routing_info_print(const struct adaptive_routing_info *ptr_struct, FILE* file, int indent_level);
int adaptive_routing_info_size(void);
#define ADAPTIVE_ROUTING_INFO_SIZE    (0x14)
void adaptive_routing_info_dump(const struct adaptive_routing_info *ptr_struct, FILE* file);
/* child_qp */
void child_qp_pack(const struct child_qp *ptr_struct, u_int8_t* ptr_buff);
void child_qp_unpack(struct child_qp *ptr_struct, const u_int8_t* ptr_buff);
void child_qp_print(const struct child_qp *ptr_struct, FILE* file, int indent_level);
int child_qp_size(void);
#define CHILD_QP_SIZE    (0x4)
void child_qp_dump(const struct child_qp *ptr_struct, FILE* file);
/* child_qpn */
void child_qpn_pack(const struct child_qpn *ptr_struct, u_int8_t* ptr_buff);
void child_qpn_unpack(struct child_qpn *ptr_struct, const u_int8_t* ptr_buff);
void child_qpn_print(const struct child_qpn *ptr_struct, FILE* file, int indent_level);
int child_qpn_size(void);
#define CHILD_QPN_SIZE    (0x4)
void child_qpn_dump(const struct child_qpn *ptr_struct, FILE* file);
/* ib_ar_lft_block_element_sx */
void ib_ar_lft_block_element_sx_pack(const struct ib_ar_lft_block_element_sx *ptr_struct, u_int8_t* ptr_buff);
void ib_ar_lft_block_element_sx_unpack(struct ib_ar_lft_block_element_sx *ptr_struct, const u_int8_t* ptr_buff);
void ib_ar_lft_block_element_sx_print(const struct ib_ar_lft_block_element_sx *ptr_struct, FILE* file, int indent_level);
int ib_ar_lft_block_element_sx_size(void);
#define IB_AR_LFT_BLOCK_ELEMENT_SX_SIZE    (0x4)
void ib_ar_lft_block_element_sx_dump(const struct ib_ar_lft_block_element_sx *ptr_struct, FILE* file);
/* ib_description_mode */
void ib_description_mode_pack(const struct ib_description_mode *ptr_struct, u_int8_t* ptr_buff);
void ib_description_mode_unpack(struct ib_description_mode *ptr_struct, const u_int8_t* ptr_buff);
void ib_description_mode_print(const struct ib_description_mode *ptr_struct, FILE* file, int indent_level);
int ib_description_mode_size(void);
#define IB_DESCRIPTION_MODE_SIZE    (0x2)
void ib_description_mode_dump(const struct ib_description_mode *ptr_struct, FILE* file);
/* ib_extended_switch_info */
void ib_extended_switch_info_pack(const struct ib_extended_switch_info *ptr_struct, u_int8_t* ptr_buff);
void ib_extended_switch_info_unpack(struct ib_extended_switch_info *ptr_struct, const u_int8_t* ptr_buff);
void ib_extended_switch_info_print(const struct ib_extended_switch_info *ptr_struct, FILE* file, int indent_level);
int ib_extended_switch_info_size(void);
#define IB_EXTENDED_SWITCH_INFO_SIZE    (0x4)
void ib_extended_switch_info_dump(const struct ib_extended_switch_info *ptr_struct, FILE* file);
/* ib_lft_def */
void ib_lft_def_pack(const struct ib_lft_def *ptr_struct, u_int8_t* ptr_buff);
void ib_lft_def_unpack(struct ib_lft_def *ptr_struct, const u_int8_t* ptr_buff);
void ib_lft_def_print(const struct ib_lft_def *ptr_struct, FILE* file, int indent_level);
int ib_lft_def_size(void);
#define IB_LFT_DEF_SIZE    (0x4)
void ib_lft_def_dump(const struct ib_lft_def *ptr_struct, FILE* file);
/* ib_port_sl_to_plft */
void ib_port_sl_to_plft_pack(const struct ib_port_sl_to_plft *ptr_struct, u_int8_t* ptr_buff);
void ib_port_sl_to_plft_unpack(struct ib_port_sl_to_plft *ptr_struct, const u_int8_t* ptr_buff);
void ib_port_sl_to_plft_print(const struct ib_port_sl_to_plft *ptr_struct, FILE* file, int indent_level);
int ib_port_sl_to_plft_size(void);
#define IB_PORT_SL_TO_PLFT_SIZE    (0x10)
void ib_port_sl_to_plft_dump(const struct ib_port_sl_to_plft *ptr_struct, FILE* file);
/* ib_private_lft_map */
void ib_private_lft_map_pack(const struct ib_private_lft_map *ptr_struct, u_int8_t* ptr_buff);
void ib_private_lft_map_unpack(struct ib_private_lft_map *ptr_struct, const u_int8_t* ptr_buff);
void ib_private_lft_map_print(const struct ib_private_lft_map *ptr_struct, FILE* file, int indent_level);
int ib_private_lft_map_size(void);
#define IB_PRIVATE_LFT_MAP_SIZE    (0x28)
void ib_private_lft_map_dump(const struct ib_private_lft_map *ptr_struct, FILE* file);
/* qpn */
void qpn_pack(const struct qpn *ptr_struct, u_int8_t* ptr_buff);
void qpn_unpack(struct qpn *ptr_struct, const u_int8_t* ptr_buff);
void qpn_print(const struct qpn *ptr_struct, FILE* file, int indent_level);
int qpn_size(void);
#define QPN_SIZE    (0x4)
void qpn_dump(const struct qpn *ptr_struct, FILE* file);
/* rn_gen_by_sub_group_prio_element */
void rn_gen_by_sub_group_prio_element_pack(const struct rn_gen_by_sub_group_prio_element *ptr_struct, u_int8_t* ptr_buff);
void rn_gen_by_sub_group_prio_element_unpack(struct rn_gen_by_sub_group_prio_element *ptr_struct, const u_int8_t* ptr_buff);
void rn_gen_by_sub_group_prio_element_print(const struct rn_gen_by_sub_group_prio_element *ptr_struct, FILE* file, int indent_level);
int rn_gen_by_sub_group_prio_element_size(void);
#define RN_GEN_BY_SUB_GROUP_PRIO_ELEMENT_SIZE    (0x4)
void rn_gen_by_sub_group_prio_element_dump(const struct rn_gen_by_sub_group_prio_element *ptr_struct, FILE* file);
/* rn_gen_by_sub_group_priority_element */
void rn_gen_by_sub_group_priority_element_pack(const struct rn_gen_by_sub_group_priority_element *ptr_struct, u_int8_t* ptr_buff);
void rn_gen_by_sub_group_priority_element_unpack(struct rn_gen_by_sub_group_priority_element *ptr_struct, const u_int8_t* ptr_buff);
void rn_gen_by_sub_group_priority_element_print(const struct rn_gen_by_sub_group_priority_element *ptr_struct, FILE* file, int indent_level);
int rn_gen_by_sub_group_priority_element_size(void);
#define RN_GEN_BY_SUB_GROUP_PRIORITY_ELEMENT_SIZE    (0x4)
void rn_gen_by_sub_group_priority_element_dump(const struct rn_gen_by_sub_group_priority_element *ptr_struct, FILE* file);
/* rn_gen_string_element */
void rn_gen_string_element_pack(const struct rn_gen_string_element *ptr_struct, u_int8_t* ptr_buff);
void rn_gen_string_element_unpack(struct rn_gen_string_element *ptr_struct, const u_int8_t* ptr_buff);
void rn_gen_string_element_print(const struct rn_gen_string_element *ptr_struct, FILE* file, int indent_level);
int rn_gen_string_element_size(void);
#define RN_GEN_STRING_ELEMENT_SIZE    (0x2)
void rn_gen_string_element_dump(const struct rn_gen_string_element *ptr_struct, FILE* file);
/* rn_rcv_string_element */
void rn_rcv_string_element_pack(const struct rn_rcv_string_element *ptr_struct, u_int8_t* ptr_buff);
void rn_rcv_string_element_unpack(struct rn_rcv_string_element *ptr_struct, const u_int8_t* ptr_buff);
void rn_rcv_string_element_print(const struct rn_rcv_string_element *ptr_struct, FILE* file, int indent_level);
int rn_rcv_string_element_size(void);
#define RN_RCV_STRING_ELEMENT_SIZE    (0x4)
void rn_rcv_string_element_dump(const struct rn_rcv_string_element *ptr_struct, FILE* file);
/* rn_sub_group_direction_tbl */
void rn_sub_group_direction_tbl_pack(const struct rn_sub_group_direction_tbl *ptr_struct, u_int8_t* ptr_buff);
void rn_sub_group_direction_tbl_unpack(struct rn_sub_group_direction_tbl *ptr_struct, const u_int8_t* ptr_buff);
void rn_sub_group_direction_tbl_print(const struct rn_sub_group_direction_tbl *ptr_struct, FILE* file, int indent_level);
int rn_sub_group_direction_tbl_size(void);
#define RN_SUB_GROUP_DIRECTION_TBL_SIZE    (0x40)
void rn_sub_group_direction_tbl_dump(const struct rn_sub_group_direction_tbl *ptr_struct, FILE* file);
/* rn_xmit_port_mask */
void rn_xmit_port_mask_pack(const struct rn_xmit_port_mask *ptr_struct, u_int8_t* ptr_buff);
void rn_xmit_port_mask_unpack(struct rn_xmit_port_mask *ptr_struct, const u_int8_t* ptr_buff);
void rn_xmit_port_mask_print(const struct rn_xmit_port_mask *ptr_struct, FILE* file, int indent_level);
int rn_xmit_port_mask_size(void);
#define RN_XMIT_PORT_MASK_SIZE    (0x40)
void rn_xmit_port_mask_dump(const struct rn_xmit_port_mask *ptr_struct, FILE* file);
/* uint64bit */
void uint64bit_pack(const struct uint64bit *ptr_struct, u_int8_t* ptr_buff);
void uint64bit_unpack(struct uint64bit *ptr_struct, const u_int8_t* ptr_buff);
void uint64bit_print(const struct uint64bit *ptr_struct, FILE* file, int indent_level);
int uint64bit_size(void);
#define UINT64BIT_SIZE    (0x8)
void uint64bit_dump(const struct uint64bit *ptr_struct, FILE* file);
/* AM_AMKeyInfo */
void AM_AMKeyInfo_pack(const struct AM_AMKeyInfo *ptr_struct, u_int8_t* ptr_buff);
void AM_AMKeyInfo_unpack(struct AM_AMKeyInfo *ptr_struct, const u_int8_t* ptr_buff);
void AM_AMKeyInfo_print(const struct AM_AMKeyInfo *ptr_struct, FILE* file, int indent_level);
int AM_AMKeyInfo_size(void);
#define AM_AMKEYINFO_SIZE    (0xc)
void AM_AMKeyInfo_dump(const struct AM_AMKeyInfo *ptr_struct, FILE* file);
/* AM_PerformanceCounters */
void AM_PerformanceCounters_pack(const struct AM_PerformanceCounters *ptr_struct, u_int8_t* ptr_buff);
void AM_PerformanceCounters_unpack(struct AM_PerformanceCounters *ptr_struct, const u_int8_t* ptr_buff);
void AM_PerformanceCounters_print(const struct AM_PerformanceCounters *ptr_struct, FILE* file, int indent_level);
int AM_PerformanceCounters_size(void);
#define AM_PERFORMANCECOUNTERS_SIZE    (0x50)
void AM_PerformanceCounters_dump(const struct AM_PerformanceCounters *ptr_struct, FILE* file);
/* AM_QPAllocation */
void AM_QPAllocation_pack(const struct AM_QPAllocation *ptr_struct, u_int8_t* ptr_buff);
void AM_QPAllocation_unpack(struct AM_QPAllocation *ptr_struct, const u_int8_t* ptr_buff);
void AM_QPAllocation_print(const struct AM_QPAllocation *ptr_struct, FILE* file, int indent_level);
int AM_QPAllocation_size(void);
#define AM_QPALLOCATION_SIZE    (0x90)
void AM_QPAllocation_dump(const struct AM_QPAllocation *ptr_struct, FILE* file);
/* AM_TrapQPAllocationTime */
void AM_TrapQPAllocationTime_pack(const struct AM_TrapQPAllocationTime *ptr_struct, u_int8_t* ptr_buff);
void AM_TrapQPAllocationTime_unpack(struct AM_TrapQPAllocationTime *ptr_struct, const u_int8_t* ptr_buff);
void AM_TrapQPAllocationTime_print(const struct AM_TrapQPAllocationTime *ptr_struct, FILE* file, int indent_level);
int AM_TrapQPAllocationTime_size(void);
#define AM_TRAPQPALLOCATIONTIME_SIZE    (0x38)
void AM_TrapQPAllocationTime_dump(const struct AM_TrapQPAllocationTime *ptr_struct, FILE* file);
/* AM_TrapQPAllocationTime_V2 */
void AM_TrapQPAllocationTime_V2_pack(const struct AM_TrapQPAllocationTime_V2 *ptr_struct, u_int8_t* ptr_buff);
void AM_TrapQPAllocationTime_V2_unpack(struct AM_TrapQPAllocationTime_V2 *ptr_struct, const u_int8_t* ptr_buff);
void AM_TrapQPAllocationTime_V2_print(const struct AM_TrapQPAllocationTime_V2 *ptr_struct, FILE* file, int indent_level);
int AM_TrapQPAllocationTime_V2_size(void);
#define AM_TRAPQPALLOCATIONTIME_V2_SIZE    (0x38)
void AM_TrapQPAllocationTime_V2_dump(const struct AM_TrapQPAllocationTime_V2 *ptr_struct, FILE* file);
/* AM_TrapQPError */
void AM_TrapQPError_pack(const struct AM_TrapQPError *ptr_struct, u_int8_t* ptr_buff);
void AM_TrapQPError_unpack(struct AM_TrapQPError *ptr_struct, const u_int8_t* ptr_buff);
void AM_TrapQPError_print(const struct AM_TrapQPError *ptr_struct, FILE* file, int indent_level);
int AM_TrapQPError_size(void);
#define AM_TRAPQPERROR_SIZE    (0x38)
void AM_TrapQPError_dump(const struct AM_TrapQPError *ptr_struct, FILE* file);
/* AM_TrapQPError_V2 */
void AM_TrapQPError_V2_pack(const struct AM_TrapQPError_V2 *ptr_struct, u_int8_t* ptr_buff);
void AM_TrapQPError_V2_unpack(struct AM_TrapQPError_V2 *ptr_struct, const u_int8_t* ptr_buff);
void AM_TrapQPError_V2_print(const struct AM_TrapQPError_V2 *ptr_struct, FILE* file, int indent_level);
int AM_TrapQPError_V2_size(void);
#define AM_TRAPQPERROR_V2_SIZE    (0x38)
void AM_TrapQPError_V2_dump(const struct AM_TrapQPError_V2 *ptr_struct, FILE* file);
/* AM_TrapSharpInvalidRequest */
void AM_TrapSharpInvalidRequest_pack(const struct AM_TrapSharpInvalidRequest *ptr_struct, u_int8_t* ptr_buff);
void AM_TrapSharpInvalidRequest_unpack(struct AM_TrapSharpInvalidRequest *ptr_struct, const u_int8_t* ptr_buff);
void AM_TrapSharpInvalidRequest_print(const struct AM_TrapSharpInvalidRequest *ptr_struct, FILE* file, int indent_level);
int AM_TrapSharpInvalidRequest_size(void);
#define AM_TRAPSHARPINVALIDREQUEST_SIZE    (0x38)
void AM_TrapSharpInvalidRequest_dump(const struct AM_TrapSharpInvalidRequest *ptr_struct, FILE* file);
/* AM_TrapSharpInvalidRequest_V2 */
void AM_TrapSharpInvalidRequest_V2_pack(const struct AM_TrapSharpInvalidRequest_V2 *ptr_struct, u_int8_t* ptr_buff);
void AM_TrapSharpInvalidRequest_V2_unpack(struct AM_TrapSharpInvalidRequest_V2 *ptr_struct, const u_int8_t* ptr_buff);
void AM_TrapSharpInvalidRequest_V2_print(const struct AM_TrapSharpInvalidRequest_V2 *ptr_struct, FILE* file, int indent_level);
int AM_TrapSharpInvalidRequest_V2_size(void);
#define AM_TRAPSHARPINVALIDREQUEST_V2_SIZE    (0x38)
void AM_TrapSharpInvalidRequest_V2_dump(const struct AM_TrapSharpInvalidRequest_V2 *ptr_struct, FILE* file);
/* AM_TreeConfig */
void AM_TreeConfig_pack(const struct AM_TreeConfig *ptr_struct, u_int8_t* ptr_buff);
void AM_TreeConfig_unpack(struct AM_TreeConfig *ptr_struct, const u_int8_t* ptr_buff);
void AM_TreeConfig_print(const struct AM_TreeConfig *ptr_struct, FILE* file, int indent_level);
int AM_TreeConfig_size(void);
#define AM_TREECONFIG_SIZE    (0xc0)
void AM_TreeConfig_dump(const struct AM_TreeConfig *ptr_struct, FILE* file);
/* CACongestionEntryList */
void CACongestionEntryList_pack(const struct CACongestionEntryList *ptr_struct, u_int8_t* ptr_buff);
void CACongestionEntryList_unpack(struct CACongestionEntryList *ptr_struct, const u_int8_t* ptr_buff);
void CACongestionEntryList_print(const struct CACongestionEntryList *ptr_struct, FILE* file, int indent_level);
int CACongestionEntryList_size(void);
#define CACONGESTIONENTRYLIST_SIZE    (0x80)
void CACongestionEntryList_dump(const struct CACongestionEntryList *ptr_struct, FILE* file);
/* CCTI_Entry_List */
void CCTI_Entry_List_pack(const struct CCTI_Entry_List *ptr_struct, u_int8_t* ptr_buff);
void CCTI_Entry_List_unpack(struct CCTI_Entry_List *ptr_struct, const u_int8_t* ptr_buff);
void CCTI_Entry_List_print(const struct CCTI_Entry_List *ptr_struct, FILE* file, int indent_level);
int CCTI_Entry_List_size(void);
#define CCTI_ENTRY_LIST_SIZE    (0x80)
void CCTI_Entry_List_dump(const struct CCTI_Entry_List *ptr_struct, FILE* file);
/* CC_CongestionKeyInfo */
void CC_CongestionKeyInfo_pack(const struct CC_CongestionKeyInfo *ptr_struct, u_int8_t* ptr_buff);
void CC_CongestionKeyInfo_unpack(struct CC_CongestionKeyInfo *ptr_struct, const u_int8_t* ptr_buff);
void CC_CongestionKeyInfo_print(const struct CC_CongestionKeyInfo *ptr_struct, FILE* file, int indent_level);
int CC_CongestionKeyInfo_size(void);
#define CC_CONGESTIONKEYINFO_SIZE    (0x10)
void CC_CongestionKeyInfo_dump(const struct CC_CongestionKeyInfo *ptr_struct, FILE* file);
/* CC_KeyViolation */
void CC_KeyViolation_pack(const struct CC_KeyViolation *ptr_struct, u_int8_t* ptr_buff);
void CC_KeyViolation_unpack(struct CC_KeyViolation *ptr_struct, const u_int8_t* ptr_buff);
void CC_KeyViolation_print(const struct CC_KeyViolation *ptr_struct, FILE* file, int indent_level);
int CC_KeyViolation_size(void);
#define CC_KEYVIOLATION_SIZE    (0x38)
void CC_KeyViolation_dump(const struct CC_KeyViolation *ptr_struct, FILE* file);
/* CC_SwitchCongestionSetting */
void CC_SwitchCongestionSetting_pack(const struct CC_SwitchCongestionSetting *ptr_struct, u_int8_t* ptr_buff);
void CC_SwitchCongestionSetting_unpack(struct CC_SwitchCongestionSetting *ptr_struct, const u_int8_t* ptr_buff);
void CC_SwitchCongestionSetting_print(const struct CC_SwitchCongestionSetting *ptr_struct, FILE* file, int indent_level);
int CC_SwitchCongestionSetting_size(void);
#define CC_SWITCHCONGESTIONSETTING_SIZE    (0x4c)
void CC_SwitchCongestionSetting_dump(const struct CC_SwitchCongestionSetting *ptr_struct, FILE* file);
/* CC_SwitchPortCongestionSetting */
void CC_SwitchPortCongestionSetting_pack(const struct CC_SwitchPortCongestionSetting *ptr_struct, u_int8_t* ptr_buff);
void CC_SwitchPortCongestionSetting_unpack(struct CC_SwitchPortCongestionSetting *ptr_struct, const u_int8_t* ptr_buff);
void CC_SwitchPortCongestionSetting_print(const struct CC_SwitchPortCongestionSetting *ptr_struct, FILE* file, int indent_level);
int CC_SwitchPortCongestionSetting_size(void);
#define CC_SWITCHPORTCONGESTIONSETTING_SIZE    (0x80)
void CC_SwitchPortCongestionSetting_dump(const struct CC_SwitchPortCongestionSetting *ptr_struct, FILE* file);
/* CongestionEntryListSwitch */
void CongestionEntryListSwitch_pack(const struct CongestionEntryListSwitch *ptr_struct, u_int8_t* ptr_buff);
void CongestionEntryListSwitch_unpack(struct CongestionEntryListSwitch *ptr_struct, const u_int8_t* ptr_buff);
void CongestionEntryListSwitch_print(const struct CongestionEntryListSwitch *ptr_struct, FILE* file, int indent_level);
int CongestionEntryListSwitch_size(void);
#define CONGESTIONENTRYLISTSWITCH_SIZE    (0xb4)
void CongestionEntryListSwitch_dump(const struct CongestionEntryListSwitch *ptr_struct, FILE* file);
/* CongestionLogEventListCA */
void CongestionLogEventListCA_pack(const struct CongestionLogEventListCA *ptr_struct, u_int8_t* ptr_buff);
void CongestionLogEventListCA_unpack(struct CongestionLogEventListCA *ptr_struct, const u_int8_t* ptr_buff);
void CongestionLogEventListCA_print(const struct CongestionLogEventListCA *ptr_struct, FILE* file, int indent_level);
int CongestionLogEventListCA_size(void);
#define CONGESTIONLOGEVENTLISTCA_SIZE    (0xd0)
void CongestionLogEventListCA_dump(const struct CongestionLogEventListCA *ptr_struct, FILE* file);
/* DD_set */
void DD_set_pack(const union DD_set *ptr_struct, u_int8_t* ptr_buff);
void DD_set_unpack(union DD_set *ptr_struct, const u_int8_t* ptr_buff);
void DD_set_print(const union DD_set *ptr_struct, FILE* file, int indent_level);
int DD_set_size(void);
#define DD_SET_SIZE    (0xd8)
void DD_set_dump(const union DD_set *ptr_struct, FILE* file);
/* FWInfo_Block_Element */
void FWInfo_Block_Element_pack(const struct FWInfo_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void FWInfo_Block_Element_unpack(struct FWInfo_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void FWInfo_Block_Element_print(const struct FWInfo_Block_Element *ptr_struct, FILE* file, int indent_level);
int FWInfo_Block_Element_size(void);
#define FWINFO_BLOCK_ELEMENT_SIZE    (0x40)
void FWInfo_Block_Element_dump(const struct FWInfo_Block_Element *ptr_struct, FILE* file);
/* GMP_AccessRegister */
void GMP_AccessRegister_pack(const struct GMP_AccessRegister *ptr_struct, u_int8_t* ptr_buff);
void GMP_AccessRegister_unpack(struct GMP_AccessRegister *ptr_struct, const u_int8_t* ptr_buff);
void GMP_AccessRegister_print(const struct GMP_AccessRegister *ptr_struct, FILE* file, int indent_level);
int GMP_AccessRegister_size(void);
#define GMP_ACCESSREGISTER_SIZE    (0xe0)
void GMP_AccessRegister_dump(const struct GMP_AccessRegister *ptr_struct, FILE* file);
/* GUID_Block_Element */
void GUID_Block_Element_pack(const struct GUID_Block_Element *ptr_struct, u_int8_t* ptr_buff);
void GUID_Block_Element_unpack(struct GUID_Block_Element *ptr_struct, const u_int8_t* ptr_buff);
void GUID_Block_Element_print(const struct GUID_Block_Element *ptr_struct, FILE* file, int indent_level);
int GUID_Block_Element_size(void);
#define GUID_BLOCK_ELEMENT_SIZE    (0x40)
void GUID_Block_Element_dump(const struct GUID_Block_Element *ptr_struct, FILE* file);
/* IB_AtomicAckETH */
void IB_AtomicAckETH_pack(const struct IB_AtomicAckETH *ptr_struct, u_int8_t* ptr_buff);
void IB_AtomicAckETH_unpack(struct IB_AtomicAckETH *ptr_struct, const u_int8_t* ptr_buff);
void IB_AtomicAckETH_print(const struct IB_AtomicAckETH *ptr_struct, FILE* file, int indent_level);
int IB_AtomicAckETH_size(void);
#define IB_ATOMICACKETH_SIZE    (0x8)
void IB_AtomicAckETH_dump(const struct IB_AtomicAckETH *ptr_struct, FILE* file);
/* IB_AtomicETH */
void IB_AtomicETH_pack(const struct IB_AtomicETH *ptr_struct, u_int8_t* ptr_buff);
void IB_AtomicETH_unpack(struct IB_AtomicETH *ptr_struct, const u_int8_t* ptr_buff);
void IB_AtomicETH_print(const struct IB_AtomicETH *ptr_struct, FILE* file, int indent_level);
int IB_AtomicETH_size(void);
#define IB_ATOMICETH_SIZE    (0x1c)
void IB_AtomicETH_dump(const struct IB_AtomicETH *ptr_struct, FILE* file);
/* IB_BTH */
void IB_BTH_pack(const struct IB_BTH *ptr_struct, u_int8_t* ptr_buff);
void IB_BTH_unpack(struct IB_BTH *ptr_struct, const u_int8_t* ptr_buff);
void IB_BTH_print(const struct IB_BTH *ptr_struct, FILE* file, int indent_level);
int IB_BTH_size(void);
#define IB_BTH_SIZE    (0xc)
void IB_BTH_dump(const struct IB_BTH *ptr_struct, FILE* file);
/* IB_BTH_CNP */
void IB_BTH_CNP_pack(const struct IB_BTH_CNP *ptr_struct, u_int8_t* ptr_buff);
void IB_BTH_CNP_unpack(struct IB_BTH_CNP *ptr_struct, const u_int8_t* ptr_buff);
void IB_BTH_CNP_print(const struct IB_BTH_CNP *ptr_struct, FILE* file, int indent_level);
int IB_BTH_CNP_size(void);
#define IB_BTH_CNP_SIZE    (0xc)
void IB_BTH_CNP_dump(const struct IB_BTH_CNP *ptr_struct, FILE* file);
/* IB_ClassPortInfo */
void IB_ClassPortInfo_pack(const struct IB_ClassPortInfo *ptr_struct, u_int8_t* ptr_buff);
void IB_ClassPortInfo_unpack(struct IB_ClassPortInfo *ptr_struct, const u_int8_t* ptr_buff);
void IB_ClassPortInfo_print(const struct IB_ClassPortInfo *ptr_struct, FILE* file, int indent_level);
int IB_ClassPortInfo_size(void);
#define IB_CLASSPORTINFO_SIZE    (0x48)
void IB_ClassPortInfo_dump(const struct IB_ClassPortInfo *ptr_struct, FILE* file);
/* IB_GRH */
void IB_GRH_pack(const struct IB_GRH *ptr_struct, u_int8_t* ptr_buff);
void IB_GRH_unpack(struct IB_GRH *ptr_struct, const u_int8_t* ptr_buff);
void IB_GRH_print(const struct IB_GRH *ptr_struct, FILE* file, int indent_level);
int IB_GRH_size(void);
#define IB_GRH_SIZE    (0x28)
void IB_GRH_dump(const struct IB_GRH *ptr_struct, FILE* file);
/* IB_RETH */
void IB_RETH_pack(const struct IB_RETH *ptr_struct, u_int8_t* ptr_buff);
void IB_RETH_unpack(struct IB_RETH *ptr_struct, const u_int8_t* ptr_buff);
void IB_RETH_print(const struct IB_RETH *ptr_struct, FILE* file, int indent_level);
int IB_RETH_size(void);
#define IB_RETH_SIZE    (0x10)
void IB_RETH_dump(const struct IB_RETH *ptr_struct, FILE* file);
/* MAD_Header_Common */
void MAD_Header_Common_pack(const struct MAD_Header_Common *ptr_struct, u_int8_t* ptr_buff);
void MAD_Header_Common_unpack(struct MAD_Header_Common *ptr_struct, const u_int8_t* ptr_buff);
void MAD_Header_Common_print(const struct MAD_Header_Common *ptr_struct, FILE* file, int indent_level);
int MAD_Header_Common_size(void);
#define MAD_HEADER_COMMON_SIZE    (0x18)
void MAD_Header_Common_dump(const struct MAD_Header_Common *ptr_struct, FILE* file);
/* MAD_Header_Common_With_RMPP */
void MAD_Header_Common_With_RMPP_pack(const struct MAD_Header_Common_With_RMPP *ptr_struct, u_int8_t* ptr_buff);
void MAD_Header_Common_With_RMPP_unpack(struct MAD_Header_Common_With_RMPP *ptr_struct, const u_int8_t* ptr_buff);
void MAD_Header_Common_With_RMPP_print(const struct MAD_Header_Common_With_RMPP *ptr_struct, FILE* file, int indent_level);
int MAD_Header_Common_With_RMPP_size(void);
#define MAD_HEADER_COMMON_WITH_RMPP_SIZE    (0x24)
void MAD_Header_Common_With_RMPP_dump(const struct MAD_Header_Common_With_RMPP *ptr_struct, FILE* file);
/* MAD_Header_SMP_Direct_Routed */
void MAD_Header_SMP_Direct_Routed_pack(const struct MAD_Header_SMP_Direct_Routed *ptr_struct, u_int8_t* ptr_buff);
void MAD_Header_SMP_Direct_Routed_unpack(struct MAD_Header_SMP_Direct_Routed *ptr_struct, const u_int8_t* ptr_buff);
void MAD_Header_SMP_Direct_Routed_print(const struct MAD_Header_SMP_Direct_Routed *ptr_struct, FILE* file, int indent_level);
int MAD_Header_SMP_Direct_Routed_size(void);
#define MAD_HEADER_SMP_DIRECT_ROUTED_SIZE    (0x18)
void MAD_Header_SMP_Direct_Routed_dump(const struct MAD_Header_SMP_Direct_Routed *ptr_struct, FILE* file);
/* NextHopRecord */
void NextHopRecord_pack(const struct NextHopRecord *ptr_struct, u_int8_t* ptr_buff);
void NextHopRecord_unpack(struct NextHopRecord *ptr_struct, const u_int8_t* ptr_buff);
void NextHopRecord_print(const struct NextHopRecord *ptr_struct, FILE* file, int indent_level);
int NextHopRecord_size(void);
#define NEXTHOPRECORD_SIZE    (0x10)
void NextHopRecord_dump(const struct NextHopRecord *ptr_struct, FILE* file);
/* PM_PortCounters */
void PM_PortCounters_pack(const struct PM_PortCounters *ptr_struct, u_int8_t* ptr_buff);
void PM_PortCounters_unpack(struct PM_PortCounters *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortCounters_print(const struct PM_PortCounters *ptr_struct, FILE* file, int indent_level);
int PM_PortCounters_size(void);
#define PM_PORTCOUNTERS_SIZE    (0x2c)
void PM_PortCounters_dump(const struct PM_PortCounters *ptr_struct, FILE* file);
/* PM_PortCountersExtended */
void PM_PortCountersExtended_pack(const struct PM_PortCountersExtended *ptr_struct, u_int8_t* ptr_buff);
void PM_PortCountersExtended_unpack(struct PM_PortCountersExtended *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortCountersExtended_print(const struct PM_PortCountersExtended *ptr_struct, FILE* file, int indent_level);
int PM_PortCountersExtended_size(void);
#define PM_PORTCOUNTERSEXTENDED_SIZE    (0x48)
void PM_PortCountersExtended_dump(const struct PM_PortCountersExtended *ptr_struct, FILE* file);
/* PM_PortExtendedSpeedsCounters */
void PM_PortExtendedSpeedsCounters_pack(const struct PM_PortExtendedSpeedsCounters *ptr_struct, u_int8_t* ptr_buff);
void PM_PortExtendedSpeedsCounters_unpack(struct PM_PortExtendedSpeedsCounters *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortExtendedSpeedsCounters_print(const struct PM_PortExtendedSpeedsCounters *ptr_struct, FILE* file, int indent_level);
int PM_PortExtendedSpeedsCounters_size(void);
#define PM_PORTEXTENDEDSPEEDSCOUNTERS_SIZE    (0x8c)
void PM_PortExtendedSpeedsCounters_dump(const struct PM_PortExtendedSpeedsCounters *ptr_struct, FILE* file);
/* PM_PortExtendedSpeedsRSFECCounters */
void PM_PortExtendedSpeedsRSFECCounters_pack(const struct PM_PortExtendedSpeedsRSFECCounters *ptr_struct, u_int8_t* ptr_buff);
void PM_PortExtendedSpeedsRSFECCounters_unpack(struct PM_PortExtendedSpeedsRSFECCounters *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortExtendedSpeedsRSFECCounters_print(const struct PM_PortExtendedSpeedsRSFECCounters *ptr_struct, FILE* file, int indent_level);
int PM_PortExtendedSpeedsRSFECCounters_size(void);
#define PM_PORTEXTENDEDSPEEDSRSFECCOUNTERS_SIZE    (0x98)
void PM_PortExtendedSpeedsRSFECCounters_dump(const struct PM_PortExtendedSpeedsRSFECCounters *ptr_struct, FILE* file);
/* PM_PortRcvErrorDetails */
void PM_PortRcvErrorDetails_pack(const struct PM_PortRcvErrorDetails *ptr_struct, u_int8_t* ptr_buff);
void PM_PortRcvErrorDetails_unpack(struct PM_PortRcvErrorDetails *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortRcvErrorDetails_print(const struct PM_PortRcvErrorDetails *ptr_struct, FILE* file, int indent_level);
int PM_PortRcvErrorDetails_size(void);
#define PM_PORTRCVERRORDETAILS_SIZE    (0x40)
void PM_PortRcvErrorDetails_dump(const struct PM_PortRcvErrorDetails *ptr_struct, FILE* file);
/* PM_PortSamplesControl */
void PM_PortSamplesControl_pack(const struct PM_PortSamplesControl *ptr_struct, u_int8_t* ptr_buff);
void PM_PortSamplesControl_unpack(struct PM_PortSamplesControl *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortSamplesControl_print(const struct PM_PortSamplesControl *ptr_struct, FILE* file, int indent_level);
int PM_PortSamplesControl_size(void);
#define PM_PORTSAMPLESCONTROL_SIZE    (0x68)
void PM_PortSamplesControl_dump(const struct PM_PortSamplesControl *ptr_struct, FILE* file);
/* PM_PortXmitDiscardDetails */
void PM_PortXmitDiscardDetails_pack(const struct PM_PortXmitDiscardDetails *ptr_struct, u_int8_t* ptr_buff);
void PM_PortXmitDiscardDetails_unpack(struct PM_PortXmitDiscardDetails *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortXmitDiscardDetails_print(const struct PM_PortXmitDiscardDetails *ptr_struct, FILE* file, int indent_level);
int PM_PortXmitDiscardDetails_size(void);
#define PM_PORTXMITDISCARDDETAILS_SIZE    (0x40)
void PM_PortXmitDiscardDetails_dump(const struct PM_PortXmitDiscardDetails *ptr_struct, FILE* file);
/* RawData_PM_PortRcvXmitCntrsSl64 */
void RawData_PM_PortRcvXmitCntrsSl64_pack(const struct RawData_PM_PortRcvXmitCntrsSl64 *ptr_struct, u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsSl64_unpack(struct RawData_PM_PortRcvXmitCntrsSl64 *ptr_struct, const u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsSl64_print(const struct RawData_PM_PortRcvXmitCntrsSl64 *ptr_struct, FILE* file, int indent_level);
int RawData_PM_PortRcvXmitCntrsSl64_size(void);
#define RAWDATA_PM_PORTRCVXMITCNTRSSL64_SIZE    (0x84)
void RawData_PM_PortRcvXmitCntrsSl64_dump(const struct RawData_PM_PortRcvXmitCntrsSl64 *ptr_struct, FILE* file);
/* RawData_PM_PortRcvXmitCntrsVl64 */
void RawData_PM_PortRcvXmitCntrsVl64_pack(const struct RawData_PM_PortRcvXmitCntrsVl64 *ptr_struct, u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsVl64_unpack(struct RawData_PM_PortRcvXmitCntrsVl64 *ptr_struct, const u_int8_t* ptr_buff);
void RawData_PM_PortRcvXmitCntrsVl64_print(const struct RawData_PM_PortRcvXmitCntrsVl64 *ptr_struct, FILE* file, int indent_level);
int RawData_PM_PortRcvXmitCntrsVl64_size(void);
#define RAWDATA_PM_PORTRCVXMITCNTRSVL64_SIZE    (0x80)
void RawData_PM_PortRcvXmitCntrsVl64_dump(const struct RawData_PM_PortRcvXmitCntrsVl64 *ptr_struct, FILE* file);
/* SA_MCMMemberRecord */
void SA_MCMMemberRecord_pack(const struct SA_MCMMemberRecord *ptr_struct, u_int8_t* ptr_buff);
void SA_MCMMemberRecord_unpack(struct SA_MCMMemberRecord *ptr_struct, const u_int8_t* ptr_buff);
void SA_MCMMemberRecord_print(const struct SA_MCMMemberRecord *ptr_struct, FILE* file, int indent_level);
int SA_MCMMemberRecord_size(void);
#define SA_MCMMEMBERRECORD_SIZE    (0x34)
void SA_MCMMemberRecord_dump(const struct SA_MCMMemberRecord *ptr_struct, FILE* file);
/* SMP_AccessRegister */
void SMP_AccessRegister_pack(const struct SMP_AccessRegister *ptr_struct, u_int8_t* ptr_buff);
void SMP_AccessRegister_unpack(struct SMP_AccessRegister *ptr_struct, const u_int8_t* ptr_buff);
void SMP_AccessRegister_print(const struct SMP_AccessRegister *ptr_struct, FILE* file, int indent_level);
int SMP_AccessRegister_size(void);
#define SMP_ACCESSREGISTER_SIZE    (0x40)
void SMP_AccessRegister_dump(const struct SMP_AccessRegister *ptr_struct, FILE* file);
/* SMP_AdjSiteLocalSubnTbl */
void SMP_AdjSiteLocalSubnTbl_pack(const struct SMP_AdjSiteLocalSubnTbl *ptr_struct, u_int8_t* ptr_buff);
void SMP_AdjSiteLocalSubnTbl_unpack(struct SMP_AdjSiteLocalSubnTbl *ptr_struct, const u_int8_t* ptr_buff);
void SMP_AdjSiteLocalSubnTbl_print(const struct SMP_AdjSiteLocalSubnTbl *ptr_struct, FILE* file, int indent_level);
int SMP_AdjSiteLocalSubnTbl_size(void);
#define SMP_ADJSITELOCALSUBNTBL_SIZE    (0x40)
void SMP_AdjSiteLocalSubnTbl_dump(const struct SMP_AdjSiteLocalSubnTbl *ptr_struct, FILE* file);
/* SMP_NodeInfo */
void SMP_NodeInfo_pack(const struct SMP_NodeInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_NodeInfo_unpack(struct SMP_NodeInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_NodeInfo_print(const struct SMP_NodeInfo *ptr_struct, FILE* file, int indent_level);
int SMP_NodeInfo_size(void);
#define SMP_NODEINFO_SIZE    (0x28)
void SMP_NodeInfo_dump(const struct SMP_NodeInfo *ptr_struct, FILE* file);
/* SMP_PKeyTable */
void SMP_PKeyTable_pack(const struct SMP_PKeyTable *ptr_struct, u_int8_t* ptr_buff);
void SMP_PKeyTable_unpack(struct SMP_PKeyTable *ptr_struct, const u_int8_t* ptr_buff);
void SMP_PKeyTable_print(const struct SMP_PKeyTable *ptr_struct, FILE* file, int indent_level);
int SMP_PKeyTable_size(void);
#define SMP_PKEYTABLE_SIZE    (0x40)
void SMP_PKeyTable_dump(const struct SMP_PKeyTable *ptr_struct, FILE* file);
/* SMP_PortInfo */
void SMP_PortInfo_pack(const struct SMP_PortInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_PortInfo_unpack(struct SMP_PortInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_PortInfo_print(const struct SMP_PortInfo *ptr_struct, FILE* file, int indent_level);
int SMP_PortInfo_size(void);
#define SMP_PORTINFO_SIZE    (0x40)
void SMP_PortInfo_dump(const struct SMP_PortInfo *ptr_struct, FILE* file);
/* SMP_QosConfigSL */
void SMP_QosConfigSL_pack(const struct SMP_QosConfigSL *ptr_struct, u_int8_t* ptr_buff);
void SMP_QosConfigSL_unpack(struct SMP_QosConfigSL *ptr_struct, const u_int8_t* ptr_buff);
void SMP_QosConfigSL_print(const struct SMP_QosConfigSL *ptr_struct, FILE* file, int indent_level);
int SMP_QosConfigSL_size(void);
#define SMP_QOSCONFIGSL_SIZE    (0x40)
void SMP_QosConfigSL_dump(const struct SMP_QosConfigSL *ptr_struct, FILE* file);
/* SMP_RandomForwardingTable */
void SMP_RandomForwardingTable_pack(const struct SMP_RandomForwardingTable *ptr_struct, u_int8_t* ptr_buff);
void SMP_RandomForwardingTable_unpack(struct SMP_RandomForwardingTable *ptr_struct, const u_int8_t* ptr_buff);
void SMP_RandomForwardingTable_print(const struct SMP_RandomForwardingTable *ptr_struct, FILE* file, int indent_level);
int SMP_RandomForwardingTable_size(void);
#define SMP_RANDOMFORWARDINGTABLE_SIZE    (0x40)
void SMP_RandomForwardingTable_dump(const struct SMP_RandomForwardingTable *ptr_struct, FILE* file);
/* SMP_SMInfo */
void SMP_SMInfo_pack(const struct SMP_SMInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_SMInfo_unpack(struct SMP_SMInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_SMInfo_print(const struct SMP_SMInfo *ptr_struct, FILE* file, int indent_level);
int SMP_SMInfo_size(void);
#define SMP_SMINFO_SIZE    (0x18)
void SMP_SMInfo_dump(const struct SMP_SMInfo *ptr_struct, FILE* file);
/* SMP_VLArbitrationTable */
void SMP_VLArbitrationTable_pack(const struct SMP_VLArbitrationTable *ptr_struct, u_int8_t* ptr_buff);
void SMP_VLArbitrationTable_unpack(struct SMP_VLArbitrationTable *ptr_struct, const u_int8_t* ptr_buff);
void SMP_VLArbitrationTable_print(const struct SMP_VLArbitrationTable *ptr_struct, FILE* file, int indent_level);
int SMP_VLArbitrationTable_size(void);
#define SMP_VLARBITRATIONTABLE_SIZE    (0x40)
void SMP_VLArbitrationTable_dump(const struct SMP_VLArbitrationTable *ptr_struct, FILE* file);
/* SMP_VNodeInfo */
void SMP_VNodeInfo_pack(const struct SMP_VNodeInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_VNodeInfo_unpack(struct SMP_VNodeInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_VNodeInfo_print(const struct SMP_VNodeInfo *ptr_struct, FILE* file, int indent_level);
int SMP_VNodeInfo_size(void);
#define SMP_VNODEINFO_SIZE    (0x40)
void SMP_VNodeInfo_dump(const struct SMP_VNodeInfo *ptr_struct, FILE* file);
/* SMP_VPortInfo */
void SMP_VPortInfo_pack(const struct SMP_VPortInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_VPortInfo_unpack(struct SMP_VPortInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_VPortInfo_print(const struct SMP_VPortInfo *ptr_struct, FILE* file, int indent_level);
int SMP_VPortInfo_size(void);
#define SMP_VPORTINFO_SIZE    (0x40)
void SMP_VPortInfo_dump(const struct SMP_VPortInfo *ptr_struct, FILE* file);
/* VendorSpec_PortLLRStatistics */
void VendorSpec_PortLLRStatistics_pack(const struct VendorSpec_PortLLRStatistics *ptr_struct, u_int8_t* ptr_buff);
void VendorSpec_PortLLRStatistics_unpack(struct VendorSpec_PortLLRStatistics *ptr_struct, const u_int8_t* ptr_buff);
void VendorSpec_PortLLRStatistics_print(const struct VendorSpec_PortLLRStatistics *ptr_struct, FILE* file, int indent_level);
int VendorSpec_PortLLRStatistics_size(void);
#define VENDORSPEC_PORTLLRSTATISTICS_SIZE    (0x60)
void VendorSpec_PortLLRStatistics_dump(const struct VendorSpec_PortLLRStatistics *ptr_struct, FILE* file);
/* adaptive_routing_group_table_copy */
void adaptive_routing_group_table_copy_pack(const struct adaptive_routing_group_table_copy *ptr_struct, u_int8_t* ptr_buff);
void adaptive_routing_group_table_copy_unpack(struct adaptive_routing_group_table_copy *ptr_struct, const u_int8_t* ptr_buff);
void adaptive_routing_group_table_copy_print(const struct adaptive_routing_group_table_copy *ptr_struct, FILE* file, int indent_level);
int adaptive_routing_group_table_copy_size(void);
#define ADAPTIVE_ROUTING_GROUP_TABLE_COPY_SIZE    (0x40)
void adaptive_routing_group_table_copy_dump(const struct adaptive_routing_group_table_copy *ptr_struct, FILE* file);
/* ib_ar_linear_forwarding_table_sx */
void ib_ar_linear_forwarding_table_sx_pack(const struct ib_ar_linear_forwarding_table_sx *ptr_struct, u_int8_t* ptr_buff);
void ib_ar_linear_forwarding_table_sx_unpack(struct ib_ar_linear_forwarding_table_sx *ptr_struct, const u_int8_t* ptr_buff);
void ib_ar_linear_forwarding_table_sx_print(const struct ib_ar_linear_forwarding_table_sx *ptr_struct, FILE* file, int indent_level);
int ib_ar_linear_forwarding_table_sx_size(void);
#define IB_AR_LINEAR_FORWARDING_TABLE_SX_SIZE    (0x40)
void ib_ar_linear_forwarding_table_sx_dump(const struct ib_ar_linear_forwarding_table_sx *ptr_struct, FILE* file);
/* ib_port_sl_to_private_lft_map */
void ib_port_sl_to_private_lft_map_pack(const struct ib_port_sl_to_private_lft_map *ptr_struct, u_int8_t* ptr_buff);
void ib_port_sl_to_private_lft_map_unpack(struct ib_port_sl_to_private_lft_map *ptr_struct, const u_int8_t* ptr_buff);
void ib_port_sl_to_private_lft_map_print(const struct ib_port_sl_to_private_lft_map *ptr_struct, FILE* file, int indent_level);
int ib_port_sl_to_private_lft_map_size(void);
#define IB_PORT_SL_TO_PRIVATE_LFT_MAP_SIZE    (0x40)
void ib_port_sl_to_private_lft_map_dump(const struct ib_port_sl_to_private_lft_map *ptr_struct, FILE* file);
/* ib_portgroup_block_element */
void ib_portgroup_block_element_pack(const struct ib_portgroup_block_element *ptr_struct, u_int8_t* ptr_buff);
void ib_portgroup_block_element_unpack(struct ib_portgroup_block_element *ptr_struct, const u_int8_t* ptr_buff);
void ib_portgroup_block_element_print(const struct ib_portgroup_block_element *ptr_struct, FILE* file, int indent_level);
int ib_portgroup_block_element_size(void);
#define IB_PORTGROUP_BLOCK_ELEMENT_SIZE    (0x20)
void ib_portgroup_block_element_dump(const struct ib_portgroup_block_element *ptr_struct, FILE* file);
/* ib_private_lft_def */
void ib_private_lft_def_pack(const struct ib_private_lft_def *ptr_struct, u_int8_t* ptr_buff);
void ib_private_lft_def_unpack(struct ib_private_lft_def *ptr_struct, const u_int8_t* ptr_buff);
void ib_private_lft_def_print(const struct ib_private_lft_def *ptr_struct, FILE* file, int indent_level);
int ib_private_lft_def_size(void);
#define IB_PRIVATE_LFT_DEF_SIZE    (0x40)
void ib_private_lft_def_dump(const struct ib_private_lft_def *ptr_struct, FILE* file);
/* ib_private_lft_info */
void ib_private_lft_info_pack(const struct ib_private_lft_info *ptr_struct, u_int8_t* ptr_buff);
void ib_private_lft_info_unpack(struct ib_private_lft_info *ptr_struct, const u_int8_t* ptr_buff);
void ib_private_lft_info_print(const struct ib_private_lft_info *ptr_struct, FILE* file, int indent_level);
int ib_private_lft_info_size(void);
#define IB_PRIVATE_LFT_INFO_SIZE    (0x40)
void ib_private_lft_info_dump(const struct ib_private_lft_info *ptr_struct, FILE* file);
/* port_rn_counters */
void port_rn_counters_pack(const struct port_rn_counters *ptr_struct, u_int8_t* ptr_buff);
void port_rn_counters_unpack(struct port_rn_counters *ptr_struct, const u_int8_t* ptr_buff);
void port_rn_counters_print(const struct port_rn_counters *ptr_struct, FILE* file, int indent_level);
int port_rn_counters_size(void);
#define PORT_RN_COUNTERS_SIZE    (0xc0)
void port_rn_counters_dump(const struct port_rn_counters *ptr_struct, FILE* file);
/* rn_gen_by_sub_group_prio */
void rn_gen_by_sub_group_prio_pack(const struct rn_gen_by_sub_group_prio *ptr_struct, u_int8_t* ptr_buff);
void rn_gen_by_sub_group_prio_unpack(struct rn_gen_by_sub_group_prio *ptr_struct, const u_int8_t* ptr_buff);
void rn_gen_by_sub_group_prio_print(const struct rn_gen_by_sub_group_prio *ptr_struct, FILE* file, int indent_level);
int rn_gen_by_sub_group_prio_size(void);
#define RN_GEN_BY_SUB_GROUP_PRIO_SIZE    (0x40)
void rn_gen_by_sub_group_prio_dump(const struct rn_gen_by_sub_group_prio *ptr_struct, FILE* file);
/* rn_gen_by_sub_group_priority */
void rn_gen_by_sub_group_priority_pack(const struct rn_gen_by_sub_group_priority *ptr_struct, u_int8_t* ptr_buff);
void rn_gen_by_sub_group_priority_unpack(struct rn_gen_by_sub_group_priority *ptr_struct, const u_int8_t* ptr_buff);
void rn_gen_by_sub_group_priority_print(const struct rn_gen_by_sub_group_priority *ptr_struct, FILE* file, int indent_level);
int rn_gen_by_sub_group_priority_size(void);
#define RN_GEN_BY_SUB_GROUP_PRIORITY_SIZE    (0x40)
void rn_gen_by_sub_group_priority_dump(const struct rn_gen_by_sub_group_priority *ptr_struct, FILE* file);
/* rn_gen_string_tbl */
void rn_gen_string_tbl_pack(const struct rn_gen_string_tbl *ptr_struct, u_int8_t* ptr_buff);
void rn_gen_string_tbl_unpack(struct rn_gen_string_tbl *ptr_struct, const u_int8_t* ptr_buff);
void rn_gen_string_tbl_print(const struct rn_gen_string_tbl *ptr_struct, FILE* file, int indent_level);
int rn_gen_string_tbl_size(void);
#define RN_GEN_STRING_TBL_SIZE    (0x40)
void rn_gen_string_tbl_dump(const struct rn_gen_string_tbl *ptr_struct, FILE* file);
/* rn_rcv_string */
void rn_rcv_string_pack(const struct rn_rcv_string *ptr_struct, u_int8_t* ptr_buff);
void rn_rcv_string_unpack(struct rn_rcv_string *ptr_struct, const u_int8_t* ptr_buff);
void rn_rcv_string_print(const struct rn_rcv_string *ptr_struct, FILE* file, int indent_level);
int rn_rcv_string_size(void);
#define RN_RCV_STRING_SIZE    (0x40)
void rn_rcv_string_dump(const struct rn_rcv_string *ptr_struct, FILE* file);
/* CC_CACongestionSetting */
void CC_CACongestionSetting_pack(const struct CC_CACongestionSetting *ptr_struct, u_int8_t* ptr_buff);
void CC_CACongestionSetting_unpack(struct CC_CACongestionSetting *ptr_struct, const u_int8_t* ptr_buff);
void CC_CACongestionSetting_print(const struct CC_CACongestionSetting *ptr_struct, FILE* file, int indent_level);
int CC_CACongestionSetting_size(void);
#define CC_CACONGESTIONSETTING_SIZE    (0x84)
void CC_CACongestionSetting_dump(const struct CC_CACongestionSetting *ptr_struct, FILE* file);
/* CC_CongestionControlTable */
void CC_CongestionControlTable_pack(const struct CC_CongestionControlTable *ptr_struct, u_int8_t* ptr_buff);
void CC_CongestionControlTable_unpack(struct CC_CongestionControlTable *ptr_struct, const u_int8_t* ptr_buff);
void CC_CongestionControlTable_print(const struct CC_CongestionControlTable *ptr_struct, FILE* file, int indent_level);
int CC_CongestionControlTable_size(void);
#define CC_CONGESTIONCONTROLTABLE_SIZE    (0x84)
void CC_CongestionControlTable_dump(const struct CC_CongestionControlTable *ptr_struct, FILE* file);
/* CC_CongestionLogCA */
void CC_CongestionLogCA_pack(const struct CC_CongestionLogCA *ptr_struct, u_int8_t* ptr_buff);
void CC_CongestionLogCA_unpack(struct CC_CongestionLogCA *ptr_struct, const u_int8_t* ptr_buff);
void CC_CongestionLogCA_print(const struct CC_CongestionLogCA *ptr_struct, FILE* file, int indent_level);
int CC_CongestionLogCA_size(void);
#define CC_CONGESTIONLOGCA_SIZE    (0xdc)
void CC_CongestionLogCA_dump(const struct CC_CongestionLogCA *ptr_struct, FILE* file);
/* CC_CongestionLogSwitch */
void CC_CongestionLogSwitch_pack(const struct CC_CongestionLogSwitch *ptr_struct, u_int8_t* ptr_buff);
void CC_CongestionLogSwitch_unpack(struct CC_CongestionLogSwitch *ptr_struct, const u_int8_t* ptr_buff);
void CC_CongestionLogSwitch_print(const struct CC_CongestionLogSwitch *ptr_struct, FILE* file, int indent_level);
int CC_CongestionLogSwitch_size(void);
#define CC_CONGESTIONLOGSWITCH_SIZE    (0xdc)
void CC_CongestionLogSwitch_dump(const struct CC_CongestionLogSwitch *ptr_struct, FILE* file);
/* CC_Notice */
void CC_Notice_pack(const struct CC_Notice *ptr_struct, u_int8_t* ptr_buff);
void CC_Notice_unpack(struct CC_Notice *ptr_struct, const u_int8_t* ptr_buff);
void CC_Notice_print(const struct CC_Notice *ptr_struct, FILE* file, int indent_level);
int CC_Notice_size(void);
#define CC_NOTICE_SIZE    (0x50)
void CC_Notice_dump(const struct CC_Notice *ptr_struct, FILE* file);
/* MAD_AggregationManagement */
void MAD_AggregationManagement_pack(const struct MAD_AggregationManagement *ptr_struct, u_int8_t* ptr_buff);
void MAD_AggregationManagement_unpack(struct MAD_AggregationManagement *ptr_struct, const u_int8_t* ptr_buff);
void MAD_AggregationManagement_print(const struct MAD_AggregationManagement *ptr_struct, FILE* file, int indent_level);
int MAD_AggregationManagement_size(void);
#define MAD_AGGREGATIONMANAGEMENT_SIZE    (0x100)
void MAD_AggregationManagement_dump(const struct MAD_AggregationManagement *ptr_struct, FILE* file);
/* MAD_CongestionControl */
void MAD_CongestionControl_pack(const struct MAD_CongestionControl *ptr_struct, u_int8_t* ptr_buff);
void MAD_CongestionControl_unpack(struct MAD_CongestionControl *ptr_struct, const u_int8_t* ptr_buff);
void MAD_CongestionControl_print(const struct MAD_CongestionControl *ptr_struct, FILE* file, int indent_level);
int MAD_CongestionControl_size(void);
#define MAD_CONGESTIONCONTROL_SIZE    (0x100)
void MAD_CongestionControl_dump(const struct MAD_CongestionControl *ptr_struct, FILE* file);
/* MAD_PerformanceManagement */
void MAD_PerformanceManagement_pack(const struct MAD_PerformanceManagement *ptr_struct, u_int8_t* ptr_buff);
void MAD_PerformanceManagement_unpack(struct MAD_PerformanceManagement *ptr_struct, const u_int8_t* ptr_buff);
void MAD_PerformanceManagement_print(const struct MAD_PerformanceManagement *ptr_struct, FILE* file, int indent_level);
int MAD_PerformanceManagement_size(void);
#define MAD_PERFORMANCEMANAGEMENT_SIZE    (0x100)
void MAD_PerformanceManagement_dump(const struct MAD_PerformanceManagement *ptr_struct, FILE* file);
/* MAD_SMP_Direct_Routed */
void MAD_SMP_Direct_Routed_pack(const struct MAD_SMP_Direct_Routed *ptr_struct, u_int8_t* ptr_buff);
void MAD_SMP_Direct_Routed_unpack(struct MAD_SMP_Direct_Routed *ptr_struct, const u_int8_t* ptr_buff);
void MAD_SMP_Direct_Routed_print(const struct MAD_SMP_Direct_Routed *ptr_struct, FILE* file, int indent_level);
int MAD_SMP_Direct_Routed_size(void);
#define MAD_SMP_DIRECT_ROUTED_SIZE    (0x100)
void MAD_SMP_Direct_Routed_dump(const struct MAD_SMP_Direct_Routed *ptr_struct, FILE* file);
/* MAD_SMP_LID_Routed */
void MAD_SMP_LID_Routed_pack(const struct MAD_SMP_LID_Routed *ptr_struct, u_int8_t* ptr_buff);
void MAD_SMP_LID_Routed_unpack(struct MAD_SMP_LID_Routed *ptr_struct, const u_int8_t* ptr_buff);
void MAD_SMP_LID_Routed_print(const struct MAD_SMP_LID_Routed *ptr_struct, FILE* file, int indent_level);
int MAD_SMP_LID_Routed_size(void);
#define MAD_SMP_LID_ROUTED_SIZE    (0x100)
void MAD_SMP_LID_Routed_dump(const struct MAD_SMP_LID_Routed *ptr_struct, FILE* file);
/* MAD_SubnetAdministartion */
void MAD_SubnetAdministartion_pack(const struct MAD_SubnetAdministartion *ptr_struct, u_int8_t* ptr_buff);
void MAD_SubnetAdministartion_unpack(struct MAD_SubnetAdministartion *ptr_struct, const u_int8_t* ptr_buff);
void MAD_SubnetAdministartion_print(const struct MAD_SubnetAdministartion *ptr_struct, FILE* file, int indent_level);
int MAD_SubnetAdministartion_size(void);
#define MAD_SUBNETADMINISTARTION_SIZE    (0x100)
void MAD_SubnetAdministartion_dump(const struct MAD_SubnetAdministartion *ptr_struct, FILE* file);
/* MAD_VendorSpec */
void MAD_VendorSpec_pack(const struct MAD_VendorSpec *ptr_struct, u_int8_t* ptr_buff);
void MAD_VendorSpec_unpack(struct MAD_VendorSpec *ptr_struct, const u_int8_t* ptr_buff);
void MAD_VendorSpec_print(const struct MAD_VendorSpec *ptr_struct, FILE* file, int indent_level);
int MAD_VendorSpec_size(void);
#define MAD_VENDORSPEC_SIZE    (0x100)
void MAD_VendorSpec_dump(const struct MAD_VendorSpec *ptr_struct, FILE* file);
/* NoticeDataDetails */
void NoticeDataDetails_pack(const union NoticeDataDetails *ptr_struct, u_int8_t* ptr_buff);
void NoticeDataDetails_unpack(union NoticeDataDetails *ptr_struct, const u_int8_t* ptr_buff);
void NoticeDataDetails_print(const union NoticeDataDetails *ptr_struct, FILE* file, int indent_level);
int NoticeDataDetails_size(void);
#define NOTICEDATADETAILS_SIZE    (0x38)
void NoticeDataDetails_dump(const union NoticeDataDetails *ptr_struct, FILE* file);
/* PM_PortRcvXmitCntrsSlVlData */
void PM_PortRcvXmitCntrsSlVlData_pack(const union PM_PortRcvXmitCntrsSlVlData *ptr_struct, u_int8_t* ptr_buff);
void PM_PortRcvXmitCntrsSlVlData_unpack(union PM_PortRcvXmitCntrsSlVlData *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortRcvXmitCntrsSlVlData_print(const union PM_PortRcvXmitCntrsSlVlData *ptr_struct, FILE* file, int indent_level);
int PM_PortRcvXmitCntrsSlVlData_size(void);
#define PM_PORTRCVXMITCNTRSSLVLDATA_SIZE    (0x84)
void PM_PortRcvXmitCntrsSlVlData_dump(const union PM_PortRcvXmitCntrsSlVlData *ptr_struct, FILE* file);
/* SMP_GUIDInfo */
void SMP_GUIDInfo_pack(const struct SMP_GUIDInfo *ptr_struct, u_int8_t* ptr_buff);
void SMP_GUIDInfo_unpack(struct SMP_GUIDInfo *ptr_struct, const u_int8_t* ptr_buff);
void SMP_GUIDInfo_print(const struct SMP_GUIDInfo *ptr_struct, FILE* file, int indent_level);
int SMP_GUIDInfo_size(void);
#define SMP_GUIDINFO_SIZE    (0x40)
void SMP_GUIDInfo_dump(const struct SMP_GUIDInfo *ptr_struct, FILE* file);
/* SMP_NextHopTbl */
void SMP_NextHopTbl_pack(const struct SMP_NextHopTbl *ptr_struct, u_int8_t* ptr_buff);
void SMP_NextHopTbl_unpack(struct SMP_NextHopTbl *ptr_struct, const u_int8_t* ptr_buff);
void SMP_NextHopTbl_print(const struct SMP_NextHopTbl *ptr_struct, FILE* file, int indent_level);
int SMP_NextHopTbl_size(void);
#define SMP_NEXTHOPTBL_SIZE    (0x40)
void SMP_NextHopTbl_dump(const struct SMP_NextHopTbl *ptr_struct, FILE* file);
/* VS_DiagnosticData */
void VS_DiagnosticData_pack(const struct VS_DiagnosticData *ptr_struct, u_int8_t* ptr_buff);
void VS_DiagnosticData_unpack(struct VS_DiagnosticData *ptr_struct, const u_int8_t* ptr_buff);
void VS_DiagnosticData_print(const struct VS_DiagnosticData *ptr_struct, FILE* file, int indent_level);
int VS_DiagnosticData_size(void);
#define VS_DIAGNOSTICDATA_SIZE    (0xe0)
void VS_DiagnosticData_dump(const struct VS_DiagnosticData *ptr_struct, FILE* file);
/* VendorSpec_GeneralInfo */
void VendorSpec_GeneralInfo_pack(const struct VendorSpec_GeneralInfo *ptr_struct, u_int8_t* ptr_buff);
void VendorSpec_GeneralInfo_unpack(struct VendorSpec_GeneralInfo *ptr_struct, const u_int8_t* ptr_buff);
void VendorSpec_GeneralInfo_print(const struct VendorSpec_GeneralInfo *ptr_struct, FILE* file, int indent_level);
int VendorSpec_GeneralInfo_size(void);
#define VENDORSPEC_GENERALINFO_SIZE    (0x90)
void VendorSpec_GeneralInfo_dump(const struct VendorSpec_GeneralInfo *ptr_struct, FILE* file);
/* ib_ar_group_table */
void ib_ar_group_table_pack(const struct ib_ar_group_table *ptr_struct, u_int8_t* ptr_buff);
void ib_ar_group_table_unpack(struct ib_ar_group_table *ptr_struct, const u_int8_t* ptr_buff);
void ib_ar_group_table_print(const struct ib_ar_group_table *ptr_struct, FILE* file, int indent_level);
int ib_ar_group_table_size(void);
#define IB_AR_GROUP_TABLE_SIZE    (0x40)
void ib_ar_group_table_dump(const struct ib_ar_group_table *ptr_struct, FILE* file);
/* CONGESTION_CONTOL */
void CONGESTION_CONTOL_pack(const union CONGESTION_CONTOL *ptr_struct, u_int8_t* ptr_buff);
void CONGESTION_CONTOL_unpack(union CONGESTION_CONTOL *ptr_struct, const u_int8_t* ptr_buff);
void CONGESTION_CONTOL_print(const union CONGESTION_CONTOL *ptr_struct, FILE* file, int indent_level);
int CONGESTION_CONTOL_size(void);
#define CONGESTION_CONTOL_SIZE    (0x20000)
void CONGESTION_CONTOL_dump(const union CONGESTION_CONTOL *ptr_struct, FILE* file);
/* Notice */
void Notice_pack(const struct Notice *ptr_struct, u_int8_t* ptr_buff);
void Notice_unpack(struct Notice *ptr_struct, const u_int8_t* ptr_buff);
void Notice_print(const struct Notice *ptr_struct, FILE* file, int indent_level);
int Notice_size(void);
#define NOTICE_SIZE    (0x40)
void Notice_dump(const struct Notice *ptr_struct, FILE* file);
/* PM_PortRcvXmitCntrsSlVl */
void PM_PortRcvXmitCntrsSlVl_pack(const struct PM_PortRcvXmitCntrsSlVl *ptr_struct, u_int8_t* ptr_buff);
void PM_PortRcvXmitCntrsSlVl_unpack(struct PM_PortRcvXmitCntrsSlVl *ptr_struct, const u_int8_t* ptr_buff);
void PM_PortRcvXmitCntrsSlVl_print(const struct PM_PortRcvXmitCntrsSlVl *ptr_struct, FILE* file, int indent_level);
int PM_PortRcvXmitCntrsSlVl_size(void);
#define PM_PORTRCVXMITCNTRSSLVL_SIZE    (0x88)
void PM_PortRcvXmitCntrsSlVl_dump(const struct PM_PortRcvXmitCntrsSlVl *ptr_struct, FILE* file);
/* SMP_MADS */
void SMP_MADS_pack(const union SMP_MADS *ptr_struct, u_int8_t* ptr_buff);
void SMP_MADS_unpack(union SMP_MADS *ptr_struct, const u_int8_t* ptr_buff);
void SMP_MADS_print(const union SMP_MADS *ptr_struct, FILE* file, int indent_level);
int SMP_MADS_size(void);
#define SMP_MADS_SIZE    (0x20000)
void SMP_MADS_dump(const union SMP_MADS *ptr_struct, FILE* file);
/* VENDOR_SPECS */
void VENDOR_SPECS_pack(const union VENDOR_SPECS *ptr_struct, u_int8_t* ptr_buff);
void VENDOR_SPECS_unpack(union VENDOR_SPECS *ptr_struct, const u_int8_t* ptr_buff);
void VENDOR_SPECS_print(const union VENDOR_SPECS *ptr_struct, FILE* file, int indent_level);
int VENDOR_SPECS_size(void);
#define VENDOR_SPECS_SIZE    (0x20000)
void VENDOR_SPECS_dump(const union VENDOR_SPECS *ptr_struct, FILE* file);
/* AGGREGATION_MADS */
void AGGREGATION_MADS_pack(const union AGGREGATION_MADS *ptr_struct, u_int8_t* ptr_buff);
void AGGREGATION_MADS_unpack(union AGGREGATION_MADS *ptr_struct, const u_int8_t* ptr_buff);
void AGGREGATION_MADS_print(const union AGGREGATION_MADS *ptr_struct, FILE* file, int indent_level);
int AGGREGATION_MADS_size(void);
#define AGGREGATION_MADS_SIZE    (0x100)
void AGGREGATION_MADS_dump(const union AGGREGATION_MADS *ptr_struct, FILE* file);
/* PERFORMANCE_MADS */
void PERFORMANCE_MADS_pack(const union PERFORMANCE_MADS *ptr_struct, u_int8_t* ptr_buff);
void PERFORMANCE_MADS_unpack(union PERFORMANCE_MADS *ptr_struct, const u_int8_t* ptr_buff);
void PERFORMANCE_MADS_print(const union PERFORMANCE_MADS *ptr_struct, FILE* file, int indent_level);
int PERFORMANCE_MADS_size(void);
#define PERFORMANCE_MADS_SIZE    (0x20000)
void PERFORMANCE_MADS_dump(const union PERFORMANCE_MADS *ptr_struct, FILE* file);
/* PACKETS_EXTERNAL */
void PACKETS_EXTERNAL_pack(const union PACKETS_EXTERNAL *ptr_struct, u_int8_t* ptr_buff);
void PACKETS_EXTERNAL_unpack(union PACKETS_EXTERNAL *ptr_struct, const u_int8_t* ptr_buff);
void PACKETS_EXTERNAL_print(const union PACKETS_EXTERNAL *ptr_struct, FILE* file, int indent_level);
int PACKETS_EXTERNAL_size(void);
#define PACKETS_EXTERNAL_SIZE    (0x1000000)
void PACKETS_EXTERNAL_dump(const union PACKETS_EXTERNAL *ptr_struct, FILE* file);


#ifdef __cplusplus
}
#endif

#endif // PACKETS_LAYOUTS_H
