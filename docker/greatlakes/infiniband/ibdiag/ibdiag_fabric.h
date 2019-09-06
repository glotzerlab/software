/*
 * Copyright (c) 2017 Mellanox Technologies LTD. All rights reserved.
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

#ifndef IBDIAG_FABRIC_H
#define IBDIAG_FABRIC_H

#include <infiniband/ibdm/Fabric.h>
#include "ibdiag_ibdm_extended_info.h"
#include <ibis/ibis.h>

class NodeRecord;
class PortRecord;
class SwitchRecord;
class LinkRecord;

class IBDiagFabric {
private:

    CsvParser m_csv_parser;

    IBFabric &discovered_fabric;
    IBDMExtendedInfo &fabric_extended_info;

    u_int32_t nodes_found;
    u_int32_t sw_found;
    u_int32_t ca_found;
    u_int64_t ports_found;

public:

    u_int32_t getNodesFound() { return nodes_found;}
    u_int32_t getSWFound()    { return sw_found;}
    u_int32_t getCAFound()    { return ca_found;}
    u_int64_t getPortsFound() { return ports_found;}

    int UpdateFabric(const string &csv_file);

    int CreateNode(const NodeRecord &nodeRecord);
    int CreatePort(const PortRecord &portRecord);
    int CreateSwitch(const SwitchRecord &switchRecord);
    int CreateLink(const LinkRecord &linkRecord);

    IBDiagFabric(IBFabric &discovered_fabric, IBDMExtendedInfo &fabric_extended_info) :
        discovered_fabric(discovered_fabric), fabric_extended_info(fabric_extended_info),
        nodes_found(0), sw_found(0), ca_found(0), ports_found(0) { }
};


/*******************************
 *       SECTION RECORDS       *
 *******************************/
class NodeRecord {

public:

    string              node_description;
    u_int16_t           num_ports;
    u_int8_t            node_type;
    u_int8_t            class_version;
    u_int8_t            base_version;
    u_int64_t           system_image_guid;
    u_int64_t           node_guid;
    u_int64_t           port_guid;
    u_int16_t           device_id;
    u_int16_t           partition_cap;
    u_int32_t           revision;
    u_int32_t           vendor_id;
    u_int8_t            local_port_num;

    static int Init(vector < ParseFieldInfo <class NodeRecord> > &parse_section_info);

    bool SetNodeDescription(const char *field_str) {
        return CsvParser::Parse(field_str, node_description);
    }

    bool SetNumPorts(const char *field_str) {
        return CsvParser::Parse(field_str, num_ports);
    }

    bool SetNodeType(const char *field_str) {
        return CsvParser::Parse(field_str, node_type);
    }

    bool SetClassVersion(const char *field_str) {
        return CsvParser::Parse(field_str, class_version);
    }

    bool SetBaseVersion(const char *field_str) {
        return CsvParser::Parse(field_str, base_version);
    }

    bool SetSystemImageGUID(const char *field_str) {
        return CsvParser::Parse(field_str, system_image_guid, 16);
    }

    bool SetNodeGUID(const char *field_str) {
        return CsvParser::Parse(field_str, node_guid, 16);
    }

    bool SetPortGUID(const char *field_str) {
        return CsvParser::Parse(field_str, port_guid, 16);
    }

    bool SetDeviceID(const char *field_str) {
        return CsvParser::Parse(field_str, device_id);
    }

    bool SetPartitionCap(const char *field_str) {
        return CsvParser::Parse(field_str, partition_cap);
    }

    bool SetRevision(const char *field_str) {
        return CsvParser::Parse(field_str, revision);
    }

    bool SetVendorID(const char *field_str) {
        return CsvParser::Parse(field_str, vendor_id);
    }

    bool SetLocalPortNum(const char *field_str) {
        return CsvParser::Parse(field_str, local_port_num);
    }
};

