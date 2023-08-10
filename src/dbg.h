#ifndef DBG_H
#define DBG_H

#include "def.h"
#include <stdio.h>

#define nl_ printf("\n")

void dbg_idx(const void * x);
void dbg_Str(const void * str);
void dbg_ulong(const void * n);
void dbg_byte(const void * x);
void dbg_raw(const void * ptr, idx size);

#endif