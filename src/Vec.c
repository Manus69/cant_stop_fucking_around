#include "Vec.h"
#include "macro.h"

#define VEC_DC (1 << 3)

Vec Vec_ctr(Buf buf, idx item_size)
{
    return (Vec)
    {
        .buf = buf,
        .item_size = item_size,
    };
}

Vec Vec_new(idx capacity, idx item_size)
{
    return Vec_ctr(Buf_new(capacity * item_size), item_size);
}

Vec Vec_new_dc(idx item_size)
{
    return Vec_new(VEC_DC, item_size);
}

void Vec_del(Vec * vec)
{
    Buf_del(& vec->buf);
    to0_(vec, Vec);
}

idx Vec_len(Vec vec)
{
    return Buf_index(vec.buf) / vec.item_size;
}

idx Vec_size(Vec vec)
{
    return Buf_size(vec.buf);
}

idx Vec_capacity(Vec vec)
{
    return Buf_capacity(vec.buf) / vec.item_size;
}

void * Vec_get(Vec vec, idx k)
{
    return Buf_get(vec.buf, k * vec.item_size);
}

void * Vec_first(Vec vec)
{
    return Vec_get(vec, 0);
}

void * Vec_last(Vec vec)
{
    return Vec_get(vec, Vec_len(vec) - 1);
}

Slc Vec_slice(Vec vec, idx k, idx len)
{
    return Slc_ctr(Vec_get(vec, k), len * vec.item_size);
}

Slc Vec_as_Slc(Vec vec)
{
    return Vec_slice(vec, 0, Vec_len(vec));
}

View Vec_view(Vec vec, idx k, idx len)
{
    return View_ctr(Vec_slice(vec, k, len), vec.item_size);
}

View Vec_as_View(Vec vec)
{
    return View_ctr(Vec_as_Slc(vec), vec.item_size);
}

void Vec_map(Vec vec, F f)
{
    return View_map(Vec_as_View(vec), f);
}

void Vec_erase(Vec * vec, F f)
{
    Vec_map(* vec, f);
    Vec_del(vec);
}

void Vec_reserve(Vec * vec, idx len)
{
    Buf_reserve(& vec->buf, len * vec->item_size);
}

void Vec_push(Vec * restrict vec, const void * restrict item, Put put)
{
    Buf_push_item(& vec->buf, item, vec->item_size, put);
}