#include "Sieve.h"
#include <assert.h>

Sieve Sieve_ctr(Bfd bfd)
{
    return (Sieve)
    {
        .bfd = bfd,
    };
}

Sieve Sieve_new(idx len)
{
    Bfd bfd;

    assert(len > 2);
    bfd = Bfd_new(len);

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

bool Sieve_is_prime(Sieve sieve, ulong n)
{
    return Bfd_bit(sieve.bfd, n);
}


