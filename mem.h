#ifndef MEM_H
#define MEM_H

#include "def.h"
#include "macro.h"
#include "mem_macro.h"

#define mem_vmap_(f, ...) mem_arr_map(f, (void * []){__VA_ARGS__, NULL})

void *  mem_alloc0(idx size);
void    mem_del(void * ptr);
void *  mem_extend(void * ptr, idx size, idx extra_size);
void *  mem_extend0(void * ptr, idx size, idx extra_size);
void    mem_raw_map(F f, void * ptr, idx step, idx n_steps);
void    mem_arr_map(F f, void * pointers[]);

#endif