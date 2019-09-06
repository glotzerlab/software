/*
 * Copyright (c) 2004-2009 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2002-2006 Mellanox Technologies LTD. All rights reserved.
 * Copyright (c) 1996-2003 Intel Corporation. All rights reserved.
 * Copyright (c) 2009-2011 ZIH, TU Dresden, Federal Republic of Germany. All rights reserved.
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
 * 	Declaration of osm_opensm_t.
 *	This object represents the OpenSM super object.
 *	This object is part of the OpenSM family of objects.
 */

#ifndef _OSM_OPENSM_H_
#define _OSM_OPENSM_H_

#include <stdio.h>
#include <complib/cl_qlist.h>
#include <complib/cl_dispatcher.h>
#include <complib/cl_passivelock.h>
#include <complib/cl_atomic.h>
#include <complib/cl_nodenamemap.h>
#include <opensm/osm_console_io.h>
#include <opensm/osm_stats.h>
#include <opensm/osm_log.h>
#include <opensm/osm_sm.h>
#include <opensm/osm_sa.h>
#include <opensm/osm_perfmgr.h>
#include <opensm/osm_event_plugin.h>
#include <opensm/osm_db.h>
#include <opensm/osm_subnet.h>
#include <opensm/osm_mad_pool.h>
#include <opensm/osm_vl15intf.h>
#include <opensm/osm_congestion_control.h>

#ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS   }
#else				/* !__cplusplus */
#  define BEGIN_C_DECLS
#  define END_C_DECLS
#endif				/* __cplusplus */

BEGIN_C_DECLS
/****h* OpenSM/OpenSM
* NAME
*	OpenSM
*
* DESCRIPTION
*	The OpenSM object encapsulates the information needed by the
*	OpenSM to govern itself.  The OpenSM is one OpenSM object.
*
*	The OpenSM object is thread safe.
*
*	This object should be treated as opaque and should
*	be manipulated only through the provided functions.
*
* AUTHOR
*	Steve King, Intel
*
*********/

typedef enum statistic_counters {
	NODE_DESC_RCV_COUNT = 0,
	NODE_DESC_SEND_COUNT,
	NODE_INFO_RCV_COUNT,
	NODE_INFO_SEND_COUNT,
	SWITCH_INFO_RCV_COUNT,
	SWITCH_INFO_SEND_COUNT,
	GUID_INFO_RCV_COUNT,
	GUID_INFO_SEND_COUNT,
	PORT_INFO_RCV_COUNT,
	PORT_INFO_SEND_COUNT,
	P_KEY_TBL_RCV_COUNT,
	P_KEY_TBL_SEND_COUNT,
	SL_VL_MAP_RCV_COUNT,
	SL_VL_MAP_SEND_COUNT,
	VL_ARBIT_TBL_RCV_COUNT,
	VL_ARBIT_TBL_SEND_COUNT,
	LFT_RCV_COUNT,
	LFT_SEND_COUNT,
	MFT_RCV_COUNT,
	MFT_SEND_COUNT,
	SM_INFO_RCV_COUNT,
	SM_INFO_SEND_COUNT,
	MEPI_RCV_COUNT,
	MEPI_SEND_COUNT,
	NOTICE_128_RCV_COUNT,
	NOTICE_128_SEND_COUNT,
	NOTICE_130_RCV_COUNT,
	NOTICE_130_SEND_COUNT,
	NOTICE_131_RCV_COUNT,
	NOTICE_131_SEND_COUNT,
	NOTICE_144_RCV_COUNT,
	NOTICE_144_SEND_COUNT,
	NOTICE_145_RCV_COUNT,
	NOTICE_145_SEND_COUNT,
	NOTICE_256_RCV_COUNT,
	NOTICE_256_SEND_COUNT,
	NOTICE_257_RCV_COUNT,
	NOTICE_257_SEND_COUNT,
	NOTICE_258_RCV_COUNT,
	NOTICE_258_SEND_COUNT,
	NOTICE_259_RCV_COUNT,
	NOTICE_259_SEND_COUNT,
	NODE_RECORD_RCV,
	NODE_RECORD_SEND,
	PORT_INFO_RECORD_RCV,
	PORT_INFO_RECORD_SEND,
	SL_VL_MAP_TBL_RECORD_RCV,
	SL_VL_MAP_TBL_RECORD_SEND,
	SWITCH_INFO_RECORD_RCV,
	SWITCH_INFO_RECORD_SEND,
	LINEAR_FORWARD_TBL_RECORD_RCV,
	LINEAR_FORWARD_TBL_RECORD_SEND,
	MULTICAST_FORWARD_TBL_RECORD_RCV,
	MULTICAST_FORWARD_TBL_RECORD_SEND,
	VL_ARBI_TBL_RECORD_RCV,
	VL_ARBI_TBL_RECORD_SEND,
	SM_INFO_RECORD_RCV,
	SM_INFO_RECORD_SEND,
	P_KEY_TBL_RECORD_RCV,
	P_KEY_TBL_RECORD_SEND,
	INFORM_INFO_RECORD_RCV,
	INFORM_INFO_RECORD_SEND,
	LINK_RECORD_RCV,
	LINK_RECORD_SEND,
	SERVICE_RECORD_RCV,
	SERVICE_RECORD_SEND,
	PATH_RECORD_RCV,
	PATH_RECORD_SEND,
	MC_MEMBER_RECORD_RCV,
	MC_MEMBER_RECORD_SEND,
	GUID_INFO_RECORD_RCV,
	GUID_INFO_RECORD_SEND,
	MULTI_PATH_RECORD_RCV,
	MULTI_PATH_RECORD_SEND,
	HEAVY_SWEEP_COUNT,
	LIGHT_SWEEP_COUNT,
	LAST_STAT_COUNTER
} statistic_counters;


