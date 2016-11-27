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
    Secret **vector;
    unsigned short free;
    unsigned short size;
};



Heap *h_init(unsigned short size)
{
    Heap *h = (Heap *) emalloc(sizeof(Heap));
    h->vector = (Secret **) emalloc(size * sizeof(Secret *)); 
    h->size = size-1;
    h->free = 0;

    return h;
}


void h_free(Heap *h, void (*free_item(Secret))) 
{
    int i;
    for (i=0; i<h->size; i++)
        free_item(h->vector[i]);
    free(h);
}



void fixup(Heap *h, int i, bool (*cmp)(Secret, Secret))
{
    while (i > 0 && cmp(h->vector[PARENT(i)], h->vector[i])) {
        h_exch(h, i, PARENT(i));
        i = PARENT(i);
    }
}

void fixdown(Heap *h, int i, int l, bool (*cmp)(Secret, Secret))
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


void h_insert(Heap *h, Secret I, bool (*cmp)(Secret, Secret))
{
    if ((h->free) <= h->size)  {
        h->vector[h->free] = I;
        fixup(h, h->free, cmp);
        h->free++;
        printf("free no insert: %d\n", h->free);
    }
    else {
        puts("Erro: A heap está cheia, impossivel inserir");
        exit(EXIT_FAILURE);
    }
}


Secret h_delmax(Heap *h, bool (*cmp)(Secret, Secret))
{
	/* Swap the first and last nodes */
	h_exch(h, 0, h->free - 1);
	fixdown(h, 0, h->free - 1, cmp);

    --(h->free);
    printf("free no delmax: %d\n", h->free);
	return h->vector[h->free];

}

bool h_empty(Heap *h) 
{
    return !(h->free);
}

void h_exch(Heap *h, int i1, int i2)
{
    if (h->vector[i1] == NULL || h->vector[i2] == NULL)
        printf("Erro: estas a tentar trocar NULL pointers (não vou crashar)!\n");
    h->vector[i1] = h->vector[i2];
    h->vector[i2] = h->vector[i1]; 

    return;
}

void h_print(Heap *h)
{
    printf("free: %d\n", h->free);
    int i=0;
    for (i=0; i<h->free; i++)
        printf("%d\n", *((int *)h->vector[i]));
}