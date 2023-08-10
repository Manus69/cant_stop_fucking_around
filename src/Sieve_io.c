#include "Sieve.h"
#include "io.h"

idx Sieve_to_file(Sieve sieve, const char * name)
{
    int fd;
    idx result;
    Buf buf;

    if ((fd = io_create_file(name)) < 0) return fd;

    buf = Buf_new(Sieve_len(sieve) / __CHAR_BIT__ + __CHAR_BIT__);
    io_encode_Slc(& buf, Sieve_as_Slc(sieve));

    result = io_write_fd(buf, fd);
    Buf_del(& buf);

    return result;
}

Sieve Sieve_decode(Buf * buf)
{
    Blk blk;

    blk = io_decode_next(buf);

    return Sieve_ctr(Bfd_ctr(blk));
}

Sieve Sieve_from_file(const char * name)
{
    Buf     buf;
    Sieve   sieve;

    buf = io_read(name);
    sieve = Sieve_decode(& buf);

    Buf_del(& buf);

    return sieve;
}