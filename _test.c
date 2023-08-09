#include "mem.h"
#include "dbg.h"

mem_put_gen(idx)
mem_cmp_gen(idx)
mem_swap_gen(idx)

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
#define FILE "txt.txt"
void test_io()
{
    Vec v = io_read_txt_by_line(FILE);
    // Vec_map(v, dbg_Str);
    dbg_Str(Vec_last(v));

    Vec_erase(& v, (F) Str_del);
}

#include "sort.h"
void test_sort(idx n)
{
    Vec v = Vec_new_(idx);
    for (idx k = 0; k < n; k ++)
    {
        Vec_push_(& v, n - k, idx);
    }

    View w = Vec_as_View(v);
    // sort_insert(w, cmp_idx, put_idx);
    // sort_merge(w, cmp_idx, put_idx);

    sort_quick(w, cmp_idx, swap_idx, put_idx);
    View_map(w, dbg_idx);
    dbg_idx(View_last(w));

    Vec_del(& v);
}

void test_sort2()
{
    Str s = Str_from_cstr("3 2 1  22");
    Vec v = Str_split(s, ' ');
    sort_(v, Vec, Str);

    Vec_map(v, dbg_Str);
    Vec_erase(& v, (F) Str_del);
    Str_del(& s);
}

void test_io2()
{
    Vec v = io_read_txt_by_line(FILE);
    sort_(v, Vec, Str);

    // View w = Vec_as_View(v);
    // sort_insert(w, cmp_Str, put_Str);
    // sort_merge(w, cmp_Str, put_Str);

    // Vec_map(v, dbg_Str);
    dbg_Str(Vec_last(v));
    Vec_erase(& v, (F) Str_del);
}

void test_io3()
{
    Str s = Str_vjoin("go", "fuck", "yourself", "\n\n\n", "retard", " !");
    io_create_file(FILE);
    idx status = io_write(Str_as_Buf(s), FILE);

    dbg_idx(& status);
    Str_del(& s);
}

//rng
int main()
{
    // test_Vec(1 << 25);
    // test_Str();
    // test_sort(1 << 25);
    // test_sort2();

    // test_io();
    test_io2();
    // test_io3();
}