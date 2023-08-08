#ifndef VEC_H
#define VEC_H

#include "View.h"
#include "Buf.h"

#define Vec_new_(type) Vec_new_dc(sizeof(type))
#define Vec_push_(vec_ptr, val, type) \
{type _t = val; Vec_push(vec_ptr, & _t, put_## type);}

typedef struct Vec Vec;

struct Vec
{
    Buf buf;
    idx item_size;
};

Vec     Vec_ctr(Buf buf, idx item_size);
Vec     Vec_new(idx capacity, idx item_size);
Vec     Vec_new_dc(idx item_size);
idx     Vec_len(Vec vec);
idx     Vec_size(Vec vec);
idx     Vec_capacity(Vec vec);
Slc     Vec_as_Slc(Vec vec);
Slc     Vec_slice(Vec vec, idx k, idx len);
void *  Vec_get(Vec vec, idx k);
void *  Vec_first(Vec vec);
void *  Vec_last(Vec vec);
View    Vec_view(Vec vec, idx k, idx len);
View    Vec_as_View(Vec vec);
void    Vec_map(Vec vec, F f);
void    Vec_del(Vec * vec);
void    Vec_push(Vec * vec, const void * item, Put put);


#endif