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
    unsigned short free;
    unsigned short size;
};

unsigned short h_get_free(Heap *heap)
{
	return heap->free;
}


Heap *h_init(unsigned short size)
{
    Heap *h = (Heap *) emalloc(sizeof(Heap));
    h->vector = (Item **) emalloc(size * sizeof(Item *));
    h->size = size-1;
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


void fixup(Heap *h, int i, bool (*cmp)(Item, Item))
{
    while (i > 0 && cmp(h->vector[PARENT(i)], h->vector[i])) {
        h_exch(h, i, PARENT(i));
        i = PARENT(i);
    }
}

void fixdown(Heap *h, int i, int l, bool (*cmp)(Item, Item))
{
    int child;

    /*
     * Iterar até chegar ao penúltimo nível
     * Escolher child para comparar com o pai
     * Comparar com o pai
     * Se o pai não tiver menos prioridade que o filho, está no sítio certo.
     * Se não, temos de trocar o pai e o filho
     * Seguir o pai antigo que agora ocupa a posição do filho antigo
     */

    while (2 * i < l - 1) {
        child = CHILD1(i);

        if (child < l - 1 && cmp(h->vector[child], h->vector[child + 1]))
            child++;

        if (!cmp(h->vector[i], h->vector[child]))
            break;

        h_exch(h, i, child);

        i = child;
    }
}

void h_insert(Heap *h, Item I, bool (*cmp)(Item, Item))
{
	h->vector[h->free] = I;
	fixup(h, h->free, cmp);
	h->free++;
}

Item h_delmax(Heap *h, bool (*cmp)(Item, Item))
{
	/* Swap the first and last nodes */
	h_exch(h, 0, h->free - 1);
	fixdown(h, 0, h->free - 1, cmp);

	return h->vector[--(h->free)];

}

bool h_empty(Heap *h)
{
    return !(h->free);
}

void h_exch(Heap *h, int i1, int i2)
{
	Item tmp;

	tmp = h->vector[i2];
    h->vector[i2] = h->vector[i1];
    h->vector[i1] = tmp;
}

void h_print(Heap *h)
{
    int i;

    printf("free: %d\n", h->free);

    for (i = 0; i < h->free; i++) {
        printf("%d ", *((int *)h->vector[i]));
    }

	puts("");
}

bool h_exists(Heap *h, Item I, bool (*is_equal)(Item, Item))
{
	int i;
	for (i=0; i < h->free; i++)
		if (is_equal(h->vector[i], I))
				return true;

	return false;
}
