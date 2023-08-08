#ifndef STR_H
#define STR_H

#include "Buf.h"
#include "Vec.h"
#include "mem_macro.h"

#include <stdbool.h>

#define Str_vjoin(...) Str_join_cstr((const char * []){__VA_ARGS__, NULL})

typedef struct Str Str;

struct Str
{
    Buf buf;  
};

mem_put_gen(Str)

Str     Str_ctr(Buf buf);
Str     Str_from_cstr_len(const char * cstr, idx len);
Str     Str_from_cstr(const char * cstr);
Str     Str_from_Slc(Slc slc);
Str     Str_new_empty(void);
idx     Str_len(Str str);
bool    Str_empty(Str str);
char *  Str_cstr(Str str);
char *  Str_get(Str str, idx k);
void    Str_del(Str * str);
void    Str_append_cstr_len(Str * restrict str, const char * restrict cstr, idx len);
void    Str_append_cstr(Str * restrict str, const char * restrict cstr);
void    Str_append_Slc(Str * str, Slc slc);
void    Str_append(Str * lhs, Str rhs);
Str     Str_join_cstr(const char * cstrs[]);
Slc     Str_slice(Str str, idx k, idx len);
Slc     Str_as_Slc(Str str);
Vec     Str_split(Str str, char x);

#endif