/*
 * Copyright (c) 2004-2009 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2002-2005,2008, 2015 Mellanox Technologies LTD. All rights reserved.
 * Copyright (c) 1996-2003 Intel Corporation. All rights reserved.
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
 * 	Declaration of osm_router_t.
 *	This object represents an IBA router.
 *	This object is part of the OpenSM family of objects.
 */

#ifndef _OSM_ROUTER_H_
#define _OSM_ROUTER_H_

#include <iba/ib_types.h>
#include <opensm/osm_base.h>
#include <opensm/osm_madw.h>
#include <opensm/osm_node.h>
#include <opensm/osm_port.h>
#include <opensm/osm_mcast_tbl.h>
#include <opensm/osm_port_profile.h>

#ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS   }
#else				/* !__cplusplus */
#  define BEGIN_C_DECLS
#  define END_C_DECLS
#endif				/* __cplusplus */

BEGIN_C_DECLS
/****h* OpenSM/Router
* NAME
*	Router
*
* DESCRIPTION
*	The Router object encapsulates the information needed by the
*	OpenSM to manage routers.  The OpenSM allocates one router object
*	per router in the IBA subnet.
*
*	The Router object is not thread safe, thus callers must provide
*	serialization.
*
*	This object should be treated as opaque and should be
*	manipulated only through the provided functions.
*
* AUTHOR
*	Hal Rosenstock, Voltaire
*
*********/

/****s* OpenSM: osm_router_tbl_t
*NAME
*       osm_router_tbl_t
*
* DESCRIPTION
*  This object stores Router Table blocks (AdjacentSiteLocalSubnetsTable MADs)
*
* The osm_router_tbl_t object should be treated as opaque and should
* be manipulated only through the provided functions.
*
* SYNOPSIS
*/
typedef struct osm_router_tbl {
        cl_ptr_vector_t blocks;
} osm_router_tbl_t;

/*
* FIELDS
*  blocks
*   The VS defined blocks of router table blocks, updated from the subnet
*
**********/

/****f* OpenSM: osm_router_tbl_construct
* NAME
*  osm_router_tbl_construct
*
* DESCRIPTION
*  Constructs the Router table object
*
* SYNOPSIS
*/
void osm_router_tbl_construct(IN osm_router_tbl_t * p_router_tbl);
/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object.
*
* NOTES
*
*********/

/****f* OpenSM: osm_router_tbl_delete
* NAME
*  osm_router_tbl_delete
*
* DESCRIPTION
*  Deletes all blocks from the Router table
*
* SYNOPSIS
*/
void osm_router_tbl_delete(IN osm_router_tbl_t * p_router_tbl);
/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object.
*
* NOTES
*
*********/

/****f* OpenSM: osm_router_tbl_destroy
* NAME
*  osm_router_tbl_destroy
*
* DESCRIPTION
*  Destroys the Router table object
*
* SYNOPSIS
*/
void osm_router_tbl_destroy(IN osm_router_tbl_t * p_router_tbl);
/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object.
*
* NOTES
*
*********/

/****f* OpenSM: osm_router_tbl_init
* NAME
*  osm_router_tbl_init
*
* DESCRIPTION
*  Inits the Router table object
*
* SYNOPSIS
*/
ib_api_status_t osm_router_tbl_init(IN osm_router_tbl_t * p_router_tbl);
/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object.
*
* NOTES
*
*********/

/****f* OpenSM: osm_router_tbl_get_num_blocks
* NAME
*  osm_router_tbl_get_num_blocks
*
* DESCRIPTION
*  Obtain the number of blocks in the router table
*
* SYNOPSIS
*/
static inline uint16_t
osm_router_tbl_get_num_blocks(IN const osm_router_tbl_t * p_router_tbl)
{
	return ((uint16_t) (cl_ptr_vector_get_size(&p_router_tbl->blocks)));
}

/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object.
*
* RETURN VALUES
*  The number of blocks in the router table
*
* NOTES
*
*********/

/****f* OpenSM: osm_router_tbl_adj_block_get
* NAME
*  osm_router_tbl_adj_block_get
*
* DESCRIPTION
*  Obtain the pointer for a specific adj block
*
* SYNOPSIS
*/
static inline ib_rtr_adj_table_block_t *
osm_router_tbl_adj_block_get(const osm_router_tbl_t * p_router_tbl, uint16_t block)
{
	return ((block < cl_ptr_vector_get_size(&p_router_tbl->blocks)) ?
		(ib_rtr_adj_table_block_t *)cl_ptr_vector_get(
		&p_router_tbl->blocks, block) : NULL);
};