class PortRecord {

public:
// 1
    u_int64_t           node_guid;
    u_int64_t           port_guid;
    u_int8_t            port_num;
    u_int64_t           m_key;
    u_int64_t           gid_prefix;
    u_int16_t           msm_lid;
    u_int16_t           lid;
// 2
    u_int32_t           cap_mask;
    u_int16_t           m_key_lease_period;
    u_int16_t           diag_code;
    u_int8_t            link_width_actv;
    u_int8_t            link_width_sup;
    u_int8_t            link_width_en;
    u_int8_t            local_port_num;
// 3
    u_int32_t           link_speed_en;
    u_int32_t           link_speed_actv;
    u_int8_t            lmc;
    u_int8_t            m_key_prot_bits;
    u_int8_t            link_down_def_state;
    u_int8_t            port_phy_state;
    u_int8_t            port_state;
    u_int32_t           link_speed_sup;
// 4
    u_int8_t            vl_arbit_High_Cap;
    u_int8_t            vl_high_limit;
    u_int8_t            init_type;
    u_int8_t            vl_cap;
    u_int8_t            msm_sl;
    u_int8_t            nmtu;
    u_int8_t            filter_raw_outbound;
// 5
    u_int8_t            filter_raw_inbound;
    u_int8_t            part_enf_outbound;
    u_int8_t            part_enf_inbound;
    u_int8_t            op_VLs;
    u_int8_t            hoq_life;
    u_int8_t            vl_stall_cnt;
    u_int8_t            mtu_cap;
// 6
    u_int8_t            init_type_reply;
    u_int8_t            vl_arbit_low_cap;
    u_int16_t           pkey_violations;
    u_int16_t           mkey_violations;
    u_int8_t            subn_time_out;
    u_int8_t            client_reregister;
    u_int8_t            guid_cap;
// 7
    u_int16_t           qkey_violations;
    u_int16_t           max_credit_hint;
    u_int8_t            overrun_errs;
    u_int8_t            local_phy_error;
    u_int8_t            resp_time_value;
    u_int32_t           link_round_trip_latency;
// 8
    string              cap_mask_2;
    string              fec_actv;
    string              retrans_actv;

    static int Init(vector < ParseFieldInfo <class PortRecord> > &parse_section_info);

//  *** 1
    bool SetNodeGuid(const char *field_str) {
        return CsvParser::Parse(field_str, node_guid, 16);
    }

    bool SetPortGuid(const char *field_str) {
        return CsvParser::Parse(field_str, port_guid, 16);
    }

    bool SetPortNum(const char *field_str) {
        return CsvParser::Parse(field_str, port_num);
    }

    bool SetMKey(const char *field_str) {
        return CsvParser::Parse(field_str, m_key, 16);
    }

    bool SetGIDPrfx(const char *field_str) {
        return CsvParser::Parse(field_str, gid_prefix, 16);
    }

    bool SetMSMLID(const char *field_str) {
        return CsvParser::Parse(field_str, msm_lid);
    }

    bool SetLid(const char *field_str) {
        return CsvParser::Parse(field_str, lid);
    }

//  *** 2
    bool SetCapMsk(const char *field_str) {
        return CsvParser::Parse(field_str, cap_mask);
    }

    bool SetM_KeyLeasePeriod(const char *field_str) {
        return CsvParser::Parse(field_str, m_key_lease_period);
    }

    bool SetDiagCode(const char *field_str) {
        return CsvParser::Parse(field_str, diag_code);
    }

    bool SetLinkWidthActv(const char *field_str) {
        return CsvParser::Parse(field_str, link_width_actv);
    }

    bool SetLinkWidthSup(const char *field_str) {
        return CsvParser::Parse(field_str, link_width_sup);
    }

    bool SetLinkWidthEn(const char *field_str) {
        return CsvParser::Parse(field_str, link_width_en);
    }

    bool SetLocalPortNum(const char *field_str) {
        return CsvParser::Parse(field_str, local_port_num);
    }

//  *** 3
    bool SetLinkSpeedEn(const char *field_str) {
        return CsvParser::Parse(field_str, link_speed_en);
    }

    bool SetLinkSpeedActv(const char *field_str) {
        return CsvParser::Parse(field_str, link_speed_actv);
    }

    bool SetLMC(const char *field_str) {
        return CsvParser::Parse(field_str, lmc);
    }

    bool SetMKeyProtBits(const char *field_str) {
        return CsvParser::Parse(field_str, m_key_prot_bits);
    }

    bool SetLinkDownDefState(const char *field_str) {
        return CsvParser::Parse(field_str, link_down_def_state);
    }

