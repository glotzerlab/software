/*
 * Copyright (c) 2004-2009 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2002-2005 Mellanox Technologies LTD. All rights reserved.
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

/****h* OpenSM/DB-Pack
* NAME
*	Database Types
*
* DESCRIPTION
*	This module provides packing and unpacking of the database
*  storage into specific types.
*
*  The following domains/conversions are supported:
*  guid2lid - key is a guid and data is a lid.
*
* AUTHOR
*	Eitan Zahavi, Mellanox Technologies LTD
*
*********/

#ifndef _OSM_DB_PACK_H_
#define _OSM_DB_PACK_H_

#include <opensm/osm_db.h>

#ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS   }
#else				/* !__cplusplus */
#  define BEGIN_C_DECLS
#  define END_C_DECLS
#endif				/* __cplusplus */

BEGIN_C_DECLS
/****f* OpenSM: DB-Pack/osm_db_guid2lid_init
* NAME
*	osm_db_guid2lid_init
*
* DESCRIPTION
*	Initialize a domain for the guid2lid table
*
* SYNOPSIS
*/
static inline osm_db_domain_t *osm_db_guid2lid_init(IN osm_db_t * p_db)
{
	return (osm_db_domain_init(p_db, "guid2lid"));
}

/*
* PARAMETERS
*	p_db
*		[in] Pointer to the database object to construct
*
* RETURN VALUES
*	The pointer to the new allocated domain object or NULL.
*
* NOTE: DB domains are destroyed by the osm_db_destroy
*
* SEE ALSO
*	Database, osm_db_init, osm_db_destroy
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2lid_init
* NAME
*	osm_db_guid2lid_init
*
* DESCRIPTION
*	Initialize a domain for the guid2lid table
*
* SYNOPSIS
*/
typedef struct osm_db_guid_elem {
	cl_list_item_t item;
	uint64_t guid;
} osm_db_guid_elem_t;
/*
* FIELDS
*	item
*		required for list manipulations
*
*  guid
*
************/

/****f* OpenSM: DB-Pack/osm_db_guid2lid_guids
* NAME
*	osm_db_guid2lid_guids
*
* DESCRIPTION
*	Provides back a list of guid elements.
*
* SYNOPSIS
*/
int osm_db_guid2lid_guids(IN osm_db_domain_t * p_g2l,
			  OUT cl_qlist_t * p_guid_list);
/*
* PARAMETERS
*	p_g2l
*		[in] Pointer to the guid2lid domain
*
*  p_guid_list
*     [out] A quick list of guid elements of type osm_db_guid_elem_t
*
* RETURN VALUES
*	0 if successful
*
* NOTE: The output qlist should be initialized before calling this function.
*       The caller is responsible for freeing the items in the list, and
*       destroying the list.
*
* SEE ALSO
* osm_db_guid2lid_init, osm_db_guid2lid_guids, osm_db_guid2lid_get
* osm_db_guid2lid_set, osm_db_guid2lid_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2lid_get
* NAME
*	osm_db_guid2lid_get
*
* DESCRIPTION
*	Get a lid range by given guid.
*
* SYNOPSIS
*/
int osm_db_guid2lid_get(IN osm_db_domain_t * p_g2l, IN uint64_t guid,
			OUT uint16_t * p_min_lid, OUT uint16_t * p_max_lid);
/*
* PARAMETERS
*	p_g2l
*		[in] Pointer to the guid2lid domain
*
*  guid
*     [in] The guid to look for
*
*  p_min_lid
*     [out] Pointer to the resulting min lid in host order.
*
*  p_max_lid
*     [out] Pointer to the resulting max lid in host order.
*
* RETURN VALUES
*	0 if successful. The lid will be set to 0 if not found.
*
* SEE ALSO
* osm_db_guid2lid_init, osm_db_guid2lid_guids
* osm_db_guid2lid_set, osm_db_guid2lid_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2lid_set
* NAME
*	osm_db_guid2lid_set
*
* DESCRIPTION
*	Set a lid range for the given guid.
*
* SYNOPSIS
*/
int osm_db_guid2lid_set(IN osm_db_domain_t * p_g2l, IN uint64_t guid,
			IN uint16_t min_lid, IN uint16_t max_lid);
