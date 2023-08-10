#include "primes.h"
#include "ulong.h"

Vec primes_lt(Sieve sieve, ulong lt)
{
    Vec primes;

    primes = Vec_new_(ulong);
    for (ulong n = 2; (n < (ulong) Sieve_len(sieve)) && (n < lt); n ++)
    {
        if (Sieve_is_prime(sieve, n)) Vec_push_(& primes, n, ulong);
    }

    return primes;
}

bool primes_is_prime(ulong n)
{
    ulong p;

    p = 2;
    while (p * p <= n)
    {
        if (n % p == 0) return false;
        ++ p;
    }

    return true;
}

bool primes_is_prime_Sieve(ulong n, Sieve sieve)
{
    return Sieve_is_prime(sieve, n);
}