#define OSM_STATISTIC_COUNTERS_SIZE		LAST_STAT_COUNTER

/****s* OpenSM: OpenSM/osm_opensm_t
* NAME
*	osm_opensm_t
*
* DESCRIPTION
*	OpenSM structure.
*
*	This object should be treated as opaque and should
*	be manipulated only through the provided functions.
*
* SYNOPSIS
*/
typedef struct osm_opensm {
	const char *osm_version;
	osm_subn_t subn;
	osm_sm_t sm;
	osm_sa_t sa;
#ifdef ENABLE_OSM_PERF_MGR
	osm_perfmgr_t perfmgr;
#endif				/* ENABLE_OSM_PERF_MGR */
	osm_congestion_control_t cc;
	cl_qlist_t plugin_list;
	osm_db_t db;
	boolean_t mad_pool_constructed;
	osm_mad_pool_t mad_pool;
	osm_vendor_t *p_vendor;
	osm_vendor_t *p_gmp_vendor;
	boolean_t vl15_constructed;
	osm_vl15_t vl15;
	osm_log_t log;
	cl_dispatcher_t disp;
	cl_dispatcher_t sminfo_get_disp;
	cl_dispatcher_t sa_set_disp;
	cl_dispatcher_t gmp_disp;
	boolean_t sa_set_disp_initialized;
	cl_plock_t lock;
	osm_stats_t stats;
	osm_console_t console;
	nn_map_t *node_name_map;
	FILE *statistic_dump_file;
	unsigned long statistic_file_size;
        unsigned long statistic_max_size;
	uint64_t stats_counters[OSM_STATISTIC_COUNTERS_SIZE];
} osm_opensm_t;
/*
* FIELDS
* 	osm_version
* 		OpenSM version (as generated in osm_version.h)
*
*	subn
*		Subnet object for this subnet.
*
*	sm
*		The Subnet Manager (SM) object for this subnet.
*
*	sa
*		The Subnet Administration (SA) object for this subnet.
*
*	db
*		Persistant storage of some data required between sessions.
*
*	mad_pool
*		Pool of Management Datagram (MAD) objects.
*
*	p_vendor
*		Pointer to the Vendor specific adapter for various
*		transport interfaces, such as UMADT, AL, etc.  The
*		particular interface is set at compile time. This adapter
*		will handle SMP MADs only
*
*	p_gmp_vendor
*		Pointer to the Vendor specific adapter for GMP MADs
*
*	vl15
*		The VL15 interface.
*
*	log
*		Log facility used by all OpenSM components.
*
*	disp
*		Dispatcher for SMP requests except SMInfo Get
*
*	sminfo_get_disp
*		SMInfo Get dispatcher containing the OpenSM SMInfo Get request.
*
*	sa_set_disp
*		Dispatcher for SA Set and Delete requests.
*
*	gmp_disp
*		Dispatcher for GMP request except SA Set and Delete requests
*
*	event_disp
*		Dispatcher for events to be reported by the SM
*
*	sa_set_disp_initialized.
*		Indicator that sa_set_disp dispatcher was initialized.
*
*	lock
*		Shared lock guarding most OpenSM structures.
*
*	stats
*		Open SM statistics block
*
*	statistic_file_size
*		The current size of the statistic file.
*
*	statistic_max_size
*		The max size of the statistic file.
*
*	stats_counters
*		The statistic counters.
*
* SEE ALSO
*********/

