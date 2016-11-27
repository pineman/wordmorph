#include "djikstra.h"


/*Implementação do algoritmo de Djikstra*/
/* st: árvore de caminhos mais curtos de src para todos os outros vértices */

/*
 * TODO: DOES NO WORK
 * 
 * 
 */
void shortest_path(Graph *g, int src, int *st, int *wt)
{
    int v; /* Index de um vértice */
	int v_adj; /* Index dum vértice adjacente a v */
    List *l; /* Aresta de v para v_adj */

    h_init(g_get_free(g));

	/* Encher a Heap com todos os vértices */
    for (v = 0; v < g_get_free(g); v++) {
        st[v] = -1;
        wt[v] = MAX_WT;
        h_insert(&v, wt);
    }

    wt[src] = 0;
    fixup(src, wt);
    while (!h_empty()) {
        if (wt[v = *((int *) h_delmax(wt))] != MAX_WT) {
            for (l = v_get_adj(v_get(g, v)); 
                 l != NULL; 
                 l = l_get_next(l)) 
            {
                v_adj = e_get_index(l_get_item(l));
                if (POT_DIST < wt[v_adj]) {
                    wt[v_adj] = POT_DIST;
                    fixup(v_adj, wt);
                    st[v_adj] = v;
                }
            }
        }
    }
}