/*
* PARAMETERS
*	p_g2l
*		[in] Pointer to the guid2lid domain
*
*  guid
*     [in] The guid to look for
*
*  min_lid
*     [in] The min lid value to set
*
*  max_lid
*     [in] The max lid value to set
*
* RETURN VALUES
*	0 if successful
*
* SEE ALSO
* osm_db_guid2lid_init, osm_db_guid2lid_guids
* osm_db_guid2lid_get, osm_db_guid2lid_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2lid_delete
* NAME
*	osm_db_guid2lid_delete
*
* DESCRIPTION
*	Delete the entry by the given guid
*
* SYNOPSIS
*/
int osm_db_guid2lid_delete(IN osm_db_domain_t * p_g2l, IN uint64_t guid);
/*
* PARAMETERS
*	p_g2l
*		[in] Pointer to the guid2lid domain
*
*  guid
*     [in] The guid to look for
*
* RETURN VALUES
*	0 if successful otherwise 1
*
* SEE ALSO
* osm_db_guid2lid_init, osm_db_guid2lid_guids
* osm_db_guid2lid_get, osm_db_guid2lid_set
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2mkey_init
* NAME
*	osm_db_guid2mkey_init
*
* DESCRIPTION
*	Initialize a domain for the guid2mkey table
*
* SYNOPSIS
*/
static inline osm_db_domain_t *osm_db_guid2mkey_init(IN osm_db_t * p_db)
{
	return osm_db_domain_init(p_db, "guid2mkey");
}

/*
* PARAMETERS
*	p_db
*		[in] Pointer to the database object to construct
*
* RETURN VALUES
*	The pointer to the new allocated domain object or NULL.
*
* NOTE: DB domains are destroyed by the osm_db_destroy
*
* SEE ALSO
*	Database, osm_db_init, osm_db_destroy
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2mkey_guids
* NAME
*	osm_db_guid2mkey_guids
*
* DESCRIPTION
*	Provides back a list of guid elements.
*
* SYNOPSIS
*/
int osm_db_guid2mkey_guids(IN osm_db_domain_t * p_g2m,
			  OUT cl_qlist_t * p_guid_list);
/*
* PARAMETERS
*	p_g2l
*		[in] Pointer to the guid2mkey domain
*
*  p_guid_list
*     [out] A quick list of guid elements of type osm_db_guid_elem_t
*
* RETURN VALUES
*	0 if successful
*
* NOTE: The output qlist should be initialized before calling this function.
*       The caller is responsible for freeing the items in the list, and
*       destroying the list.
*
* SEE ALSO
* osm_db_guid2mkey_init, osm_db_guid2mkey_guids, osm_db_guid2mkey_get
* osm_db_guid2mkey_set, osm_db_guid2mkey_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2mkey_get
* NAME
*	osm_db_guid2mkey_get
*
* DESCRIPTION
*	Get the mkey for the given guid.
*
* SYNOPSIS
*/
int osm_db_guid2mkey_get(IN osm_db_domain_t * p_g2m, IN uint64_t guid,
			 OUT uint64_t * p_mkey);
/*
* PARAMETERS
*	p_g2m
*		[in] Pointer to the guid2mkey domain
*
*  guid
*     [in] The guid to look for
*
*  p_mkey
*     [out] Pointer to the resulting mkey in host order.
*
* RETURN VALUES
*	0 if successful. The lid will be set to 0 if not found.
*
* SEE ALSO
* osm_db_guid2mkey_init, osm_db_guid2mkey_guids
* osm_db_guid2mkey_set, osm_db_guid2mkey_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2mkey_set
* NAME
*	osm_db_guid2mkey_set
*
* DESCRIPTION
*	Set the mkey for the given guid.
*
* SYNOPSIS
*/
int osm_db_guid2mkey_set(IN osm_db_domain_t * p_g2m, IN uint64_t guid,
			 IN uint64_t mkey);
/*
* PARAMETERS
*	p_g2m
*		[in] Pointer to the guid2mkey domain
*
*  guid
*     [in] The guid to look for
*
*  mkey
*     [in] The mkey value to set, in host order
*
* RETURN VALUES
*	0 if successful
*
* SEE ALSO
* osm_db_guid2mkey_init, osm_db_guid2mkey_guids
* osm_db_guid2mkey_get, osm_db_guid2mkey_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_guid2mkey_delete
* NAME
*	osm_db_guid2mkey_delete
*
* DESCRIPTION
*	Delete the entry by the given guid
*
* SYNOPSIS
*/
int osm_db_guid2mkey_delete(IN osm_db_domain_t * p_g2m, IN uint64_t guid);
/*
* PARAMETERS
*	p_g2m
*		[in] Pointer to the guid2mkey domain
*
*  guid
*     [in] The guid to look for
*
* RETURN VALUES
*	0 if successful otherwise 1
*
* SEE ALSO
* osm_db_guid2mkey_init, osm_db_guid2mkey_guids
* osm_db_guid2mkey_get, osm_db_guid2mkey_set
*********/

