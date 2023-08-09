#ifndef BUF_H
#define BUF_H

#include "Blk.h"

typedef struct Buf Buf;

struct Buf
{
    Blk blk;
    idx index;
};

Buf     Buf_ctr(Blk blk, idx index);
Buf     Buf_new(idx size);
idx     Buf_size(Buf buf);
idx     Buf_index(Buf buf);
idx     Buf_capacity(Buf buf);
Slc     Buf_slice(Buf buf, idx k, idx size);
Slc     Buf_as_Slc(Buf buf);
void *  Buf_get(Buf buf, idx k);
void *  Buf_first(Buf buf);
void *  Buf_at_index(Buf buf);
void    Buf_del(Buf * buf);
void    Buf_shift_index(Buf * buf, idx n);
void    Buf_inject(Buf buf, idx k, const void * src, idx size);
void    Buf_extend(Buf * buf, idx size);
void    Buf_extend0(Buf * buf, idx size);
void    Buf_reserve(Buf * buf, idx size);
void    Buf_reserve0(Buf * buf, idx size);
void    Buf_push(Buf * restrict buf, const void * restrict src, idx size);
void    Buf_push_item(Buf * restrict buf, const void * restrict item, idx size, Put put);
void    Buf_reset(Buf * buf);
void    Buf_set_byte(Buf buf, idx k, byte x);

#endif