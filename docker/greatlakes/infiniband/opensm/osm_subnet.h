/*
 * Copyright (c) 2004-2010 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2002-2015 Mellanox Technologies LTD. All rights reserved.
 * Copyright (c) 1996-2003 Intel Corporation. All rights reserved.
 * Copyright (c) 2008 Xsigo Systems Inc.  All rights reserved.
 * Copyright (c) 2009 System Fabric Works, Inc. All rights reserved.
 * Copyright (c) 2009 HNR Consulting. All rights reserved.
 * Copyright (c) 2009-2015 ZIH, TU Dresden, Federal Republic of Germany. All rights reserved.
 * Copyright (C) 2012-2017 Tokyo Institute of Technology. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
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

/*
 * Abstract:
 *	Declaration of osm_subn_t.
 *	This object represents an IBA subnet.
 *	This object is part of the OpenSM family of objects.
 */

#ifndef _OSM_SUBNET_H_
#define _OSM_SUBNET_H_

#include <iba/ib_types.h>
#include <complib/cl_qmap.h>
#include <complib/cl_fleximap.h>
#include <complib/cl_map.h>
#include <complib/cl_ptr_vector.h>
#include <complib/cl_list.h>
#include <opensm/osm_base.h>
#include <opensm/osm_prefix_route.h>
#include <opensm/osm_db.h>
#include <opensm/osm_log.h>
#include <stdio.h>

#ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS   }
#else				/* !__cplusplus */
#  define BEGIN_C_DECLS
#  define END_C_DECLS
#endif				/* __cplusplus */

BEGIN_C_DECLS
#define OSM_SUBNET_VECTOR_MIN_SIZE			0
#define OSM_SUBNET_VECTOR_GROW_SIZE			1
#define OSM_SUBNET_VECTOR_CAPACITY			256

#define OSM_PARTITION_ENFORCE_BOTH			"both"
#define OSM_PARTITION_ENFORCE_IN			"in"
#define OSM_PARTITION_ENFORCE_OUT			"out"
#define OSM_PARTITION_ENFORCE_OFF			"off"
#define OSM_DEFAULT_STATISTIC_DUMP_TIME			3600000
#define OSM_MAX_STATISTIC_DUMP_TIME			UINT32_MAX/60000
#define OSM_MAX_STATISTIC_DUMP_FILE_SIZE		4095
#define OSM_DEFAULT_STATISTIC_DUMP_FILE_SIZE		20
#define OSM_DEFAULT_AGUID_HOP_LIMIT			1
#define OSM_ACTIVITY_DEFAULT_SUBJECTS			OSM_ACTIVITY_SUBJECTS_NONE

typedef enum _osm_capability_type_enum {
	OSM_CAPABILITY_IGNORED = 0,
	OSM_CAPABILITY_DISABLED,
	OSM_CAPABILITY_ENABLED
} osm_capability_type_enum;

#define OSM_SHARP_CAP_DEFAULT	OSM_CAPABILITY_IGNORED

typedef enum _osm_partition_enforce_type_enum {
	OSM_PARTITION_ENFORCE_TYPE_BOTH,
	OSM_PARTITION_ENFORCE_TYPE_IN,
	OSM_PARTITION_ENFORCE_TYPE_OUT,
	OSM_PARTITION_ENFORCE_TYPE_OFF
} osm_partition_enforce_type_enum;

typedef enum _osm_hm_cond_type_enum {
	OSM_HM_COND_REBOOT = 0,
	OSM_HM_COND_FLAPPING,
	OSM_HM_COND_UNRESPONSIVE,
	OSM_HM_COND_NOISY,
	OSM_HM_COND_SET_ERR,
	OSM_HM_COND_ILLEGAL,
	OSM_HM_COND_MANUAL,
	OSM_HM_COND_MAX
} osm_hm_cond_type_enum;

typedef enum _osm_hm_action_type_enum {
	OSM_HM_ACTION_IGNORE = 0,
	OSM_HM_ACTION_REPORT,
	OSM_HM_ACTION_ISOLATE,
	OSM_HM_ACTION_NO_DISCOVER,
	OSM_HM_ACTION_DISABLE,
	OSM_HM_ACTION_MAX
} osm_hm_action_type_enum;

extern const char *osm_hm_action_str[OSM_HM_ACTION_MAX];

/* XXX: not actual max, max we're currently going to support */
#define OSM_CCT_ENTRY_MAX        128
#define OSM_CCT_ENTRY_MAD_BLOCKS (OSM_CCT_ENTRY_MAX/64)
#define OSM_SUBNET_DEFAULT_PATH_BITS 0xFF

struct osm_opensm;
struct osm_qos_policy;
struct osm_physp;
struct osm_mgrp_box;
struct osm_node;
struct osm_sm;

/****d* OpenSM: OpenSM/osm_routing_engine_type_t
* NAME
*       osm_routing_engine_type_t
*
* DESCRIPTION
*       Enumerates the possible routing engines that
*       could be used to route a subnet.
*
* SYNOPSIS
*/
typedef enum _osm_routing_engine_type {
	OSM_ROUTING_ENGINE_TYPE_NONE = 0,
	OSM_ROUTING_ENGINE_TYPE_MINHOP,
	OSM_ROUTING_ENGINE_TYPE_UPDN,
	OSM_ROUTING_ENGINE_TYPE_DNUP,
	OSM_ROUTING_ENGINE_TYPE_FILE,
	OSM_ROUTING_ENGINE_TYPE_FTREE,
	OSM_ROUTING_ENGINE_TYPE_PQFT,
	OSM_ROUTING_ENGINE_TYPE_LASH,
	OSM_ROUTING_ENGINE_TYPE_DOR,
	OSM_ROUTING_ENGINE_TYPE_TORUS_2QOS,
	OSM_ROUTING_ENGINE_TYPE_SSSP,
	OSM_ROUTING_ENGINE_TYPE_DFSSSP,
	OSM_ROUTING_ENGINE_TYPE_CHAIN,
	OSM_ROUTING_ENGINE_TYPE_UNKNOWN
} osm_routing_engine_type_t;
/***********/

/****s* OpenSM: OpenSM/osm_routing_engine
* NAME
*	struct osm_routing_engine
*
* DESCRIPTION
*	OpenSM routing engine module definition.
* NOTES
*	routing engine structure - multicast callbacks may be
*	added later.
*/
struct osm_routing_engine {
	osm_routing_engine_type_t type;
	const char *name;
	void *context;
	int (*build_lid_matrices) (void *context);
	int (*ucast_build_fwd_tables) (void *context);
	void (*ucast_dump_tables) (void *context);
	void (*update_sl2vl)(void *context, IN struct osm_physp *port,
			     IN uint8_t in_port_num, IN uint8_t out_port_num,
			     IN OUT ib_slvl_table_t *t);
	void (*update_vlarb)(void *context, IN struct osm_physp *port,
			     IN uint8_t port_num,
			     IN OUT ib_vl_arb_table_t *block,
			     unsigned block_length, unsigned block_num);
	uint8_t (*path_sl)(void *context, IN uint8_t path_sl_hint,
			   IN const ib_net16_t slid, IN const ib_net16_t dlid);
	ib_api_status_t (*mcast_build_stree)(void *context,
					     IN OUT struct osm_mgrp_box *mgb);
	int (*ITR_init)(void *context);
	int (*ITR_get_bs)(void *context, IN ib_net64_t sw_guid,
				OUT ib_net64_t *bs_guid);
	void (*destroy) (void *context);
	struct osm_routing_engine *next;
};
/*
* FIELDS
*	name
*		The routing engine name (will be used in logs).
*
*	context
*		The routing engine context. Will be passed as parameter
*		to the callback functions.
*
*	build_lid_matrices
*		The callback for lid matrices generation.
*
*	ucast_build_fwd_tables
*		The callback for unicast forwarding table generation.
*
*	ucast_dump_tables
*		The callback for dumping unicast routing tables.
*
*	update_sl2vl(void *context, IN osm_physp_t *port,
*		     IN uint8_t in_port_num, IN uint8_t out_port_num,
*		     OUT ib_slvl_table_t *t)
*		The callback to allow routing engine input for SL2VL maps.
*		*port is the physical port for which the SL2VL map is to be
*		updated. For switches, in_port_num/out_port_num identify
*		which part of the SL2VL map to update.  For router/HCA ports,
*		in_port_num/out_port_num should be ignored.
*
*	update_vlarb(void *context, IN osm_physp_t *port,
*		     IN uint8_t port_num,
*		     IN OUT ib_vl_arb_table_t *block,
*		     unsigned block_length, unsigned block_num)
*		The callback to allow routing engine input for VLArbitration.
*		*port is the physical port for which the VLArb table is to be
*		updated.
*
*	path_sl
*		The callback for computing path SL.
*
*	mcast_build_stree
*		The callback for building the spanning tree for multicast
*		forwarding, called per MLID.
*
*	ITR_init
*		Perform any action required in order to support ITR (inter
*		Topology Routing).
*
*	ITR_get_BS_lid
*		Get a lid and return the lid of the Border Switch to route
*		to in ITR in order to get to this lid.
*
*	destroy
*		The destroy method, may be used for routing engine
*		internals cleanup.
*
*	next
*		Pointer to next routing engine in the list.
*/
/****h* OpenSM/Subnet
* NAME
*	Subnet
*
* DESCRIPTION
*	The Subnet object encapsulates the information needed by the
*	OpenSM to manage a subnet.  The OpenSM allocates one Subnet object
*	per IBA subnet.
*
*	The Subnet object is not thread safe, thus callers must provide
*	serialization.
*
*	This object is essentially a container for the various components
*	of a subnet.  Callers may directly access the member variables.
*
* AUTHOR
*	Steve King, Intel
*
*********/

/****s* OpenSM: Subnet/osm_qos_options_t
* NAME
*	osm_qos_options_t
*
* DESCRIPTION
*	Subnet QoS options structure.  This structure contains the various
*	QoS specific configuration parameters for the subnet.
*
* SYNOPSIS
*/
typedef struct osm_qos_options {
	unsigned max_vls;
	int high_limit;
	char *vlarb_high;
	char *vlarb_low;
	char *sl2vl;
} osm_qos_options_t;
/*
* FIELDS
*
*	max_vls
*		The number of maximum VLs on the Subnet (0 == use default)
*
*	high_limit
*		The limit of High Priority component of VL Arbitration
*		table (IBA 7.6.9) (-1 == use default)
*
*	vlarb_high
*		High priority VL Arbitration table template. (NULL == use default)
*
*	vlarb_low
*		Low priority VL Arbitration table template. (NULL == use default)
*
*	sl2vl
*		SL2VL Mapping table (IBA 7.6.6) template. (NULL == use default)
*
*********/

/****s* OpenSM: Subnet/osm_cct_entry_t
* NAME
*	osm_cct_entry_t
*
* DESCRIPTION
*	Subnet Congestion Control Table entry.  See A10.2.2.1.1 for format details.
*
* SYNOPSIS
*/
typedef struct osm_cct_entry {
	uint8_t shift; //Alex: shift 2 bits
	uint16_t multiplier; //Alex multiplier 14 bits
} osm_cct_entry_t;
/*
* FIELDS
*
*	shift
*		shift field in CCT entry.  See A10.2.2.1.1.
*
*	multiplier
*		multiplier field in CCT entry.  See A10.2.2.1.1.
*
*********/

