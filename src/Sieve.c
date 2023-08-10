#include "Sieve.h"
#include "ulong.h"

Sieve Sieve_ctr(Bfd bfd)
{
    return (Sieve)
    {
        .bfd = bfd,
    };
}

static inline void _cast_out(Bfd bfd, idx n)
{
    for (idx k = n + n; k < Bfd_len(bfd); k += n)
    {
        Bfd_clear(bfd, k);
    }
}

static inline idx _next_prime(Bfd bfd, idx n)
{
    n ++;
    while (n < Bfd_len(bfd))
    {
        if (Bfd_bit(bfd, n)) return n;
        n ++;
    }

    return NO_IDX;
}

static inline void _sieve(Bfd bfd)
{
    idx p;

    p = 2;
    while (likely_(p != NO_IDX))
    {
        _cast_out(bfd, p);
        p = _next_prime(bfd, p);
    }
}

Sieve Sieve_new(idx len)
{
    Bfd bfd;

    bfd = Bfd_new(len);
    Bfd_complement(bfd);

    Bfd_clear(bfd, 0);
    Bfd_clear(bfd, 1);

    _sieve(bfd);

    return Sieve_ctr(bfd);
}

void Sieve_del(Sieve * sieve)
{
    Bfd_del(& sieve->bfd);
    to0_(sieve, Sieve);
}

idx Sieve_len(Sieve sieve)
{
    return Bfd_len(sieve.bfd);
}

Slc Sieve_as_Slc(Sieve sieve)
{
    return Bfd_as_Slc(sieve.bfd);
}

bool Sieve_is_prime(Sieve sieve, ulong n)
{
    return Bfd_bit(sieve.bfd, n);
}
