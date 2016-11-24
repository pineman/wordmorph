#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "heap.h"

int main(int argc, char **argv) 
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;
    h_init(10);
    for (i=0; i<10; i++) {
        printf("ola\n");
        h_insert(&(array[i]));
    }

    printf("%d\n", h_empty());


	return EXIT_SUCCESS;
}