/****s* OpenSM: Subnet/osm_cacongestion_entry_t
* NAME
*	osm_cacongestion_entry_t
*
* DESCRIPTION
*	Subnet CA Congestion entry.  See A10.4.3.8.4 for format details.
*
* SYNOPSIS
*/
typedef struct osm_cacongestion_entry {
	ib_net16_t ccti_timer; //Alex: ccti_timer and ccti_increase should be replaced
	uint8_t ccti_increase;
	uint8_t trigger_threshold;
	uint8_t ccti_min;
} osm_cacongestion_entry_t;
/*
* FIELDS
*
*	ccti_timer
*		CCTI Timer
*
*	ccti_increase
*		CCTI Increase
*
*	trigger_threshold
*		CCTI trigger for log message
*
*	ccti_min
*		CCTI Minimum
*
*********/

/****s* OpenSM: Subnet/osm_cct_t
* NAME
*	osm_cct_t
*
* DESCRIPTION
*	Subnet CongestionControlTable.  See A10.4.3.9 for format details.
*
* SYNOPSIS
*/
typedef struct osm_cct {
	osm_cct_entry_t entries[OSM_CCT_ENTRY_MAX];
	unsigned int entries_len;
	char *input_str;
} osm_cct_t;
/*
* FIELDS
*
*	entries
*		Entries in CCT
*
*	entries_len
*		Length of entries
*
*	input_str
*		Original str input
*
*********/

/****d* OpenSM: OpenSM/osm_port_reset_type_enum
* NAME
*	osm_port_reset_type_enum
*
* DESCRIPTION
*	Types of port reset action.
*
* SYNOPSIS
*/
typedef enum _osm_port_reset_type_enum {
	OSM_PORT_RESET_TYPE_NONE = 0,
	OSM_PORT_RESET_TYPE_LOGICAL,
	OSM_PORT_RESET_TYPE_PHYSICAL,
	OSM_PORT_RESET_TYPE_MAX

} osm_port_reset_type_enum;
/***********/

