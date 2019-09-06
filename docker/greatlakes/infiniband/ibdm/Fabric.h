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


/*
 * Fabric Utilities Project
 *
 * Data Model Header file
 *
 */

#ifndef IBDM_FABRIC_H
#define IBDM_FABRIC_H

#if HAVE_CONFIG_H
#  include "config.h"
#endif

#include <functional>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <inttypes.h>

using namespace std;

#include <infiniband/ibutils/ibutils_common.h>
#include <infiniband/ibutils/ports_bitset.h>

///////////////////////////////////////////////////////////////////////////////
const char * get_ibdm_version();

// string vectorization (Vectorize.cpp)
std::string compressNames (std::list<std::string> &words);

///////////////////////////////////////////////////////////////////////////////
#define IB_LID_UNASSIGNED 0
#define IB_LFT_UNASSIGNED 255
#define IB_AR_LFT_UNASSIGNED 0xFFFF
#define IB_SLT_UNASSIGNED 255
#define IB_HOP_UNASSIGNED 255
#define IB_NUM_SL 16
#define IB_DROP_VL 15

#define SPLIT_PORTS_SW_NUM_PORTS 80

//maximum number of virtual ports that can be returned in vnode info (not counting port 0)
//the max number of the vport can be 64000
#define IB_MAX_VIRT_NUM_PORTS  64000
//maximum number of physical ports that can be returned in node info (not counting port 0)
#define IB_MAX_PHYS_NUM_PORTS  254
#define IB_MIN_PHYS_NUM_PORTS  1
#define IB_MAX_UCAST_LID       0xBFFF

#define IB_MCAST_STATE_SENDER_ONLY_BIT 0x4
#define IB_MCAST_STATE_SENDER_ONLY_FULL_MEMBER_BIT 0x8

#ifndef PRIx64
#if __WORDSIZE == 64
#define PRIx64 "lx"
#else
#define PRIx64 "llx"
#endif
#endif


#define GET_LID_STEP(lmc) ((lid_t)(1 << lmc))
#define LID_INC(lid,inc) (lid = (lid_t)(lid + inc))

// When system has one mlx, node description will present mlx_0.
// As the max number of mlx in a system is from parsing the node description,
// we need to initialize the number of mlx with the value -1 and not 0, because 0 says
// we have one mlx
#define MLX_NA  -1
///////////////////////////////////////////////////////////////////////////////
//
// STL TYPEDEFS
//
// This section defines typedefs for all the STL containers used by the package

// for comparing strings
struct strless : public binary_function <string, string, bool> {
    bool operator()(const string& x, const string& y) const {
        return (strcmp(x.c_str(), y.c_str()) < 0);
    }
};

typedef vector<int > vec_int;
typedef vector<vec_int > vec_vec_int;
typedef vector<uint8_t > vec_byte;
typedef vector<uint16_t > vec_uint16;
typedef vector<vec_uint16 > vec_vec_uint16;
typedef vector<uint64_t > vec_uint64;
typedef vector<vec_byte > vec_vec_byte;
typedef vector<vec_vec_byte > vec3_byte;
typedef vector< PortsBitset > vec_port_bitset;

typedef vector<phys_port_t > vec_phys_ports;
typedef vector<lid_t > vec_lids;
typedef vector<class IBPort * > vec_pport;
typedef vector<class IBVPort * > vec_pvport;
typedef map< uint16_t, class IBVPort *, less< uint16_t > > map_vportnum_vport;
typedef vector<class IBNode * > vec_pnode;
typedef vector<class VChannel * > vec_pvch;
typedef vector<class CrdRoute > vec_crd_route;
typedef map< string, class IBSysPort *, strless > map_str_psysport;
typedef map< string, class IBNode *, strless > map_str_pnode;
typedef map< string, class IBSystem *, strless > map_str_psys;
typedef map< uint64_t, class IBPort *, less<uint64_t> > map_guid_pport;
typedef map< uint64_t, class IBVPort *, less<uint64_t> > map_guid_pvport;
typedef map< uint64_t, class IBVNode *, less<uint64_t> > map_guid_pvnode;
typedef map< uint64_t, class IBNode *, less<uint64_t> > map_guid_pnode;
typedef map< uint64_t, class IBSystem *, less<uint64_t> > map_guid_psys;
typedef map< uint64_t, string, less<uint64_t> > map_guid_str;
typedef map< string, int, strless > map_str_int;
typedef map< string, string, strless > map_str_str;
typedef list<lid_t > list_lid;
typedef list<class IBPort * > list_pport;
typedef list<class IBNode * > list_pnode;
typedef list<class IBSystem * > list_psystem;
typedef list<class CrdRoute > list_crd_route;
typedef list<int > list_int;
typedef list<unsigned > list_unsigned;
typedef list<char * > list_charp;
typedef list<string > list_str;
typedef list<phys_port_t > list_phys_ports;
typedef vector<list_phys_ports > vec_list_phys_ports;
typedef map< IBNode *, int, less< IBNode *> > map_pnode_int;
typedef map< IBPort *, int, less< IBPort *> > map_pport_int;
typedef map< IBNode *, vec_int, less< IBNode *> > map_pnode_vec_int;
typedef map< IBSystem *, int, less< IBSystem *> > map_psystem_int;
typedef map< string, list_pnode > map_str_list_pnode;
typedef set< uint8_t, less< uint16_t > > set_uint8;
typedef set< uint16_t, less< uint16_t > > set_uint16;
typedef map< IBNode *, rank_t, less< IBNode *> > map_pnode_rank;

typedef map< IBNode *, IBNode * > map_template_pnode;
typedef set< string > set_boards;
typedef set< IBNode * > set_nodes_ptr;
typedef map< IBNode *, PortsBitset, less< IBNode *> >
        map_pnode_ports_bitset;

typedef struct direct_route direct_route_t;
typedef list< pair <IBNode *,direct_route_t *> > direct_route_list;
typedef direct_route_list::iterator direct_route_list_iter;
typedef direct_route_list::const_iterator direct_route_list_const_iter;

typedef pair < u_int16_t, IBVPort * > pair_vportnum_vport;
///////////////////////////////////////////////////////////////////////////////
//
// CONSTANTS
//
#define FABU_LOG_NONE 0x0
#define FABU_LOG_ERROR 0x1
#define FABU_LOG_INFO 0x2
#define FABU_LOG_VERBOSE 0x4
#define IBNODE_UNASSIGNED_RANK 0xFF

#define MAX_PLFT_NUM 3
// DFS constants type
typedef enum {Untouched,Open,Closed} dfs_t;

//
// GLOBALS
//
// Log level should be part of the "main" module
extern uint8_t FabricUtilsVerboseLevel;

void ibdmUseInternalLog();
void ibdmUseCoutLog();
void ibdmClearInternalLog();
char *ibdmGetAndClearInternalLog();


///////////////////////////////////////////////////////////////////////////////
// We only recognize CA or SW nodes
typedef enum {
    IB_UNKNOWN_NODE_TYPE,
    IB_CA_NODE,
    IB_SW_NODE,
    IB_RTR_NODE
} IBNodeType;

static inline IBNodeType char2nodetype(const char *w)
{
    if (!w || (*w == '\0')) return IB_UNKNOWN_NODE_TYPE;
    if (!strcmp(w,"SW"))    return IB_SW_NODE;
    if (!strcmp(w,"CA"))    return IB_CA_NODE;
    if (!strcmp(w,"RTR"))   return IB_RTR_NODE;
    return IB_UNKNOWN_NODE_TYPE;
};

