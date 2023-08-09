#include "sort.h"
#include "mem_macro.h"

#include <stdlib.h>

static inline idx _pivot_idx(View view, Cmp cmp, Put put)
{
    (void) cmp;
    (void) put;
    
    return rand() % View_len(view);
}

static inline idx _partition(View view, Cmp cmp, Swap swap, Put put)
{
    void *  pivot;
    idx     pivot_idx;

    pivot_idx = _pivot_idx(view, cmp, put);
    swap(View_get(view, pivot_idx), View_last(view));
    pivot = View_last(view);
    pivot_idx = -1;

    for (idx current = 0; current < View_len(view) - 1; current ++)
    {
        if (cmp(pivot, View_get(view, current)) > 0)
        {
            pivot_idx ++;
            swap(View_get(view, pivot_idx), View_get(view, current));
        }
    }

    pivot_idx ++;
    swap(pivot, View_get(view, pivot_idx));

    return pivot_idx;
}

#define LIMIT (1 << 5)
void sort_quick(View view, Cmp cmp, Swap swap, Put put)
{
    idx pivot_idx;

    if (View_len(view) <= LIMIT) return sort_insert(view, cmp, put);

    pivot_idx = _partition(view, cmp, swap, put);

    sort_quick(View_view(view, 0, pivot_idx), cmp, swap, put);
    sort_quick(View_view(view, pivot_idx + 1, View_len(view) - pivot_idx - 1), cmp, swap, put);
}