/****s* OpenSM: Subnet/osm_subn_opt_t
* NAME
*	osm_subn_opt_t
*
* DESCRIPTION
*	Subnet options structure.  This structure contains the various
*	site specific configuration parameters for the subnet.
*
* SYNOPSIS
*/
typedef struct osm_subn_opt {
	char *config_file;
	ib_net64_t guid;
	ib_net64_t m_key;
	ib_net64_t sm_key;
	ib_net64_t sa_key;
	ib_net64_t subnet_prefix;
	ib_net16_t m_key_lease_period;
	uint8_t m_key_protect_bits;
	boolean_t m_key_lookup;
	uint32_t sweep_interval;
	uint32_t max_wire_smps;
	uint32_t max_wire_smps2;
	uint32_t max_smps_timeout;
	uint32_t transaction_timeout;
	uint32_t transaction_retries;
	uint32_t long_transaction_timeout;
	uint32_t max_sa_reports_queued;
	uint32_t max_sa_reports_on_wire;
	uint8_t sm_priority;
	uint8_t master_sm_priority;
	uint8_t lmc;
	boolean_t lmc_esp0;
	uint8_t max_op_vls;
	uint8_t max_neighbor_mtu;
	uint8_t force_link_speed;
	uint8_t force_link_speed_ext;
	uint8_t force_link_width;
	uint8_t fdr10;
	boolean_t support_mepi_speeds;
	uint8_t mepi_enabled_speeds;
	boolean_t reassign_lids;
	boolean_t ignore_other_sm;
	boolean_t single_thread;
	boolean_t disable_multicast;
	boolean_t force_log_flush;
	uint8_t subnet_timeout;
	uint8_t packet_life_time;
	uint8_t vl_stall_count;
	uint8_t leaf_vl_stall_count;
	uint8_t head_of_queue_lifetime;
	uint8_t leaf_head_of_queue_lifetime;
	uint8_t local_phy_errors_threshold;
	uint8_t overrun_errors_threshold;
	boolean_t use_mfttop;
	uint32_t sminfo_polling_timeout;
	uint32_t polling_retry_number;
	uint32_t max_msg_fifo_timeout;
	boolean_t force_heavy_sweep;
	uint8_t log_flags;
	uint8_t syslog_log_flags;
	char *dump_files_dir;
	char *log_file;
	uint32_t log_max_size;
	char *partition_config_file;
	boolean_t no_partition_enforcement;
	char *part_enforce;
	osm_partition_enforce_type_enum part_enforce_enum;
	boolean_t allow_both_pkeys;
	boolean_t keep_pkey_indexes;
	uint8_t sm_assigned_guid;
	boolean_t qos;
	char *qos_policy_file;
	char *enhanced_qos_policy_file;
	boolean_t suppress_sl2vl_mad_status_errors;
	uint8_t override_create_mcg_sl;
	boolean_t accum_log_file;
	char *console;
	uint16_t console_port;
	char *port_prof_ignore_file;
	char *hop_weights_file;
	char *port_search_ordering_file;
	boolean_t port_profile_switch_nodes;
	boolean_t sweep_on_trap;
	char *routing_engine_names;
	boolean_t avoid_throttled_links;
	boolean_t use_ucast_cache;
	boolean_t connect_roots;
	boolean_t calc_missing_routes;
	char *lid_matrix_dump_file;
	char *lfts_file;
	char *root_guid_file;
	char *pgrp_policy_file;
	char *topo_policy_file;
	char *rch_policy_file;
	char *ftree_ca_order_dump_file;
	char *held_back_sw_file;
	char *cn_guid_file;
	char *io_guid_file;
	boolean_t port_shifting;
	uint32_t scatter_ports;
	boolean_t updn_lid_tracking_mode;
	boolean_t updn_lid_tracking_converge_routes;
	uint16_t max_reverse_hops;
	uint16_t routing_threads_num;
	uint16_t max_threads_per_core;
	char *ids_guid_file;
	char *guid_routing_order_file;
	char *pqft_structure;
	boolean_t guid_routing_order_no_scatter;
	boolean_t use_scatter_for_switch_lid;
	boolean_t offsweep_balancing_enabled;
	uint32_t  offsweep_balancing_window;
	char *sa_db_file;
	boolean_t sa_db_dump;
	boolean_t sm_db_dump;
	char *torus_conf_file;
	char *pid_file;
	boolean_t do_mesh_analysis;
	boolean_t exit_on_fatal;
	boolean_t honor_guid2lid_file;
	boolean_t const_multicast;
	boolean_t daemon;
	boolean_t sm_inactive;
	boolean_t babbling_port_policy;
	uint8_t reports;
	boolean_t use_optimized_slvl;
	boolean_t fsync_high_avail_files;
	uint8_t default_mcg_mtu;
	uint8_t default_mcg_rate;
	osm_qos_options_t qos_options, qos_options_prev;
	osm_qos_options_t qos_ca_options, qos_ca_options_prev;
	osm_qos_options_t qos_sw0_options, qos_sw0_options_prev;
	osm_qos_options_t qos_swe_options, qos_swe_options_prev;
	osm_qos_options_t qos_rtr_options, qos_rtr_options_prev;
	boolean_t congestion_control;
	ib_net64_t cc_key;
	uint32_t cc_max_outstanding_mads;
	ib_net32_t cc_sw_cong_setting_control_map;
	uint8_t cc_sw_cong_setting_victim_mask[IB_CC_PORT_MASK_DATA_SIZE];
	uint8_t cc_sw_cong_setting_credit_mask[IB_CC_PORT_MASK_DATA_SIZE];
	uint8_t cc_sw_cong_setting_threshold;
	uint8_t cc_sw_cong_setting_packet_size;
	uint8_t cc_sw_cong_setting_credit_starvation_threshold;
	osm_cct_entry_t cc_sw_cong_setting_credit_starvation_return_delay;
	ib_net16_t cc_sw_cong_setting_marking_rate;
	ib_net16_t cc_ca_cong_setting_port_control;
	ib_net16_t cc_ca_cong_setting_control_map;
	osm_cacongestion_entry_t cc_ca_cong_entries[IB_CA_CONG_ENTRY_DATA_SIZE];
	osm_cct_t cc_cct;
	boolean_t enable_quirks;
	boolean_t no_clients_rereg;
#ifdef ENABLE_OSM_PERF_MGR
	boolean_t perfmgr;
	boolean_t perfmgr_redir;
	uint16_t perfmgr_sweep_time_s;
	uint32_t perfmgr_max_outstanding_queries;
	boolean_t perfmgr_ignore_cas;
	char *event_db_dump_file;
	int perfmgr_rm_nodes;
	boolean_t perfmgr_log_errors;
	boolean_t perfmgr_query_cpi;
	boolean_t perfmgr_xmit_wait_log;
	uint32_t perfmgr_xmit_wait_threshold;
#endif				/* ENABLE_OSM_PERF_MGR */
	char *event_plugin_name;
	char *event_plugin_options;
	char *node_name_map_name;
	char *prefix_routes_file;
	char *log_prefix;
	boolean_t consolidate_ipv6_snm_req;
	uint32_t  consolidate_ipv4_mask;
	struct osm_subn_opt *file_opts; /* used for update */
	uint8_t lash_start_vl;			/* starting vl to use in lash */
	uint8_t sm_sl;			/* which SL to use for SM/SA communication */
	uint32_t max_seq_redisc;	/* Maximal sequential failed discovery */
	boolean_t rereg_on_guid_migr;
	boolean_t aguid_inout_notice;
	char *sm_assign_guid_func;
	ib_net64_t mc_primary_root_guid;
	ib_net64_t mc_secondary_root_guid;
	char *mc_roots_file;
	boolean_t drop_subscr_on_report_fail;
	boolean_t drop_event_subscriptions;
	boolean_t ipoib_mcgroup_creation_validation;
	boolean_t mcgroup_join_validation;
	boolean_t use_original_extended_sa_rates_only;
	char *per_module_logging_file;
	char *switch_name;
	uint32_t max_msg_fifo_len;
	uint32_t max_alt_dr_path_retries;
	uint32_t ca_port_soft_limit;
	uint32_t ca_port_num_limit;
	boolean_t sa_pr_full_world_queries_allowed;
	boolean_t enable_crashd;
	boolean_t hm_unhealthy_ports_checks;
	char *hm_ports_health_policy_file;
	char *hm_ca_reboot_action_s;
	char *hm_ca_unresponsive_action_s;
	char *hm_ca_noisy_action_s;
	char *hm_ca_seterr_action_s;
	char *hm_ca_flapping_action_s;
	char *hm_ca_illegal_action_s;
	char *hm_ca_manual_action_s;
	char *hm_sw_reboot_action_s;
	char *hm_sw_unresponsive_action_s;
	char *hm_sw_noisy_action_s;
	char *hm_sw_seterr_action_s;
	char *hm_sw_flapping_action_s;
	char *hm_sw_illegal_action_s;
	char *hm_sw_manual_action_s;
	osm_hm_action_type_enum hm_ca_reboot_action;
	osm_hm_action_type_enum hm_ca_unresponsive_action;
	osm_hm_action_type_enum hm_ca_noisy_action;
	osm_hm_action_type_enum hm_ca_seterr_action;
	osm_hm_action_type_enum hm_ca_flapping_action;
	osm_hm_action_type_enum hm_ca_illegal_action;
	osm_hm_action_type_enum hm_ca_manual_action;
	osm_hm_action_type_enum hm_sw_reboot_action;
	osm_hm_action_type_enum hm_sw_unresponsive_action;
	osm_hm_action_type_enum hm_sw_noisy_action;
	osm_hm_action_type_enum hm_sw_seterr_action;
	osm_hm_action_type_enum hm_sw_flapping_action;
	osm_hm_action_type_enum hm_sw_illegal_action;
	osm_hm_action_type_enum hm_sw_manual_action;
	uint32_t hm_num_reboots;
	uint32_t hm_reboots_period_secs;
	uint32_t hm_num_set_err_sweeps;
	uint32_t hm_num_set_err_sweeps_window;
	uint32_t hm_num_no_resp_sweeps;
	uint32_t hm_num_no_resp_sweeps_window;
	uint32_t hm_num_traps;
	uint32_t hm_num_traps_period_secs;
	uint32_t hm_num_flapping_sweeps;
	uint32_t hm_num_flapping_sweeps_window;
	uint32_t hm_num_illegal;
	int32_t force_heavy_sweep_window;
	boolean_t validate_smps;
	uint8_t max_topologies_per_sw;
	boolean_t auto_join_hca_wo_topo;
	boolean_t enable_inc_mc_routing;
	boolean_t allow_sm_port_reset;
	boolean_t support_mlnx_enhanced_link;
	boolean_t mlnx_enhanced_link_enable;
	char *port_speed_change_action_s;
	char *port_ext_speed_change_action_s;
	char *port_mepi_speed_change_action_s;
	char *port_mtu_change_action_s;
	char *port_vl_change_action_s;
	char *port_ame_bit_change_action_s;
	osm_port_reset_type_enum port_speed_change_action;
	osm_port_reset_type_enum port_ext_speed_change_action;
	osm_port_reset_type_enum port_mepi_speed_change_action;
	osm_port_reset_type_enum port_mtu_change_action;
	osm_port_reset_type_enum port_vl_change_action;
	osm_port_reset_type_enum port_ame_bit_change_action;
	boolean_t mepi_cache_enabled;
	uint32_t virt_enabled;
	uint16_t virt_max_ports_in_process;
	uint8_t virt_default_hop_limit;
	boolean_t improved_lmc_path_distribution;
	boolean_t sweep_every_hup_signal;
	uint32_t osm_stats_interval;
	unsigned long osm_stats_dump_limit;
	boolean_t quasi_ftree_indexing;
	uint8_t sharp_enabled;
	uint8_t rtr_aguid_enable;
	uint32_t rtr_pr_flow_label;
	uint8_t rtr_pr_tclass;
	uint8_t rtr_pr_sl;
	uint8_t rtr_pr_mtu;
	uint8_t rtr_pr_rate;
	uint8_t aguid_default_hop_limit;
	char *router_policy_file;
	boolean_t router_policy_enabled;
	boolean_t load_inform_info_from_sadb;
	char *verbose_bypass_policy_file;
	char *sa_db_dump_file;
	char *subnet_lst_file;
	char *virt_dump_file;
	boolean_t dor_hyper_cube_mode;
	osm_sm_standalone_t stand_alone;
	char *additional_gi_supporting_devices;
	char *additional_mepi_force_devices;
	boolean_t disable_default_gi_support;
	char *activity_report_subjects;
	struct osm_subn_opt *opts_def; /* Keep defaults */
} osm_subn_opt_t;
/*
* FIELDS
*
*	config_file
*		The name of the config file.
*
*	guid
*		The port guid that the SM is binding to.
*
*	m_key
*		M_Key value sent to all ports qualifying all Set(PortInfo).
*
*	sm_key
*		SM_Key value of the SM used for SM authentication.
*
*	sa_key
*		SM_Key value to qualify rcv SA queries as "trusted".
*
*	subnet_prefix
*		Subnet prefix used on this subnet.
*
*	m_key_lease_period
*		The lease period used for the M_Key on this subnet.
*
*	sweep_interval
*		The number of seconds between subnet sweeps.  A value of 0
*		disables sweeping.
*
*	max_wire_smps
*		The maximum number of SMPs sent in parallel.  Default is 4.
*
*	max_wire_smps2
*		The maximum number of timeout SMPs allowed to be outstanding.
*		Default is same as max_wire_smps which disables the timeout
*		mechanism.
*
*	max_smps_timeout
*		The wait time in usec for timeout based SMPs.  Default is
*		timeout * retries.
*
*	transaction_timeout
*		The maximum time in milliseconds allowed for a transaction
*		to complete.  Default is 200.
*
*	transaction_retries
*		The number of retries for a transaction. Default is 3.
*
*	long_transaction_timeout
*		The maximum time in milliseconds allowed for "long" transaction
*		to complete.  Default is 500.
*
*	sm_priority
*		The priority of this SM as specified by the user.  This
*		value is made available in the SMInfo attribute.
*
*	master_sm_priority
*		The priority of this SM when it becomes MASTER.
*
*	lmc
*		The LMC value used on this subnet.
*
*	lmc_esp0
*		Whether LMC value used on subnet should be used for
*		enhanced switch port 0 or not.  If TRUE, it is used.
*		Otherwise (the default), LMC is set to 0 for ESP0.
*
*	max_op_vls
*		Limit the maximal operational VLs. default is 1.
*
*	max_neighbor_mtu
*		Limit the maximal neighbor MTU. (0 - no limit).
*
*	reassign_lids
*		If TRUE cause all lids to be re-assigend.
*		Otherwise (the default),
*		OpenSM always tries to preserve as LIDs as much as possible.
*
*	ignore_other_sm_option
*		This flag is TRUE if other SMs on the subnet should be ignored.
*
*	disable_multicast
*		This flag is TRUE if OpenSM should disable multicast support.
*
*	max_msg_fifo_timeout
*		The maximal time a message can stay in the incoming message
*		queue. If there is more than one message in the queue and the
*		last message stayed in the queue more than this value the SA
*		request will be immediately returned with a BUSY status.
*
*	subnet_timeout
*		The subnet_timeout that will be set for all the ports in the
*		design SubnSet(PortInfo.vl_stall_life))
*
*	vl_stall_count
*		The number of sequential packets dropped that cause the port
*		to enter the VLStalled state.
*
*	leaf_vl_stall_count
*		The number of sequential packets dropped that cause the port
*		to enter the VLStalled state. This is for switch ports driving
*		a CA or router port.
*
*	head_of_queue_lifetime
*		The maximal time a packet can live at the head of a VL queue
*		on any port not driving a CA or router port.
*
*	leaf_head_of_queue_lifetime
*		The maximal time a packet can live at the head of a VL queue
*		on switch ports driving a CA or router.
*
*	local_phy_errors_threshold
*		Threshold of local phy errors for sending Trap 129
*
*	overrun_errors_threshold
*		Threshold of credits overrun errors for sending Trap 129
*
*	sminfo_polling_timeout
*		Specifies the polling timeout (in milliseconds) - the timeout
*		between one poll to another.
*
*	packet_life_time
*		The maximal time a packet can stay in a switch.
*		The value is send to all switches as
*		SubnSet(SwitchInfo.life_state)
*
*	dump_files_dir
*		The directory to be used for opensm-subnet.lst, opensm.fdbs,
*		opensm.mcfdbs, and default log file (the latter for Windows,
*		not Linux).
*
*	log_file
*		Name of the log file (or NULL) for stdout.
*
*	log_max_size
*		This option defines maximal log file size in MB. When
*		specified the log file will be truncated upon reaching
*		this limit.
*
*	qos
*		Boolean that specifies whether the OpenSM QoS functionality
*		should be off or on.
*
*	qos_policy_file
*		Name of the QoS policy file.
*
*	enhanced_qos_policy_file
*		Name of the enhanced QoS policy file.
*
*	override_create_mcg_sl
*		Override multicast SL provided in join/create requests
*
*	accum_log_file
*		If TRUE (default) - the log file will be accumulated.
*		If FALSE - the log file will be erased before starting
*		current opensm run.
*
*	port_prof_ignore_file
*		Name of file with port guids to be ignored by port profiling.
*
*	port_profile_switch_nodes
*		If TRUE will count the number of switch nodes routed through
*		the link. If FALSE - only CA/RT nodes are counted.
*
*	sweep_on_trap
*		Received traps will initiate a new sweep.
*
*	routing_engine_names
*		Name of routing engine(s) to use.
*
*	avoid_throttled_links
*		This option will enforce that throttled switch-to-switch links
*		in the fabric are treated as 'broken' by the routing engines
*		(if they support it), and hence no path is assigned to these
*		underperforming links and a warning is logged instead.
*
*	connect_roots
*		The option which will enforce root to root connectivity with
*		up/down and fat-tree routing engines (even if this violates
*		"pure" deadlock free up/down or fat-tree algorithm)
*
*	use_ucast_cache
*		When TRUE enables unicast routing cache.
*
*	lid_matrix_dump_file
*		Name of the lid matrix dump file from where switch
*		lid matrices (min hops tables) will be loaded
*
*	lfts_file
*		Name of the unicast LFTs routing file from where switch
*		forwarding tables will be loaded
*
*	root_guid_file
*		Name of the file that contains list of root guids that
*		will be used by fat-tree or up/dn routing (provided by User)
*
*	pgrp_policy_file
*		Name of the file that contains the port group policy data
*		will be used by port groups parser
*
*	topo_policy_file
*		Name of the file that contains the topology policy data
*		will be used by topology parser
*
*	rch_policy_file
*		Name of the file that contains the routing chain policy data
*		will be used by routing chain parser
*
*	routing_threads_num
*		Number of threads to be used for minhop/updn calculation
*
*	held_back_sw_file
*		Name of the file that contains list of node guids that
*		will be held-back (ignored) during discovery
*
*	cn_guid_file
*		Name of the file that contains list of compute node guids that
*		will be used by fat-tree routing (provided by User)
*
*	io_guid_file
*		Name of the file that contains list of I/O node guids that
*		will be used by fat-tree routing (provided by User)
*
*	port_shifting
*		This option will turn on port_shifting in routing.
*
*	ids_guid_file
*		Name of the file that contains list of ids which should be
*		used by Up/Down algorithm instead of node GUIDs
*
*	guid_routing_order_file
*		Name of the file that contains list of guids for routing order
*		that will be used by minhop and up/dn routing (provided by User).
*
*	pgft_structure
*		The definition of the expected Fat Tree topology:
*		PGFT(h; M1, M2,...Mh; W1,W2,...Wh; P1,P2,...Ph) or
*		QFT(h; M1, M2,...Mh; W1,W2,...Wh; P1,P2,...Ph)
*		Where:
*		h = height of tree (layers of switches)
*		Mi = Number of children for switches at level i (i=1 is leafs)
*		Wi = Number of different switch parents for switches at level i-1
*		Pi = For PGFT - number of parallel down links for switches at level i
*		     For QFT - number of additional children for switches at level i
*
*	offsweep_balancing_enabled
*		Rebalance the port load during heavy sweep routing
*
*	offsweep_balancing_window
*		Perform routing rebalancing offsweep_balancing_window
*		seconds after last heavy sweep if needed
*
*	sa_db_file
*		Name of the SA database file.
*
*	sa_db_dump
*		When TRUE causes OpenSM to dump SA DB at the end of every
*		light sweep regardless the current verbosity level.
*
*	sm_db_dump
*		When TRUE causes OpenSM to dump SM DB at the end of every
*		heavy sweep.
*
*	torus_conf_file
*		Name of the file with extra configuration info for torus-2QoS
*		routing engine.
*
*	exit_on_fatal
*		If TRUE (default) - SM will exit on fatal subnet initialization
*		issues.
*		If FALSE - SM will not exit.
*		Fatal initialization issues:
*		a. SM recognizes 2 different nodes with the same guid, or
*		   12x link with lane reversal badly configured.
*
*	honor_guid2lid_file
*		Always honor the guid2lid file if it exists and is valid. This
*		means that the file will be honored when SM is coming out of
*		STANDBY. By default this is FALSE.
*
*	daemon
*		OpenSM will run in daemon mode.
*
*	sm_inactive
*		OpenSM will start with SM in not active state.
*
*	babbling_port_policy
*		OpenSM will enforce its "babbling" port policy.
*
*	ipoib_mcgroup_creation_validation
*		OpenSM will validate IPoIB non-broadcast group parameters
*		against IPoIB broadcast group.
*
*	mcgroup_join_validation
*		OpenSM will validate multicast join parameters against
*		multicast group parameters when MC group already exists.
*
*	use_original_extended_sa_rates_only
*		Use only original extended SA rates (up through 300 Gbps
*		for 12x EDR). Option is needed for subnets with
*		old kernels/drivers that don't understand the
*		new SA rates for 2x link width and/or HDR link speed (19-22).
*
*	use_optimized_slvl
*		Use optimized SLtoVLMappingTable programming if
*		device indicates it supports this.
*
*	fsync_high_avail_files
*		Synchronize high availability in memory files
*		with storage.
*
*	perfmgr
*		Enable or disable the performance manager
*
*	perfmgr_redir
*		Enable or disable the saving of redirection by PerfMgr
*
*	perfmgr_sweep_time_s
*		Define the period (in seconds) of PerfMgr sweeps
*
*       event_db_dump_file
*               File to dump the event database to
*
*       event_plugin_name
*               Specify the name(s) of the event plugin(s)
*
*       event_plugin_options
*               Options string that would be passed to the plugin(s)
*
*	qos_options
*		Default set of QoS options
*
*	qos_ca_options
*		QoS options for CA ports
*
*	qos_sw0_options
*		QoS options for switches' port 0
*
*	qos_swe_options
*		QoS options for switches' external ports
*
*	qos_rtr_options
*		QoS options for router ports
*
*	congestion_control
*		Boolean that specifies whether OpenSM congestion control configuration
*		should be off or no.
*
*	cc_key
*		CCkey to use when configuring congestion control.
*
*	cc_max_outstanding_mads
*		Max number of outstanding CC mads that can be on the wire.
*
*	cc_sw_cong_setting_control_map
*		Congestion Control Switch Congestion Setting Control Map
*		configuration setting.
*
*	cc_sw_cong_setting_victim_mask
*		Congestion Control Switch Congestion Setting Victim Mask
*		configuration setting.
*
*	cc_sw_cong_setting_credit_mask
*		Congestion Control Switch Congestion Setting Credit Mask
*		configuration setting.
*
*	cc_sw_cong_setting_threshold
*		Congestion Control Switch Congestion Setting Threshold
*		configuration setting.
*
*	cc_sw_cong_setting_packet_size
*		Congestion Control Switch Congestion Setting Packet Size
*		configuration setting.
*
*	cc_sw_cong_setting_credit_starvation_threshold
*		Congestion Control Switch Congestion Setting Credit Staraction Threshold
*		configuration setting.
*
*	cc_sw_cong_setting_credit_starvation_return_delay
*		Congestion Control Switch Congestion Setting Credit Starvation Return Delay
*		configuration setting.
*
*	cc_sw_cong_setting_marking_rate
*		Congestion Control Switch Congestion Setting Marking Rate
*		configuration setting.
*
*	cc_ca_cong_setting_port_control
*		Congestion Control CA Congestion Setting Port Control
*
*	cc_ca_cong_setting_control_map
*		Congestion Control CA Congestion Setting Control Map

*	cc_ca_cong_entries
*		Congestion Control CA Congestion Setting Entries
*
*	cc_cct
*		Congestion Control Table array of entries
*
*	enable_quirks
*		Enable high risk new features and not fully qualified
*		hardware specific work arounds
*
*	no_clients_rereg
*		When TRUE disables clients reregistration request
*
*	scatter_ports
*		When not zero, randomize best possible ports chosen
*		for a route. The value is used as a random key seed.
*
*	updn_lid_tracking_mode
*		Enable LID tracking mode for Up/Down.
*
*	updn_lid_tracking_converge_routes
*		With LID tracking mode:
*		when TRUE, consolidate routes to the same DLID
*		in the fabric as early as possible.
*		Otherwise, consolidate the routes as close
*		to destination as possible.
*
*	max_seq_redisc
*		When not zero, defines the maximum number of sequential
*		failed discoveries that may be run, before SM will perform
*		the whole heavy sweep cycle.
*
* 	mc_roots_file
*		Name of the file that contains mapping from MGID to switches
*		that OpenSM will try to use as roots for their multicast trees
*
*	per_module_logging_file
*		File name of per module logging configuration.
*
* 	max_alt_dr_path_retries
* 		Maximum number of attempts to find alternative direct route
* 		towards unresponsive ports.
*
* 	sa_pr_full_world_queries_allowed
* 		Enables SA to generate full World Path Records
* 		(for each pair of ports).
*
*	enable_crashd
*		When TRUE enables OpenSM crash daemon.
*
*	hm_unhealthy_ports_checks
*		When TRUE enable Unhealthy Ports feature.
*
*	hm_ports_health_policy_file
*		Unhealthy policy file.
*
*	hm_ca_reboot_action
*		Action to be taken for CAs/RTRs with Reboot condition.
*
*	hm_ca_unresponsive_action
*		Action to be taken for CAs/RTRs with Unresponsive condition.
*
*	hm_ca_noisy_action
*		Action to be taken for CAs/RTRs with Noisy condition.
*
*	hm_ca_seterr_action
*		Action to be taken for CAs/RTRs with SetErr condition.
*
*	hm_ca_flapping_action
*		Action to be taken for CAs/RTRs with Flapping link condition.
*
*	hm_ca_illegal_action
*		Action to be taken for CAs/RTRs with Illegal condition.
*
*	hm_ca_manual_action
*		Action to be taken for CAs/RTRs with manual condition.
*
*	hm_sw_reboot_action
*		Action to be taken for switch with Reboot condition.
*
*	hm_sw_unresponsive_action
*		Action to be taken for switch with Unresponsive condition.
*
*	hm_sw_noisy_action
*		Action to be taken for switch with Noisy condition.
*
*	hm_sw_seterr_action
*		Action to be taken for switch with SetErr condition.
*
*	hm_sw_flapping_action
*		Action to be taken for switch with Flapping link condition.
*
*	hm_sw_illegal_action
*		Action to be taken for switch with Illegal condition.
*
*	hm_sw_manual_action
*		Action to be taken for switch with manual condition.
*
*	hm_num_reboots
*		Number of reboots in a period to declare a node as unhealthy.
*
*	hm_reboots_period_secs
*		The period for counting number of reboots.
*
*	hm_num_set_err_sweeps
*		The number of sweeps that had that node report back an error
*		for a Set MAD.
*
*	hm_num_set_err_sweeps_window
*		The number of sweeps of which any node exceeding
*		hm_num_set_err_sweeps is declared unhealthy.
*
*	hm_num_no_resp_sweeps
*		The number of sweeps that had that node unresponsive.
*
*	hm_num_no_resp_sweeps_window
*		The number of sweeps of which any node exceeding
*		hm_num_no_resp_sweeps is declared unhealthy.
*
*	hm_num_traps
*		The number of received traps in a period to declare a node
*		as unhealthy.
*
*	hm_num_traps_period_secs
*		The period for counting received traps number.
*
*	hm_num_flapping_sweeps
*		The number of sweeps to declare a port as flapping.
*
*	hm_num_flapping_sweeps_window
*		The number of sweeps of which any port exceeding
*		hm_num_flapping_sweeps is declared unhealthy.
*
*	hm_num_illegal
*		Number of illegal SMPs a node may return to be declared
*		unhealthy.
*
*	force_heavy_sweep_window
*		Force heavy sweep after number of light sweep performed.
*
*	validate_smps
*		Enable SMPs validations
*
*	max_topologies_per_sw
*		Number of max topologies sw is allowed to be part of
*
*	auto_join_hca_wo_topo
*		Automatically join hca without topology to its sw topology
*
*	enable_inc_mc_routing
*		Enable incremental multicast routing
*
*	allow_sm_port_reset
*		Allow reseting SM port after changing port's properties
*
*	mepi_cache_enabled
*		Avoid sending MEPI to every port every heavy sweep.
*
*	virt_enabled
*		Enable virtualization support
*
*	virt_max_ports_in_process
*		Maximal number of ports to be processed simultaneously by
*		Virtualization Manager
*
*	virt_default_hop_limit
*		Default value for hop limit of path record where either source
*		or detination is virtual port.
*
*	improved_lmc_path_distribution
*		Provides better local outgoing ports selection with LMC>0
*		for base LID + N (N in 1..2^LMC-1). Relevant for updn/minhop only
*
*	sweep_every_hup_signal
*		Flag indicating whether to perform heavy sweep in case of hup
*		signal received and no changes recognized in configuration
*
*	osm_stats_interval
*		Time interval [in min] between statistics dumps
*
*	osm_stats_dump_limit
*		The max size [in MB] of statisic dump file
*
*	sharp_enabled
*		Enable sharp support
*	rtr_aguid_enable
*		Enable creation of alias guids for algo router.
*	rtr_pr_flow_label
*		Inter subnet PathRecord FlowLabel
*	rtr_pr_tclass
*		Inter subnet PathRecord TClass
*	rtr_pr_sl
*		Inter subnet PathRecord SL
*	rtr_pr_mtu
*		Inter subnet PathRecord MTU
*	rtr_pr_rate
*		Inter subnet PathRecord Rate
*	router_policy_file
*		Name of the route policy file
*	router_policy_enabled
*		Enable router policy feature support
*	aguid_default_hop_limit
*		Default value for hop limit of path record where either source
*		or detination is alias guid.
*	load_inform_info_from_sadb
*		Enable load inform info from sadb file
*	verbose_bypass_policy_file
*		File name for log verbosity bypass policy
*	sa_db_dump_file
*		Full path file name for sa db dump file
*	subnet_lst_file
*		Full path file name for subnet lst dump file
*	virt_dump_file
*		Full path file name for virtualization dump file
*	dor_hyper_cube_mode
*		Perform Hyper-Cube topology analysis when using DOR routing
*		algorithm.
*	additional_gi_supporting_devices
*		Devices which supports general info mad in addition to the
*		devices which are defined by default
*
*	additional_mepi_force_devices
*		Devices which we force sending mepi for, in addition to the
*		devices which are defined by default
*
*	disable_default_gi_support
*		Disable general info support.
*
*	activity_report_subjects
*		Subjects to include in activity report
*
*	opts_def
*		Structure that keeps all option defaults
*
* SEE ALSO
*	Subnet object
*********/