static inline const char * nodetype2char(const IBNodeType w)
{
    switch (w) {
    case IB_SW_NODE:    return("SW");
    case IB_CA_NODE:    return("CA");
    case IB_RTR_NODE:   return("RTR");
    default:            return("UNKNOWN");
    }
};


typedef enum {IB_UNKNOWN_LINK_WIDTH = 0,
              IB_LINK_WIDTH_1X = 1,
              IB_LINK_WIDTH_4X = 2,
              IB_LINK_WIDTH_8X = 4,
              IB_LINK_WIDTH_12X = 8,
              IB_LINK_WIDTH_2X = 0x10,
} IBLinkWidth;

static inline IBLinkWidth char2width(const char *w)
{
    if (!w || (*w == '\0')) return IB_UNKNOWN_LINK_WIDTH;
    if (!strcmp(w,"1x"))    return IB_LINK_WIDTH_1X;
    if (!strcmp(w,"4x"))    return IB_LINK_WIDTH_4X;
    if (!strcmp(w,"8x"))    return IB_LINK_WIDTH_8X;
    if (!strcmp(w,"12x"))   return IB_LINK_WIDTH_12X;
    if (!strcmp(w,"2x"))    return IB_LINK_WIDTH_2X;
    return IB_UNKNOWN_LINK_WIDTH;
};

static inline const char * width2char(const IBLinkWidth w)
{
    switch (w) {
    case IB_LINK_WIDTH_1X:  return("1x");
    case IB_LINK_WIDTH_4X:  return("4x");
    case IB_LINK_WIDTH_8X:  return("8x");
    case IB_LINK_WIDTH_12X: return("12x");
    case IB_LINK_WIDTH_2X:  return("2x");
    default:                return("UNKNOWN");
    }
};


typedef enum {IB_UNKNOWN_LINK_SPEED = 0,
              IB_LINK_SPEED_2_5     = 1,
              IB_LINK_SPEED_5       = 2,
              IB_LINK_SPEED_10      = 4,
              IB_LINK_SPEED_14      = 1 << 8,   /* second byte is for extended ones */
              IB_LINK_SPEED_25      = 2 << 8,   /* second byte is for extended ones */
              IB_LINK_SPEED_50      = 4 << 8,   /* second byte is for extended ones */
              IB_LINK_SPEED_FDR_10  = 1 << 16,  /* third byte is for vendor specific ones */
              IB_LINK_SPEED_EDR_20  = 2 << 16   /* third byte is for vendor specific ones */
} IBLinkSpeed;

#define IB_UNKNOWN_LINK_SPEED_STR    "UNKNOWN"
#define IB_LINK_SPEED_2_5_STR        "2.5"
#define IB_LINK_SPEED_5_STR          "5"
#define IB_LINK_SPEED_10_STR         "10"
#define IB_LINK_SPEED_14_STR         "14"
#define IB_LINK_SPEED_25_STR         "25"
#define IB_LINK_SPEED_50_STR         "50"
#define IB_LINK_SPEED_FDR_10_STR     "FDR10"
#define IB_LINK_SPEED_EDR_20_STR     "EDR20"

static inline const char * speed2char(const IBLinkSpeed s)
{
    switch (s) {
    case IB_LINK_SPEED_2_5:     return(IB_LINK_SPEED_2_5_STR);
    case IB_LINK_SPEED_5:       return(IB_LINK_SPEED_5_STR);
    case IB_LINK_SPEED_10:      return(IB_LINK_SPEED_10_STR);
    case IB_LINK_SPEED_14:      return(IB_LINK_SPEED_14_STR);
    case IB_LINK_SPEED_25:      return(IB_LINK_SPEED_25_STR);
    case IB_LINK_SPEED_50:      return(IB_LINK_SPEED_50_STR);
    case IB_LINK_SPEED_FDR_10:  return(IB_LINK_SPEED_FDR_10_STR);
    case IB_LINK_SPEED_EDR_20:  return(IB_LINK_SPEED_EDR_20_STR);
    default:                    return(IB_UNKNOWN_LINK_SPEED_STR);
    }
};

static inline IBLinkSpeed char2speed(const char *s)
{
    if (!s || (*s == '\0'))                   return IB_UNKNOWN_LINK_SPEED;
    if (!strcmp(s, IB_LINK_SPEED_2_5_STR))    return IB_LINK_SPEED_2_5;
    if (!strcmp(s, IB_LINK_SPEED_5_STR))      return IB_LINK_SPEED_5;
    if (!strcmp(s, IB_LINK_SPEED_10_STR))     return IB_LINK_SPEED_10;
    if (!strcmp(s, IB_LINK_SPEED_14_STR))     return IB_LINK_SPEED_14;
    if (!strcmp(s, IB_LINK_SPEED_25_STR))     return IB_LINK_SPEED_25;
    if (!strcmp(s, IB_LINK_SPEED_50_STR))     return IB_LINK_SPEED_50;
    if (!strcmp(s, IB_LINK_SPEED_FDR_10_STR)) return IB_LINK_SPEED_FDR_10;
    if (!strcmp(s, IB_LINK_SPEED_EDR_20_STR)) return IB_LINK_SPEED_EDR_20;
    return IB_UNKNOWN_LINK_SPEED;
};

static inline IBLinkSpeed extspeed2speed(uint8_t ext_speed)
{
    switch (ext_speed) {
    case 1 /* IB_LINK_SPEED_14 >> 8 */: return IB_LINK_SPEED_14;
    case 2 /* IB_LINK_SPEED_25 >> 8 */: return IB_LINK_SPEED_25;
    case 4 /* IB_LINK_SPEED_50 >> 8 */: return IB_LINK_SPEED_50;
    default:                            return IB_UNKNOWN_LINK_SPEED;
    }
};

static inline IBLinkSpeed mlnxspeed2speed(uint8_t mlnx_speed)
{
    switch (mlnx_speed) {
    case 1 /* IB_LINK_SPEED_FDR_10 >> 16 */:    return IB_LINK_SPEED_FDR_10;
    case 2 /* IB_LINK_SPEED_EDR_20 >> 16 */:    return IB_LINK_SPEED_EDR_20;
    default:                                    return IB_UNKNOWN_LINK_SPEED;
    }
};

//enum for retransmission mode
typedef enum {
    RETRANS_NO_RETRANS          = 0,
    RETRANS_LLR_ACTIVE_CELL_64  = 1,
    RETRANS_LLR_ACTIVE_CELL_128 = 2,
    RETRANS_PLR                 = 3
} EnRetransmissionMode;

static inline unsigned int llr_active_cell2size(u_int8_t active_cell)
{
    switch (active_cell) {
    case RETRANS_LLR_ACTIVE_CELL_64:
        return 64;
    case RETRANS_LLR_ACTIVE_CELL_128:
        return 128;
    case RETRANS_NO_RETRANS: default:
        return 0;
    }
};

#define RETRANS_MODE_NO_RETRANS_STR "NO-RTR"
#define RETRANS_MODE_LLR64_STR      "LLR64"
#define RETRANS_MODE_LLR128_STR     "LLR128"
#define RETRANS_MODE_PLR_STR        "PLR"
#define RETRANS_MODE_NA             "N/A"

static inline const char * retransmission2char(const EnRetransmissionMode r)
{
    switch (r) {
    case RETRANS_NO_RETRANS:
        return (RETRANS_MODE_NO_RETRANS_STR);
    case RETRANS_LLR_ACTIVE_CELL_64:
        return (RETRANS_MODE_LLR64_STR);
    case RETRANS_LLR_ACTIVE_CELL_128:
        return(RETRANS_MODE_LLR128_STR);
    case RETRANS_PLR:
        return(RETRANS_MODE_PLR_STR);
    default:
        return(RETRANS_MODE_NA);
    }
};

