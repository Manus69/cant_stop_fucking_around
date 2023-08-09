#include "Str.h"
#include "macro.h"

#include <string.h>

#define STR_DC (1 << 3)

Str Str_ctr(Buf buf)
{
    return (Str)
    {
        .buf = buf,
    };
}

Str Str_from_cstr_len(const char * cstr, idx len)
{
    Buf buf;

    buf = Buf_new(len + 1);
    Buf_push(& buf, cstr, len);

    return Str_ctr(buf);
}

Str Str_from_cstr(const char * cstr)
{
    return Str_from_cstr_len(cstr, strlen(cstr));
}

Str Str_from_Slc(Slc slc)
{
    return Str_from_cstr_len(Slc_first(slc), Slc_size(slc));
}

Str Str_new_empty(void)
{
    return Str_ctr(Buf_new(STR_DC));
}

void Str_del(Str * str)
{
    Buf_del(& str->buf);
    to0_(str, Str);
}

idx Str_len(Str str)
{
    return Buf_index(str.buf);
}

bool Str_empty(Str str)
{
    return Str_len(str) == 0;
}

char * Str_cstr(Str str)
{
    return Buf_first(str.buf);
}

char * Str_get(Str str, idx k)
{
    return Buf_get(str.buf, k);
}

void Str_set(Str str, idx k, byte x)
{
    deref_(byte) Str_get(str, k) = x;
}

void Str_append_cstr_len(Str * restrict str, const char * restrict cstr, idx len)
{
    Buf_push(& str->buf, cstr, len);
    Buf_set_byte(str->buf, Buf_index(str->buf), '\0');
}

void Str_append_cstr(Str * restrict str, const char * restrict cstr)
{
    Str_append_cstr_len(str, cstr, strlen(cstr));
}

void Str_append_Slc(Str * str, Slc slc)
{
    Str_append_cstr_len(str, Slc_first(slc), Slc_size(slc));
}

void Str_append(Str * lhs, Str rhs)
{
    Str_append_cstr_len(lhs, Str_cstr(rhs), Str_len(rhs));
}

Str Str_join_cstr(const char * cstrs[])
{
    Str           str;
    const char *  current;

    str = Str_new_empty();
    while ((current = * cstrs ++)) Str_append_cstr(& str, current);

    return str;
}

Slc Str_slice(Str str, idx k, idx len)
{
    return Slc_ctr(Str_get(str, k), len);
}

Slc Str_as_Slc(Str str)
{
    return Str_slice(str, 0, Str_len(str));
}

Buf Str_as_Buf(Str str)
{
    return str.buf;
}

Vec Str_split(Str str, char x)
{
    Vec split;
    Slc slc;
    Str current;

    split = Vec_new_(Str);
    slc = Str_as_Slc(str);

    while (Slc_empty(slc) == false)
    {
        current = Str_from_Slc(Slc_split_next(& slc, x));
        Vec_push_(& split, current, Str);
    }

    return split;
}

idx Str_cmp(Str lhs, Str rhs)
{ 
    return strcmp(Str_cstr(lhs), Str_cstr(rhs));
}

idx cmp_Str(const void * lhs, const void * rhs)
{
    return Str_cmp(deref_(Str) lhs, deref_(Str) rhs);
}