/****s* OpenSM: Subnet/osm_subn_t
* NAME
*	osm_subn_t
*
* DESCRIPTION
*	Subnet structure.  Callers may directly access member components,
*	after grabbing a lock.
*
* TO DO
*	This structure should probably be volatile.
*
* SYNOPSIS
*/
typedef struct osm_subn {
	struct osm_opensm *p_osm;
	cl_qmap_t sw_guid_tbl;
	cl_qmap_t node_guid_tbl;
	cl_qmap_t port_guid_tbl;
	cl_qmap_t alias_port_guid_tbl;
	cl_qmap_t assigned_guids_tbl;
	cl_qmap_t rtr_guid_tbl;
	cl_qlist_t prefix_routes_list;
	cl_qmap_t prtn_pkey_tbl;
	cl_qmap_t sm_guid_tbl;
	cl_qlist_t sa_sr_list;
	cl_qlist_t sa_infr_list;
	cl_qlist_t alias_guid_list;
	cl_qmap_t held_back_sw_tbl;
	cl_fmap_t rcvd_traps_tbl;
	cl_qlist_t rcvd_traps_list;
	cl_qlist_t sa_reports_list;
	cl_fmap_t unhealthy_ports_tbl;
	cl_list_t ignored_nodes_list;
	cl_ptr_vector_t port_lid_tbl;
	uint16_t max_lid;
	uint16_t max_mlid;
	ib_net16_t master_sm_base_lid;
	ib_net16_t sm_base_lid;
	ib_net64_t sm_port_guid;
	uint8_t last_sm_port_state;
	uint8_t sm_state;
	uint8_t active_sm_priority;
	osm_subn_opt_t opt;
	struct osm_qos_policy *p_qos_policy;
	atomic32_t tid;
	uint16_t max_ucast_lid_ho;
	uint16_t max_mcast_lid_ho;
	uint8_t min_ca_mtu;
	uint8_t min_ca_rate;
	uint8_t min_data_vls;
	uint8_t min_sw_data_vls;
	boolean_t ignore_existing_lfts;
	boolean_t subnet_initialization_error;
	boolean_t force_heavy_sweep;
	boolean_t force_reroute;
	boolean_t in_sweep_hop_0;
	boolean_t force_first_time_master_sweep;
	boolean_t first_time_master_sweep;
	boolean_t coming_out_of_standby;
	boolean_t sweeping_enabled;
	boolean_t in_heavy_sweep;
	boolean_t found_ignored_port;
	boolean_t restore_links;
	unsigned need_update;
	boolean_t force_client_rereg;
	cl_fmap_t mgrp_mgid_tbl;
	cl_fmap_t mc_roots_tbl;
	ib_net64_t global_mc_root_guid;
	osm_db_domain_t *p_g2m;
	osm_db_domain_t *p_neighbor;
	osm_db_domain_t *p_an2an;
	void *mboxes[IB_LID_MCAST_END_HO - IB_LID_MCAST_START_HO + 1];
	struct osm_routing_engine *routing_engine_list;
	struct osm_routing_engine *last_routing_engine;
	struct osm_routing_engine *routing_engine_used;
	struct osm_routing_engine *default_routing_engine;
	int routing_chain_engine_id;
	boolean_t no_fallback_routing_engine;
	uint8_t path_bit;
	uint32_t light_sweep_counter;
	cl_qmap_t border_sw_tbl;
	cl_list_t leaf_switches_list;
	ib_net64_t hub_switch_guid;
	boolean_t force_multicast_rerouting;
	boolean_t reroute_all_mlids;
	boolean_t found_link_for_reset;
	boolean_t hup_signal;
	cl_fmap_t prefix_rtr_table;
} osm_subn_t;
/*
* FIELDS
*	sw_guid_tbl
*		Container of pointers to all Switch objects in the subnet.
*		Indexed by node GUID.
*
*	node_guid_tbl
*		Container of pointers to all Node objects in the subnet.
*		Indexed by node GUID.
*
*	port_guid_tbl
*		Container of pointers to all Port objects in the subnet.
*		Indexed by port GUID.
*
*	rtr_guid_tbl
*		Container of pointers to all Router objects in the subnet.
*		Indexed by node GUID.
*
*	prtn_pkey_tbl
*		Container of pointers to all Partition objects in the subnet.
*		Indexed by P_KEY.
*
*	sm_guid_tbl
*		Container of pointers to SM objects representing other SMs
*		on the subnet.
*
*	held_back_sw_tbl
*		Container of empty items indexed by node guid.
*		The node guid keys are used to store info about switches
*		configured as held-back
*
*	port_lid_tbl
*		Container of pointers to all Port objects in the subnet.
*		Indexed by port LID.
*
*	max_lid
*		The max lid value in the subnet.
*
*	max_mlid
*		The max mlid value in the subnet.
*
*	master_sm_base_lid
*		The base LID owned by the subnet's master SM.
*
*	sm_base_lid
*		The base LID of the local port where the SM is.
*
*	sm_port_guid
*		This SM's own port GUID.
*
*	last_sm_port_state
*		Last state of this SM's port.
*		0 is down and 1 is up.
*
*	sm_state
*		The high-level state of the SM.  This value is made available
*		in the SMInfo attribute.
*
*	active_sm_priority
*		Active SM priority, In case SM in MASTER state it will be
*		MAX(sm_priority, master_sm_priority) and sm_priority otherwise.
*
*	opt
*		Subnet options structure contains site specific configuration.
*
*	p_qos_policy
*		Subnet QoS policy structure.
*
*	max_ucast_lid_ho
*		The minimal max unicast lid reported by all switches
*
*	max_mcast_lid_ho
*		The minimal max multicast lid reported by all switches
*
*	min_ca_mtu
*		The minimal MTU reported by all CAs ports on the subnet
*
*	min_ca_rate
*		The minimal rate reported by all CA ports on the subnet
*
*	ignore_existing_lfts
*		This flag is a dynamic flag to instruct the LFT assignment to
*		ignore existing legal LFT settings.
*		The value will be set according to :
*		- Any change to the list of switches will set it to high
*		- Coming out of STANDBY it will be cleared (other SM worked)
*		- Set to FALSE upon end of all lft assignments.
*
*	subnet_initalization_error
*		Similar to the force_heavy_sweep flag. If TRUE - means that
*		we had errors during initialization (due to SubnSet requests
*		that failed). We want to declare the subnet as unhealthy, and
*		force another heavy sweep.
*
*	force_heavy_sweep
*		If TRUE - we want to force a heavy sweep. This can be done
*		either due to receiving of trap - meaning there is some change
*		on the subnet, or we received a handover from a remote sm.
*		In this case we want to sweep and reconfigure the entire
*		subnet. This will cause another heavy sweep to occure when
*		the current sweep is done.
*
*	force_reroute
*		If TRUE - we want to force switches in the fabric to be
*		rerouted.
*
*	in_sweep_hop_0
*		When in_sweep_hop_0 flag is set to TRUE - this means we are
*		in sweep_hop_0 - meaning we do not want to continue beyond
*		the current node.
*		This is relevant for the case of SM on switch, since in the
*		switch info we need to signal somehow not to continue
*		the sweeping.
*
*       force_first_time_master_sweep
*		This flag is used to avoid race condition when Master SM being
*		in the middle of very long configuration stage of the heavy sweep,
*		receives HANDOVER from another MASTER SM. When the current heavy sweep
*		is finished, new heavy sweep will be started immediately.
*		At the beginning of the sweep, opensm will set first_time_master_sweep,
*		force_heavy_sweep and coming_out_of_standby flags in order to allow full
*		reconfiguration of the fabric. This is required as another MASTER SM could
*		change configuration of the fabric before sending HANDOVER to MASTER SM.
*
*	first_time_master_sweep
*		This flag is used for the PortInfo setting. On the first
*		sweep as master (meaning after moving from Standby|Discovering
*		state), the SM must send a PortInfoSet to all ports. After
*		that - we want to minimize the number of PortInfoSet requests
*		sent, and to send only requests that change the value from
*		what is updated in the port (or send a first request if this
*		is a new port). We will set this flag to TRUE when entering
*		the master state, and set it back to FALSE at the end of the
*		drop manager. This is done since at the end of the drop manager
*		we have updated all the ports that are reachable, and from now
*		on these are the only ports we have data of. We don't want
*		to send extra set requests to these ports anymore.
*
*	coming_out_of_standby
*		TRUE on the first sweep after the SM was in standby.
*		Used for nulling any cache of LID and Routing.
*		The flag is set true if the SM state was standby and now
*		changed to MASTER it is reset at the end of the sweep.
*
*	sweeping_enabled
*		FALSE - sweeping is administratively disabled, all
*		sweeping is inhibited, TRUE - sweeping is done
*		normally
*
*	in_heavy_sweep
*		Indicates whether heavy sweep is in process or not
*
*	need_update
*		This flag should be on during first non-master heavy
*		(including pre-master discovery stage)
*
*	mgrp_mgid_tbl
*		Container of pointers to all Multicast group objects in
*		the subnet. Indexed by MGID.
*
*	mc_roots_tbl
*		Map between MGID to lists of switches that will be used
*		multicast tree roots.
*
*	mboxes
*		Array of pointers to all Multicast MLID box objects in the
*		subnet. Indexed by MLID offset from base MLID.
*
*	routing_engine_list
*		List of routing engines that should be tried for use.
*
*	routing_engine_used
*		Indicates which routing engine was used to route a subnet.
*
*	routing_chain_engine_id
*		holds the routing chain engine id used for this subnet.
*		when the main engine is not chain this field will be 0.
*
*	no_fallback_routing_engine
*		Indicates if default routing engine should not be used.
*
*	path_bit
*		limit routing for subnet to specific lmc LID offset
*
*	light_sweep_counter
*		Number of light sweep performed since last heavy sweep.
*
*	border_sw_tbl
*		Container of pointers to switches which are part of other
*		topologies subnets.
*
*	leaf_switches_list
*		a list of leaf switches updated by routing engine
*
*	hub_switch_guid
*		Guid of the hub switch used for calculating missing LID routes.
*
*	force_multicast_rerouting
*		Flag indicating whether to force rerouting all multicast trees.
*
*	reroute_all_mlids
*		Flag indicating whether to reroute all mlids at next multicast
*		processing.
*
*	found_link_for_reset
*		Flag indicating whether there are links that need to be reset.
*
*	hup_signal
*		Indication whether hup signal received
*
*	prefix_rtr_table
*		table of <subnet prefix, pkey> -> list of routers that have
*		these subnets and pkeys
*
* SEE ALSO
*	Subnet object
*********/

