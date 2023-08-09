#include "View.h"
#include "mem.h"

View View_ctr(Slc slc, idx item_size)
{
    return (View)
    {
        .slc = slc,
        .item_size = item_size,
    };
}

View View_from_ptr(void * ptr, idx len, idx item_size)
{
    return View_ctr(Slc_ctr(ptr, len * item_size), item_size);
}

idx View_len(View view)
{
    return Slc_size(view.slc) / view.item_size;
}

void * View_get(View view, idx k)
{
    return Slc_get(view.slc, k * view.item_size);
}

void * View_first(View view)
{
    return View_get(view, 0);
}

void * View_last(View view)
{
    return View_get(view, View_len(view) - 1);
}

void View_map(View view, F f)
{
    mem_raw_map(f, View_first(view), view.item_size, View_len(view));
}

Slc View_as_Slc(View view)
{
    return view.slc;
}

View View_view(View view, idx k, idx len)
{
    return View_from_ptr(View_get(view, k), len, view.item_size);
}

View View_chop_front(View * view, idx len)
{
    return View_ctr(Slc_chop_front(& view->slc, len * view->item_size), view->item_size);
}

View View_chop_all(View * view)
{
    return View_ctr(Slc_chop_all(& view->slc), view->item_size);
}

View View_chop_front_check(View * view, idx len)
{
    return View_ctr(Slc_chop_front_check(& view->slc, len * view->item_size), view->item_size);
}

idx View_find(View view, const void * item, Cmp cmp)
{
    for (idx k = 0; k < View_len(view); k ++)
    {
        if (cmp(View_get(view, k), item) == 0) return k;
    }

    return NO_IDX;
}

void View_shift(View * view, idx len)
{
    Slc_shift(& view->slc, len * view->item_size);
}

void * View_pop_front(View * view)
{
    void * ptr;

    ptr = View_first(* view);
    View_shift(view, view->item_size);

    return ptr;
}