/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object.
*
*  block
*     [in] The block number to get
*
* RETURN VALUES
*  The IB router table, which is one block in the osm router table object.
*  Returns NULL in case of invalid block number.
*
* NOTES
*
*********/

/****f* OpenSM: osm_router_tbl_nh_block_get
* NAME
*  osm_router_tbl_nh_block_get
*
* DESCRIPTION
*  Obtain the pointer for a specific next hop block
*
* SYNOPSIS
*/
static inline ib_rtr_next_hop_table_block_t *
osm_router_tbl_nh_block_get(const osm_router_tbl_t * p_router_tbl, uint16_t block)
{
	return ((block < cl_ptr_vector_get_size(&p_router_tbl->blocks)) ?
		(ib_rtr_next_hop_table_block_t *)cl_ptr_vector_get(
		&p_router_tbl->blocks, block) : NULL);
};

/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object.
*
*  block
*     [in] The block number to get
*
* RETURN VALUES
*  The IB router table, which is one block in the osm router table object.
*  Returns NULL in case of invalid block number.
*
* NOTES
*
*********/

/****f* OpenSM: osm_adj_router_tbl_set
* NAME
*  osm_adj_router_tbl_set
*
* DESCRIPTION
*  Set the adjacent Router table block provided in the Router object.
*
* SYNOPSIS
*/
ib_api_status_t
osm_adj_router_tbl_set(IN osm_router_tbl_t * p_router_tbl,
		       IN uint16_t block,
		       IN ib_rtr_adj_table_block_t * p_tbl);
/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object
*
*  block
*     [in] The block number to set
*
*  p_tbl
*     [in] The IB Router adjacent table block to copy to the object
*
* RETURN VALUES
*  IB_SUCCESS or IB_ERROR
*
* NOTES
*
*********/

/****f* OpenSM: osm_next_hop_router_tbl_set
* NAME
*  osm_next_hop_router_tbl_set
*
* DESCRIPTION
*  Set the next hop Router table block provided in the Router object.
*
* SYNOPSIS
*/
ib_api_status_t
osm_next_hop_router_tbl_set(IN osm_router_tbl_t * p_router_tbl,
			    IN uint16_t block,
			    IN ib_rtr_next_hop_table_block_t * p_tbl);
/*
*  p_router_tbl
*     [in] Pointer to osm_router_tbl_t object
*
*  block
*     [in] The block number to set
*
*  p_tbl
*     [in] IB Router next hop table block to copy to the router table object
*
* RETURN VALUES
*  IB_SUCCESS or IB_ERROR
*
* NOTES
*
*********/

/********************************* END OF ROUTER TABLE ***********************/
/****s* OpenSM: Subnet/osm_router_tbl_data_t
* NAME
*	osm_router_tbl_data_t
*
* DESCRIPTION
*	This struct defines the data to keep on router in routers table
*	This will be used for both adjacent and next hop routers
* SYNOPSIS
*/
typedef struct osm_router_tbl_data {
	cl_fmap_item_t map_item;
	ib_net64_t subnet_prefix;
	ib_net16_t pkey;
	ib_net16_t master_sm_lid;
	boolean_t is_adjacent;
} osm_router_tbl_data_t;
/*
* FIELDS
*	map_item
*		Linkage structure for cl_fmap.  MUST BE FIRST MEMBER!
*
*	subnet_prefix
*		subnet pefix in which router has a "leg"
*
*	pkey
*		pkey on the port of the router in that subnet
*
*	master_sm_lid
*		lid of master sm in that subnet
*
*	is_adjacent
*		An indication if this is adjacent router (if not then this is
*		a next hop router)
*
* SEE ALSO
*********/

/****s* OpenSM: Router/osm_router_t
* NAME
*	osm_router_t
*
* DESCRIPTION
*	Router structure.
*
*	This object should be treated as opaque and should
*	be manipulated only through the provided functions.
*
* SYNOPSIS
*/
typedef struct osm_router {
	cl_map_item_t map_item;
	osm_port_t   *p_port;
	ib_router_info_t router_info;
	osm_router_tbl_t adj_router_tbl;
	osm_router_tbl_t next_hop_router_tbl;
	cl_fmap_t subnet_prefix_tbl;
} osm_router_t;
/*
* FIELDS
*	map_item
*		Linkage structure for cl_qmap.  MUST BE FIRST MEMBER!
*
*	p_port
*		Pointer to the Port object for this router.
*
*	router_info
*		router info for this router.
*
*	adj_router_tbl
*		adjacent router table blocks for this router.
*
*	next_hop_router_tbl
*		next hop router table blocks for this router.
*
*	subnet_prefix_tbl
*		Subnet prefixes and their pkeys of this router.
*		The key of the table is a pair <subnet prefix, pkey>.
* SEE ALSO
*	Router object
*********/

