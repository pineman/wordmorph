#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "item.h"

void fixup(int Idx);
void fixdown(int Idx, int N);
void h_init();
bool h_empty();
void h_insert(Item);
Item h_delmax();




#endif