/****f* OpenSM: OpenSM/osm_opensm_construct
* NAME
*	osm_opensm_construct
*
* DESCRIPTION
*	This function constructs an OpenSM object.
*
* SYNOPSIS
*/
void osm_opensm_construct(IN osm_opensm_t * p_osm);
/*
* PARAMETERS
*	p_osm
*		[in] Pointer to a OpenSM object to construct.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*	Allows calling osm_opensm_init, osm_opensm_destroy
*
*	Calling osm_opensm_construct is a prerequisite to calling any other
*	method except osm_opensm_init.
*
* SEE ALSO
*	SM object, osm_opensm_init, osm_opensm_destroy
*********/

/****f* OpenSM: OpenSM/osm_opensm_construct_finish
* NAME
*	osm_opensm_construct_finish
*
* DESCRIPTION
*	The osm_opensm_construct_finish function completes
*	the second phase of constucting an OpenSM object.
*
* SYNOPSIS
*/
void osm_opensm_construct_finish(IN osm_opensm_t * p_osm);
/*
* PARAMETERS
*	p_osm
*		[in] Pointer to a OpenSM object to construct.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*	Calling osm_opensm_construct/osm_construct_finish is a prerequisite
*	to calling any other method except osm_opensm_init/osm_opensm_init_finish.
*
* SEE ALSO
*	SM object, osm_opensm_init, osm_opensm_construct_finish,
*	osm_opensm_destroy, osm_opensm_destroy_finish
*********/


/****f* OpenSM: OpenSM/osm_opensm_destroy
* NAME
*	osm_opensm_destroy
*
* DESCRIPTION
*	The osm_opensm_destroy function destroys an SM, releasing
*	all resources.
*
* SYNOPSIS
*/
void osm_opensm_destroy(IN osm_opensm_t * p_osm);
/*
* PARAMETERS
*	p_osm
*		[in] Pointer to a OpenSM object to destroy.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*	Performs any necessary cleanup of the specified OpenSM object.
*	Further operations should not be attempted on the destroyed object.
*	This function should only be called after a call to osm_opensm_construct or
*	osm_opensm_init.
*
* SEE ALSO
*	SM object, osm_opensm_construct, osm_opensm_init
*********/

/****f* OpenSM: OpenSM/osm_opensm_destroy_finish
* NAME
*	osm_opensm_destroy_finish
*
* DESCRIPTION
*	The osm_opensm_destroy_finish function handles the second phase
*	of destroying an SM, releasing all resources.
*
* SYNOPSIS
*/
void osm_opensm_destroy_finish(IN osm_opensm_t * p_osm);
/*
* PARAMETERS
*	p_osm
*		[in] Pointer to a OpenSM object to destroy.
*
* RETURN VALUE
*	This function does not return a value.
*
* NOTES
*	Performs second phase of any necessary cleanup of the specified OpenSM object.
*	Further operations should not be attempted on the destroyed object.
*	This function should only be called after a call to
*	osm_opensm_construct_finish or osm_opensm_init_finish.
*
* SEE ALSO
*	SM object, osm_opensm_construct, osm_opensm_construct_finish,
*	osm_opensm_init, osm_opensm_init_finish
*********/

/****f* OpenSM: OpenSM/osm_opensm_init
* NAME
*	osm_opensm_init
*
* DESCRIPTION
*	The osm_opensm_init function initializes a OpenSM object for use.
*
* SYNOPSIS
*/
ib_api_status_t osm_opensm_init(IN osm_opensm_t * p_osm,
				IN const osm_subn_opt_t * p_opt);
/*
* PARAMETERS
*	p_osm
*		[in] Pointer to an osm_opensm_t object to initialize.
*
*	p_opt
*		[in] Pointer to the subnet options structure.
*
* RETURN VALUES
*	IB_SUCCESS if the OpenSM object was initialized successfully.
*
* NOTES
*	Allows calling other OpenSM methods.
*
* SEE ALSO
*	SM object, osm_opensm_construct, osm_opensm_destroy
*********/

/****f* OpenSM: OpenSM/osm_opensm_init_finish
* NAME
*	osm_opensm_init_finish
*
* DESCRIPTION
*	The osm_opensm_init_finish function performs the second phase
*	of initialization of an OpenSM object.
*
* SYNOPSIS
*/
ib_api_status_t osm_opensm_init_finish(IN osm_opensm_t * p_osm,
				       IN const osm_subn_opt_t * p_opt);
/*
* PARAMETERS
*	p_osm
*		[in] Pointer to an osm_opensm_t object to initialize.
*
*	p_opt
*		[in] Pointer to the subnet options structure.
*
* RETURN VALUES
*	IB_SUCCESS if the OpenSM object was initialized successfully.
*
* NOTES
*	Allows calling other OpenSM methods.
*
* SEE ALSO
*	SM object, osm_opensm_construct, osm_opensm_construct_finish,
*	osm_opensm_destroy, osm_opensm_destroy_finish
*********/

