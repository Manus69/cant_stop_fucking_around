#ifndef SLC_H
#define SLC_H

#include "def.h"

typedef struct Slc Slc;

struct Slc
{
    void *  ptr;
    idx     size;
};

Slc     Slc_ctr(void * ptr, idx size);
Slc     Slc_from_cstr_len(const char * cstr, idx len);
Slc     Slc_from_cstr(const char * cstr);
idx     Slc_size(Slc slc);
void *  Slc_get(Slc slc, idx k);
void *  Slc_first(Slc slc);
void    Slc_shift(Slc * slc, idx n);
void    Slc_inject(Slc slc, idx k, const void * src, idx size);
Slc     Slc_slice(Slc slc, idx k, idx size);
Slc     Slc_chop_front(Slc * slc, idx size);
Slc     Slc_chop_all(Slc * slc);
Slc     Slc_chop_front_check(Slc * slc, idx size);
idx     Slc_find(Slc slc, byte x);
Slc     Slc_split_next(Slc * slc, byte x);

#endif