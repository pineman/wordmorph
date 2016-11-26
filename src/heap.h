#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "item.h"

void fixup(int Idx, bool (*cmp)(Item i1, Item i2));
void fixdown(int Idx, int N, bool (*cmp)(Item i1, Item i2));
void h_init();
bool h_empty();
void h_insert(Item I, bool(*cmp)(Item i1, Item i2));
Item h_delmax();




#endif
