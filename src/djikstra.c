#include "djikstra.h"
#include "utils.h"

 /*TODO: ugly global var*/ 
static int *wt;

void shortest_path(Graph *g, int src, int *st)
{
    int v; /* Index de um vértice */
	int v_adj; /* Index dum vértice adjacente a v */
    int *n;
    List *l; /* Aresta de v para v_adj */

    Heap *heap = h_init(g_get_free(g));
    wt = realloc(wt, g_get_free(g) * sizeof(int));
    
	/* Encher a Heap com todos os vértices */
    for (v = 0; v < g_get_free(g); v++) {
        st[v] = -1;
        wt[v] = MAX_WT;
        n = (int *) emalloc(sizeof(int));
        *n = v;
        h_insert(heap, n, cmp);
    }

    wt[src] = 0;
    fixup(heap, src, cmp);
    while (!h_empty(heap)) {
        if (wt[v = *((int *) h_delmax(heap, cmp))] != MAX_WT) {
            for (l = v_get_adj(v_get(g, v)); 
                 l != NULL; 
                 l = l_get_next(l)) 
            {
                v_adj = e_get_index(l_get_item(l));
                if (POT_DIST < wt[v_adj]) {
                    wt[v_adj] = POT_DIST;
                    fixup(heap, v_adj, cmp);
                    st[v_adj] = v;
                }
            }
        }
    }
}

bool cmp(Secret s1, Secret s2)
{
    return wt[*((int *) s1)] < wt[*((int *) s2)];
}
