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

#include "Str.h"
void test_Str()
{
    Str s = Str_vjoin("eat ", "my", " ass");
    dbg_Str(& s);

    Vec v = Str_split(s, ' ');
    Vec_map(v, dbg_Str);

    Vec_erase(& v, (F) Str_del);
    Str_del(& s);

}

#include "io.h"
void test_io()
{
    Vec v = io_read_txt_by_line("txt.txt");
    // Vec_map(v, dbg_Str);
    dbg_Str(Vec_last(v));

    Vec_erase(& v, (F) Str_del);
}

//vec reserve
//src folder
int main()
{
    // test_Vec(1 << 25);
    // test_Str();
    test_io();
}