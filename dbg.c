#include "dbg.h"
#include "macro.h"

void dbg_idx(void * x)
{
    printf("%ld ", deref_(idx) x);
}