/****s* OpenSM: Subnet/osm_assigned_guids_t
* NAME
*	osm_assigned_guids_t
*
* DESCRIPTION
*	SA assigned GUIDs structure.
*
* SYNOPSIS
*/
typedef struct osm_assigned_guids {
	cl_map_item_t map_item;
	ib_net64_t port_guid;
	ib_net64_t assigned_guid[1];
} osm_assigned_guids_t;
/*
* FIELDS
*	map_item
*		Linkage structure for cl_qmap.  MUST BE FIRST MEMBER!
*
*	port_guid
*		Base port GUID.
*
*	assigned_guids
*		Table of persistent SA assigned GUIDs.
*
* SEE ALSO
*	Subnet object
*********/

/****s* OpenSM: Subnet/osm_mc_roots_list_t
* NAME
*	osm_mc_roots_list_t
*
* DESCRIPTION
* 	Container of list of pointers to switches that OpenSM should try to use
* 	as roots when calculating multicast trees.
*
* SYNOPSIS
*/
typedef struct osm_mc_roots_list {
	cl_fmap_item_t map_item;
	ib_gid_t mgid;
	cl_list_t switch_list;
} osm_mc_roots_list_t;
/*
* FIELDS
*	map_item
*		Linkage structure for cl_fmap.  MUST BE FIRST MEMBER!
*
*	switch_list
*		List of pointers to osm_switch_t objects.
*
* SEE ALSO
*	Subnet object
*********/

