#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "heap.h"
#include "graph.h"

int main(int argc, char **argv)
{
    unsigned int i;
    int **pointers = (int **) malloc(sizeof(int *) * 10);
    Graph *graph = g_init(10, 2);


    for (i=0; i<10; i++) {
        pointers[i] = (int *) malloc(sizeof(int));
        *(pointers[i]) = i;
    }

    for (i=0; i<10; i++) {
        g_insert(graph, pointers[i]);
    }


    printf("Nós:\n");
    for (i=0; i<10; i++) {
        printf("%d\n", *((int *) (v_get_item(v_get(graph, i)))));
    }

    g_update_links(graph, calc_weight);

    printf("Adj:\n");
    for (i=0; i<10; i++){
        List *aux = v_get_adj(v_get(graph, i));
        printf("Nó %d:\n", i);
        while(aux != NULL) {
            printf("Link: %d, %d\n", e_get_index(l_get_item(aux)), e_get_weight(l_get_item(aux)));
            aux = l_get_next(aux);
        }

    }

    for (i=0; i<10; i++) {
		free(pointers[i]);
    }
	free(pointers);
    g_free(graph, free);

	return EXIT_SUCCESS;
}


