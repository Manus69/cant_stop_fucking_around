#ifndef BLK_H
#define BLK_H

#include "Slc.h"

typedef struct Blk Blk;

struct Blk
{
    void *  data;
    idx     size;
};

Blk     Blk_ctr(void * data, idx size);
Blk     Blk_new0(idx size);
void    Blk_del(Blk * blk);
idx     Blk_size(Blk blk);
void *  Blk_get(Blk blk, idx k);
void *  Blk_first(Blk blk);
Slc     Blk_slice(Blk blk, idx k, idx size);
Slc     Blk_as_Slc(Blk blk);
void    Blk_inject(Blk blk, idx k, const void * src, idx size);
void    Blk_extend(Blk * blk, idx size);
void    Blk_extend0(Blk * blk, idx size);

#endif