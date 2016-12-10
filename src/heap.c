/**
 * @file heap.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do algoritmo de Dijkstra.
 * @details
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "bool.h"
#include "utils.h"

#define CHILD1(i) ((2*(i))+1)
#define CHILD2(i) ((2*(i))+2)
#define PARENT(i) (((i)-1)/2)

/*
 * Interface das heaps
 */

struct _Heap {
	Item **vector;
	unsigned short *hash_table;
	/* free é o índice da primeira posição livre, logo,
	 * o último elemento encotra-se posição free - 1 */
	unsigned short free;
	unsigned short size;
};


Heap *h_init(unsigned short size)
{
	Heap *h = (Heap *) emalloc(sizeof(Heap));
	h->vector = (Item **) emalloc(size * sizeof(Item *));
	h->hash_table = (unsigned short *) ecalloc(size, sizeof(unsigned short));
	h->size = size;
	h->free = 0;

	return h;
}

/* TODO: devia ter free_item? mas depois é chato
 * porque o nosso item não pode ser free()'d. */
void h_free(Heap *h)
{
	free(h->vector);
	free(h->hash_table);
	free(h);
}


void h_fixup(Heap *h, int i, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	while (i > 0 && less_pri(h->vector[PARENT(i)], h->vector[i])) {
		h_exch(h, i, PARENT(i), hash);
		i = PARENT(i);
	}
}

void h_fixdown(Heap *h, int i, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	int child;

	/* Iterar até chegar ao penúltimo nível da árvore inclusivé */
	while (2 * i < h->free - 1) {
		child = CHILD1(i);

		/* Escolher o filho com maior prioridade, para comparar com o pai */
		if (child < h->free - 1 && less_pri(h->vector[child], h->vector[child + 1])) {
			/* O outro filho tem mais prioridade! */
			child++;
		}

		/* Se o pai tiver mais (não tiver menos) prioridade que o filho,
		 * o filho está então no sítio certo na heap. */
		if (!less_pri(h->vector[i], h->vector[child])) {
			break;
		}

		/* Se não, temos de trocar o pai com o filho */
		h_exch(h, i, child, hash);

		/* Continuar a iterar a árvore para baixo, seguindo o pai antigo
		 * que agora ocupa a posição do filho antigo */
		i = child;
	}
}

void h_insert(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	h->vector[h->free] = a;
	h->hash_table[hash(a)] = h->free;

	h_fixup(h, h->free, less_pri, hash);
	h->free++;
}

Item h_del_max_pri(Heap *h, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	/* Trocar o último elemento com o primeiro. */
	h_exch(h, 0, h->free - 1, hash);

	/* Ignorar o último elemento, pois vai ser removido. */
	h->free--;

	/* Encontrar o sítio certo do antigo último elemento
	 * (agora na posição 0) */
	h_fixdown(h, 0, less_pri, hash);

	return h->vector[h->free];
}

unsigned short h_find(Heap *h, Item a, unsigned short (*hash)(Item))
{
	return h->hash_table[hash(a)];
}

void h_inc_pri(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	h_fixup(h, h_find(h, a, hash), less_pri, hash);
}

void h_exch(Heap *h, unsigned short i1, unsigned short i2, unsigned short (*hash)(Item))
{
	Item tmp;
	unsigned short tmp_i;

	/* Atualizar hash table */
	tmp_i = h->hash_table[hash(h->vector[i2])];
	h->hash_table[hash(h->vector[i2])] = h->hash_table[hash(h->vector[i1])];
	h->hash_table[hash(h->vector[i1])] = tmp_i;

	/* Troca é fácil pois apenas trabalhamos com Items (ponteiros!) */
	tmp = h->vector[i2];
	h->vector[i2] = h->vector[i1];
	h->vector[i1] = tmp;
}

bool h_empty(Heap *h)
{
	return !(h->free);
}


/* TODO: print function */
#include "graph.h"
void h_print(Heap *h, Graph *g)
{
	int i;

	printf("free: %d\n", h->free);

	for (i = 0; i < h->free; i++) {
		printf("%d:%s:%d ", *((int *)h->vector[i]), (char *) v_get_item(v_get(g, *((int *)h->vector[i]))), i);
	}

	puts("\n");

	for (i = 0; i < h->size; i++) {
		printf("%d:%s:%hu ", i, (char *) v_get_item(v_get(g, i)), h->hash_table[i]);
	}

	puts("\n");
}
