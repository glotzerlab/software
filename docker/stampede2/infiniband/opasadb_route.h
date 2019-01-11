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

/* [ICS VERSION STRING: @(#) ./opasadb/opasadb_route.h 10_6_1_0_2 [10/25/17 20:34] */


#ifndef _OPA_SA_DB_ROUTE_H
#define _OPA_SA_DB_ROUTE_H


/*******************************************************************************
 *
 * INCLUDES
 */

#include <inttypes.h>               // type definitions


#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *
 * DEFINES
 */

// Constants

// Max number of port GUIDs in a job (LID values 0x0001-0xBFFF)
#define OP_ROUTE_MAX_GUIDS         49151

// Max number of switch indices in a job (index values 0x0000-0x7FFF)
//  switch_index is 15 bits in struct op_route_use_element)
#define OP_ROUTE_MAX_SWITCHES      32768

// Max number of created jobs (num_jobs is 16 bits in struct op_route_job_list)
#define OP_ROUTE_MAX_JOBS          65535

// Max number of chars in names
#define OP_ROUTE_MAX_JOB_NAME_LEN  64
#define OP_ROUTE_MAX_APP_NAME_LEN  64

// Create Job options
#define OP_ROUTE_CREATE_JOB_NORMAL     0x0000  // No options
#define OP_ROUTE_CREATE_JOB_NO_CREATE  0x0001  // Don't create job

// Function call return status
enum op_route_status
{
	OP_ROUTE_STATUS_OK = 0,         // success
	OP_ROUTE_STATUS_OK_PARTIAL,     // success w/exception
	OP_ROUTE_STATUS_ERROR,          // general failure
	OP_ROUTE_STATUS_SEND_ERROR,     // send failure
	OP_ROUTE_STATUS_RECV_ERROR,     // recv failure: bad response status
	OP_ROUTE_STATUS_TIMEOUT,        // recv failure: timeout
	OP_ROUTE_STATUS_INVALID_JOB,    // invalid job_id
	OP_ROUTE_STATUS_INVALID_PARAM   // invalid parameter
};

// Job status
enum op_route_job_status
{
	OP_ROUTE_JOB_STATUS_READY = 0,
	OP_ROUTE_JOB_STATUS_NOT_READY
};

// PORT_HANDLE: handle for a connection to an HFI port
typedef uint64_t OP_ROUTE_PORT_HANDLE;

// JOB_ID: identifier for a created job
typedef uint64_t OP_ROUTE_JOB_ID;

// op_route_job_parameters: contains (application) parameters for a job
struct op_route_job_parameters
{
	                                    // name associated with job
	char name[OP_ROUTE_MAX_JOB_NAME_LEN + 1];
	                                    // name associated with application
	char application_name[OP_ROUTE_MAX_APP_NAME_LEN + 1];
	uint64_t pid;                       // process ID
	uint64_t uid;                       // unique ID for job
};

// op_route_job_info: contains information about a job, including job_parameters
struct op_route_job_info
{
	OP_ROUTE_JOB_ID job_id;             // unique (SM-assigned) ID for job
	time_t time_stamp;                  // job start time stamp
	uint16_t reserved : 14;             // reserved flags
	uint16_t routed   :  1;             // TRUE: job's routing complete
	uint16_t has_use  :  1;             // TRUE: use matrix associated with job
	struct op_route_job_parameters params;  // job creation parameters
};

// op_route_job_list: contains list of all jobs for an OP_ROUTE_PORT_HANDLE
struct op_route_job_list
{
	uint16_t num_jobs;                      // Number of jobs in job_list
	struct op_route_job_info * p_job_info;  // array of job_list
};

// op_route_portguid_vec: vector (array) of HFI port GUIDs in a job.
struct op_route_portguid_vec
{
	uint16_t num_guids;             // number of port GUIDs in vector
	uint64_t * p_guids;             // array of port GUIDs
};

/* switch_map: map (array) of switch indices associated with a job.  Switch
 * indices are assigned by the Subnet Manager as a reference to each edge
 * switch in a job and range from 0 to num_switches - 1.  Each
 * switch_indices[n] entry provides the switch index for the switch
 * associated with portguid_vec.guids[n].  The number of switch_indices
 * entries in switch_map is the same as the number of port GUID entries
 * in portguid_vec.
 */
struct op_route_switch_map
{
	uint16_t num_switches;          // number of switches in map
	uint16_t * p_switch_indices;    // array of switch indices for port GUIDs
};

/* cost_matrix: matrix (table) of cost values for a job.  cost_matrix is two
 * dimensional, with source-switch index as the horizontal axis and
 * dest-switch as the vertical axis.  Each cost value represents the cost
 * to use the fabric from source-switch to dest-switch.  Cost values take
 * into account link speed, link width and hop count, and are comparable
 * between jobs.  cost_matrix is stored, row-major order, as an array of
 * cost values.
 */
