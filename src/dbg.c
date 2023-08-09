#include "dbg.h"
#include "macro.h"
#include "Str.h"

void dbg_idx(void * x)
{
    printf("%ld ", deref_(idx) x);
}

void dbg_Str(void * str)
{
    printf("'%s'", Str_cstr(deref_(Str) str));
    nl_;
}
