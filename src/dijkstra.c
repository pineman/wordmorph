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

/* wt é a tabela de distâncias utilizada pela função shortest_path().
 * É global privada deste ficheiro dijkstra.c, para facilitar
 * o acesso à variável pela função d_less_pri(), chamada em heap.c.
 *
 * Este ponteiro é devolvido pela função shortest_path e utilizado em file.c.
 * No entanto, da próxima vez que shortest_path() será chamada,
 * esta variável será realocada e reinicializada, evitando quaisquer problemas.
 * No fim, é libertada em file.c, solve_pal(). */
static int *wt = NULL;

/**
 * @brief Encontra o caminho mais curto entre os vértices src e dst no grafo g.
 * @details Implementa o algoritmo de Dijkstra fonte-destino,
 *	recorrendo a uma fila prioritária implementada por acervo (heap).
 *	Inicialmente, o vértice de origem é inserido na fila, para ser
 *	retirado na primeira iteração do ciclo principal, sendo inseridos
 *	agora na fila apenas vértices adjacentes à origem e assim em diante.
 *
 * @param g Grafo a procurar.
 * @param src Índice do vértice de origem.
 * @param dst Índice do vértice de destino.
 * @param st Árvore de caminhos.
 * @param max_weight Peso máximo de arestas a considerar.
 *
 * @return wt Tabela de distâncias.
 */
int *shortest_path(Graph *g, int src, int dst, int *st, unsigned short max_weight)
{
	int v; /* Indíce de um vértice */
	int v_adj; /* Indíce de um vértice adjacente a v */
	Edge *l; /* Aresta de v para v_adj */
	int i;
	unsigned short w_v_adj;
	int *array; /* Tabela ajudante para o tipo abstrato a usar na fila. */
	bool in_heap;

	/* Inicializar fila. */
	Heap *heap = h_init(g_get_size(g));

	/* Realocar wt (global para este ficheiro) para o tamanho corrente. */
	wt = realloc(wt, g_get_size(g) * sizeof(int));

	/* Inicializar árvore de caminho e array de distâncias. */
	for (v = 0; v < g_get_size(g); v++) {
		st[v] = -1;
		wt[v] = MAX_WT;
	}

	/* Inicializar a fila apenas com o vértice de origem */
	/* Items da fila são ints (correspondentes a indíces dos vértices no grafo) */
	array = (int *) emalloc(g_get_size(g) * sizeof(int));
	for (i = 0; i < g_get_size(g); i++) {
		array[i] = i;
	}
	h_insert(heap, &array[src], d_less_pri, d_hash);

	wt[src] = 0;
	/* Colocar na heap os vértices adjacentes e calcular distâncias. */
	while (!h_empty(heap)) {
		v = *((int *) h_del_max_pri(heap, d_less_pri, d_hash));

		/* Parar quando o vértice de destino sai da fila prioritária,
		 * pois garantimos que temos o caminho mais curto até lá. */
		if (v == dst) break;

		/* Percorrer a lista de adjacências de v. */
		for (l = v_get_adj(g_get_vertex(g, v)); l != NULL; l = e_get_next(l)) {
			w_v_adj = e_get_weight(l);
			/* Ignorar arestas de peso maior ao peso máximo que estamos
			 * a considerar. */
			if (w_v_adj > max_weight) continue;

			v_adj = e_get_index(l);
			if (wt[v] + w_v_adj < wt[v_adj]) {
				/* A partir de v conseguimos minimizar a distância a v_adj,
				* previamente calculada. */
				in_heap = (wt[v_adj] != MAX_WT);

				/* Atualizar distância com o novo valor. */
				wt[v_adj] = wt[v] + w_v_adj;
				/* Marcar v como antecessor de v_adj. */
				st[v_adj] = v;

				if (in_heap) {
					/* ... Se v_adj já estiver na fila, incrementamos a sua
					 * prioridade. */
					h_inc_pri(heap, &(array[v_adj]), d_less_pri, d_hash);
				}
				else {
					/* Senão, inserimo-lo nesta. */
					h_insert(heap, &(array[v_adj]), d_less_pri, d_hash);
				}
			}
		}
	}

	/* Libertar a fila e a array temporária. */
	h_free(heap);
	free(array);

	return wt;
}

/**
 * @brief Averigua entre dois items qual tem menos prioridade.
 * @details Se s1 tem menos prioridade que s2, é porque
 * s1 tem maior distância à origem considerada do grafo.
 *
 * @param s1 Item (ponteiro para inteiro) 1
 * @param s2 Item (ponteiro para inteiro) 2
 *
 * @return booleano: 1 (true) se s1 tiver menos prioridade que s2,
 *	0 se s1 tiver maior ou igual prioridade a s2.
 */
bool d_less_pri(Item s1, Item s2)
{
	return wt[*((int *) s1)] > wt[*((int *) s2)];
}

/**
 * @brief Função de dispersão para a tabela de dispersão na fila.
 * @details Esta função de dispersão é particularmente trivial pois
 *	mapeia indíces do grafo para indíces da fila. Assim, existe uma
 *	relação 1:1, evitando colisões.
 *
 * @param a Item (ponteiro para inteiro) que está na fila.
 *
 * @return Índice do vértice no grafo correspondente a este Item.
 */
unsigned short d_hash(Item a)
{
	return *((int *) a);
}
