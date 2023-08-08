#ifndef VIEW_H
#define VIEW_H

#include "Slc.h"

typedef struct View View;

struct View
{
    Slc slc;
    idx item_size;
};

View    View_ctr(Slc slc, idx item_size);
View    View_from_ptr(void * ptr, idx len, idx item_size);
idx     View_len(View view);
void *  View_get(View view, idx k);
void *  View_first(View view);
void *  View_last(View view);
void    View_map(View view, F f);
Slc     View_as_Slc(View view);
View    View_view(View view, idx k, idx len);
View    View_chop_front(View * view, idx len);
View    View_chop_all(View * view);
View    View_chop_front_check(View * view, idx len);
idx     View_find(View view, const void * item, Cmp cmp);

#endif