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



Heap *h_init(unsigned short size)
{
    Heap *h = (Heap *) emalloc(sizeof(Heap));
    h->vector = (Item **) emalloc(size * sizeof(Item *));
    h->size = size-1;
    h->free = 0;

    return h;
}


void h_free(Heap *h, void (*free_item)(Item))
{
    int i;
    for (i = 0; i <= h->size; i++) {
        free_item(h->vector[i]);
	}

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
    if ((h->free) <= h->size)  {
        h->vector[h->free] = I;
        fixup(h, h->free, cmp);
        h->free++;
    }
    else {
        puts("Erro: A heap está cheia, impossivel inserir");
        exit(EXIT_FAILURE);
    }
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

    if (h->vector[i1] == NULL || h->vector[i2] == NULL) {
        printf("Erro: estas a tentar trocar NULL pointers (não vou crashar)!\n");
    }

	tmp = h->vector[i2];
    h->vector[i2] = h->vector[i1];
    h->vector[i1] = tmp;

    return;
}

void h_print(Heap *h)
{
    int i;

    printf("free: %d\n", h->free);

    for (i=0; i<h->free; i++)
        printf("%d ", *((int *)h->vector[i]));

    /*putchar('\n');*/
}