/****f* OpenSM: DB-Pack/osm_db_neighbor_init
* NAME
*	osm_db_neighbor_init
*
* DESCRIPTION
*	Initialize a domain for the neighbors table
*
* SYNOPSIS
*/
static inline osm_db_domain_t *osm_db_neighbor_init(IN osm_db_t * p_db)
{
	return osm_db_domain_init(p_db, "neighbors");
}

/*
* PARAMETERS
*	p_db
*		[in] Pointer to the database object to construct
*
* RETURN VALUES
*	The pointer to the new allocated domain object or NULL.
*
* NOTE: DB domains are destroyed by the osm_db_destroy
*
* SEE ALSO
*	Database, osm_db_init, osm_db_destroy
*********/

/****f* OpenSM: DB-Pack/osm_db_neighbor_elem
* NAME
*	osm_db_neighbor_elem
*
* DESCRIPTION
*	Initialize a domain for the neighbor table
*
* SYNOPSIS
*/
typedef struct osm_db_neighbor_elem {
	cl_list_item_t item;
	uint64_t guid;
	uint8_t portnum;
} osm_db_neighbor_elem_t;
/*
* FIELDS
*	item
*		required for list manipulations
*
*  guid
*  portnum
*
************/

/****f* OpenSM: DB-Pack/osm_db_neighbor_guids
* NAME
*	osm_db_neighbor_guids
*
* DESCRIPTION
*	Provides back a list of neighbor elements.
*
* SYNOPSIS
*/
int osm_db_neighbor_guids(IN osm_db_domain_t * p_neighbor,
			  OUT cl_qlist_t * p_guid_list);
/*
* PARAMETERS
*	p_neighbor
*		[in] Pointer to the neighbor domain
*
*  p_guid_list
*     [out] A quick list of neighbor elements of type osm_db_neighbor_elem_t
*
* RETURN VALUES
*	0 if successful
*
* NOTE: The output qlist should be initialized before calling this function.
*       The caller is responsible for freeing the items in the list, and
*       destroying the list.
*
* SEE ALSO
* osm_db_neighbor_init, osm_db_neighbor_guids, osm_db_neighbor_get
* osm_db_neighbor_set, osm_db_neighbor_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_neighbor_get
* NAME
*	osm_db_neighbor_get
*
* DESCRIPTION
*	Get a neighbor's guid by given guid/port.
*
* SYNOPSIS
*/
int osm_db_neighbor_get(IN osm_db_domain_t * p_neighbor, IN uint64_t guid1,
			IN uint8_t port1, OUT uint64_t * p_guid2,
			OUT uint8_t * p_port2);
/*
* PARAMETERS
*	p_neighbor
*		[in] Pointer to the neighbor domain
*
*  guid1
*     [in] The guid to look for
*
*  port1
*     [in] The port to look for
*
*  p_guid2
*     [out] Pointer to the resulting guid of the neighboring port.
*
*  p_port2
*     [out] Pointer to the resulting port of the neighboring port.
*
* RETURN VALUES
*	0 if successful. The lid will be set to 0 if not found.
*
* SEE ALSO
* osm_db_neighbor_init, osm_db_neighbor_guids
* osm_db_neighbor_set, osm_db_neighbor_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_neighbor_set
* NAME
*	osm_db_neighbor_set
*
* DESCRIPTION
*	Set up a relationship between two ports
*
* SYNOPSIS
*/
int osm_db_neighbor_set(IN osm_db_domain_t * p_neighbor, IN uint64_t guid1,
			IN uint8_t port1, IN uint64_t guid2, IN uint8_t port2);
/*
* PARAMETERS
*	p_neighbor
*		[in] Pointer to the neighbor domain
*
*  guid1
*     [in] The first guid in the relationship
*
*  port1
*     [in] The first port in the relationship
*
*  guid2
*     [in] The second guid in the relationship
*
*  port2
*     [in] The second port in the relationship
*
* RETURN VALUES
*	0 if successful
*
* SEE ALSO
* osm_db_neighbor_init, osm_db_neighbor_guids
* osm_db_neighbor_get, osm_db_neighbor_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_neighbor_delete
* NAME
*	osm_db_neighbor_delete
*
* DESCRIPTION
*	Delete the relationship between two ports
*
* SYNOPSIS
*/
int osm_db_neighbor_delete(IN osm_db_domain_t * p_neighbor,
			   IN uint64_t guid, IN uint8_t port);
/*
* PARAMETERS
*	p_neighbor
*		[in] Pointer to the neighbor domain
*
*  guid
*     [in] The guid to look for
*
*  port
*     [in] The port to look for
*
* RETURN VALUES
*	0 if successful otherwise 1
*
* SEE ALSO
* osm_db_neighbor_init, osm_db_neighbor_guids
* osm_db_neighbor_get, osm_db_neighbor_set
*********/

