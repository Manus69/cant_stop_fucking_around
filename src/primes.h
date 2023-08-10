#ifndef PRIMES_H
#define PRIMES_H

#include "Sieve.h"
#include "Vec.h"

Vec     primes_lt(Sieve sieve, ulong lt);
bool    primes_is_prime(ulong n);
bool    primes_is_prime_Sieve(ulong n, Sieve sieve);


#endif