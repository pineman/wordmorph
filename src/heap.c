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
	/* free é o índice da primeira posição livre, logo,
	 * o último elemento encotra-se posição free - 1 */
	unsigned short free;
	unsigned short size;
};


Heap *h_init(unsigned short size)
{
	Heap *h = (Heap *) emalloc(sizeof(Heap));
	h->vector = (Item **) emalloc(size * sizeof(Item *));
	h->size = size - 1;
	h->free = 0;

	return h;
}

/* TODO: devia ter free_item? mas depois é chato
 * porque o nosso item não pode ser free()'d. */
void h_free(Heap *h)
{
	free(h->vector);
	free(h);
}


void h_fixup(Heap *h, int i, bool (*less_pri)(Item, Item))
{
	while (i > 0 && less_pri(h->vector[PARENT(i)], h->vector[i])) {
		h_exch(h, i, PARENT(i));
		i = PARENT(i);
	}
}

void h_fixdown(Heap *h, int i, bool (*less_pri)(Item, Item))
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
		h_exch(h, i, child);

		/* Continuar a iterar a árvore para baixo, seguindo o pai antigo
		 * que agora ocupa a posição do filho antigo */
		i = child;
	}
}

void h_insert(Heap *h, Item I, bool (*less_pri)(Item, Item))
{
	#include <assert.h>
	assert(h->free < h->size);

	h->vector[h->free] = I;
	h_fixup(h, h->free, less_pri);
	h->free++;
}

Item h_del_max_pri(Heap *h, bool (*less_pri)(Item, Item))
{
	/* Trocar o último elemento com o primeiro. */
	h_exch(h, 0, h->free - 1);

	/* Ignorar o último elemento, pois vai ser removido. */
	h->free--;

	/* Encontrar o sítio certo do antigo último elemento
	 * (agora na posição 0) */
	h_fixdown(h, 0, less_pri);

	return h->vector[h->free];

}

bool h_empty(Heap *h)
{
	return !(h->free);
}

void h_exch(Heap *h, int i1, int i2)
{
	Item tmp;

	/* Troca é fácil pois apenas trabalhamos com Items (pointeiros!) */
	tmp = h->vector[i2];
	h->vector[i2] = h->vector[i1];
	h->vector[i1] = tmp;
}

/* TODO: print function */
#include "graph.h"
void h_print(Heap *h, Graph *g)
{
	int i;

	printf("free: %d\n", h->free);

	for (i = 0; i < h->free; i++) {
		printf("%d:%s ", *((int *)h->vector[i]), (char *) v_get_item(v_get(g, *((int *)h->vector[i]))));
	}

	puts("\n");
}
