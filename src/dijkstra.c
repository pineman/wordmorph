/**
 * @file dijkstra.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do algoritmo de Dijkstra para encontrar caminhos mais
 * curtos em grafos.
 */
#include <stdlib.h>

#include "dijkstra.h"
#include "utils.h"
#include "graph.h"
#include "heap.h"

/* wt é global privada do dijkstra.c, para facilitar
 * o acesso pela função d_less_pri(). */
static int *wt;

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param g [description]
 * @param src [description]
 * @param dst [description]
 * @param st [description]
 * @param max_perm [description]
 * @return [description]
 */
int *shortest_path(Graph *g, int src, int dst, int *st, unsigned short max_perm)
{
	int v; /* Indíce de um vértice */
	int v_adj; /* Indíce de um vértice adjacente a v */
	Edge *l; /* Aresta de v para v_adj */
	int i;
	unsigned short w_v_adj;
	int *array;
	bool itemIsInsideHeapDataStructure;

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
	h_insert(heap, &array[src], d_less_pri, d_hash);

	wt[src] = 0;
	/* Colocar na heap os vértices adjacentes e calcular distâncias. */
	while (!h_empty(heap)) {
		v = *((int *) h_del_max_pri(heap, d_less_pri, d_hash));

		if (v == dst) break;

		for (l = v_get_adj(g_get_vertex(g, v)); l != NULL; l = e_get_next(l)) {
			w_v_adj = e_get_weight(l);
			if (w_v_adj > max_perm) continue;

			v_adj = e_get_index(l);
			if (wt[v] + w_v_adj < wt[v_adj]) {
				itemIsInsideHeapDataStructure = (wt[v_adj] != MAX_WT);

				wt[v_adj] = wt[v] + w_v_adj;
				st[v_adj] = v;

				if (itemIsInsideHeapDataStructure) {
					h_inc_pri(heap, &(array[v_adj]), d_less_pri, d_hash);
				}
				else {
					h_insert(heap, &(array[v_adj]), d_less_pri, d_hash);
				}
			}
		}
	}

	h_free(heap);
	free(array);

	return wt;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param s1 [description]
 * @param s2 [description]
 * @return [description]
 */
bool d_less_pri(Item s1, Item s2)
{
	/* Se s1 tem menos prioridade que s2, é porque
	 * s1 tem maior distância à origem considerada do grafo. */
	return wt[*((int *) s1)] > wt[*((int *) s2)];
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param a [description]
 * @return [description]
 */
unsigned short d_hash(Item a)
{
	return *((int *) a);
}
