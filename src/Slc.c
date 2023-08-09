#include "Slc.h"
#include "macro.h"

#include <string.h>

Slc Slc_ctr(void * ptr, idx size)
{
    return (Slc)
    {
        .ptr = ptr, 
        .size = size
    };
}

Slc Slc_from_cstr_len(const char * cstr, idx len)
{
    return Slc_ctr((void *) cstr, len);
}

Slc Slc_from_cstr(const char * cstr)
{
    return Slc_from_cstr_len(cstr, strlen(cstr));
}

idx Slc_size(Slc slc)
{
    return slc.size;
}

bool Slc_empty(Slc slc)
{
    return slc.size == 0;
}

void * Slc_get(Slc slc, idx k)
{
    return slc.ptr + k;
}

void * Slc_first(Slc slc)
{
    return slc.ptr;
}

void Slc_inject(Slc slc, idx k, const void * src, idx size)
{
    memcpy(Slc_get(slc, k), src, size);
}

void Slc_shift(Slc * slc, idx n)
{
    slc->ptr += n;
    slc->size -= n;
}

Slc Slc_slice(Slc slc, idx k, idx size)
{
    return Slc_ctr(Slc_get(slc, k), size);
}

Slc Slc_chop_front(Slc * slc, idx size)
{
    Slc chop;

    chop = Slc_slice(* slc, 0, size);
    Slc_shift(slc, size);

    return chop;
}

Slc Slc_chop_all(Slc * slc)
{
    return Slc_chop_front(slc, slc->size);
}

Slc Slc_chop_front_check(Slc * slc, idx size)
{
    return size < slc->size ? Slc_chop_front(slc, size) : Slc_chop_all(slc);
}

Slc Slc_chop_front_prob(Slc * slc, idx size)
{
    if (unlikely_(size >= slc->size)) return Slc_chop_all(slc);

    return Slc_chop_front(slc, size);
}

idx Slc_find(Slc slc, byte x)
{
    for (idx k = 0; k < slc.size; k ++)
    {
        if (deref_(byte) Slc_get(slc, k) == x) return k;
    }

    return NO_IDX;
}

Slc Slc_split_next(Slc * slc, byte x)
{
    Slc chop;
    idx k;

    if ((k = Slc_find(* slc, x)) == NO_IDX) return Slc_chop_all(slc);

    chop = Slc_chop_front(slc, k);
    Slc_shift(slc, 1);

    return chop;
}