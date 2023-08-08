#include "mem.h"
#include "dbg.h"

mem_put_gen(idx)

#include "Vec.h"
void test_Vec(idx n)
{
    Vec v = Vec_new_(idx);
    for (idx k = 0; k < n; k ++)
    {
        Vec_push_(& v, n - k, idx);
    }

    // Vec_map(v, dbg_idx);
    dbg_idx(Vec_last(v));
    Vec_del(& v);
}

int main()
{
    test_Vec(1 << 25);
}