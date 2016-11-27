#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "secret.h"

typedef struct _Heap Heap;

/*void h_init(unsigned short Size);
void h_free();

void exch(Secret *i1, Secret *i2);
bool less_pri(Secret i1, Secret i2, int *wt);
void fixup(int i, int *wt);
void fixdown(int i, int l, int *wt);

void h_insert(Secret I, int *wt);
Secret h_delmax(int *wt);
bool h_empty();*/

Heap *h_init(unsigned short size);
void h_free(Heap *h, void (*free_item(Secret))); 

void fixup(Heap *h, int i, bool (*cmp)(Secret, Secret));
void fixdown(Heap *h, int i, int l, bool (*cmp)(Secret, Secret));

void h_insert(Heap *h, Secret I, bool (*cmp)(Secret, Secret));
Secret h_delmax(Heap *h, bool (*cmp)(Secret, Secret));

bool h_empty(Heap *h);

void h_exch(Heap *h, int i1, int i2);

void h_print(Heap *h);

#endif
