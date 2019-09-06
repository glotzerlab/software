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

#ifndef IBDIAG_CSV_OUT_H_
#define IBDIAG_CSV_OUT_H_

#include <infiniband/ibdm/Fabric.h>
#include "ibdiag_types.h"

#define SECTION_INDEX_TABLE "INDEX_TABLE"


class CSVOut {

    ofstream sout;
    list_index_line index_table;
    size_t cur_CSV_line;
    size_t idx_tbl_comment_pos;
    index_line_t cur_idx;

    string CommentString(size_t offset, size_t line)
    {
        char buf[256];
        sprintf(buf, "offset: %11lu, line: %11lu", offset, line);
        return string(buf);
    }

public:

    CSVOut() : cur_CSV_line(1), idx_tbl_comment_pos(0) { }

    ~CSVOut()
    {
        if (sout.is_open())
            sout.close();
    }

    int Init(string &db_file_str, string &err_message)
    {
        return IBFabric::OpenFile(db_file_str.c_str(), sout, false, err_message);
    }

    void SetCommentPos();

    void DumpStart(const char *name);
    void DumpEnd(const char *name);
    void WriteLine(string line)
    {
        sout << line;
        ++cur_CSV_line;
    }
    void WriteBuf(string buf);

    void DumpIndexTableCSV();
};


#endif          /* not defined IBDIAG_CSV_OUT_H_ */
