#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "item.h"

typedef struct _Heap Heap;

Heap *h_init(unsigned short size);
void h_free(Heap *h);

void h_fixup(Heap *h, int i, bool (*less_pri)(Item, Item));
void h_fixdown(Heap *h, int i, bool (*less_pri)(Item, Item));
void h_insert(Heap *h, Item I, bool (*less_pri)(Item, Item));
Item h_del_max_pri(Heap *h, bool (*less_pri)(Item, Item));
bool h_empty(Heap *h);

void h_exch(Heap *h, int i1, int i2);

/* TODO: print function */
#include "graph.h"
void h_print(Heap *h, Graph *g);

#endif
