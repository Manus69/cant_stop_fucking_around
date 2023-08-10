#ifndef SIEVE_H
#define SIEVE_H

#include "Bfd.h"
#include "Vec.h"

typedef struct Sieve Sieve;

struct Sieve
{
    Bfd bfd;
};

Sieve   Sieve_ctr(Bfd bfd);
Sieve   Sieve_new(idx len);
void    Sieve_del(Sieve * sieve);
idx     Sieve_len(Sieve sieve);
bool    Sieve_is_prime(Sieve sieve, ulong n);
Vec     Sieve_primes_lt(Sieve sieve, ulong lt);

#endif