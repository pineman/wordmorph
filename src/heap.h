#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "item.h"



void exch(Item *i1, Item *i2);
bool less_pri(Item i1, Item i2, int *wt);
void fixup(int i, int *wt);
void fixdown(int i, int l, int *wt);
void h_init(unsigned Size);
void h_free();
void h_insert(Item I, int *wt);
Item h_delmax(int *wt);
bool h_empty();

#endif
