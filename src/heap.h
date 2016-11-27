#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "secret.h"

typedef struct _Heap Heap;

Heap *h_init(unsigned short size);
void h_free(Heap *h, void (*free_item)(Secret)); 

void fixup(Heap *h, int i, bool (*cmp)(Secret, Secret));
void fixdown(Heap *h, int i, int l, bool (*cmp)(Secret, Secret));

void h_insert(Heap *h, Secret I, bool (*cmp)(Secret, Secret));
Secret h_delmax(Heap *h, bool (*cmp)(Secret, Secret));

bool h_empty(Heap *h);

void h_exch(Heap *h, int i1, int i2);

void h_print(Heap *h);

#endif
