/**
 * @file heap.h
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação da biblioteca de acervos.
 * @details
 * Implementação de uma fila prioritária utilizando acervos.
 *
 */
#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include "item.h"

typedef struct _Heap Heap;

Heap *h_init(unsigned short size);
void h_free(Heap *h);

void h_fixup(Heap *h, int i, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item));
void h_fixdown(Heap *h, int i, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item));

void h_insert(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item));
Item h_del_max_pri(Heap *h, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item));

unsigned short h_find(Heap *h, Item a, unsigned short (*hash)(Item));
void h_inc_pri(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item));

void h_exch(Heap *h, unsigned short i1, unsigned short i2, unsigned short (*hash)(Item));
bool h_empty(Heap *h);

#endif
