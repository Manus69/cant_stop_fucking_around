#include "sort.h"
#include "Buf.h"

static inline void _drop(Buf * buf, View * view, Put put)
{
    Buf_push_item(buf, View_pop_front(view), View_item_size(* view), put);
}

static inline void _dump(Buf * buf, View view)
{
    Buf_push(buf, View_first(view), View_size(view));
}

static inline void _dump_all(Buf * buf, View lhs, View rhs)
{
    _dump(buf, lhs);
    _dump(buf, rhs);
}

static inline bool _is_sorted(View lhs, View rhs, Cmp cmp)
{
    return View_empty(rhs) || (cmp(View_last(lhs), View_first(rhs)) < 0);
}

static inline void _merge(Buf * buf, View lhs, View rhs, Cmp cmp, Put put)
{
    if (_is_sorted(lhs, rhs, cmp)) return _dump_all(buf, lhs, rhs);

    while (true)
    {
        if (View_empty(rhs)) return _dump(buf, lhs);
        if (View_empty(lhs)) return _dump(buf, rhs);

        if (cmp(View_first(lhs), View_first(rhs)) < 0) _drop(buf, & lhs, put);
        else _drop(buf, & rhs, put);
    }
}

static void _pass(Buf * buf, View src, idx frame, Cmp cmp, Put put)
{
    View lhs;
    View rhs;

    while (View_empty(src) == false)
    {
        lhs = View_chop_front_prob(& src, frame);
        rhs = View_chop_front_prob(& src, frame);

        _merge(buf, lhs, rhs, cmp, put);
    }
}

static idx _preprocess(View view, idx frame, Cmp cmp, Put put)
{
    View current;

    while (likely_(View_empty(view) == false))
    {
        current = View_chop_front_prob(& view, frame);
        sort_insert(current, cmp, put);
    }

    return frame;
}

#define PRPR_FRAME (1 << 4)
void sort_merge(View view, Cmp cmp, Put put)
{
    Buf buf;
    idx frame;
    idx n_swaps;

    buf = Buf_new(View_size(view) + View_item_size(view));
    frame = _preprocess(view, PRPR_FRAME, cmp, put);
    n_swaps = 0;

    while (frame <= View_len(view))
    {
        _pass(& buf, view, frame, cmp, put);
        frame <<= 1;

        mem_swap_(& buf.blk.data, & view.slc.ptr, void *);
        Buf_reset(& buf);
        n_swaps ++;
    }

    if (n_swaps % 2)
    {
        mem_swap_(& buf.blk.data, & view.slc.ptr, void *);
        View_inject(view, 0, Buf_first(buf), View_len(view));
    }

    Buf_del(& buf);
}