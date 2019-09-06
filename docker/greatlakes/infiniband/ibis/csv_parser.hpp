/*
 * Copyright (c) 2017-2018 Mellanox Technologies LTD. All rights reserved.
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

#include "ibis.h"

#define CSV_PARSER_INVALID_FIELD 0xFF

template <class SectionRecord>
ParseFieldInfo<SectionRecord>::ParseFieldInfo(
        const char *field_name,
        bool (SectionRecord::*p_setter_func)(const char *)):
        m_field_name(field_name), m_p_setter_func(p_setter_func),
        m_mandatory(true)
{
}

template <class SectionRecord>
ParseFieldInfo<SectionRecord>::ParseFieldInfo(
        const char *field_name,
        bool (SectionRecord::*p_setter_func)(const char *),
        const string &default_value):
        m_field_name(field_name), m_p_setter_func(p_setter_func),
        m_mandatory(false), m_default_value(default_value)
{
}

template <class SectionRecord>
SectionParser<SectionRecord>::SectionParser()
{
}

template <class SectionRecord>
SectionParser<SectionRecord>::~SectionParser()
{
    m_parse_section_info.clear();
    m_section_data.clear();
}

template <class SectionRecord>
void SectionParser<SectionRecord>::ClearData()
{
    m_section_data.clear();
}

template <class SectionRecord>
int CsvParser::ParseSection(CsvFileStream &cfs,
                            SectionParser <SectionRecord> &section_parser)
{
    int rc = 0;
    bool field_found = false;
    char line_buff[LINE_BUFF_SIZE] = {0};
    vec_str_t line_tokens;


    if (!cfs.IsFileOpen()) {
        CSV_LOG(TT_LOG_LEVEL_ERROR,
                 "-E- csv file %s is not open. Needs to provide open"
                 " file to csv parser\n",
                 cfs.m_file_name.c_str());
        return 1;
    }
    ifstream &fs = cfs.GetFileStream();
    const map_str_to_offset_t::iterator it =
        cfs.m_section_name_to_offset.find(section_parser.GetSectionName());

    if (it == cfs.m_section_name_to_offset.end()) {
        CSV_LOG(TT_LOG_LEVEL_ERROR,
                "-E- Failed to find section name :%s\n",
                section_parser.GetSectionName().c_str());
        return 1;
    }

    struct offset_info off_info = (*it).second;
    try {
        fs.seekg(off_info.offset);
    } catch (const ifstream::failure& e) {
        CSV_LOG(TT_LOG_LEVEL_ERROR,
                "-E- Failed to find section in file %s, error: %s\n",
                cfs.m_file_name.c_str(), e.what());
        return 1;
    } catch (...) {
        CSV_LOG(TT_LOG_LEVEL_ERROR,
                "-E- Failed to find section in file %s\n",
                cfs.m_file_name.c_str());
        return 1;
    }

    //Get the fields names
    rc= GetNextLineAndSplitIntoTokens(fs, line_buff, line_tokens);
    u_int16_t number_of_fields = (u_int16_t)line_tokens.size();

    vec_uint8_t vec_fields_location(section_parser.GetParseSectionInfo().size());

    for(unsigned int i = 0; i < section_parser.GetParseSectionInfo().size(); i++) {

        field_found = false;
        for (unsigned int field_location = 0; field_location < line_tokens.size();
                field_location++) {

            if (!strcmp(line_tokens[field_location],
                        (section_parser.GetParseSectionInfo()[i]).GetFieldName().c_str())) {
                vec_fields_location[i] = (u_int8_t)field_location;
                field_found = true;
                break;
            }
        }

        if (!field_found) {
            if (section_parser.GetParseSectionInfo()[i].IsMandatory()) {
                CSV_LOG(TT_LOG_LEVEL_ERROR,
                        "-E- Failed to find field %s for line number %d. Line is:%s\n",
                        section_parser.GetParseSectionInfo()[i].GetFieldName().c_str(),
                        off_info.start_line,
                        line_buff);
                return 1;
            } else {
                CSV_LOG(TT_LOG_LEVEL_DEBUG,
                        "-D- Failed to find field %s for section %s in line number %d."
                        " Using default value %s\n",
                        section_parser.GetParseSectionInfo()[i].GetFieldName().c_str(),
                        section_parser.GetSectionName().c_str(),
                        off_info.start_line,
                        section_parser.GetParseSectionInfo()[i].GetDefaultValue().c_str());
               vec_fields_location[i] = CSV_PARSER_INVALID_FIELD;
            }
        }
    }

    u_int32_t current_row_number = off_info.start_line;
    try {
        while ((unsigned int)fs.tellg() < (off_info.offset + off_info.length) &&
               fs.good()) {
            current_row_number++;
            rc = GetNextLineAndSplitIntoTokens(fs, line_buff, line_tokens);
            if (rc) {
                CSV_LOG(TT_LOG_LEVEL_ERROR,
                        "-E- CSV Parser: Failed to parse line %d"
                        " for section %s\n",
                        current_row_number, section_parser.GetSectionName().c_str());
                continue;
            }
            if (number_of_fields != line_tokens.size()) {
                CSV_LOG(TT_LOG_LEVEL_ERROR,
                        "-E- CSV Parser: number of fields in line %d doesn't"
                        " match the number of fields in this section\n",
                        current_row_number);
                continue;
            }

            SectionRecord curr_record;
            for (unsigned int fi = 0; fi < vec_fields_location.size(); fi++) {
                try {
                    if (vec_fields_location[fi] == CSV_PARSER_INVALID_FIELD) {
                        (curr_record.*((section_parser.GetParseSectionInfo()[fi]).GetSetterFunc()))(
                            section_parser.GetParseSectionInfo()[fi].GetDefaultValue().c_str());
                     } else {
                         (curr_record.*((section_parser.GetParseSectionInfo()[fi]).GetSetterFunc()))(
                             line_tokens[vec_fields_location[fi]]);
                     }
                } catch (TypeParseError &e) {
                    switch (e.GetReason()) {
                    case TypeParseError::EMPTY_VALUE:
                        CSV_LOG(TT_LOG_LEVEL_ERROR,
                            "-E- CSV Parser: Found empty value for field name %s, line %d"
                            " in section %s\n",
                            (section_parser.GetParseSectionInfo()[fi]).GetFieldName().c_str(),
                            current_row_number, section_parser.GetSectionName().c_str());
                        break;
                    case TypeParseError::TOO_LONG_VALUE:
                        CSV_LOG(TT_LOG_LEVEL_ERROR,
                            "-E- CSV Parser: Found invalid size (over 64 bytes) value for field"
                            " name %s, line %d in section %s\n",
                            (section_parser.GetParseSectionInfo()[fi]).GetFieldName().c_str(),
                            current_row_number, section_parser.GetSectionName().c_str());
                        break;
                    default:
                        CSV_LOG(TT_LOG_LEVEL_ERROR,
                            "-E- CSV Parser: Unknown exception for field name %s, line %d"
                            " in section %s\n",
                            (section_parser.GetParseSectionInfo()[fi]).GetFieldName().c_str(),
                            current_row_number, section_parser.GetSectionName().c_str());
                    }
                    return 1;
                }
            }

            section_parser.InsertSectionData(curr_record);
        }
    } catch (const ifstream::failure& e) {
        CSV_LOG(TT_LOG_LEVEL_ERROR,
                "-E- Failed to get info from file %s, error: %s\n",
                cfs.m_file_name.c_str(), e.what());
        return 1;
    }

    return(rc);
}

template <class SectionRecord, class Handler>
int CsvParser::ParseAndHandleSection(
        CsvFileStream &cfs,
        SectionParser <SectionRecord> &section_parser,
        Handler *p_handler,
        int (Handler::*handler_func)(const SectionRecord &)) {

    int rc;

    rc = ParseSection(cfs, section_parser);
    if (rc)
        return (1);
    for (unsigned int i = 0;
         i < section_parser.GetSectionData().size();
         i++)
        (p_handler->*handler_func)(section_parser.GetSectionData()[i]);

    section_parser.ClearData();
    return 0;
}

