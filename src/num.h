#ifndef NUM_H
#define NUM_H

#include "ulong.h"
#include "Vec.h"

Vec     num_prime_divisors(ulong n);
Vec     num_divisors(ulong n);
ulong   num_gcd(ulong a, ulong b);
ulong   num_lcm(ulong a, ulong b);

#endif