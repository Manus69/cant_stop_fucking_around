#include "num.h"

Vec num_prime_divisors(ulong n)
{
    Vec vec;

    vec = Vec_new_(ulong);
    for (ulong p = 2; p <= n; p ++)
    {
        while (n % p == 0)
        {
            Vec_push_(& vec, p, ulong);
            n /= p;
        }
    }

    return vec;
}

Vec num_divisors(ulong n)
{
    Vec vec;

    vec = Vec_new_(ulong);
    for (ulong k = 1; k <= n; k ++)
    {
        if (n % k == 0) Vec_push_(& vec, k, ulong);
    }

    return vec;
}

ulong num_gcd(ulong a, ulong b)
{
    ulong r;

    if (a < b) mem_swap_(& a, & b, ulong);

    while (b)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

ulong num_lcm(ulong a, ulong b)
{
    return (a * b) / gcd(a, b); 
}