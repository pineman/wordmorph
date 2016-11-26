#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "graph.h"

static Item *heap;
static int avail; 
static int hsize;

void fixup(int Idx)
{
    while (Idx > 0  &&  less_pri(heap[(Idx-1)/2], heap[Idx], e_cmp_edges)) {
        exch(heap[Idx], heap[(Idx-1)/2]);
        Idx = (Idx-1)/2;
    }
}

void fixdown(int Idx, int N) 
{
    int child;
    while(2*Idx < N - 1) {
        child = 2*Idx + 1;
        if (child < (N - 1) && less_pri(heap[child], heap[child + 1], e_cmp_edges)) 
			child++;
        if (!less_pri(heap[Idx], heap[child], e_cmp_edges)) 
			break;
        exch(heap[Idx], heap[child]);
        Idx = child;
        }
}

void h_init(unsigned Size) 
{
    heap = (Item *) malloc(Size * sizeof(Item));
    hsize = Size; 
    avail = 0;
}

void h_insert(Item I) 
{
    if ((avail) < hsize)  {
        heap[avail] = I; 
        fixup(avail);
        avail++;
    }
    else {
        puts("Erro: A heap está cheia, impossivel inserir");
        exit(EXIT_FAILURE);
    }
}

Item h_delmax() 
{
	exch(heap[0], heap[avail-1]);
	fixdown(0, avail-1); 
	return heap[--avail]; 
}

bool h_empty() {    
    return avail ? true : false;
}
