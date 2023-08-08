#include "Buf.h"
#include "macro.h"

Buf Buf_ctr(Blk blk, idx index)
{
    return (Buf)
    {
        .blk = blk,
        .index = index,
    };
}

Buf Buf_new(idx size)
{
    return Buf_ctr(Blk_new0(size), 0);
}

void Buf_del(Buf * buf)
{
    Blk_del(& buf->blk);
    to0_(buf, Buf);
}

idx Buf_size(Buf buf)
{
    return Blk_size(buf.blk);
}

idx Buf_index(Buf buf)
{
    return buf.index;
}

idx Buf_capacity(Buf buf)
{
    return Buf_size(buf) - buf.index;
}

void * Buf_get(Buf buf, idx k)
{
    return Blk_get(buf.blk, k);
}

void * Buf_first(Buf buf)
{
    return Buf_get(buf, 0);
}

void * Buf_at_index(Buf buf)
{
    return Buf_get(buf, buf.index);
}

Slc Buf_slice(Buf buf, idx k, idx size)
{
    return Slc_ctr(Buf_get(buf, k), size);
}

Slc Buf_as_Slc(Buf buf)
{
    return Buf_slice(buf, 0, buf.index - 1);
}

void Buf_inject(Buf buf, idx k, const void * src, idx size)
{
    Blk_inject(buf.blk, k, src, size);
}

void Buf_set_byte(Buf buf, idx k, byte x)
{
    Blk_set_byte(buf.blk, k, x);
}

void Buf_extend(Buf * buf, idx size)
{
    Blk_extend(& buf->blk, size);
}

void Buf_extend0(Buf * buf, idx size)
{
    Blk_extend0(& buf->blk, size);
}

void Buf_reserve(Buf * buf, idx size)
{
    if (Buf_capacity(* buf) < size) Buf_extend(buf, size);
}

void Buf_push(Buf * restrict buf, const void * restrict src, idx size)
{
    if (unlikely_(Buf_capacity(* buf) <= size)) Buf_extend(buf, size);

    Buf_inject(* buf, buf->index, src, size);
    buf->index += size;
}

void Buf_push_item(Buf * restrict buf, const void * restrict item, idx size, Put put)
{
    if (unlikely_(Buf_capacity(* buf) <= size)) Buf_extend(buf, size);

    put(Buf_get(* buf, buf->index), item);
    buf->index += size;
}

void Buf_reset(Buf * buf)
{
    buf->index = 0;
}