#ifndef SORT_H
#define SORT_H

#include "View.h"

void sort_insert(View view, Cmp cmp, Put put);
void sort_merge(View view, Cmp cmp, Put put);

#endif