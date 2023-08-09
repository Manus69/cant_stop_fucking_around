#include "io.h"
#include "idx.h"

#define SIZE (1 << 10)
static byte zeroes[SIZE] = {};

typedef struct Enc Enc;

struct Enc
{
    idx     size;
    idx     pad;
    void *  ptr;
};

static inline Enc _get_Enc(Slc slc)
{
    idx size;
    idx pad;

    size = (Slc_size(slc) / __BIGGEST_ALIGNMENT__) * __BIGGEST_ALIGNMENT__ + __BIGGEST_ALIGNMENT__;
    pad = size - Slc_size(slc);

    return (Enc)
    {
        .size = size,
        .pad = pad,
        .ptr = Slc_first(slc),
    };
}

void io_encode_Slc(Buf * buf, Slc slc)
{
    Enc enc;

    enc = _get_Enc(slc);

    Buf_push_item(buf, & enc.size, sizeof(idx), put_idx);
    Buf_push_item(buf, & enc.pad, sizeof(idx), put_idx);
    Buf_push(buf, enc.ptr, enc.size - enc.pad);
    Buf_push(buf, zeroes, enc.pad);
}

Blk io_decode_next(Buf * buf)
{
    Enc enc;
    Blk blk;

    put_idx(& enc.size, Buf_at_index(* buf));
    Buf_shift_index(buf, sizeof(idx));

    put_idx(& enc.pad, Buf_at_index(* buf));
    Buf_shift_index(buf, sizeof(idx));

    enc.ptr = Buf_at_index(* buf);
    blk = Blk_new0(enc.size - enc.pad);
    Blk_inject(blk, 0, enc.ptr, enc.size - enc.pad);

    Buf_shift_index(buf, enc.size);

    return blk;
}