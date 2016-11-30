#include <stdlib.h>

#include "dijkstra.h"
#include "utils.h"
#include "graph.h"
#include "heap.h"

 /*TODO: ugly global var*/
static int *wt;

int *shortest_path(Graph *g, int src, int *st, int max_perm)
{
    int v; /* Index de um vértice */
	int v_adj; /* Index dum vértice adjacente a v */
    List *l; /* Aresta de v para v_adj */
    int *n;
	Item V;

    Heap *heap = h_init(g_get_free(g));
    wt = realloc(wt, g_get_free(g) * sizeof(int));
	

    for (v = 0; v < g_get_free(g); v++) {
        st[v] = -1;
        wt[v] = MAX_WT;
    }

	/*Inicializar a heap apenas com o vertice src*/
	n = (int *) emalloc(sizeof(int));
	*n = src;
	h_insert(heap, n, cmp);

    wt[src] = 0;

	/* Colocar adjacentes hà medida que vao aparecendo*/
    while (!h_empty(heap)) {
		V = h_delmax(heap, cmp);
		v = *((int *) V);
		free(V);
        if (wt[v] != MAX_WT) {
            for (l = v_get_adj(v_get(g, v));
                 l != NULL;
                 l = l_get_next(l))
            {
                v_adj = e_get_index(l_get_item(l));
                if (POT_DIST < wt[v_adj]) {
                    wt[v_adj] = POT_DIST;
                    st[v_adj] = v;
					n = (int *) emalloc(sizeof(int));
					*n = v_adj;
					if (st[v_adj] != -1)
						h_insert(heap, n, cmp);
                }
            }
			
        }
    }

    h_free(heap, free);
	printf("did the dijkstra\n");

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
