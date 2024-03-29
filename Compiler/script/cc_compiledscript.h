//=============================================================================
//
// Adventure Game Studio (AGS)
//
// Copyright (C) 1999-2011 Chris Jones and 2011-2024 various contributors
// The full list of copyright holders can be found in the Copyright.txt
// file, which is part of this source code distribution.
//
// The AGS source code is provided under the Artistic License 2.0.
// A copy of this license can be found in the file License.txt and at
// https://opensource.org/license/artistic-2-0/
//
//=============================================================================
#ifndef __CC_COMPILEDSCRIPT_H
#define __CC_COMPILEDSCRIPT_H

#include <cstdint>
#include <string>
#include "script/cc_script.h"       // ccScript
#include "cs_parser_common.h"   // macro definitions
#include "cc_symboldef.h"       // SymbolDef


struct ccCompiledScript: public ccScript {
    int32_t codeallocated;
    char*functions[MAX_FUNCTIONS];
    int32_t funccodeoffs[MAX_FUNCTIONS];
    int16_t funcnumparams[MAX_FUNCTIONS];
    int32_t numfunctions;
    int32_t cur_sp;
    int  next_line;  // line number of next code
    int  ax_val_type;  // type of value in AX
    int  ax_val_scope;  // SYM_LOCALVAR or SYM_GLOBALAVR

    void init();
    void shutdown();
    void free_extra();
    int  add_global(int,const char*);
    int  add_string(const char*);
    void add_fixup(int32_t,char);
    void fixup_previous(char);
    int  add_new_function(const char*, int *idx);
    int  add_new_import(const char*);
    int  add_new_export(const char*, int, int32_t, int);
    void write_code(int32_t);
    void set_line_number(int nlum) { next_line=nlum; }
    void flush_line_numbers();
    int  remove_any_import(const char*, SymbolDef *oldSym);
    const char* start_new_section(const char *name);

    void write_cmd(int cmdd);
    void write_cmd1(int cmdd,int param);
    void write_cmd2(int cmdd,int param,int param2);
    void write_cmd3(int cmdd,int param,int param2,int param3);

    void push_reg(int regg);
    void pop_reg(int regg);

    ccCompiledScript();
    virtual ~ccCompiledScript();
};

#endif // __CC_COMPILEDSCRIPT_H