/****f* OpenSM: OpenSM/osm_opensm_sweep
* NAME
*	osm_opensm_sweep
*
* DESCRIPTION
*	Initiates a subnet sweep.
*
* SYNOPSIS
*/
static inline void osm_opensm_sweep(IN osm_opensm_t * p_osm)
{
	osm_sm_sweep(&p_osm->sm);
}

/*
* PARAMETERS
*	p_osm
*		[in] Pointer to an osm_opensm_t object on which to
*		initiate a sweep.
*
* RETURN VALUES
*	None
*
* NOTES
*	If the OpenSM object is not bound to a port, this function
*	does nothing.
*
* SEE ALSO
*********/

/****f* OpenSM: OpenSM/osm_opensm_set_log_flags
* NAME
*	osm_opensm_set_log_flags
*
* DESCRIPTION
*	Sets the log level.
*
* SYNOPSIS
*/
static inline void osm_opensm_set_log_flags(IN osm_opensm_t * p_osm,
					    IN osm_log_level_t log_flags)
{
	osm_log_set_level(&p_osm->log, log_flags);
}

/*
* PARAMETERS
*	p_osm
*		[in] Pointer to an osm_opensm_t object.
*
*	log_flags
*		[in] Log level flags to set.
*
* RETURN VALUES
*	None
*
* NOTES
*
* SEE ALSO
*********/

/****f* OpenSM: OpenSM/osm_opensm_bind
* NAME
*	osm_opensm_bind
*
* DESCRIPTION
*	Binds the opensm object to a port guid.
*
* SYNOPSIS
*/
ib_api_status_t osm_opensm_bind(IN osm_opensm_t * p_osm, IN ib_net64_t guid);
/*
* PARAMETERS
*	p_osm
*		[in] Pointer to an osm_opensm_t object to bind.
*
*	guid
*		[in] Local port GUID with which to bind.
*
* RETURN VALUES
*	None
*
* NOTES
*	A given opensm object can only be bound to one port at a time.
*
* SEE ALSO
*********/

/****f* OpenSM: OpenSM/osm_opensm_wait_for_subnet_up
* NAME
*	osm_opensm_wait_for_subnet_up
*
* DESCRIPTION
*	Blocks the calling thread until the subnet is up.
*
* SYNOPSIS
*/
static inline cl_status_t
osm_opensm_wait_for_subnet_up(IN osm_opensm_t * p_osm, IN uint32_t wait_us,
			      IN boolean_t interruptible)
{
	return osm_sm_wait_for_subnet_up(&p_osm->sm, wait_us, interruptible);
}

/*
* PARAMETERS
*	p_osm
*		[in] Pointer to an osm_opensm_t object.
*
*	wait_us
*		[in] Number of microseconds to wait.
*
*	interruptible
*		[in] Indicates whether the wait operation can be interrupted
*		by external signals.
*
* RETURN VALUES
*	CL_SUCCESS if the wait operation succeeded in response to the event
*	being set.
*
*	CL_TIMEOUT if the specified time period elapses.
*
*	CL_NOT_DONE if the wait was interrupted by an external signal.
*
*	CL_ERROR if the wait operation failed.
*
* NOTES
*
* SEE ALSO
*********/

void osm_opensm_report_event(osm_opensm_t *osm, osm_epi_event_id_t event_id,
			     void *event_data);

/* dump helpers */
void osm_dump_virtualization(osm_opensm_t * osm);
void osm_dump_mcast_routes(osm_opensm_t * osm);
void osm_dump_subn_all(osm_opensm_t * osm, osm_subn_t *p_subn, char* prefix,
		       boolean_t routing_only);
void osm_dump_lfts(osm_opensm_t * osm, osm_subn_t *p_subn, char* prefix);
void osm_dump_main_all(osm_opensm_t * osm);
void osm_dump_qmap_to_file(osm_opensm_t * p_osm, const char *file_name,
			   cl_qmap_t * map,
			   void (*func) (cl_map_item_t *, FILE *, void *),
			   void *cxt);
void osm_dump_func_to_file(osm_opensm_t * p_osm, const char *file_path,
			   void (*func) (FILE *, void *),
			   void *cxt);
void osm_dump_statistic(osm_opensm_t * p_osm);
void osm_dump_sm_db(IN osm_opensm_t * p_osm);

/****v* OpenSM/osm_exit_flag
*/
extern volatile unsigned int osm_exit_flag;
/*
* DESCRIPTION
*  Set to one to cause all threads to leave
*********/

END_C_DECLS
#endif				/* _OSM_OPENSM_H_ */
