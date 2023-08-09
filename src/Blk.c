#include "Blk.h"
#include "Slc.h"
#include "mem.h"

#include <string.h>

Blk Blk_ctr(void * data, idx size)
{
    return (Blk)
    {
        .data = data,
        .size = size,
    };
}

Blk Blk_new0(idx size)
{
    return Blk_ctr(mem_alloc0(size), size);
}

void Blk_del(Blk * blk)
{
    mem_del(blk->data);
    to0_(blk, Blk);
}

idx Blk_size(Blk blk)
{
    return blk.size;
}

void * Blk_get(Blk blk, idx k)
{
    return blk.data + k;
}

void * Blk_first(Blk blk)
{
    return Blk_get(blk, 0);
}

Slc Blk_slice(Blk blk, idx k, idx size)
{
    return Slc_ctr(Blk_get(blk, k), size);
}

Slc Blk_as_Slc(Blk blk)
{
    return Blk_slice(blk, 0, blk.size);
}

void Blk_inject(Blk blk, idx k, const void * src, idx size)
{
    memcpy(Blk_get(blk, k), src, size);
}

void Blk_set_byte(Blk blk, idx k, byte x)
{
    deref_(byte) Blk_get(blk, k) = x;
}

void Blk_extend(Blk * blk, idx size)
{
    blk->size = mem_extend(& blk->data, blk->size, size);
}

void Blk_extend0(Blk * blk, idx size)
{
    blk->size = mem_extend0(& blk->data, blk->size, size);
}

void Blk_resize(Blk * blk, idx size)
{
    blk->size = mem_resize(& blk->data, size);
}

void Blk_resize0(Blk * blk, idx size)
{
    idx current_size;

    current_size = blk->size;
    blk->size = mem_resize(& blk->data, size);

    if (likely_(blk->size > current_size))
    {
        memset(Blk_get(* blk, current_size), 0, blk->size - current_size);
    }
}