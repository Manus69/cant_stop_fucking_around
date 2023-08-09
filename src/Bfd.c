#include "Bfd.h"
#include "macro.h"

Bfd Bfd_ctr(Blk blk)
{
    return (Bfd)
    {
        .blk = blk,
    };
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
    deref_(byte) _byte(bfd, k) ^= (1u << (k % __CHAR_BIT__));
}

void Bfd_set_check(Bfd * bfd, idx k)
{

}