#ifndef VIEW_H
#define VIEW_H

#include "Slc.h"

typedef struct View View;

struct View
{
    Slc slc;
    idx item_size;
};

#endif