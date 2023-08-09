#ifndef BFD_H
#define BFD_H

#include "Buf.h"
#include "Str.h"

typedef struct Bfd Bfd;

struct Bfd
{
    Blk blk;
};

Bfd     Bfd_ctr(Blk blk);
idx     Bfd_len(Bfd bfd);
bool    Bfd_bit(Bfd bfd, idx k);
bool    Bfd_bit_check(Bfd bfd, idx k);
void    Bfd_del(Bfd * bfd);
void    Bfd_set(Bfd bfd, idx k);
void    Bfd_clear(Bfd bfd, idx k);
void    Bfd_toggle(Bfd bfd, idx k);
void    Bfd_resize(Bfd * bfd, idx n_bits);
void    Bfd_set_check(Bfd * bfd, idx k);
Bfd     Bfd_from_cstr(const char * cstr);
Str     Bfd_to_Str(Bfd bfd);


#endif