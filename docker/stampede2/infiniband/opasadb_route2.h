/* BEGIN_ICS_COPYRIGHT7 ****************************************

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

** END_ICS_COPYRIGHT7   ****************************************/

/* [ICS VERSION STRING: @(#) ./opasadb/opasadb_route2.h 10_6_1_0_2 [10/25/17 20:34] */


#ifndef _OPA_SA_DB_ROUTE2_H
#define _OPA_SA_DB_ROUTE2_H


/*******************************************************************************
 *
 * INCLUDES
 */

#include "opasadb_route.h"
#include "ib_sd.h"                  // opasadb_route built on ib_sd layer


#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *
 * DEFINES
 */

// Attribute IDs

// Attribute Modifiers
#define OP_ROUTE_AMOD_CLASS_INFO        0x0001
#define OP_ROUTE_AMOD_CREATE_JOB        0x0002
#define OP_ROUTE_AMOD_SET_USE_MATRIX    0x0003
#define OP_ROUTE_AMOD_POLL_READY        0x0004
#define OP_ROUTE_AMOD_COMPLETE_JOB      0x0005
#define OP_ROUTE_AMOD_GET_PORTGUID_VEC  0x0006
#define OP_ROUTE_AMOD_GET_SWITCH_MAP    0x0007
#define OP_ROUTE_AMOD_GET_COST_MATRIX   0x0008
#define OP_ROUTE_AMOD_GET_USE_MATRIX    0x0009
#define OP_ROUTE_AMOD_GET_JOBS          0x000A

#define OP_ROUTE_MIN_BASE_VERSION      1        // Min base for operation
#define OP_ROUTE_MIN_SA_CLASS_VERSION  2        // Min SA class for operation
#define OP_ROUTE_MIN_JM_CLASS_VERSION  1        // Min JM class for operation
// TBD change if minimum raised above 0
#define OP_ROUTE_MIN_NUM_GUIDS         0        // Min number of GUIDS
#define OP_ROUTE_MAX_NUM_SWITCHES      32768    // Max number of switches

// Configuration parameters
#define NUM_PARAM_PORT_HANDLE_ALLOC  8      // Num port table entries to alloc

// Protocol wire status
enum op_route_wire_status
{
	OP_ROUTE_WIRE_STATUS_OK = 0,            // success
	OP_ROUTE_WIRE_STATUS_OK_PARTIAL,        // success w/exception
	OP_ROUTE_WIRE_STATUS_ERROR,             // general failure
	OP_ROUTE_WIRE_STATUS_INVALID_JOB        // invalid job_id
};

// Parameter allocation structures
// Replicated (array) structure for an allocated parameter; this structure
//  is a model for parameter-specific structures
struct op_route_param_alloc_entry
{
	uint64_t size_param;            // Size of param (bf_data) allocated (bytes)
	uint64_t size_data;             // Size of param (bf_data) in use (bytes)
	uint64_t info_param;            // Info about param (param specific)
	//  NOTE: previous uint64_t ensures uint64_t alignment of bf_data
	char bf_data[];                 // Allocated param buffer
};

// Base (root) structure for an allocated parameter
struct op_route_param_alloc
{
	size_t size_param;              // Size of param entry
	uint16_t num_allocated;         // Num params allocated
	uint16_t num_used;              // Num params in use
	uint16_t num_alloc;             // Num params in allocation unit
	                                // Pointer to allocated parameters
	struct op_route_param_alloc_entry * p_params;
};


/*******************************************************************************
 *
 * FUNCTION PROTOTYPES
 */

extern void op_route_dump( char * p_title,
                int fb_port_handles,
                OP_ROUTE_PORT_HANDLE * p_port_handle,
                OP_ROUTE_JOB_ID * p_job_id,
                struct op_route_job_parameters * p_job_params,
                struct op_route_portguid_vec * p_guid_vec,
                struct op_route_switch_map * p_switch_map,
                uint16_t * p_cost_matrix,
                struct op_route_use_matrix * p_use_matrix,
                struct op_route_job_info * p_job_info,
                struct op_route_job_list * p_job_list );

extern int op_route_init_param( struct op_route_param_alloc * p_param,
                uint32_t size_param,
                uint32_t num_alloc );

extern void op_route_free_param(struct op_route_param_alloc * p_param);

extern int op_route_alloc_param(struct op_route_param_alloc * p_param);

extern void op_route_dump_param( char * p_title,
                struct op_route_param_alloc * p_param );

// DEBUG temporary
extern void op_route_put_fvdebug(uint32_t fvDebug);


#ifdef __cplusplus
};
#endif

#endif /* _OPA_SA_DB_ROUTE2_H */

