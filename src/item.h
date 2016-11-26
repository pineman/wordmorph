#ifndef _ITEM_H
#define _ITEM_H

#define Item void*

#include "bool.h"

void exch(Item *, Item *);
bool less_pri(Item i1, Item i2, bool (cmp_item)(Item, Item));

/*unsigned int calc_weight(Item i1, Item i2, unsigned int max);*/

#endif