/****f* OpenSM: DB-Pack/osm_db_an2an_elem
* NAME
*	osm_db_an2an_elem
*
* DESCRIPTION
*	Object representation of an2an cache entry. An an2an entry is keyed by
*	a pair of adjacent switch guids, and contains the port numbers through
*	which each switch routes to the 2nd switch's AN.
*
* SYNOPSIS
*/
typedef struct osm_db_an2an_elem {
	cl_list_item_t item;
	uint64_t guid1;
	uint64_t guid2;
	uint8_t portnum1;
	uint8_t portnum2;
} osm_db_an2an_elem_t;
/*
* FIELDS
*	item
*		required for list manipulations
*	guid1
*		guid of the first switch
*	guid2
*		guid of the second switch
*	portnum1
*		port number through which routing from the first switch to the
*		second aggregation node takes place
*	portnum2
*		port number through which routing from the second switch to the
*		first aggregation node takes place
*
************/

/****f* OpenSM: DB-Pack/osm_db_an2an_get_all
* NAME
*	osm_db_an2an_get_all
*
* DESCRIPTION
*	Provides a list of an2an elements.
*
* SYNOPSIS
*/
int osm_db_an2an_get_all(IN osm_db_domain_t * p_domain,
			 OUT cl_qlist_t * p_elements);
/*
* PARAMETERS
*  p_domain
*     [in] Pointer to the an2an domain
*
*  p_elements
*     [out] A quick list of an2an elements of type osm_db_an2an_elem_t
*
* RETURN VALUES
*	0 if successful
*
* NOTE: The output qlist should be initialized before calling this function.
*       The caller is responsible for freeing the items in the list, and
*       destroying the list.
*
* SEE ALSO
* osm_db_an2an_get, osm_db_an2an_set, osm_db_an2an_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_an2an_get
* NAME
*	osm_db_an2an_get
*
* DESCRIPTION
*	Get the an2an route for the given switches (guids). The route is defined
*	as the port numbers (port1, port2) through which each switch routes to
*	the 2nd switch's AN.
*
* SYNOPSIS
*/
int osm_db_an2an_get(IN osm_db_domain_t * p_domain,
		     IN uint64_t sw_guid1, IN uint64_t sw_guid2,
		     OUT uint8_t * port1, OUT uint8_t * port2);
/*
* PARAMETERS
*   p_domain
*     [in] Pointer to the an2an domain
*
*  sw_guid1
*     [in] The first switch guid.
*
*  sw_guid2
*     [in] The second switch guid
*
*  port1
*     [out] Pointer to the stored route's first port number
*
*  port2
*     [out] Pointer to the stored route's second port number
*
* RETURN VALUES
*	0 if successful. In case of a failure, the value of port1/port2 is
*	undefined.
*
* SEE ALSO
* osm_db_an2an_get_all, osm_db_an2an_set, osm_db_an2an_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_an2an_set
* NAME
*	osm_db_an2an_set
*
* DESCRIPTION
*	Set the an2an route for the given switches (guids). The route is defined
*	as the port numbers (port1, port2) through which each switch routes to
*	the 2nd switch's AN.
*
* SYNOPSIS
*/
int osm_db_an2an_set(IN osm_db_domain_t * p_domain,
		     IN uint64_t sw_guid1, IN uint64_t sw_guid2,
		     IN uint8_t port1, IN uint8_t port2);
/*
* PARAMETERS
*  p_domain
*     [in] Pointer to the an2an domain
*
*  sw_guid1
*     [in] The first switch guid
*
*  sw_guid2
*     [in] The second switch guid
*
*  port1
*     [in] The stored route's first port number
*
*  port2
*     [in] The stored route's second port number
*
* RETURN VALUES
*	0 if successful
*
* SEE ALSO
* osm_db_an2an_get_all, osm_db_an2an_get, osm_db_an2an_delete
*********/

/****f* OpenSM: DB-Pack/osm_db_an2an_delete
* NAME
*	osm_db_an2an_delete
*
* DESCRIPTION
*	Delete an an2an route for given switch guids
*
* SYNOPSIS
*/
int osm_db_an2an_delete(IN osm_db_domain_t * p_domain,
			IN uint64_t sw_guid1, IN uint64_t sw_guid2);
/*
* PARAMETERS
*  p_domain
*     [in] Pointer to the an2an domain
*
*  sw_guid1
*     [in] The first switch guid
*
*  sw_guid2
*     [in] The second switch guid
*
* RETURN VALUES
*	0 if successful otherwise 1
*
* SEE ALSO
* osm_db_an2an_get_all, osm_db_an2an_get, osm_db_an2an_set
*********/

END_C_DECLS
#endif				/* _OSM_DB_PACK_H_ */
