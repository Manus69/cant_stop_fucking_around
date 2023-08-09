#include "sort.h"
#include "mem.h"
#include "dbg.h"

void sort_insert(View view, Cmp cmp, Put put)
{
    void *  buff;
    idx     current;

    buff = mem_alloc0(View_item_size(view));
    for (idx sorted = 1; sorted < View_len(view); sorted ++)
    {
        put(buff, View_get(view, sorted));
        for (current = sorted - 1; current >= 0; current --)
        {
            if (cmp(View_get(view, current), buff) <= 0) break ;
            put(View_get(view, current + 1), View_get(view, current));
        }

        current ++;
        put(View_get(view, current), buff);
    }

    mem_del(buff);
}