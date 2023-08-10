#include "Bfd.h"
#include "macro.h"

Bfd Bfd_ctr(Blk blk)
{
    return (Bfd)
    {
        .blk = blk,
    };
}

Bfd Bfd_new(idx len)
{
    Bfd_ctr(Blk_new0(len / __CHAR_BIT__ + 1));
}

void Bfd_del(Bfd * bfd)
{
    Blk_del(& bfd->blk);
    to0_(bfd, Bfd);
}

idx Bfd_len(Bfd bfd)
{
    return Blk_size(bfd.blk) * __CHAR_BIT__; 
}

static inline byte * _byte(Bfd bfd, idx bit_idx)
{
    return Blk_get(bfd.blk, bit_idx / __CHAR_BIT__);
}

__attribute__ ((const))
static inline byte _bit(idx k)
{
    return 1u << (k % __CHAR_BIT__);
}

bool Bfd_bit(Bfd bfd, idx k)
{
    return (deref_(byte) _byte(bfd, k)) & _bit(k); 
}

bool Bfd_bit_check(Bfd bfd, idx k)
{
    return k < Bfd_len(bfd) ? Bfd_bit(bfd, k) : 0;
}

void Bfd_set(Bfd bfd, idx k)
{
    deref_(byte) _byte(bfd, k) |= _bit(k);
}

void Bfd_clear(Bfd bfd, idx k)
{
    deref_(byte) _byte(bfd, k) &= ~ _bit(k);
}

void Bfd_toggle(Bfd bfd, idx k)
{
    deref_(byte) _byte(bfd, k) ^= _bit(k);
}

void Bfd_resize(Bfd * bfd, idx n_bits)
{
    Blk_resize0(& bfd->blk, n_bits / __CHAR_BIT__);
}

void Bfd_set_check(Bfd * bfd, idx k)
{
    if (unlikely_(k >= Bfd_len(* bfd))) Bfd_resize(bfd, k + 1);

    Bfd_set(* bfd, k);
}

void Bfd_complement(Bfd bfd)
{
    for (idx k = 0; k < Blk_size(bfd.blk); k ++)
    {
        Blk_set_byte(bfd.blk, k, ~ (deref_(byte) Blk_get(bfd.blk, k)));
    }
}

#define BFD_DC (1)
Bfd Bfd_from_cstr(const char * cstr)
{
    Bfd bfd;

    bfd = Bfd_ctr(Blk_new0(BFD_DC));
    for (idx k = 0; cstr[k]; k ++)
    {
        if (cstr[k] == '1') Bfd_set_check(& bfd, k);
    }

    return bfd;
}

Str Bfd_to_Str(Bfd bfd)
{
    Blk     blk;
    byte    bytes[] = {'0', '1'};

    blk = Blk_new0(Bfd_len(bfd) + 1);
    for (idx k = 0; k < Bfd_len(bfd); k ++)
    {
        Blk_set_byte(blk, k, bytes[Bfd_bit(bfd, k)]);
    }

    return Str_ctr(Buf_ctr(blk, Bfd_len(bfd)));
}