    bool SetPortPhyState(const char *field_str) {
        return CsvParser::Parse(field_str, port_phy_state);
    }

    bool SetPortState(const char *field_str) {
        return CsvParser::Parse(field_str, port_state);
    }

    bool SetLinkSpeedSup(const char *field_str) {
        return CsvParser::Parse(field_str, link_speed_sup);
    }

//  *** 4
    bool SetVLArbHighCap(const char *field_str) {
        return CsvParser::Parse(field_str, vl_arbit_High_Cap);
    }

    bool SetVLHighLimit(const char *field_str) {
        return CsvParser::Parse(field_str, vl_high_limit);
    }

    bool SetInitType(const char *field_str) {
        return CsvParser::Parse(field_str, init_type);
    }

    bool SetVLCap(const char *field_str) {
        return CsvParser::Parse(field_str, vl_cap);
    }

    bool SetMSMSL(const char *field_str) {
        return CsvParser::Parse(field_str, msm_sl);
    }

    bool SetNMTU(const char *field_str) {
        return CsvParser::Parse(field_str, nmtu);
    }

    bool SetFilterRawOutb(const char *field_str) {
        return CsvParser::Parse(field_str, filter_raw_outbound);
    }

//  *** 5
    bool SetFilterRawInb(const char *field_str) {
        return CsvParser::Parse(field_str, filter_raw_inbound);
    }

    bool SetPartEnfOutb(const char *field_str) {
        return CsvParser::Parse(field_str, part_enf_outbound);
    }

    bool SetPartEnfInb(const char *field_str) {
        return CsvParser::Parse(field_str, part_enf_inbound);
    }

    bool SetOpVLs(const char *field_str) {
        return CsvParser::Parse(field_str, op_VLs);
    }

    bool SetHoQLife(const char *field_str) {
        return CsvParser::Parse(field_str, hoq_life);
    }

    bool SetVLStallCnt(const char *field_str) {
        return CsvParser::Parse(field_str, vl_stall_cnt);
    }

    bool SetMTUCap(const char *field_str) {
        return CsvParser::Parse(field_str, mtu_cap);
    }

//  *** 6
    bool SetInitTypeReply(const char *field_str) {
        return CsvParser::Parse(field_str, init_type_reply);
    }

    bool SetVLArbLowCap(const char *field_str) {
        return CsvParser::Parse(field_str, vl_arbit_low_cap);
    }

    bool SetPKeyViolations(const char *field_str) {
        return CsvParser::Parse(field_str, pkey_violations);
    }

    bool SetMKeyViolations(const char *field_str) {
        return CsvParser::Parse(field_str, mkey_violations);
    }

    bool SetSubnTmo(const char *field_str) {
        return CsvParser::Parse(field_str, subn_time_out);
    }

    bool SetClientReregister(const char *field_str) {
        return CsvParser::Parse(field_str, client_reregister);
    }

    bool SetGUIDCap(const char *field_str) {
        return CsvParser::Parse(field_str, guid_cap);
    }

//  *** 7
    bool SetQKeyViolations(const char *field_str) {
        return CsvParser::Parse(field_str, qkey_violations);
    }

    bool SetMaxCreditHint(const char *field_str) {
        return CsvParser::Parse(field_str, max_credit_hint);
    }

    bool SetOverrunErrs(const char *field_str) {
        return CsvParser::Parse(field_str, overrun_errs);
    }

    bool SetLocalPhyError(const char *field_str) {
        return CsvParser::Parse(field_str, local_phy_error);
    }

    bool SetRespTimeValue(const char *field_str) {
        return CsvParser::Parse(field_str, resp_time_value);
    }

    bool SetLinkRoundTripLatency(const char *field_str) {
        return CsvParser::Parse(field_str, link_round_trip_latency);
    }

//  *** 8
    bool SetCapMsk2(const char *field_str) {
        return CsvParser::Parse(field_str, cap_mask_2);
    }

    bool SetFECActv(const char *field_str) {
        return CsvParser::Parse(field_str, fec_actv);
    }

    bool SetRetransActv(const char *field_str) {
        return CsvParser::Parse(field_str, retrans_actv);
    }
};

class SwitchRecord {

public:
    u_int64_t           node_guid;

