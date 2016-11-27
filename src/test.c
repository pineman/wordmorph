#include "heap.h"
#include "utils.h"
#include "bool.h"

bool cmp(Secret i1, Secret i2)
{
    return *((int *)i1) < *((int *) i2);
}

int main(int argc, char const *argv[])
{
    int i;

    Heap *heap = h_init(20);
    
    int **array = (int **) emalloc(20 * sizeof(int *));

    for (i=0; i<20; i++) {
        array[i] = (int *) emalloc(sizeof(int));
        *(array[i]) = 20 - i;
    }
    for (i=0; i<20; i++)
        h_insert(heap, array[i], cmp);

    h_print(heap);

    for (i=0; i<20; i++) {
        printf("indice: %d \t", i);
        printf("valor: %d\n", *((int *)h_delmax(heap, cmp)));
    }

    return 0;
}