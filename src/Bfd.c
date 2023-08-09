#include "Bfd.h"
#include "macro.h"

Bfd Bfd_ctr(Buf buf)
{
    return (Bfd)
    {
        .buf = buf,
    };
}

void Bfd_del(Bfd * bfd)
{
    Buf_del(& bfd->buf);
    to0_(bfd, Bfd);
}

idx Bfd_len(Bfd bfd)
{
    return (Buf_index(bfd.buf) - 1) * __CHAR_BIT__; 
}

static inline byte * _byte(Bfd bfd, idx bit_idx)
{
    return Buf_get(bfd.buf, bit_idx / __CHAR_BIT__);
}

bool Bfd_bit(Bfd bfd, idx k)
{
    return (deref_(byte) _byte(bfd, k)) & (1u << (k % __CHAR_BIT__)); 
}

void Bfd_set(Bfd bfd, idx k)
{
    deref_(byte) _byte(bfd, k) |= (1u << (k % __CHAR_BIT__));
}

void Bfd_clear(Bfd bfd, idx k)
{
    deref_(byte) _byte(bfd, k) &= ~(1u << (k % __CHAR_BIT__));
}

void Bfd_toggle(Bfd bfd, idx k)
{
    deref_(byte) _byte(bfd, k) ^= (1u << (k % __CHAR_BIT__));
}