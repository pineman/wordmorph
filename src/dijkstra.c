#include <stdlib.h>

#include "dijkstra.h"
#include "utils.h"
#include "graph.h"
#include "heap.h"

/* TODO: ugly global var */
static int *wt;

int *shortest_path(Graph *g, int src, int dst, int *st, unsigned short max_perm)
{
	int v; /* Index de um vértice */
	int v_adj; /* Index dum vértice adjacente a v */
	List *l; /* Aresta de v para v_adj */
	int i;
	unsigned short w_v_adj;
	int *array;

	Heap *heap = h_init(g_get_free(g));
	wt = realloc(wt, g_get_free(g) * sizeof(int));

	/* Inicializar árvore de caminho e array de distâncias. */
	for (v = 0; v < g_get_free(g); v++) {
		st[v] = -1;
		wt[v] = MAX_WT;
	}

	/* Inicializar a heap apenas com o vértice de origem */
	/* Item são ints (indíces dos vértices no grafo) */
	array = (int *) emalloc(g_get_free(g) * sizeof(int));
	for (i = 0; i < g_get_free(g); i++) {
		array[i] = i;
	}
	h_insert(heap, &array[src], d_less_pri);

	wt[src] = 0;
	/* Colocar na heap os vértices adjacentes e calcular distâncias. */
	while (!h_empty(heap)) {
		/*h_print(heap, g);*/
		v = *((int *) h_del_max_pri(heap, d_less_pri));
		if (v == dst) break;

		for (l = v_get_adj(v_get(g, v)); l != NULL; l = l_get_next(l)) {
			w_v_adj = e_get_weight(l_get_item(l));
			if (w_v_adj > max_perm) continue;

			v_adj = e_get_index(l_get_item(l));
			if (wt[v] + w_v_adj < wt[v_adj]) {
				wt[v_adj] = wt[v] + w_v_adj ;
				st[v_adj] = v;
				h_insert(heap, &(array[v_adj]), d_less_pri);
			}
		}
	}

	h_free(heap);
	free(array);

	return wt;
}

bool d_less_pri(Item s1, Item s2)
{
	/* Se s1 tem menos prioridade que s2, é porque
	 * s1 tem maior distância à origem considerada do grafo. */
	return wt[*((int *) s1)] > wt[*((int *) s2)];
}
