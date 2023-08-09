#include "mem.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void * mem_alloc0(idx size)
{
    void * ptr;

    ptr = calloc(size, 1);
    assert(ptr);

    return ptr;
}

void mem_del(void * ptr)
{
    free(ptr);
}

idx mem_resize(void ** ptr, idx size)
{
    size = next_pow2_(size);
    * ptr = realloc(* ptr, size);
    assert(* ptr);

    return size;
}

idx mem_extend(void ** ptr, idx size, idx extra_size)
{
    return mem_resize(ptr, size + extra_size);
}

idx mem_extend0(void ** ptr, idx size, idx extra_size)
{
    idx new_size;

    new_size = mem_extend(ptr, size, extra_size);
    memset(* ptr + size, 0, extra_size);

    return new_size;    
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