/****s* OpenSM: Subnet/osm_subnet_prefix_pkey_t
* NAME
*	osm_subnet_prefix_pkey_t
*
* DESCRIPTION
*	subnet prefix p_key pair
* SYNOPSIS
*/
typedef struct osm_subnet_prefix_pkey {
	ib_net64_t subnet_prefix;
	ib_net16_t pkey;
} osm_subnet_prefix_pkey_t;
/*
* FIELDS
*	subnet_prefix
*		subnet_prefix published in the routing table
*
*	p_key
*		p_key published for that subnet prefix in the routing table
*
* SEE ALSO
*	Subnet object
*********/

/****s* OpenSM: Subnet/osm_router_prefix_rtrs_map_t
* NAME
*	osm_router_prefix_rtrs_map_t
*
* DESCRIPTION
* 	Container of a map of pointers to routers that OpenSM should try to use
* 	when given subnet prefix + p_key
* 	as roots when calculating multicast trees.
* SYNOPSIS
*/
typedef struct osm_router_prefix_rtrs_map {
	cl_fmap_item_t map_item;
	cl_map_t rtrs;
} osm_router_prefix_rtrs_map_t;
/*
* FIELDS
*	map_item
*		Linkage structure for cl_fmap.  MUST BE FIRST MEMBER!
*
*	rtrs
*		map of router guids.
*
* SEE ALSO
*	Subnet object
*********/

