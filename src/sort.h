#ifndef SORT_H
#define SORT_H

#include "View.h"

#define sort_(container, c_type, i_type) \
{View _w = c_type##_as_View(container); sort_merge(_w, cmp_##i_type, put_ ##i_type);}

void sort_insert(View view, Cmp cmp, Put put);
void sort_merge(View view, Cmp cmp, Put put);
void sort_quick(View view, Cmp cmp, Swap swap, Put put);

#endif