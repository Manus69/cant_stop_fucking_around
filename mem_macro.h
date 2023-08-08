#ifndef MEM_MACRO_H
#define MEM_MACRO_H

#include "def.h"
#include "macro.h"

#define mem_put_gen(type) \
__attribute__ ((hot, always_inline)) \
static inline void put_##type(void * dst, const void * src) \
{deref_(type) dst = deref_(type) src;}

#define mem_cmp_gen(type) \
__attribute__ ((hot, pure, always_inline)) \
static inline idx cmp_##type(const void * lhs, const void * rhs) \
{return deref_(type) lhs < deref_(type) rhs ? -1 : deref_(type) lhs > deref_(type) rhs;}
// {return deref_(type) lhs - deref_(type) rhs;}

#define mem_swap_(lhs, rhs, type) \
{ \
    type _lhs = deref_(type) lhs; \
    type _rhs = deref_(type) rhs; \
    deref_(type) lhs = _rhs; \
    deref_(type) rhs = _lhs; \
}

#endif