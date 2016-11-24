#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

static Item *heap;
static int avail; 
static int hsize;

void FixUp(int Idx)
{
    while (Idx > 0  &&  less_pri(heap[(Idx-1)/2], heap[Idx])) {
        exch(heap[Idx], heap[(Idx-1)/2]);
        Idx = (Idx-1)/2;
    }
}

void FixDown(int Idx, int N) 
{
    int child; /* índice de um nó descendente */
    while(2*Idx < N - 1) { /* enquanto não chegar às folhas */
        child = 2*Idx + 1;
        /* Selecciona o maior descendente.                         */
        /* Nota: se índice Child é N-1, então só há um descendente */
        if (Child < (N - 1) && less_pri(heap[child], heap[child + 1])) child++;
        if (!less_pri(heap[Idx], heap[child])) break; /* condição acervo */
        /* satisfeita      */
        exch(heap[Idx], heap[hild]);
        /* continua a descer a árvore */
        Idx = child;
        }
}

void h_init(unsigned Size) {
    heap = (Item *) malloc(Size * sizeof(Item));
    hsize = Size; 
    avail = 0;
}

void h_insert(Item I) {
    if ((avail) < hsize) 
        index[avail] = I; 
        FixUp(index, avail);
        avail++;
    else {
        puts("Erro: A heap está cheia, impossivel inserir");
        exit(EXIT_FAILURE);
    }
}

/*Item PQdelmax() {

    exch(index[0], index[avail-1]);
    FixDown(index, 0, avail-1); 

    return index[--avail]; 
}*/

bool h_empty() {    
    return avail ? true : false;
}