typedef enum {IB_UNKNOWN_PORT_STATE = 0,
              IB_PORT_STATE_DOWN = 1,
              IB_PORT_STATE_INIT = 2,
              IB_PORT_STATE_ARM = 3,
              IB_PORT_STATE_ACTIVE = 4
} IBPortState;

static inline IBPortState char2portstate(const char *w)
{
    if (!w || (*w == '\0')) return IB_UNKNOWN_PORT_STATE;
    if (!strcmp(w,"DOWN"))  return IB_PORT_STATE_DOWN;
    if (!strcmp(w,"INI"))   return IB_PORT_STATE_INIT;
    if (!strcmp(w,"ARM"))   return IB_PORT_STATE_ARM;
    if (!strcmp(w,"ACT"))   return IB_PORT_STATE_ACTIVE;
    return IB_UNKNOWN_PORT_STATE;
};

static inline const char * portstate2char(const IBPortState w)
{
    switch (w)
    {
    case IB_PORT_STATE_DOWN:    return("DOWN");
    case IB_PORT_STATE_INIT:    return("INI");
    case IB_PORT_STATE_ARM:     return("ARM");
    case IB_PORT_STATE_ACTIVE:  return("ACT");
    default:                    return("UNKNOWN");
    }
};


static inline string guid2str(uint64_t guid) {
    char buff[19];
    sprintf(buff, "0x%016" PRIx64 , guid);
    return buff;
};

//Represents the available FEC Modes, that are presented
//in Mlnx Extended Port Info FECModeActive field
typedef enum {
    IB_FEC_NO_FEC               = 0,
    IB_FEC_FIRECODE_FEC         = 1,
    IB_FEC_RS_FEC               = 2,
    IB_FEC_LL_RS_FEC            = 3,
    IB_FEC_RS_FEC_544_514       = 4,
    //5-7 Reserved
    IB_FEC_MLNX_STRONG_RS_FEC   = 8,
    IB_FEC_MLNX_LL_RS_FEC       = 9,
    IB_FEC_MLNX_ADAPTIVE_RS_FEC = 10,
    IB_FEC_MLNX_COD_FEC         = 11,
    IB_FEC_MLNX_ZL_FEC          = 12,
    IB_FEC_MLNX_RS_544_514_PLR  = 13,
    IB_FEC_MLNX_RS_271_257_PLR  = 14,
    //15 Reserved
    IB_FEC_NA                   = 0xff
} IBFECMode;

#define IB_FEC_NO_FEC_STR                "NO-FEC"
#define IB_FEC_FIRECODE_FEC_STR          "FIRECODE"
#define IB_FEC_RS_FEC_STR                "STD-RS"
#define IB_FEC_LL_RS_FEC_STR             "STD-LL-RS"
#define IB_FEC_MLNX_STRONG_RS_FEC_STR    "MLNX-STRONG-RS"
#define IB_FEC_MLNX_LL_RS_FEC_STR        "MLNX-LL-RS"
#define IB_FEC_MLNX_ADAPTIVE_RS_FEC_STR  "MLNX-ADAPT-RS"
#define IB_FEC_MLNX_COD_FEC_STR          "MLNX-ZL-FEC"
#define IB_FEC_NA_STR                    "N/A"

static inline const char * fec2char(const IBFECMode f)
{
    switch (f) {
    case IB_FEC_NO_FEC:               return(IB_FEC_NO_FEC_STR);
    case IB_FEC_FIRECODE_FEC:         return(IB_FEC_FIRECODE_FEC_STR);
    case IB_FEC_RS_FEC:               return(IB_FEC_RS_FEC_STR);
    case IB_FEC_LL_RS_FEC:            return(IB_FEC_LL_RS_FEC_STR);
    case IB_FEC_MLNX_STRONG_RS_FEC:   return(IB_FEC_MLNX_STRONG_RS_FEC_STR);
    case IB_FEC_MLNX_LL_RS_FEC:       return(IB_FEC_MLNX_LL_RS_FEC_STR);
    case IB_FEC_MLNX_ADAPTIVE_RS_FEC: return(IB_FEC_MLNX_ADAPTIVE_RS_FEC_STR);
    case IB_FEC_MLNX_COD_FEC:         return(IB_FEC_MLNX_COD_FEC_STR);
    case IB_FEC_NA: default:          return(IB_FEC_NA_STR);
    }
};

static inline IBFECMode fec_mask2value(u_int16_t mask)
{
    switch (mask) {
    case 0x1:    return(IB_FEC_NO_FEC);
    case 0x2:    return(IB_FEC_FIRECODE_FEC);
    case 0x4:    return(IB_FEC_RS_FEC);
    case 0x8:    return(IB_FEC_LL_RS_FEC);
    default:     return(IB_FEC_NA);
    }
}

//return true for any type of RS-FEC fec mode
static inline bool isRSFEC(const IBFECMode f)
{
    switch (f) {
    case IB_FEC_RS_FEC:
    case IB_FEC_LL_RS_FEC:
    case IB_FEC_MLNX_STRONG_RS_FEC:
    case IB_FEC_MLNX_LL_RS_FEC:
    case IB_FEC_MLNX_ADAPTIVE_RS_FEC:
    case IB_FEC_MLNX_COD_FEC:
        return (true);

    case IB_FEC_NO_FEC:
    case IB_FEC_FIRECODE_FEC:
    case IB_FEC_NA:
    default:
        return (false);
    }
}

