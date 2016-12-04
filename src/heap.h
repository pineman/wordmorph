#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "item.h"

typedef struct _Heap Heap;

Heap *h_init(unsigned short size);
void h_free(Heap *h);

void h_fixup(Heap *h, int i, bool (*less_pri)(Item, Item));
void h_fixdown(Heap *h, int i, bool (*less_pri)(Item, Item));

void h_insert(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item));
Item h_del_max_pri(Heap *h, bool (*less_pri)(Item, Item));

unsigned short h_find(Heap *h, Item a, unsigned short (*hash)(Item));
void h_inc_pri(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item));

void h_exch(Heap *h, unsigned short i1, unsigned short i2);
bool h_empty(Heap *h);

/* TODO: print function */
#include "graph.h"
void h_print(Heap *h, Graph *g);

#endif
