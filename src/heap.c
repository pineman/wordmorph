#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "graph.h"
#include "bool.h"

#define CHILD1(i) ((2*(i))+1)
#define CHILD2(i) ((2*(i))+2)
#define PARENT(i) (((i)-1)/2)

static Item *heap;
static int avail;
static int hsize;

/* TODO: ITEM É INT!!! */

/* TODO: A heap tem de saber da array wt para saber
 * comparar distâncias (prioridades) */

void fixup(int i, bool (*cmp)(Item i1, Item i2))
{
    while (i > 0 && less_pri(heap[PARENT(i)], heap[i], cmp)) {
        exch(heap[i], heap[PARENT(i)]);
        i = PARENT(i);
    }
}

void fixdown(int i, int l, bool (*cmp)(Item i1, Item i2))
{
    int child;

	/* Iterar até chegar ao penúltimo nível */
    while (2 * i < l - 1) {
        child = CHILD1(i);
		/* Escolher child para comparar com o pai */
        if (child < l - 1 && less_pri(heap[child], heap[child + 1], cmp))
			child++;

		/* Comparar com o pai */
        if (!less_pri(heap[i], heap[child], cmp)) {
			/* Se o pai não tiver menos prioridade que o filho, está
			 * no sítio certo. */
			break;
		}

		/* Se não, temos de trocar o pai e o filho */
        exch(heap[i], heap[child]);
        /* Seguir o pai antigo que agora ocupa a posição do filho antigo */
        i = child;
    }
}

void h_init(unsigned Size)
{
    heap = (Item *) malloc(Size * sizeof(Item));
    hsize = Size;
    avail = 0;
}

void h_free() {
	free(heap);
}

void h_insert(Item I, bool (*cmp)(Item i1, Item i2))
{
    if ((avail) < hsize)  {
        heap[avail] = I;
        fixup(avail, cmp);
        avail++;
    }
    else {
        puts("Erro: A heap está cheia, impossivel inserir");
        exit(EXIT_FAILURE);
    }
}

Item h_delmax(bool (*cmp) (Item i1, Item i2))
{
	/* Swap the first and last nodes */
	exch(heap[0], heap[avail-1]);
	fixdown(0, avail - 1, cmp);

	return heap[--avail];
}

bool h_empty() {
    return !avail;
}