static inline bool IsPortStateDown(IBPortState s) {
    switch (s) {
        case IB_PORT_STATE_INIT:
        case IB_PORT_STATE_ARM:
        case IB_PORT_STATE_ACTIVE:
            return false;
        case IB_PORT_STATE_DOWN:
        // unknown stage is consider as down
        case IB_UNKNOWN_PORT_STATE:
        default:
            return true;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// Multicast SA Info
//
class McastGroupInfo;
class McastGroupMemberInfo;
typedef map< lid_t, class McastGroupInfo, less<uint64_t> > map_mcast_groups;
typedef pair< map_mcast_groups::iterator, bool > McastGroupMapInsertRes;
typedef map< IBPort *, class McastGroupMemberInfo, less< IBPort *> > map_mcast_members;
typedef pair< map_mcast_members::iterator, bool > McastMemberMapInsertRes;

class McastGroupInfo {
public:
    map_mcast_members m_members;
};

// We may have several entries(reflected in the opensm-sa.dump file)
// of the same port, for the same mlid, with different is_sender_only
// flag and sl.
// We save a global is_sender_only flag (not per sl) which is the
// sum of all is_sender_only flags
class McastGroupMemberInfo {
public:
    set_uint8 m_sls;
    bool is_sender_only;
};



///////////////////////////////////////////////////////////////////////////////
//
// Virtual Channel class
// Used for credit loops verification
//
class VChannel;

class CrdRoute {
public:
    VChannel *m_pvch;
    lid_t m_slid;
    lid_t m_dlid;
    //algorithm optimization
    //if dlid is same as last dlid and sl is same as last sl
    //no need to continue checking this flow
    lid_t m_lastDlid;
    u_int16_t m_lastSLs;

    // Constructor
    CrdRoute():m_pvch(NULL), m_slid(0), m_dlid(0),
        m_lastDlid(0),m_lastSLs(0) {}
    CrdRoute(VChannel *pvch, lid_t slid, lid_t dlid):
        m_pvch(pvch), m_slid(slid), m_dlid(dlid),
        m_lastDlid(0), m_lastSLs(0){}
    CrdRoute(VChannel *pvch, lid_t slid, lid_t dlid, u_int8_t sl):
        m_pvch(pvch), m_slid(slid), m_dlid(dlid),
        m_lastDlid(dlid), m_lastSLs((u_int16_t)(1 << sl)){}

};

class VChannel {
    //vec_pvch depend;    // Vector of dependencies
    vec_crd_route depend;    // Vector of dependencies
    dfs_t    flag;      // DFS state
public:
    IBPort  *pPort;
    int vl;

    // Constructor
    VChannel(IBPort * p, int v) {
        flag = Untouched;
        pPort = p;
        vl = v;
    };

    //Getters/Setters
    inline void setDependSize(int numDepend) {
        if (depend.size() != (unsigned)numDepend) {
            depend.resize(numDepend);
            /*
            for (int i=0;i<numDepend;i++) {
                depend[i] = NULL;
            }
            */
        }
    };
    inline int getDependSize() {
        return (int)depend.size();
    };

    inline dfs_t getFlag() {
        return flag;
    };
    inline void setFlag(dfs_t f) {
        flag = f;
    };

    inline void setDependency(int i,VChannel* p, lid_t slid, lid_t dlid) {
        if(depend[i].m_pvch == NULL)
            depend[i]=CrdRoute(p,slid,dlid);
    };

    //return 0 if add new Dependency
    //return 1 if set new dlid or new sl
    //return 2 if nothing was changed
    inline int setDependency(int i,VChannel* p, lid_t slid, lid_t dlid,
                              u_int8_t sl) {
        if(depend[i].m_pvch == NULL){
            depend[i]=CrdRoute(p,slid,dlid, sl);
            return 0;
        }

        u_int16_t slMask = (u_int16_t)(1 << sl);

        if (depend[i].m_lastDlid != dlid) {
            depend[i].m_lastDlid = dlid;
            depend[i].m_lastSLs = slMask;
            return 1;
        }

        if (!(depend[i].m_lastSLs | slMask)) {
            depend[i].m_lastSLs =
                (u_int16_t)(depend[i].m_lastSLs | slMask);
            return 1;
        }

        return 2;
    };
    inline CrdRoute & getDependency(int i) {
        return depend[i];
    };
    inline VChannel* getDependencyPvch(int i) {
        return depend[i].m_pvch;
    };
};


///////////////////////////////////////////////////////////////////////////////
//
// IB Port class.
// This is not the "End Node" but the physical port of
// a node.
//
class IBPort {
    uint64_t        guid;           // The port GUID (on SW only on Port0)
    IBLinkWidth     width;          // The link width of the port
    IBLinkSpeed     speed;          // The link speed of the port
    IBPortState     port_state;     // The state of the port
    bool            in_sub_fabric;
    IBFECMode       fec_mode;       // The FEC mode of the port
public:
    class IBPort    *p_remotePort;  // Port connected on the other side of link
    class IBSysPort *p_sysPort;     // The system port (if any) connected to
    class IBNode    *p_node;        // The node the port is part of.
    vec_pvch        channels;       // Virtual channels associated with the port
    phys_port_t     num;            // Physical ports are identified by number.
    lid_t           base_lid;       // The base lid assigned to the port.
    uint8_t         lmc;            // The LMC assigned to the port (0 <= lmc < 8)
    unsigned int    counter1;       // a generic value to be used by various algorithms
    unsigned int    counter2;       // a generic value to be used by various algorithms
    u_int32_t       createIndex;    // Port index, we will use it to create vectors of extended
                                    // info regarding this node and access the info in O(1)
    map_vportnum_vport  VPorts;     // map vport number to vports ,we use map because only not down vports are in the map

    // constructor
    IBPort(IBNode *p_nodePtr, phys_port_t number);

    // destructor:
    ~IBPort();

    // get the port name
    string getName();

    string numAsString();
    bool isValid();

    // if the node isn't in sub cluster then the port is also not in sub cluster
    bool getInSubFabric();
    void setInSubFabric(bool in_sub_fabric);

    // connect the port to another node port
    void connect(IBPort *p_otherPort);

    // disconnect the port. Return 0 if successful
    int disconnect(int duringSysPortDisconnect = 0);

    inline uint64_t guid_get() {return guid;};
    void guid_set(uint64_t g);

    //get_internal and get_common wraper functions
    //It can occur in the abric that the ports on the link
    //report different speed/width/state. This is illegal situation in the fabric.
    //It means that one of the port's fw is lying, but we don't know which.
    //This is why everywhere that access to speed/width/state is needed,
    //use get_common_speed/width/state (that return the common data on the link)
    //Except when we want to check and report the inconsistency on the link in that data,
    //then use get_internal functions.

    //get internal port state
    IBPortState get_internal_state() { return port_state; }
    //set internal port_state
    void set_internal_state(IBPortState s) { port_state = s; }
    //get common port_state on the port and its peer
    IBPortState get_common_state();

    //get internal port width
    IBLinkWidth get_internal_width() { return width; }
    //set internal port width
    void set_internal_width(IBLinkWidth w) { width = w; }
    //get common port width on the port and its peer
    IBLinkWidth get_common_width();

    //get internal speed
    IBLinkSpeed get_internal_speed() { return speed; }
    //set internal speed
    void set_internal_speed(IBLinkSpeed sp) { speed = sp; }
    //get common port speed on the port and its peer
    IBLinkSpeed get_common_speed();

    void set_internal_data(IBLinkSpeed sp, IBLinkWidth w, IBPortState s) {
        speed = sp;
        width = w;
        port_state = s;
    }

    //Port that is worth reading/checking data, port that is not down,
    //not in undefined state,
    //and is in the scope of the fabric, we currently look at.
    bool is_data_worthy() {
        return ((port_state > IB_PORT_STATE_DOWN) && getInSubFabric());
    }
    IBFECMode get_fec_mode() { return fec_mode; }
    void set_fec_mode(IBFECMode fec) { fec_mode = fec; }
    IBVPort *getVPort(virtual_port_t num) {
        if (num >= VPorts.size() )
            return NULL;
        return VPorts[num];
    }
};



///////////////////////////////////////////////////////////////////////////////
//
// IB VPort class.
// This is the virtual port part of physical port.
// vports are only relevant for HCAs
class IBVPort {
    uint64_t        m_guid;           // The port GUID
    IBPortState     m_vport_state;    // The state of the vport
    class IBFabric *      m_p_fabric;
    // If lid_required is set to 1, the  vport lid assigned by SM
    lid_t           m_vlid;
    class IBPort    *m_p_phys_port;   // The phys port the vport is part of.
    virtual_port_t  m_num;            // The index number in the physical port's vports.

public:


    u_int32_t       createIndex;    // VPort index, we will use it to create vectors of extended
                                    // info regarding this vport and access the info in O(1)
    class IBVNode   *m_p_vnode;       // A pointer to Vnode which this VPort is part of
    // constructor
    IBVPort(IBPort *p_phys_portPtr, virtual_port_t number,
            uint64_t guid, IBPortState vport_state, IBFabric *p_fab);
    // destructor:
    ~IBVPort();

    // get the port name
    string getName();

    inline lid_t get_vlid() const { return m_vlid; }
    void set_vlid(lid_t l) { m_vlid = l; }

    inline uint64_t guid_get() { return m_guid; };
    void guid_set(uint64_t g);

    //get port state
    IBPortState get_state() { return m_vport_state; }
    //set port_state
    void set_state(IBPortState s) { m_vport_state = s; }

    // when creating the VPort we don't know it's VNode yes.
    // so the VNode will be set later
    void setVNodePtr(IBVNode *p_vnode);

    IBVNode *getVNodePtr();

    inline IBPort *getIBPortPtr() { return m_p_phys_port; }
    inline IBFabric *getIBFabricPtr() { return m_p_fabric; }
    inline virtual_port_t getVPortNum() { return m_num; }
};


///////////////////////////////////////////////////////////////////////////////
//
// IB VNode class.
// This is the virtual node part of physical node.
// May have many Virtual HCAs on physical HCA.
class IBVNode {
    uint64_t        guid;           // The port GUID
    class IBFabric  *p_fabric;
    virtual_port_t  numVPorts;
    string          description;           //Description of the vnode

public:
    u_int32_t       createIndex;    // VNode index, we will use it to create vectors of extended
                                    // info regarding this vnode and access the info in O(1)
    map_vportnum_vport  VPorts;     // map vport number to vports ,we use map
                                    // because only not down vports are in the map

    // constructor
    IBVNode(uint64_t guid, IBFabric *p_fab, virtual_port_t np);
    // destructor:
    ~IBVNode();

    inline uint64_t guid_get() { return guid; };

    // get the vnode description
    string getDescription();

    // set the vnode description
    void setDescription(string n);

    //Get the VNode name. Currently returns the vnode description.
    string getName();


    // add vport into VPort
    int addVPort(virtual_port_t num, IBVPort *p_vport);
};

///////////////////////////////////////////////////////////////////////////////
//
// Private App Data
//
typedef union _PrivateAppData {
    void        *ptr;
    uint64_t    val;
} PrivateAppData;

enum SMP_AR_LID_STATE {
    AR_IB_LID_STATE_BOUNDED = 0x0,
    AR_IB_LID_STATE_FREE = 0x1,
    AR_IB_LID_STATE_STATIC = 0x2,
    AR_IB_LID_STATE_LAST
};

//
// AR Group class
//
class ARgrp {
    int subGrpsNum;
    vec_list_phys_ports subGrps;

public:
    ARgrp(int subGrpsNum = 2) :
            subGrpsNum(subGrpsNum) {
        subGrps = vec_list_phys_ports(subGrpsNum);
    }
    virtual ~ARgrp() {
    }

    void setSubGrp(const list_phys_ports& subGrpToSet, int idx) {
        subGrps[idx] = subGrpToSet;
    }
    const list_phys_ports& getSubGrp(int idx) const {
        return subGrps[idx];
    }
    list_phys_ports& operator[](int idx) {
        return subGrps[idx];
    }
    const list_phys_ports& operator[](int idx) const {
        return subGrps[idx];
    }

    bool operator==(const ARgrp& grp2) const {
        return (this->subGrps == grp2.subGrps
                && this->subGrpsNum == grp2.subGrpsNum);
    }
    int getSubGrpsNum() {
        return this->subGrpsNum;
    }

};
//
// IB Node class
//
class IBNode {
    uint64_t        guid;
    uint64_t        sys_guid;       // guid of the system that node is part of
    vec_pport       Ports;          // Vector of all the ports (in index 0 we will put port0 if exist)
    static bool     usePSL;         // true if should use data from PSL
    static u_int8_t maxSL;          //maxSL used in the fabric if usePSL
    static bool     useSLVL;        // true if should use data from SLVL
    vector<bool>    replaceSLsByInVL;

    //PLFT
    bool            pLFTEnabled;
    vec_vec_byte    portSLToPLFTMap;
    vec_uint16      pLFTTop;
    u_int8_t        maxPLFT; //max pLFT ID
    //AR - refers also to FR
    u_int16_t       arGroupTop;
    u_int16_t       arEnableBySLMask;
    u_int8_t        arSubGrpsActive;
    vec_list_phys_ports   arPortGroups;
    u_int16_t       arMaxGroupNumber;
    vec_vec_uint16  arLFT; //arLFT[plft][lid] = portGroup

    //ARmodes + subgroups
    vector< vector<SMP_AR_LID_STATE> > arState; // arState[plft][lid] = lid's state
    map<uint16_t , ARgrp> arGroups; //Adaptive Routing Groups. ( arGroups[ARgroupIdx] = ArGroup )
                                    //Differently from arPortGroups supports division to sub groups.
                                    //Updated by parsing ".far" file

    bool            frEnabled;
    u_int8_t        by_transport_disable;

    bool            in_sub_fabric;

 public:
    string          name;           // Name of the node (instance name of the chip)
    IBNodeType      type;           // Either a CA or SW
    device_id_t     devId;          // The device ID of the node
    uint32_t        revId;          // The device revision Id.
    uint32_t        vendId;         // The device Vendor ID.
    uint8_t         rank;           // The tree level the node is at 0 is root.
    class IBSystem  *p_system;      // What system we belong to
    class IBFabric  *p_fabric;      // What fabric we belong to.
    phys_port_t     numPorts;       // Number of physical ports
    string          attributes;     // Comma-sep string of arbitrary attributes k=v
    string          description;    // Description of the node
    string          orig_description;// Original description,
                                     //when usr map file is given
    vec_vec_byte    MinHopsTable;   // Table describing minimal hop count through
                                    // each port to each target lid
    vec_vec_byte    LFT;            // The LFT of this node (for switches only)
    vec_byte        PSL;            // PSL table (CAxCA->SL mapping) of this node (for CAs only)
    vec3_byte       SLVL;           // SL2VL table of this node (for switches only)
    vec_phys_ports  slvlPortsGroups; //group ports with same optPort-vl-vl value
    vec_port_bitset MFT;            // The Multicast forwarding table
    PrivateAppData  appData1;       // Application Private Data #1
    PrivateAppData  appData2;       // Application Private Data #2
    PrivateAppData  appData3;       // Application Private Data #3
    u_int32_t       createIndex;    // Node index, we will use it to create vectors of extended
                                    // info regarding this node and access the info in O(1)
    bool            toIgnore;
    phys_port_t     numVirtPorts;   // number of ports out of the numPorts that are virtual
                                    // (for these ports there is no checking in topodiff)


    // Constructor
    IBNode(string n, class IBFabric *p_fab, class IBSystem *p_sys,
            IBNodeType t, phys_port_t np);

    // destructor:
    ~IBNode();

    bool getInSubFabric() {return this->in_sub_fabric; }
    void setInSubFabric(bool in_sub_fabric) {
        this->in_sub_fabric = in_sub_fabric;
    }

    // get the node name
    inline const string &getName() { return name; }

    //get original description
    inline const string &getOrigNodeDescription() {
        return orig_description.empty() ? description : orig_description;
    }

    // create a new port by name if required to
    IBPort *makePort(phys_port_t num);

    // get a port by number num = 1..N:
    inline IBPort *getPort(phys_port_t num) {
        if ((type == IB_SW_NODE) && (num == 0))
            return Ports[0];
        if ((num < 1) || (Ports.size() <= num))
            return NULL;
        return Ports[num];
    }

    // Set the min hop for the given port (* is all) lid pair
    void setHops(IBPort *p_port, lid_t lid, uint8_t hops);

    // Get the min number of hops defined for the given port or all
    uint8_t getHops(IBPort *p_port, lid_t lid);

    // Report Hop Table of the given node
    void repHopTable();

    // Scan the node ports and find the first port
    // with min hop to the lid
    IBPort *getFirstMinHopPort(lid_t lid);

    // Set the Linear Forwarding Table:
    void setLFTPortForLid(lid_t lid, phys_port_t portNum, u_int8_t pLFT=0);

    // Set the Switch AR State Table (for the given lid)
    void setARstateForLid(lid_t lid, SMP_AR_LID_STATE state, u_int8_t pLFT = 0);

    //get the AR state for the given lid
    SMP_AR_LID_STATE getARstateForLid(lid_t lid, u_int8_t pLFT = 0) const;

    // Get the LFT for a given lid
    phys_port_t getLFTPortForLid(lid_t lid, phys_port_t port, sl_vl_t slvl) const {
        return getLFTPortForLid(lid, getPLFTMapping(port, slvl));}

    phys_port_t getLFTPortForLid(lid_t lid, u_int8_t pLFT=0) const;
    //unsecure version of getLFTPortForLid
    phys_port_t getLFTEntry(lid_t lid, u_int8_t pLFT=0) {
        return ( LFT[pLFT][lid] );}

    // Resize the Linear Forwarding Table (can be resize with linear top value):
    void resizeLFT(uint16_t newSize, u_int8_t pLFT=0);

    void clearLFT(u_int8_t pLFT) {LFT[pLFT].clear();}

    // Set the PSL table
    void setPSLForLid(lid_t lid, lid_t maxLid, uint8_t sl);

    //set replaceSLsByInVL
    void setSL2VLAct(u_int8_t slvlAct);
    void setVL2VL(u_int8_t sl);

    void getSL2VLCfg(char *line) const;

    //get SL or VL according to replaceSLsByInVL
    u_int8_t getUsedSLOrVL(sl_vl_t slvl) const;

    // Add entry to SL2VL table
    void setSLVL(phys_port_t iport,phys_port_t oport,uint8_t sl, uint8_t vl);

    // Get the PSL table for a given lid
    uint8_t getPSLForLid(lid_t lid);

    // Check if node contains PSL Info:
    bool isValidPSLInfo() { return !(PSL.empty() && usePSL); }
    static uint8_t getMaxSL() { return maxSL; }
    static void setMaxSL(uint8_t sl) { maxSL = max(maxSL, sl); }

    uint8_t getVL(phys_port_t iport, phys_port_t oport, sl_vl_t slvl) const;
    // Get the SL2VL table entry
    void getSLVL(phys_port_t iport, phys_port_t oport,
                                const sl_vl_t &iSLVL, sl_vl_t &oSLVL);

    //check that all SLs leads to valid VLs
    int checkSL2VLTable() const;

    phys_port_t getSLVLPortGroup(phys_port_t port);
    void buildSLVLPortsGroups();

    // Set the Multicast FDB table
    void setMFTPortForMLid(lid_t lid, phys_port_t portNum);
    void setMFTPortForMLid(lid_t lid, uint16_t portMask, uint8_t portGroup);

    // Get the list of ports for the givan MLID from the MFT
    list_phys_ports getMFTPortsForMLid(lid_t lid);

    int getLidAndLMC(phys_port_t portNum, lid_t &lid, uint8_t &lmc);

    inline uint64_t guid_get() const {return guid;};
    void guid_set(uint64_t g);
    inline uint64_t system_guid_get() {return sys_guid;};
    void system_guid_set(uint64_t g);

    //PLFT
    void setPLFTEnabled();
    bool isPLFTEnabled() const {return pLFTEnabled;}
    void setPLFTMapping(phys_port_t port, u_int8_t nSLVL, u_int8_t pLFT) {
        portSLToPLFTMap[port][nSLVL] = pLFT;
        maxPLFT = max(maxPLFT, pLFT);
    }

    void setMaxPLFT(u_int8_t pLFT) { maxPLFT = pLFT; }
    u_int8_t getMaxPLFT() const {return maxPLFT;}

    u_int8_t getPLFTMapping(phys_port_t port, sl_vl_t slvl) const;
    void getPLFTMapping(phys_port_t port, char *plft_line) const;

    void setLFDBTop(u_int8_t pLFT, u_int16_t lfdbTop){pLFTTop[pLFT] = lfdbTop;}
    u_int16_t getLFDBTop(u_int8_t pLFT = 0) const {return pLFTTop[pLFT];}

    //AR
    void setAREnabled(u_int16_t enableBySLMask, u_int8_t subGrpsActive,
                      u_int8_t fr_enabled, u_int8_t by_transp_cap, u_int8_t by_transp_disable) {
        arEnableBySLMask = enableBySLMask;
        arSubGrpsActive = subGrpsActive;
        frEnabled = (bool)fr_enabled;
        by_transport_disable = by_transp_cap ? by_transp_disable : (u_int8_t)0;
    }
    void setAREnabled(u_int8_t sl) {
        arEnableBySLMask =
            (u_int16_t)(arEnableBySLMask | (u_int16_t)(1<< sl));
    }
    bool isFREnabled(){
        return frEnabled;
    }
    u_int8_t getTranspDisable(){
        return by_transport_disable;
    }
    void setFREnabled(){
        frEnabled =  true;
    }
    void setARGroupTop(u_int16_t group_top) {
        arGroupTop = group_top;
        if(arPortGroups.size() <= arGroupTop)
            arPortGroups.resize(arGroupTop + 1);
    }
    //isAREnable also refer to FR
    bool isAREnable() const {return (frEnabled || arEnableBySLMask != 0);}
    bool isARActive(sl_vl_t slvl) const;
    void getARActiveCfg(char *line) const;
    void getARGroupCfg(u_int16_t groupNumber, char *line) const;

    void setARPortGroup(u_int16_t groupNum,
                        list_phys_ports portsList);

    u_int16_t getARSubGrpsActive() {
        return arSubGrpsActive;
    }

    u_int16_t getARGroupTop() {
        return arGroupTop;
    }

    u_int16_t getNonEmptyARGroupNumber() {
        u_int16_t arGroupNum = 0;
        for (u_int16_t grp = 0; grp <= arGroupTop; ++grp) {
            if (!arPortGroups[grp].empty())
                arGroupNum++;
        }
        return arGroupNum;
    }

    u_int16_t getMaxARGroupNumber(){return arMaxGroupNumber;}
    //void IBNode::resizeARPortGroup(size_t size) {arPortGroups.resize(size);}

    void setARLFTPortGroupForLid(lid_t lid, u_int16_t portGroup,
                                 u_int8_t pLFT);
    u_int16_t getARLFTPortGroupForLid(lid_t lid, u_int8_t pLFT) const;
    void getLFTPortListForLid(lid_t lid, u_int8_t pLFT,
                              bool useAR, list_phys_ports &portsList) const ;
    void getLFTPortListForLid(lid_t lid, phys_port_t inPort,
                              sl_vl_t slvl, list_phys_ports &portsList) const;

    void getLFTPortListForLid(phys_port_t staticOutPortNum,
                              u_int16_t portGroup, list_phys_ports &portsList) const;


    void resizeARLFT(uint16_t newSize, u_int8_t pLFT);

    inline phys_port_t numRealPorts() {
        return (this->numPorts >= this->numVirtPorts) ?
                (phys_port_t)(this->numPorts - this->numVirtPorts) :
                (phys_port_t)0;
    }
    inline bool isRealPort(phys_port_t pn) {
        return pn <= this->numRealPorts();
    }

    void resizeARstate(uint16_t newSize, u_int8_t pLFT);

    //AR+ sub Groups
    void setARSubGrp(u_int16_t group, u_int16_t subGroup,
            const list_phys_ports& portsList);

    list_phys_ports& getARSubGrp(u_int16_t group, u_int16_t subGroup) {
        return this->arGroups[group][subGroup];
    }
    ARgrp& getARgroup(u_int16_t grpIdx) {
        return this->arGroups[grpIdx];
    }

};
// Class IBNode

///////////////////////////////////////////////////////////////////////////////
//
// System Port Class
// The System Port is a front pannel entity.
//
class IBSysPort {
public:
    string          name;               // The front pannel name of the port
    class IBSysPort *p_remoteSysPort;   // If connected the other side sys port
    class IBSystem  *p_system;          // System it benongs to
    class IBPort    *p_nodePort;        // The node port it connects to.

    // Constructor
    IBSysPort(string n, class IBSystem *p_sys);

    // destructor:
    ~IBSysPort();

    // connect two SysPorts
    void connectPorts(IBSysPort *p_otherSysPort);

    // connect two SysPorts and two node ports
    void connect(IBSysPort *p_otherSysPort,
            IBLinkWidth width = IB_LINK_WIDTH_4X,
            IBLinkSpeed speed = IB_LINK_SPEED_2_5,
            IBPortState state = IB_PORT_STATE_ACTIVE);

    // disconnect the SysPort (and ports). Return 0 if successful
    int disconnect(int duringPortDisconnect = 0);
};

///////////////////////////////////////////////////////////////////////////////

//typedef enum {IB_SYS_OK, IB_SYS_MOD, IB_SYS_NEW} IBSysTypeDesc;

///////////////////////////////////////////////////////////////////////////////
//
// IB System Class
// This is normally derived into a system specific class
//
class IBSystem {
public:
    string              name;       // the "host" name of the system
    string              type;       // what is the type i.e. Cougar, Buffalo etc
    string              cfg;        // configuration string modifier
    class IBFabric      *p_fabric;  // fabric belongs to
    map_str_psysport    PortByName; // A map provising pointer to the SysPort by name
    map_str_pnode       NodeByName; // All the nodes belonging to this system.
    bool                newDef;     // system without SysDef
    bool                sys_mlx_nd_format; //system with node description of format "hostname mlx_card_name"
    //TBD, if more card types are added or changed, consider holding
    //the max index of each card type in a map by type
    int                 max_mlx4; // if the format is with NDD this value holds the max mlx4 HCAs
    int                 max_mlx5; // if the format is with NDD this value holds the max mlx5 HCAs

    // Default Constractor - empty need to be overwritten
    IBSystem() {} ;

    // Destructor must be virtual
    virtual ~IBSystem();

    // Constractor
    IBSystem(const string &n, class IBFabric *p_fab, const string &t,
             bool new_nd_format = false);

    // Get a string with all the System Port Names (even if not connected)
    virtual list_str getAllSysPortNames();

    // Get a Sys Port by name
    IBSysPort *getSysPort(string name);

    inline IBNode *getNode(string nName) {
        map_str_pnode::iterator nI = NodeByName.find(nName);
        if (nI != NodeByName.end()) {
            return (*nI).second;
        } else {
            return NULL;
        }
    };

    // make sure we got the port defined (so define it if not)
    virtual IBSysPort *makeSysPort(string pName);

    // get the node port for the given sys port by name
    virtual IBPort *getSysPortNodePortByName(string sysPortName);

    // Remove a sub module of the system
    int removeBoard(string boardName);

    // parse configuration string into a vector
    void cfg2Vector(const string& cfg,
            vector<string>& boardCfgs,
            int numBoards);

    int CreateMissingSystemMlxNodes(map_str_pnode *pIBNLFabricNodes);

    // Write system IBNL into the given directory and return IBNL name
    int dumpIBNL(const char *ibnlDir, string &sysType);

    void generateSysPortName(char *buf, IBNode *p_node, unsigned int  pn);
};

//forward declaration of the scope class
class IBScope;

///////////////////////////////////////////////////////////////////////////////
//
// IB Fabric Class
// The entire fabric
//
class IBFabric {
private:
    u_int32_t       numOfNodesCreated;
    u_int32_t       numOfPortsCreated;
    u_int32_t       numOfVPortsCreated;
    u_int32_t       numOfVNodesCreated;

    u_int8_t        defaultSL;      //default SL used for routing check
    phys_port_t     maxNodePorts;   // Track max ports for a node in the fabric.
public:
    map_str_pnode           NodeByName;     // Provide the node pointer by its name
    map_str_pnode           FullNodeByName; // Provide the node pointer by its name
    map_guid_pnode          NodeByGuid;     // Provides the node by guid
    map_str_psys            SystemByName;   // Provide the system pointer by its name
    map_guid_pnode          NodeBySystemGuid; // Provides the node by system guid
    map_guid_pport          PortByGuid;     // Provides the port by guid
    map_guid_pvnode         VNodeByGuid;    // Provides VNode by guid
    map_guid_pvport         VPortByGuid;    // Provides VPort by guid
    map_guid_pport          PortByAGuid;    // Provides the port by aguid
    map_str_list_pnode      NodeByDesc;     // Provides nodes by node description - valid
                                            // only for discovery process, after that we will
                                            // not update this field if delete a node
    map_guid_str            NGuid2Name;     // Maps node guid to user given name
    map_mcast_groups        McastGroups;    // Multicast group information
                                            // valid only after parsing sa_dump
    vec_pport               PortByLid;      // Pointer to the Port by its lid
    vec_pvport              VPortByLid;     // Pointer to the VPort by its lid
    lid_t                   minLid;         // Track min lid used.
    lid_t                   maxLid;         // Track max lid used.
    uint8_t                 caLmc;          // Default LMC value used for all CAs and Routers
    uint8_t                 swLmc;          // Default LMC value used for all Switches
    uint8_t                 defAllPorts;    // If not zero all ports (unconn) are declared
    uint8_t                 subnCANames;    // CA nodes are marked by name
    uint8_t                 numSLs;         // Number of used SLs
    uint8_t                 numVLs;         // Number of used VLs
    set_uint16              mcGroups;       // A set of all active multicast groups
    bool                    pLFTEnabled;    //Private LFT is enabled on at least one switch

    // Constructor
    IBFabric() {
        maxLid              = 0;
        defAllPorts         = 1;
        subnCANames         = 1;
        numSLs              = 1;
        numVLs              = 1;
        defaultSL           = 0;
        caLmc               = 0;
        swLmc               = 0;
        minLid              = 0;
        PortByLid.push_back(NULL); // make sure we always have one for LID=0
        numOfNodesCreated   = 0;
        numOfPortsCreated   = 0;
        numOfVPortsCreated   = 0;
        numOfVNodesCreated   = 0;
        pLFTEnabled = false;
        maxNodePorts         = 1;
    };

    // Destructor
    ~IBFabric();

    inline u_int32_t getNodeIndex() { return numOfNodesCreated++; }
    inline u_int32_t getPortIndex() { return numOfPortsCreated++; }
    inline u_int32_t getVPortIndex() { return numOfVPortsCreated++; }
    inline u_int32_t getVNodeIndex() { return numOfVNodesCreated++; }

    // get the node by its name (create one of does not exist)
    IBNode *makeNode(string n,
                IBSystem *p_sys,
                IBNodeType type,
                phys_port_t numPorts);

    // get port by guid:
    IBPort *getPortByGuid(uint64_t guid);
    IBPort *getPortByGuid(uint64_t guid, bool get_vguid, bool get_aguid);

    // get the node by its name
    IBNode *getNode(string name);
    IBNode *getNodeByGuid(uint64_t guid);

    // get vport by guid:
    IBVPort *getVPortByGuid(uint64_t guid);

    // return the list of node pointers matching the required type
    list_pnode *getNodesByType(IBNodeType type);

    // crate a new generic system - basically an empty contaner for nodes...
    IBSystem *makeGenericSystem(const string &name, const string &sysType,
                                bool new_nd_format);

    // crate a new system - the type must have a pre-red SysDef
    IBSystem *makeSystem(string name, string type, string cfg = "");

    // get a system by name
    IBSystem *getSystem(string name);

    // get a system by guid
    IBSystem *getSystemByGuid(uint64_t guid);

    // Add a cable connection
    int addCable(string t1, string n1, string p1,
            string t2, string n2, string p2,
            IBLinkWidth width, IBLinkSpeed speed);

    // Parse the cables file and build the fabric
    int parseCables(const string &fn);

    // Parse Topology File according to file name extension
    // Supports ibnetdiscover (ibnd), subnet links (lst), and topo file (topo)
    int parseTopology(const string &fn);

    // Add a link into the fabric - this will create nodes / ports and link between them
    // by calling the forward methods makeNode + setNodePortsystem + makeLinkBetweenPorts
    int addLink(string type1, phys_port_t numPorts1,
            uint64_t sysGuid1, uint64_t nodeGuid1,  uint64_t portGuid1,
            int vend1, device_id_t devId1, int rev1, string desc1,
            lid_t lid1, uint8_t lmc1, phys_port_t portNum1,
            string type2, phys_port_t numPorts2,
            uint64_t sysGuid2, uint64_t nodeGuid2,  uint64_t portGuid2,
            int vend2, device_id_t devId2, int rev2, string desc2,
            lid_t lid2, uint8_t lmc2, phys_port_t portNum2,
            IBLinkWidth width, IBLinkSpeed speed, IBPortState portState);

    // create a new node in fabric (don't check if exists already), also create system if required
    IBNode * makeNode(IBNodeType type, phys_port_t numPorts,
                    uint64_t sysGuid, uint64_t nodeGuid,
                    int vend, device_id_t devId, int rev, string desc);

    // set the node's port given data (create one of does not exist).
    IBPort * setNodePort(IBNode * p_node, uint64_t portGuid,
			 lid_t lid, uint8_t limc, phys_port_t portNum,
			 IBLinkWidth width, IBLinkSpeed speed, IBPortState port_state);

    // Add a link between the given ports.
    // not creating sys ports for now.
    int makeLinkBetweenPorts(IBPort *p_port1, IBPort *p_port2);

    int getFileVersion(ifstream &f, u_int16_t &fileVersion);

    // Parse the OpenSM subnet.lst file and build the fabric from it.
    int parseSubnetLinks (string fn);

    // Parse ibnetdiscover file and build the fabric from it.
    int parseIBNetDiscover (string fn);

    // Parse topo file and build the fabric from it.
    int parseTopoFile(const string &fn);

    // Parse OpenSM FDB dump file
    int parseFdbFile(string fn);

    // Parse PSL mapping
    int parsePSLFile(const string& fn);

    // Parse SLVL mapping
    int parseSLVLFile(const string& fn);

    // Parse an OpenSM MCFDBs file and set the MFT table accordingly
    int parseMCFdbFile(string fn);

    int parseVL2VLFile(string fn);

    int parseARFile(string fn);
    int parseFARFile(string fn);

    int parsePLFTFile(string fn);

    int parseSADumpFile(string fn);
    //parse file that maps node name to guid
    //int parseApplyNodeNameMapFile(string fn);
    int parseNodeNameMapFile(string fn);

    // set a lid port
    void setLidPort(lid_t lid, IBPort *p_port);
    void setLidVPort(lid_t lid, IBVPort *p_vport);

    // get a port by lid
    inline IBPort *getPortByLid(lid_t lid) {
        if ( PortByLid.empty() || (PortByLid.size() < (unsigned)lid+1))
            return NULL;
        return (PortByLid[lid]);
    };

    // get a port by vlid
    inline IBVPort *getVPortByLid(lid_t lid) {
        if ( VPortByLid.empty() || (VPortByLid.size() < (unsigned)lid+1))
            return NULL;
        return (VPortByLid[lid]);
    };

    //set number of SLs
    inline void setNumSLs(uint8_t nSL) {
        numSLs=nSL;
    };

    //get number of SLs
    inline uint8_t getNumSLs() {
        return numSLs;
    };

    //set number of VLs
    inline void setNumVLs(uint8_t nVL) {
        numVLs=nVL;
    };

    //get number of VLs
    inline uint8_t getNumVLs() {
        return numVLs;
    };

    // dump out the contents of the entire fabric
    void dump(ostream &sout);

    // write out a topology file
    int dumpTopology(const char *fileName, const char *ibnlDir);

    // write out a LST file
    int dumpLSTFile(char *fileName, bool write_with_lmc);

    // Write out the name to guid and LID map
    int dumpNameMap(const char *fileName);

    //finish systems construction, create IBSystem ports and check sys type
    void constructSystems();

    //Returns: SUCCESS_CODE / ERR_CODE_IO_ERR
    static int OpenFile(const char *file_name,
                        ofstream& sout,
                        bool to_append,
                        string & err_message,
                        bool add_header = false,
                        ios_base::openmode mode = ios_base::out);

    void setPLFTEnabled(){pLFTEnabled = true;}
    bool isPLFTEnabled(){return pLFTEnabled;}

    int parseScopePortGuidsFile(const string& fn,
                                bool include_in_scope);
    int markInScopeNodes(IBScope &in_scope);
    int markOutScopeNodes(IBScope &out_scope);
    int applySubCluster();

    IBVNode * makeVNode(uint64_t guid,
                        virtual_port_t num_vports,
                        IBVPort *p_vport,
                        virtual_port_t local_vport_num);

    IBVPort *makeVPort(IBPort *p_port, virtual_port_t vport_num,
                       uint64_t guid, IBPortState vport_state);

    void SetDefaultSL(u_int8_t sl) {
        defaultSL = sl;
        IBNode::setMaxSL(sl);
    }
    u_int8_t GetDefaultSL() {
        return defaultSL;
    }

    inline phys_port_t GetMaxNodePorts() {
        return maxNodePorts;
    }

private:
    int parseSubnetLine(char *line);
    int constructGeneralSystem(IBSystem *p_system);
    int constructGeneralSystemNode(IBSystem *p_system, IBNode *p_node);
    int constructSystem(IBSystem *p_system,
                        IBSystem *p_systemTemplate, bool isHCA);
    int constructSystemNode(IBNode *p_node, IBNode *p_nodeT,
                            set_nodes_ptr &missingNodesPtr,
                            map_template_pnode &systemToTemplateMap,
                            bool &isModSys, bool &isNewSys);

    int parseCommaSeperatedValues(
        const string &line, vector<u_int32_t> &vecRes);

};

///////////////////////////////////////////////////////////////////////////////
//
// IB Scope Class
// The scope of nodes to be left or excluded in/from fabric
//
class IBScope {
public:
    //node guid with number ports to be in scope
    map_pnode_ports_bitset    node_ports;
    bool                      is_all_sw;
    bool                      is_all_ca;

    IBScope(map_pnode_ports_bitset &nodes, bool all_sw, bool all_ca) {
        node_ports = nodes;
        is_all_sw = all_sw;
        is_all_ca = all_ca;
    }
    ~IBScope() {};
};


#endif /* IBDM_FABRIC_H */

