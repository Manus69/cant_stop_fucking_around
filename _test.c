
#include "mem.h"
#include "dbg.h"

int main()
{
    void * a = mem_alloc0(100);
    void * b = mem_alloc0(0);

    mem_vmap_(mem_del, a, b);
}