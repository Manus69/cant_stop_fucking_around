#ifndef SIEVE_H
#define SIEVE_H

#include "Bfd.h"
#include "Vec.h"

#define SIEVE_FILE_NAME         "__sieve"
#define Sieve_to_file_(sieve)   Sieve_to_file(sieve, SIEVE_FILE_NAME)
#define Sieve_from_file_() Sieve_from_file(SIEVE_FILE_NAME)

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
Slc     Sieve_as_Slc(Sieve sieve);
idx     Sieve_to_file(Sieve sieve, const char * name);
Sieve   Sieve_decode(Buf * buf);
Sieve   Sieve_from_file(const char * name);


#endif