    u_int16_t           linear_FDB_cap;
    u_int16_t           random_FDB_cap;
    u_int16_t           mcast_FDB_cap;
    u_int16_t           linear_FDB_top;

    u_int8_t            def_port;
    u_int8_t            def_mcast_pri_port;
    u_int8_t            def_mcast_not_pri_port;
    u_int8_t            life_time_value;

    u_int8_t            port_state_change;
    u_int8_t            optimized_SLVL_mapping;
    u_int16_t           lids_per_port;
    u_int16_t           part_enf_cap;

    u_int8_t            inb_enf_cap;
    u_int8_t            outb_enf_cap;
    u_int8_t            filter_raw_inb_cap;
    u_int8_t            filter_raw_outb_cap;

    u_int8_t            en_port0;
    u_int16_t           mcast_FDB_top;

    static int Init(vector < ParseFieldInfo <class SwitchRecord> > &parse_section_info);

    bool SetNodeGuid(const char *field_str) {
        return CsvParser::Parse(field_str, node_guid, 16);
    }

    bool SetLinearFDBCap(const char *field_str) {
       return CsvParser::Parse(field_str, linear_FDB_cap);
    }

    bool SetRandomFDBCap(const char *field_str) {
       return CsvParser::Parse(field_str, random_FDB_cap);
    }

    bool SetMCastFDBCap(const char *field_str) {
       return CsvParser::Parse(field_str, mcast_FDB_cap);
    }

    bool SetLinearFDBTop(const char *field_str) {
       return CsvParser::Parse(field_str, linear_FDB_top);
    }

    bool SetDefPort(const char *field_str) {
       return CsvParser::Parse(field_str, def_port);
    }

    bool SetDefMCastPriPort(const char *field_str) {
       return CsvParser::Parse(field_str, def_mcast_pri_port);
    }

    bool SetDefMCastNotPriPort(const char *field_str) {
       return CsvParser::Parse(field_str, def_mcast_not_pri_port);
    }

    bool SetLifeTimeValue(const char *field_str) {
       return CsvParser::Parse(field_str, life_time_value);
    }

    bool SetPortStateChange(const char *field_str) {
       return CsvParser::Parse(field_str, port_state_change);
    }

    bool SetOptimizedSLVLMapping(const char *field_str) {
       return CsvParser::Parse(field_str, optimized_SLVL_mapping);
    }

    bool SetLidsPerPort(const char *field_str) {
       return CsvParser::Parse(field_str, lids_per_port);
    }

    bool SetPartEnfCap(const char *field_str) {
       return CsvParser::Parse(field_str, part_enf_cap);
    }

    bool SetInbEnfCap(const char *field_str) {
       return CsvParser::Parse(field_str, inb_enf_cap);
    }

    bool SetOutbEnfCap(const char *field_str) {
       return CsvParser::Parse(field_str, outb_enf_cap);
    }

    bool SetFilterRawInbCap(const char *field_str) {
       return CsvParser::Parse(field_str, filter_raw_inb_cap);
    }

    bool SetFilterRawOutbCap(const char *field_str) {
       return CsvParser::Parse(field_str, filter_raw_outb_cap);
    }

    bool SetENP0(const char *field_str) {
       return CsvParser::Parse(field_str, en_port0);
    }

    bool SetMCastFDBTop(const char *field_str) {
       return CsvParser::Parse(field_str, mcast_FDB_top);
    }
};

class LinkRecord {

public:

    u_int64_t           node_guid1;
    u_int8_t            port_num1;
    u_int64_t           node_guid2;
    u_int8_t            port_num2;

    static int Init(vector < ParseFieldInfo <class LinkRecord> > &parse_section_info);

    bool SetNodeGuid1(const char *field_str) {
        return CsvParser::Parse(field_str, node_guid1, 16);
    }

    bool SetPortNum1(const char *field_str) {
        return CsvParser::Parse(field_str, port_num1);
    }

    bool SetNodeGuid2(const char *field_str) {
        return CsvParser::Parse(field_str, node_guid2, 16);
    }

    bool SetPortNum2(const char *field_str) {
        return CsvParser::Parse(field_str, port_num2);
    }
};

#endif   /* IBDIAG_FABRIC_H */
