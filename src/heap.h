#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "item.h"

typedef struct _Heap Heap;

Heap *h_init(unsigned short size);
void h_free(Heap *h, void (*free_item)(Item));

void fixup(Heap *h, int i, bool (*cmp)(Item, Item));
void fixdown(Heap *h, int i, int l, bool (*cmp)(Item, Item));

void h_insert(Heap *h, Item I, bool (*cmp)(Item, Item));
Item h_delmax(Heap *h, bool (*cmp)(Item, Item));

bool h_empty(Heap *h);

void h_exch(Heap *h, int i1, int i2);

bool h_exists(Heap *h, Item I, bool (*is_equal)(Item, Item));

void h_print(Heap *h);

#endif