/****f* OpenSM: Router/osm_router_delete
* NAME
*	osm_router_delete
*
* DESCRIPTION
*	Destroys and deallocates the object.
*
* SYNOPSIS
*/
void osm_router_delete(IN OUT osm_router_t ** pp_rtr);
/*
* PARAMETERS
*	p_rtr
*		[in] Pointer to the object to destroy.
*
* RETURN VALUE
*	None.
*
* NOTES
*
* SEE ALSO
*	Router object, osm_router_new
*********/

/****f* OpenSM: Router/osm_router_new
* NAME
*	osm_router_new
*
* DESCRIPTION
*	The osm_router_new function initializes a Router object for use.
*
* SYNOPSIS
*/
osm_router_t *osm_router_new(IN osm_port_t * p_port);
/*
* PARAMETERS
*	p_node
*		[in] Pointer to the node object of this router
*
* RETURN VALUES
*	Pointer to the new initialized router object.
*
* NOTES
*
* SEE ALSO
*	Router object, osm_router_new
*********/

/****f* OpenSM: Router/osm_router_get_port_ptr
* NAME
*	osm_router_get_port_ptr
*
* DESCRIPTION
*	Returns a pointer to the Port object for this router.
*
* SYNOPSIS
*/
static inline osm_port_t *osm_router_get_port_ptr(IN const osm_router_t * p_rtr)
{
	return p_rtr->p_port;
}

/*
* PARAMETERS
*	p_rtr
*		[in] Pointer to an osm_router_t object.
*
* RETURN VALUES
*	Returns a pointer to the Port object for this router.
*
* NOTES
*
* SEE ALSO
*	Router object
*********/

/****f* OpenSM: Router/osm_router_get_node_ptr
* NAME
*	osm_router_get_node_ptr
*
* DESCRIPTION
*	Returns a pointer to the Node object for this router.
*
* SYNOPSIS
*/
static inline osm_node_t *osm_router_get_node_ptr(IN const osm_router_t * p_rtr)
{
	return p_rtr->p_port->p_node;
}

/*
* PARAMETERS
*	p_rtr
*		[in] Pointer to an osm_router_t object.
*
* RETURN VALUES
*	Returns a pointer to the Node object for this router.
*
* NOTES
*
* SEE ALSO
*	Router object
*********/

/****f* OpenSM: Switch/osm_router_set_router_info
* NAME
*  osm_router_set_router_info
*
* DESCRIPTION
*  Updates the router info attribute of this router.
*
* SYNOPSIS
*/
static inline void osm_router_set_router_info(IN osm_router_t * p_rtr,
					      IN const ib_router_info_t * p_ri)
{
	OSM_ASSERT(p_rtr);
	OSM_ASSERT(p_ri);
	p_rtr->router_info = *p_ri;
}
/*
* PARAMETERS
*	p_rtr
*		[in] Pointer to an osm_router_t object.
*
*	p_ri
*		[in] Pointer to router info.
*
* RETURN VALUES
*
* NOTES
*
* SEE ALSO
*	Router object
*********/

/****f* OpenSM: Switch/osm_router_find_pkey
* NAME
*  osm_router_find_pkey
*
* DESCRIPTION
*  Finds pkey that matches the remote gid subnet in the routing table
*  and is configured both on source and on the subnet matching router.
*
* SYNOPSIS
*/
ib_api_status_t osm_router_find_pkey(
	IN osm_subn_t *p_subn,
	IN const osm_alias_guid_t *p_router_alias_guid,
	IN const ib_gid_t *p_remote_gid,
	IN const osm_pkey_tbl_t *pkey_tbl_src,
	IN const osm_pkey_tbl_t *pkey_tbl_dest,
	OUT ib_net16_t *pkey);
/*
* PARAMETERS
*	p_subn
*		[in] Pointer to opensm subnet object.
*
*	p_router_alias_guid
*		[in] Pointer to router alias guid object.
*
*	p_remote_gid
*		[in] pointer to gid in the remote subnet, i.e the destination
*
* 	pkey_tbl_src
* 		[in] the pkey table of the source in the path record
*
* 	pkey_tbl_dest
* 		[i] the pkey table of the inspected router
*
*	pkey
*		[out] pointer to pkey to return
*
* RETURN VALUES
*	Returns success or not found, if the given router is not in the the db.
* NOTES
*
* SEE ALSO
*	Router object
*********/

END_C_DECLS
#endif				/* _OSM_ROUTER_H_ */
