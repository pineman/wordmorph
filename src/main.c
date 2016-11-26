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
        printf("%d\n", *((int *) (g_get_item(g_get_node(graph, i)))));
    }

    g_update_links(graph, calc_weight);

    printf("Adj\n:");
    for (i=0; i<10; i++){
        List *aux = g_get_adj(g_get_node(graph, i));
        printf("Nó %d:\n", i);
        while(aux != NULL) {
            printf("Link: %d, %d\n", g_get_index(l_get_item(aux)), g_get_weight(l_get_item(aux)));
            aux = l_get_next(aux);
        }

    }



	return EXIT_SUCCESS;
}