// uint16_t * cost_matrix;

/* use_matrix: matrix (table) of use values for a job.  use_matrix is two
 * dimensional, with switch index and DLID as the axis variables.  Each use
 * value represents the use that the corresponding switch-DLID combination
 * is expected to make of the fabric.  Use values are relative within a
 * job as 8-bit values, but when multiplied by multiplier become comparable
 * between jobs.
 *
 * use_matrix is expected to have most use values at a default value
 * default_use.  Only exceptions to this value are specified explicitly.
 * Therefore use_matrix is stored as an array of elements for the
 * explicit (non-default) values.  Each element contains the corresponding
 * switch_index and DLID values and the use value; a "bursty" flag is also
 * included to indicate switch_index-DLID combinations whose use could
 * experience temporary, significant change from a "sustained" condition.
 */
struct op_route_use_element
{
	uint16_t bursty       :  1;     // TRUE: bursty, otherwise sustained
	uint16_t switch_index : 15;     // switch index of the use element
	uint16_t dlid;                  // DLID of the use element
	uint8_t use;                    // (relative) value of the use element
};

struct op_route_use_matrix
{
	uint8_t default_use;                    // default use value
	uint16_t multiplier;                    // use value multiplier
	uint16_t num_elements;                  // number of use_matrix elements
	struct op_route_use_element * p_elements;   // use elements, 1 per switch-DLID
};


/*******************************************************************************
 *
 * FUNCTION PROTOTYPES
 */

extern enum op_route_status op_route_open( struct omgt_port * port,
								uint64_t port_guid,
                                OP_ROUTE_PORT_HANDLE * p_port_handle ); // output

extern enum op_route_status op_route_close(OP_ROUTE_PORT_HANDLE port_handle);

extern enum op_route_status op_route_create_job( OP_ROUTE_PORT_HANDLE port_handle,
                                uint16_t optn_create,
                                struct op_route_job_parameters * p_job_params,
                                struct op_route_portguid_vec * p_guid_vec,
								struct omgt_port * port,
                                OP_ROUTE_JOB_ID * p_job_id,         // output
                                struct op_route_switch_map * p_switch_map, // output
                                uint16_t ** pp_cost_matrix );       // output

extern enum op_route_status op_route_complete_job( OP_ROUTE_PORT_HANDLE port_handle,
                                OP_ROUTE_JOB_ID job_id,
								struct omgt_port * port );

extern enum op_route_status op_route_get_portguid_vec( OP_ROUTE_PORT_HANDLE port_handle,
                                OP_ROUTE_JOB_ID job_id,
								struct omgt_port * port,
                                struct op_route_portguid_vec * p_guid_vec ); // output

extern void op_route_release_portguid_vec(struct op_route_portguid_vec * p_guid_vec);

extern enum op_route_status op_route_get_switch_map( OP_ROUTE_PORT_HANDLE port_handle,
                                OP_ROUTE_JOB_ID job_id,
								struct omgt_port * port,
                                struct op_route_switch_map * p_switch_map ); // output

extern void op_route_release_switch_map(struct op_route_switch_map * p_switch_map);

extern enum op_route_status op_route_get_cost_matrix( OP_ROUTE_PORT_HANDLE port_handle,
                                OP_ROUTE_JOB_ID job_id,
								struct omgt_port * port,
                                uint16_t ** pp_cost_matrix );   // output

extern void op_route_release_cost_matrix(uint16_t * p_cost_matrix);

extern enum op_route_status op_route_get_use_matrix( OP_ROUTE_PORT_HANDLE port_handle,
                                OP_ROUTE_JOB_ID job_id,
								struct omgt_port * port,
                                struct op_route_use_matrix * p_use_matrix ); // output

extern enum op_route_status op_route_set_use_matrix( OP_ROUTE_PORT_HANDLE port_handle,
                                OP_ROUTE_JOB_ID job_id,
								struct omgt_port * port,
                                struct op_route_use_matrix * p_use_matrix );

extern void op_route_release_use_matrix(struct op_route_use_matrix * p_use_matrix);

extern enum op_route_status op_route_get_job_list( OP_ROUTE_PORT_HANDLE port_handle,
								struct omgt_port * port,
                                struct op_route_job_list * p_job_list); // output

extern void op_route_release_job_list(struct op_route_job_list * p_job_list);

extern enum op_route_status op_route_poll_ready( OP_ROUTE_PORT_HANDLE port_handle,
                                OP_ROUTE_JOB_ID job_id,
								struct omgt_port * port,
                                enum op_route_job_status * p_job_status );

extern char * op_route_get_status_text(enum op_route_status status);

#ifdef __cplusplus
};
#endif

#endif /* _OPA_SA_DB_ROUTE_H */

