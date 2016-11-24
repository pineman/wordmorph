#include <string.h>
#include "item.h"

void exch(Item *i1, Item *i2) 
{
    Item tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;

    return;
}

bool less_pri(Item i1, Item i2)
{
    return i1 > i2;
}
