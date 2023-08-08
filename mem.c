#include "mem.h"
#include <stdlib.h>
#include <string.h>

void * mem_alloc0(idx size)
{
    return calloc(size, 1);
}

void mem_del(void * ptr)
{
    free(ptr);
}

void * mem_extend(void * ptr, idx size, idx extra_size)
{
    idx new_size;

    new_size = next_pow2_(size + extra_size);
    return realloc(ptr, new_size);
}

void * mem_extend0(void * ptr, idx size, idx extra_size)
{
    ptr = mem_extend(ptr, size, extra_size);
    memset(ptr + size, 0, extra_size);

    return ptr;
}

void mem_raw_map(F f, void * ptr, idx step, idx n_steps)
{
    while (n_steps --)
    {
        f(ptr);
        ptr += step;
    }
}

void mem_arr_map(F f, void * pointers[])
{
    void * ptr;

    while ((ptr = * pointers ++)) f(ptr);
}