#include "dbg.h"
#include "macro.h"
#include "Str.h"

void dbg_idx(const void * x)
{
    printf("%ld ", deref_(idx) x);
}

void dbg_Str(const void * str)
{
    printf("'%s'", Str_cstr(deref_(Str) str));
    nl_;
}

void dbg_ulong(const void * n)
{
    printf("%lu ", deref_(ulong) n);
}

void dbg_byte(const void * x)
{
    printf("%u ", deref_(byte) x);
}
void dbg_raw(const void * ptr, idx size)
{
    while (size --) dbg_byte(ptr ++);
    nl_;
}