/****f* OpenSM: Subnet/osm_subn_construct
* NAME
*	osm_subn_construct
*
* DESCRIPTION
*	This function constructs a Subnet object.
*
* SYNOPSIS
*/
void osm_subn_construct(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a Subnet object to construct.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*	Allows calling osm_subn_init, and osm_subn_destroy.
*
*	Calling osm_subn_construct is a prerequisite to calling any other
*	method except osm_subn_init.
*
* SEE ALSO
*	Subnet object, osm_subn_init, osm_subn_destroy
*********/

/****f* OpenSM: Subnet/osm_subn_destroy_prefix_router_db
* NAME
*	osm_subn_destroy_prefix_router_db
*
* DESCRIPTION
*	The osm_subn_destroy_prefix_router_db function destroys a prefix router db, releasing
*	all resources.
*
* SYNOPSIS
*/
void osm_subn_destroy_prefix_router_db(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a Subnet object,
*		which prefix router table to destroy.
*
* RETURN VALUE
*	This function does not return a value.
*********/

/****f* OpenSM: Subnet/osm_subn_destroy
* NAME
*	osm_subn_destroy
*
* DESCRIPTION
*	The osm_subn_destroy function destroys a subnet, releasing
*	all resources.
*
* SYNOPSIS
*/
void osm_subn_destroy(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a Subnet object to destroy.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*	Performs any necessary cleanup of the specified Subnet object.
*	Further operations should not be attempted on the destroyed object.
*	This function should only be called after a call to osm_subn_construct
*	or osm_subn_init.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_init
*********/

/****f* OpenSM: Subnet/osm_subn_init
* NAME
*	osm_subn_init
*
* DESCRIPTION
*	The osm_subn_init function initializes a Subnet object for use.
*
* SYNOPSIS
*/
ib_api_status_t osm_subn_init(IN osm_subn_t * p_subn,
			      IN struct osm_opensm *p_osm,
			      IN const osm_subn_opt_t * p_opt);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object to initialize.
*
*	p_opt
*		[in] Pointer to the subnet options structure.
*
* RETURN VALUES
*	IB_SUCCESS if the Subnet object was initialized successfully.
*
* NOTES
*	Allows calling other Subnet methods.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy
*********/

/*
  Forward references.
*/
struct osm_mad_addr;
struct osm_log;
struct osm_switch;
struct osm_physp;
struct osm_port;
struct osm_mgrp;
struct osm_router;

/****f* OpenSM: Subnet/osm_subn_prefix_router_tbl_remove_rtr
* NAME
*	osm_subn_prefix_router_tbl_remove_rtr
*
* DESCRIPTION
*	The osm_subn_prefix_router_tbl_remove_rtr function removes a router
*	from all subnet prefixes.
*
* SYNOPSIS
*/
void osm_subn_prefix_router_tbl_remove_rtr(IN osm_subn_t * p_subn,
					   IN struct osm_router * p_rtr);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a Subnet object,
*		which prefix router table to remove router from.
*	p_rtr
*		[in] Pointer to a router object,
*		which router table to remove.
*
* RETURN VALUE
*	This function does not return a value.
*********/

/****f* OpenSM: Helper/osm_get_gid_by_mad_addr
* NAME
*	osm_get_gid_by_mad_addr
*
* DESCRIPTION
*	Looks for the requester gid in the mad address.
*
* Note: This code is not thread safe. Need to grab the lock before
* calling it.
*
* SYNOPSIS
*/
ib_api_status_t osm_get_gid_by_mad_addr(IN struct osm_log *p_log,
					IN const osm_subn_t * p_subn,
					IN struct osm_mad_addr *p_mad_addr,
					OUT ib_gid_t * p_gid);
/*
* PARAMETERS
*	p_log
*		[in] Pointer to a log object.
*
*	p_subn
*		[in] Pointer to subnet object.
*
*	p_mad_addr
*		[in] Pointer to mad address object.
*
*	p_gid
*		[out] Pointer to the GID structure to fill in.
*
* RETURN VALUES
*     IB_SUCCESS if able to find the GID by address given.
*
* NOTES
*
* SEE ALSO
*********/

/****f* OpenSM: Helper/osm_get_physp_by_mad_addr
* NAME
*	osm_get_physp_by_mad_addr
*
* DESCRIPTION
*	Looks for the requester physical port in the mad address.
*
* Note: This code is not thread safe. Need to grab the lock before
* calling it.
*
* SYNOPSIS
*/
struct osm_physp *osm_get_physp_by_mad_addr(IN struct osm_log *p_log,
					     IN const osm_subn_t * p_subn,
					     IN struct osm_mad_addr
					     *p_mad_addr);
/*
* PARAMETERS
*	p_log
*		[in] Pointer to a log object.
*
*	p_subn
*		[in] Pointer to subnet object.
*
*	p_mad_addr
*		[in] Pointer to mad address object.
*
* RETURN VALUES
*	Pointer to requester physical port object if found. Null otherwise.
*
* NOTES
*
* SEE ALSO
*********/


/****f* OpenSM: Helper/osm_get_physp_by_dr
* NAME
*	osm_get_physp_by_dr
*
* DESCRIPTION
*	Looks for the requester physical port by the given DR path
*
* Note: This code is not thread safe. Need to grab the lock before
* calling it.
*
* SYNOPSIS
*/
struct osm_physp *osm_get_physp_by_dr(IN struct osm_log * p_log,
				      IN const osm_subn_t * p_subn,
				      IN const uint8_t hop_count,
				      IN const uint8_t *dr_path);
/*
* PARAMETERS
*	p_log
*		[in] Pointer to a log object.
*
*	p_subn
*		[in] Pointer to subnet object.
*
*	hop_count
*		[in] Number of hops in the DR path
*
*  dr_path
*     [in] The DR path to traverse
*
* RETURN VALUES
*	Pointer to requester physical port object if found. Null otherwise.
*
* NOTES
*
* SEE ALSO
*********/

/****f* OpenSM: Helper/osm_get_port_by_mad_addr
* NAME
*	osm_get_port_by_mad_addr
*
* DESCRIPTION
*	Looks for the requester port in the mad address.
*
* Note: This code is not thread safe. Need to grab the lock before
* calling it.
*
* SYNOPSIS
*/
struct osm_port *osm_get_port_by_mad_addr(IN struct osm_log *p_log,
					  IN const osm_subn_t * p_subn,
					  IN struct osm_mad_addr *p_mad_addr);
/*
* PARAMETERS
*	p_log
*		[in] Pointer to a log object.
*
*	p_subn
*		[in] Pointer to subnet object.
*
*	p_mad_addr
*		[in] Pointer to mad address object.
*
* RETURN VALUES
*	Pointer to requester port object if found. Null otherwise.
*
* NOTES
*
* SEE ALSO
*********/

/****f* OpenSM: Subnet/osm_get_switch_by_guid
* NAME
*	osm_get_switch_by_guid
*
* DESCRIPTION
*	Looks for the given switch guid in the subnet table of switches by guid.
*  NOTE: this code is not thread safe. Need to grab the lock before
*  calling it.
*
* SYNOPSIS
*/
struct osm_switch *osm_get_switch_by_guid(IN const osm_subn_t * p_subn,
					  IN ib_net64_t guid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	guid
*		[in] The node guid in network byte order
*
* RETURN VALUES
*	The switch structure pointer if found. NULL otherwise.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy,
*	osm_switch_t
*********/

/****f* OpenSM: Subnet/osm_get_node_by_guid
* NAME
*	osm_get_node_by_guid
*
* DESCRIPTION
*	This looks for the given node guid in the subnet table of nodes by guid.
*  NOTE: this code is not thread safe. Need to grab the lock before
*  calling it.
*
* SYNOPSIS
*/
struct osm_node *osm_get_node_by_guid(IN osm_subn_t const *p_subn,
				      IN ib_net64_t guid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	guid
*		[in] The node guid in network byte order
*
* RETURN VALUES
*	The node structure pointer if found. NULL otherwise.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy,
*	osm_node_t
*********/

/****f* OpenSM: Subnet/osm_get_port_by_guid
* NAME
*	osm_get_port_by_guid
*
* DESCRIPTION
*	This looks for the given port guid in the subnet table of ports by guid.
*  NOTE: this code is not thread safe. Need to grab the lock before
*  calling it.
*
* SYNOPSIS
*/
struct osm_port *osm_get_port_by_guid(IN osm_subn_t const *p_subn,
				      IN ib_net64_t guid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	guid
*		[in] The port guid in network order
*
* RETURN VALUES
*	The port structure pointer if found. NULL otherwise.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy,
*	osm_port_t
*********/

/****f* OpenSM: Port/osm_get_port_by_lid_ho
* NAME
*	osm_get_port_by_lid_ho
*
* DESCRIPTION
*	Returns a pointer of the port object for given lid value.
*
* SYNOPSIS
*/
struct osm_port *osm_get_port_by_lid_ho(const osm_subn_t * subn, uint16_t lid);
/*
* PARAMETERS
*	subn
*		[in] Pointer to the subnet data structure.
*
*	lid
*		[in] LID requested in host byte order.
*
* RETURN VALUES
*	The port structure pointer if found. NULL otherwise.
*
* SEE ALSO
*       Subnet object, osm_port_t
*********/

/****f* OpenSM: Subnet/osm_get_alias_guid_by_guid
* NAME
*	osm_get_alias_guid_by_guid
*
* DESCRIPTION
*	This looks for the given port guid in the subnet table of ports by
*	alias guid.
*  NOTE: this code is not thread safe. Need to grab the lock before
*  calling it.
*
* SYNOPSIS
*/
struct osm_alias_guid *osm_get_alias_guid_by_guid(IN osm_subn_t const *p_subn,
						  IN ib_net64_t guid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	guid
*		[in] The alias port guid in network order
*
* RETURN VALUES
*	The alias guid structure pointer if found. NULL otherwise.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy,
*	osm_alias_guid_t
*********/

/****f* OpenSM: Helper/osm_get_alias_guid_by_mad_addr
* NAME
*	osm_get_alias_guid_by_mad_addr
*
* DESCRIPTION
*	Looks for the requester alias guid object in the mad address.
*
* Note: This code is not thread safe. Need to grab the lock before
* calling it.
*
* SYNOPSIS
*/
struct osm_alias_guid *
osm_get_alias_guid_by_mad_addr(IN struct osm_log * p_log,
			       IN const osm_subn_t * p_subn,
			       IN struct osm_mad_addr *p_mad_addr);
/*
* PARAMETERS
*	p_log
*		[in] Pointer to a log object.
*
*	p_subn
*		[in] Pointer to subnet object.
*
*	p_mad_addr
*		[in] Pointer to mad address object.
*
* RETURN VALUES
*	Pointer to requester alias guid object if found. Null otherwise.
*
* NOTES
*
* SEE ALSO
*********/

/****f* OpenSM: Subnet/osm_get_guid_by_lid
* NAME
*	osm_get_guid_by_lid
*
* DESCRIPTION
*  Find guid of port or vport which owns a given lid
*  NOTE: this code is not thread safe. Need to grab the lock before
*  calling it.
*
* SYNOPSIS
*/
ib_net64_t osm_get_guid_by_lid(IN osm_subn_t const *p_subn, IN ib_net16_t lid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	lid
*		[in] The lid to find in network order
*
* RETURN VALUES
*	The guid if found. Zero otherwise.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy,
*	osm_alias_guid_t
*********/

/****f* OpenSM: Subnet/osm_get_port_by_alias_guid
* NAME
*	osm_get_port_by_alias_guid
*
* DESCRIPTION
*	This looks for the given port guid in the subnet table of ports by
*	alias guid.
*  NOTE: this code is not thread safe. Need to grab the lock before
*  calling it.
*
* SYNOPSIS
*/
struct osm_port *osm_get_port_by_alias_guid(IN osm_subn_t const *p_subn,
					    IN ib_net64_t guid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	guid
*		[in] The alias port guid in network order
*
* RETURN VALUES
*	The port structure pointer if found. NULL otherwise.
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy,
*	osm_port_t
*********/

/****f* OpenSM: Subnet/osm_is_alias_guid
* NAME
*	osm_is_alias_guid
*
* DESCRIPTION
*	All guids (alias or real) are represented as osm_alias_guid in the
*	alias guid table.
*	This function gets a osm_alias_guid from the alias guid table and return
*	indication if this is an alias guid (which means it is NOT real guid)
*
* SYNOPSIS
*/
boolean_t osm_is_alias_guid(IN const struct osm_alias_guid *p_alias_guid);
/*
* PARAMETERS
*	p_alias_guid
*		[in] Pointer to an alias guid object
*
* RETURN VALUES
*	TRUE - This alias guid represents an alias guid
*	FALSE - This alias guid represents a real guid
*********/

/****f* OpenSM: Port/osm_assigned_guids_new
* NAME
*	osm_assigned_guids_new
*
* DESCRIPTION
*	This function allocates and initializes an assigned guids object.
*
* SYNOPSIS
*/
osm_assigned_guids_t *osm_assigned_guids_new(IN const ib_net64_t port_guid,
					     IN const uint32_t num_guids);
/*
* PARAMETERS
*       port_guid
*               [in] Base port GUID in network order
*
* RETURN VALUE
*       Pointer to the initialized assigned alias guid object.
*
* SEE ALSO
*	Subnet object, osm_assigned_guids_t, osm_assigned_guids_delete,
*	osm_get_assigned_guids_by_guid
*********/

/****f* OpenSM: Port/osm_assigned_guids_delete
* NAME
*	osm_assigned_guids_delete
*
* DESCRIPTION
*	This function destroys and deallocates an assigned guids object.
*
* SYNOPSIS
*/
void osm_assigned_guids_delete(IN OUT osm_assigned_guids_t ** pp_assigned_guids);
/*
* PARAMETERS
*       pp_assigned_guids
*		[in][out] Pointer to a pointer to an assigned guids object to delete.
*		On return, this pointer is NULL.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*	Performs any necessary cleanup of the specified assigned guids object.
*
* SEE ALSO
*	Subnet object, osm_assigned_guids_new, osm_get_assigned_guids_by_guid
*********/

/****f* OpenSM: Subnet/osm_get_assigned_guids_by_guid
* NAME
*	osm_get_assigned_guids_by_guid
*
* DESCRIPTION
*	This looks for the given port guid and returns a pointer
*	to the guid table of SA assigned alias guids for that port.
*
* SYNOPSIS
*/
osm_assigned_guids_t *osm_get_assigned_guids_by_guid(IN osm_subn_t const *p_subn,
						     IN ib_net64_t port_guid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	port_guid
*		[in] The base port guid in network order
*
* RETURN VALUES
*	The osm_assigned_guids structure pointer if found. NULL otherwise.
*
* SEE ALSO
*	Subnet object, osm_assigned_guids_new, osm_assigned_guids_delete,
*	osm_assigned_guids_t
*********/

/****f* OpenSM: Port/osm_get_port_by_lid
* NAME
*	osm_get_port_by_lid
*
* DESCRIPTION
*	Returns a pointer of the port object for given lid value.
*
* SYNOPSIS
*/
static inline struct osm_port *osm_get_port_by_lid(IN osm_subn_t const * subn,
						   IN ib_net16_t lid)
{
	return osm_get_port_by_lid_ho(subn, cl_ntoh16(lid));
}
/*
* PARAMETERS
*	subn
*		[in] Pointer to the subnet data structure.
*
*	lid
*		[in] LID requested in network byte order.
*
* RETURN VALUES
*	The port structure pointer if found. NULL otherwise.
*
* SEE ALSO
*       Subnet object, osm_port_t
*********/

/****f* OpenSM: Subnet/osm_get_mgrp_by_mgid
* NAME
*	osm_get_mgrp_by_mgid
*
* DESCRIPTION
*	This looks for the given multicast group in the subnet table by mgid.
*	NOTE: this code is not thread safe. Need to grab the lock before
*	calling it.
*
* SYNOPSIS
*/
struct osm_mgrp *osm_get_mgrp_by_mgid(IN osm_subn_t * subn, IN ib_gid_t * mgid);
/*
* PARAMETERS
*	subn
*		[in] Pointer to an osm_subn_t object
*
*	mgid
*		[in] The multicast group MGID value
*
* RETURN VALUES
*	The multicast group structure pointer if found. NULL otherwise.
*********/

/****f* OpenSM: Subnet/osm_get_routers_by_subnet_prefix
* NAME
*	osm_get_routers_by_subnet_prefix
*
* DESCRIPTION
*	This looks for the given subnet prefix in the routers table by subnet prefix
*	NOTE: this code is not thread safe. Need to grab the lock before
*	calling it.
*
* SYNOPSIS
*/
osm_router_prefix_rtrs_map_t *
osm_get_routers_by_subnet_prefix(osm_subn_t const *p_subn,
				 osm_subnet_prefix_pkey_t *p_subnet_pkey);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	p_subnet_pkey
*		[in] The subnet pkey pair
*
* RETURN VALUES
*	The routers map pointer if found. NULL otherwise.
*********/

/****f* OpenSM: Subnet/osm_get_mbox_by_mlid
* NAME
*	osm_get_mbox_by_mlid
*
* DESCRIPTION
*	This looks for the given multicast group in the subnet table by mlid.
*	NOTE: this code is not thread safe. Need to grab the lock before
*	calling it.
*
* SYNOPSIS
*/
static inline struct osm_mgrp_box *osm_get_mbox_by_mlid(osm_subn_t const *p_subn, ib_net16_t mlid)
{
	return (struct osm_mgrp_box *)p_subn->mboxes[cl_ntoh16(mlid) - IB_LID_MCAST_START_HO];
}
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to an osm_subn_t object
*
*	mlid
*		[in] The multicast group mlid in network order
*
* RETURN VALUES
*	The multicast group structure pointer if found. NULL otherwise.
*********/

/****f* OpenSM: Subnet/is_mepi_supported
* NAME
*	is_mepi_supported
*
* DESCRIPTION
*	Checks if given node supports mlnx estended port info
*
* SYNOPSIS
*/
boolean_t is_mepi_supported(struct osm_sm *p_sm, struct osm_node *p_node);
/*
* PARAMETERS
*	p_sm
*		[in] Pointer to sm object
*
*	p_node
*		[in] Pointer to node object
*
* RETURN VALUES
*	Boolean indication whether given node support mlnx ext port info
*********/

/****f* OpenSM: Subnet/osm_subn_set_default_opt
* NAME
*	osm_subn_set_default_opt
*
* DESCRIPTION
*	The osm_subn_set_default_opt function sets the default options.
*
* SYNOPSIS
*/
void osm_subn_set_default_opt(IN osm_subn_opt_t * p_opt);
/*
* PARAMETERS
*
*	p_opt
*		[in] Pointer to the subnet options structure.
*
* RETURN VALUES
*	None
*
* NOTES
*
* SEE ALSO
*	Subnet object, osm_subn_construct, osm_subn_destroy
*********/

/****f* OpenSM: Subnet/osm_subn_parse_conf_file
* NAME
*	osm_subn_parse_conf_file
*
* DESCRIPTION
*	The osm_subn_parse_conf_file function parses the configuration file
*	and sets the defaults accordingly.
*
* SYNOPSIS
*/
int osm_subn_parse_conf_file(char *conf_file, osm_subn_opt_t * p_opt,
			     boolean_t log, boolean_t qos_log);
/*
* PARAMETERS
*
*	conf_file
*		name of configuration file
*	p_opt
*		[in] Pointer to the subnet options structure.
*	log
*		indication whether log print required
*	qos_log
*		indication whether log print required for qos options
*
* RETURN VALUES
*	0 on success, positive value if file doesn't exist,
*	negative value otherwise
*********/

/****f* OpenSM: Subnet/osm_subn_rescan_conf_files
* NAME
*	osm_subn_rescan_conf_files
*
* DESCRIPTION
*	The osm_subn_rescan_conf_files function parses the configuration
*	files and update selected subnet options
*
* SYNOPSIS
*/
int osm_subn_rescan_conf_files(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*
*	p_subn
*		[in] Pointer to the subnet structure.
*
* RETURN VALUES
*	0 on success, positive value if file doesn't exist,
*	negative value otherwise
*
*********/

/****f* OpenSM: Subnet/osm_subn_output_conf
* NAME
*	osm_subn_output_conf
*
* DESCRIPTION
*	Output configuration info
*
* SYNOPSIS
*/
void osm_subn_output_conf(FILE *out, IN osm_subn_opt_t * p_opt);
/*
* PARAMETERS
*
*	out
*		[in] File stream to output to.
*
*	p_opt
*		[in] Pointer to the subnet options structure.
*
* RETURN VALUES
*	This method does not return a value
*********/

/****f* OpenSM: Subnet/osm_subn_write_conf_file
* NAME
*	osm_subn_write_conf_file
*
* DESCRIPTION
*	Write the configuration file into the cache
*
* SYNOPSIS
*/
int osm_subn_write_conf_file(char *file_name, IN osm_subn_opt_t * p_opt);
/*
* PARAMETERS
*
*	p_opt
*		[in] Pointer to the subnet options structure.
*
* RETURN VALUES
*	0 on success, negative value otherwise
*
* NOTES
*	Assumes the conf file is part of the cache dir which defaults to
*	OSM_DEFAULT_CACHE_DIR or OSM_CACHE_DIR the name is opensm.opts
*********/
int osm_subn_verify_config(osm_subn_opt_t * p_opt);

/****f* OpenSM: Subnet/osm_is_held_back_sw
* NAME
*	osm_is_held_back_sw
*
* DESCRIPTION
*	Returns true if this switch persists in held_back list
*
* SYNOPSIS
*/
boolean_t osm_is_held_back_sw(IN osm_subn_t const *p_subn, IN ib_net64_t guid);
/*
* PARAMETERS
*
*	p_subn
*		[in] Pointer to the subnet structure.
*
*	guid
*		[in] Guid
*
* RETURN VALUES
*	TRUE if the switch is found and FALSE otherwise.
*********/

/****f* OpenSM: Subnet/subn_opt_destroy
* NAME
*	subn_opt_destroy
*
* DESCRIPTION
*	Destroy opt object
*
* SYNOPSIS
*/
void subn_opt_destroy(osm_subn_opt_t * p_opt);
/*
* PARAMETERS
*
*	p_opt
*		Pointer to the opt object to destroy.
*********/

/****f* OpenSM: OpenSM/osm_routing_engine_type_str
* NAME
*	osm_routing_engine_type_str
*
* DESCRIPTION
*	Returns a string for the specified routing engine type.
*
* SYNOPSIS
*/
const char *osm_routing_engine_type_str(IN osm_routing_engine_type_t type);
/*
* PARAMETERS
*	type
*		[in] routing engine type.
*
* RETURN VALUES
*	Pointer to routing engine name.
*
* NOTES
*
* SEE ALSO
*********/

/****f* OpenSM: OpenSM/osm_routing_engine_type
* NAME
*	osm_routing_engine_type
*
* DESCRIPTION
*	Returns a routing engine type specified routing engine name string.
*
* SYNOPSIS
*/

osm_routing_engine_type_t osm_routing_engine_type(IN const char *str);
/*
* PARAMETERS
*	str
*		[in] routing engine name string.
*
* RETURN VALUES
*	Routing engine type.
*
* NOTES
*
* SEE ALSO
*********/

/****f* OpenSM: OpenSM/osm_update_routing_engines
* NAME
*	osm_update_routing_engines
*
* DESCRIPTION
*	The osm_update_routing_engines function updates routing engines
*
* SYNOPSIS
*/
void osm_update_routing_engines(osm_subn_t *subn, const char *engine_names);
/*
* PARAMETERS
*	subn
*		[in] Pointer to a subnet object.
*	engine_names
*		[in] Routing engine names
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_setup_routing_engines
* NAME
*	osm_setup_routing_engines
*
* DESCRIPTION
*	The osm_setup_routing_engines function set up routing engines
*
* SYNOPSIS
*/
void osm_setup_routing_engines(osm_subn_t *subn, const char *engine_names);
/*
* PARAMETERS
*	subn
*		[in] Pointer to a subnet object.
*	engine_names
*		[in] Routing engine names
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/void destroy_default_routing_engine
* NAME
*	destroy_default_routing_engine
*
* DESCRIPTION
*	destroy the default routing engine
*
* SYNOPSIS
*/
void osm_destroy_default_routing_engine(osm_subn_t *subn);
/*
* PARAMETERS
*	subn
*		[in] Pointer to a subnet object.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_destroy_routing_engines
* NAME
*	osm_destroy_routing_engines
*
* DESCRIPTION
*	The osm_destroy_routing_engines function destroy routing engines
*
* SYNOPSIS
*/
void osm_destroy_routing_engines(osm_subn_t *subn);
/*
* PARAMETERS
*	subn
*		[in] Pointer to a subnet object.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/lookup_held_back_switch
* NAME
*	lookup_held_back_switch
*
* DESCRIPTION
*	Finds whether this node appears in held_back list
*
* SYNOPSIS
*/

boolean_t lookup_held_back_switch(IN osm_subn_t *subn,
				  IN struct osm_node * p_node);
/*
* PARAMETERS
*	subn
*		[in] Pointer to a subnet object.
*
* 	p_node
* 		[in] Pointer to a node object.
*
* RETURN VALUE
*	True if this node appears in held back switch list and false otherwise.
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_add_leaf
* NAME
*	osm_subn_add_leaf
*
* DESCRIPTION
*	Adds switch to subnets list of leaf switches.
*
* SYNOPSIS
*/
int osm_subn_add_leaf(IN osm_subn_t * p_subn, IN struct osm_switch * p_sw);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
*
* 	p_sw
* 		[in] Pointer to a switch object.
*
* RETURN VALUE
*	0 on success, negative value otherwise
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_clear_leafs
* NAME
*	osm_subn_clear_leafs
*
* DESCRIPTION
*	Clears subnet's list of leaf switches.
*
* SYNOPSIS
*/
void osm_subn_clear_leafs(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_clear_hub_switch
* NAME
*	osm_subn_clear_hub_switch
*
* DESCRIPTION
* 	removes sibmet hub switch.
*
* SYNOPSIS
*/
static inline void osm_subn_clear_hub_switch(IN osm_subn_t * p_subn)
{
	p_subn->hub_switch_guid = 0;
}
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_get_hub_switch_guid
* NAME
*	osm_subn_get_hub_switch_guid
*
* DESCRIPTION
* 	returns guid of subnet hub switch.
*
* SYNOPSIS
*/
static inline ib_net64_t osm_subn_get_hub_switch_guid(IN osm_subn_t * p_subn)
{
	return p_subn->hub_switch_guid;
}
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
* RETURN VALUES
*	Returns guid of the hub switch of the given subnet object
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_get_hub_switch
* NAME
*	osm_subn_get_hub_switch
*
* DESCRIPTION
* 	returns subnet hub switch.
*
* SYNOPSIS
*/
static inline struct osm_switch * osm_subn_get_hub_switch(IN osm_subn_t * p_subn)
{
	cl_map_item_t * p_item;
	if (!p_subn->hub_switch_guid)
		return NULL;
	p_item = cl_qmap_get(&p_subn->sw_guid_tbl, p_subn->hub_switch_guid);
	OSM_ASSERT(p_item != cl_qmap_end(&p_subn->sw_guid_tbl));
	return (struct osm_switch *)p_item;
}
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
* RETURN VALUES
*	Returns pointer to osm_switch_t object of the hub switch.
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_get_max_mlid
* NAME
*	osm_subn_get_max_mlid
*
* DESCRIPTION
*	Returns the highest MLID value in use.
*
* SYNOPSIS
*/
uint16_t osm_subn_get_max_mlid(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
* RETURN VALUES
*	Returns the highest MLID value in use.
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_set_mbox
* NAME
*	osm_subn_set_mbox
*
* DESCRIPTION
*	Sets value in array of multicast box objects and updates the value of
*	max_mlid.
*
* SYNOPSIS
*/
void osm_subn_set_mbox(IN osm_subn_t * p_subn, struct osm_mgrp_box  * mbox);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
*
*	mbox
*		[in] Pointer to a mbox object.
*
* RETURN VALUE
*	This function does not return a value.
*
* SEE ALSO
*
*********/

/****f* OpenSM: OpenSM/osm_subn_remove_mbox
* NAME
*	osm_subn_remove_mbox
*
* DESCRIPTION
*	Remove multicast box object from the array, and updates the value of
*	max_mlid.
*
* SYNOPSIS
*/
void osm_subn_remove_mbox(IN osm_subn_t * p_subn, IN uint16_t mlid);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to a subnet object.
*
*	mlid
*		[in] mlid if the mbox object to remove.
*
* RETURN VALUE
*	This function does not return a value.
*
* SEE ALSO
*
*********/

/****f* OpenSM: Port/osm_subn_bs_count
* NAME
*	osm_subn_bs_count
*
* DESCRIPTION
*	Returns number of border switches in the subnet.
*
* SYNOPSIS
*/
static inline size_t osm_subn_bs_count(IN osm_subn_t const *p_subn)
{
	return cl_qmap_count(&p_subn->border_sw_tbl);
}
/*
* PARAMETERS
*	subn
*		[in] Pointer to the subnet data structure.
*
* RETURN VALUES
*	Count of border switches in the subnet.
*********/

/****f* OpenSM: Subnet/osm_subn_mark_mbox_by_sw_port
* NAME
*	osm_subn_mark_mbox_by_sw_port
*
* DESCRIPTION
* 	Mark osm_mgrp_box_t objects with multicast tree on a given switch port
* 	for recalculation.
*
* SYNOPSIS
*/
void osm_subn_mark_mbox_by_sw(IN osm_subn_t * p_subn,
			      IN struct osm_switch * p_sw,
			      IN uint8_t port_num);
/*
* PARAMETERS
*	subn
*		[in] Pointer to the subnet data structure.
*
*	p_sw
*		[in] Pointer to osm_switch_t object.
*
* 	port_num
*		[in] Port number on the switch. If port_num is 0, check all
*		ports of the switch.
*
*
* RETURN VALUE
*	This function does not return a value.
*
* SEE ALSO
*
*********/

/****f* OpenSM: Subnet/osm_subn_clear_mtrees
* NAME
*	osm_subn_clear_mtrees
*
* DESCRIPTION
*	Clear multicast tree information from all osm_mgrp_box_t objects of
*	the subnet.
*
* SYNOPSIS
*/
void osm_subn_clear_mtrees(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to the subnet data structure.
*
* RETURN VALUE
*	This function does not return a value.
*
* SEE ALSO
*
*********/

/****f* OpenSM: Subnet/osm_subn_clear_mc_roots_tbl
* NAME
*	osm_subn_clear_mc_roots_tbl
*
* DESCRIPTION
*
* SYNOPSIS
*/
void osm_subn_clear_mc_roots_tbl(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to the subnet data structure.
*
* RETURN VALUE
*	This function does not return a value.
*
* SEE ALSO
*
*********/

/****f* OpenSM: Subnet/osm_subn_parse_mc_roots_file
* NAME
*	osm_subn_parse_mc_roots_file
*
* DESCRIPTION
* 	Parse multicast roots file
*
* SYNOPSIS
*/
int osm_subn_parse_mc_roots_file(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to the subnet data structure.
*
* RETURN VALUE
* 	Returns 0 if OpenSM parsed the file.
* 	1 otherwise.
*
* SEE ALSO
*
*********/

/****f* OpenSM: Subnet/osm_subn_apply_vlids_to_lfts
* NAME
*	osm_subn_apply_vlids_to_lfts
*
* DESCRIPTION
*	Add virtual ports lids into lft tables.
*	Virtual lids are added with exit port copied from the physical
*	port lid exit port.
*
* SYNOPSIS
*/
boolean_t osm_subn_apply_vlids_to_lfts(IN osm_subn_t * p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to the subnet data structure.
*
* RETURN VALUE
*	boolean indication whether vlids applied or not
*
* SEE ALSO
*
*********/

/****f* OpenSM: Subnet/osm_subn_print_conf_changes
* NAME
*	osm_subn_print_conf_changes
*
* DESCRIPTION
*	Print summary of configuration in non-default value
*
* SYNOPSIS
*/
void osm_subn_print_conf_changes(osm_subn_t *p_subn);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to the subnet data structure.
*
* RETURN VALUE
*	None
*
* SEE ALSO
*
*********/

END_C_DECLS
#endif				/* _OSM_SUBNET_H_ */
