#include <stdlib.h>

#include "dijkstra.h"
#include "utils.h"
#include "graph.h"
#include "heap.h"

 /*TODO: ugly global var*/
static int *wt;

int *shortest_path(Graph *g, int src, int dst, int *st, int max_perm)
{
    int v; /* Index de um vértice */
	int v_adj; /* Index dum vértice adjacente a v */
    List *l; /* Aresta de v para v_adj */
    int i;
    int *array;

    Heap *heap = h_init(g_get_free(g));
    wt = realloc(wt, g_get_free(g) * sizeof(int));


    for (v = 0; v < g_get_free(g); v++) {
        st[v] = -1;
        wt[v] = MAX_WT;
    }

	/*Inicializar a heap apenas com o vertice src*/
    array = (int *) ecalloc(g_get_free(g), sizeof(int));
    for (i = 0; i < g_get_free(g); i++) {
        array[i] = i;
	}

	h_insert(heap, &array[src], cmp);

    wt[src] = 0;

	/* Colocar adjacentes hà medida que vao aparecendo*/
    while (!h_empty(heap)) {
        if ((wt[v = *((int *) h_delmax(heap, cmp))]) != MAX_WT) {
            for (l = v_get_adj(v_get(g, v)); l != NULL; l = l_get_next(l)) {
                v_adj = e_get_index(l_get_item(l));
                if (POT_DIST < wt[v_adj]) {
                    wt[v_adj] = POT_DIST;
                    st[v_adj] = v;
					if (st[v_adj] != -1 && e_get_weight(l_get_item(l)) <= max_perm)
						h_insert(heap, &(array[v_adj]), cmp);
                }
            }
        }
    }

    h_free(heap, free);
    free(array);

	return wt;
}

bool cmp(Item s1, Item s2)
{
    return wt[*((int *) s1)] < wt[*((int *) s2)];
}


bool is_equal(Item s1, Item s2)
{
    return wt[*((int *) s1)] == wt[*((int *) s2)];
}
