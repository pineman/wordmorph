#include "graph.h"
#include "utils.h"
#include "bool.h"
#include "heap.h"

#include <string.h>

/*
 * Um grafo é uma array de Vertices.
 * Cada Vertex guarda um Item de um tipo não especificado e uma lista
 * simplesmente ligada de Edges.
 *
 * Os Edges definem uma ligação e têm informação sobre o Vertex de chegada,
 * através do seu indice no array de Vertex, e sobre o peso da ligação.
 */

struct _Vertex {
	Item item;
	List *adj;
};

struct _Edge {
	unsigned short weight;
	unsigned short index;
};

/* free - posição livre do array de Vertices
 * size - tamanho total do Grafo
 * max_weight - peso máximo de uma aresta no grafo
 */
struct _Graph {
	Vertex **vertices;
	unsigned short free;
	unsigned short size;
	unsigned short max_weight;
};


/* Graph functions */
Graph *g_init(unsigned short size, unsigned short max_weight)
{
	Graph *g = (Graph *) emalloc(sizeof(Graph));
	g->vertices = (Vertex **) emalloc(sizeof(Vertex *) * size);
	g->free = 0;
	g->size = size;
	g->max_weight = max_weight;

	return g;
}

void g_free(Graph *g, void (free_item)(Item item))
{
	unsigned int i;
	Vertex *aux;

	for (i = 0; i < g->size; i++) {
		aux = g->vertices[i];
		l_free(aux->adj, free);
		free_item(aux->item);
		free(aux);
	}

	free(g->vertices);
	free(g);
}

void g_insert(Graph *g, Item i)
{
	Vertex *new_vertex;

	new_vertex = v_init(i);
	g->vertices[g->free] = new_vertex;
	g->free++;
}

/* Creates links between Vertices in the Graph
 * Warning: O(v^2)
 * TODO: É mesmo necessario criar duas edges sempre que se faz uma ligação?
 */
void g_make_edges(Graph *g, unsigned short (*calc_weight)(Item i1, Item i2, unsigned short max))
{
	unsigned short i, j;
	unsigned short weight;

	for (i = 0; i < g->size; i++) {
		for (j = 0; j < i; j++) {
			weight = calc_weight(g->vertices[i]->item, g->vertices[j]->item, g->max_weight);
			if (weight <= g->max_weight) {
				/*printf("vertice: %s, edge: %s\n", (char *) g->vertices[i]->item, (char *) g->vertices[j]->item);*/
				e_add(g, i, j, weight);
			}
		}
	}
}

unsigned short g_get_size(Graph *g)
{
	return g->size;
}

unsigned short g_get_free(Graph *g)
{
	return g->free;
}

unsigned short g_get_max_weight(Graph *g)
{
	return g->max_weight;
}

Vertex *g_get_vert(Graph *g, unsigned short i)
{
	return g->vertices[i];
}

void g_print(Graph *g)
{
	int i;
	Edge *e;
	List *l;

	for (i = 0; i < g->size; i++) {
		printf("Adjacency list for vertex %d (%s):\n", i, (char *) g->vertices[i]->item);
		for (l = g->vertices[i]->adj; l != NULL; l = l_get_next(l)) {
			e = (Edge *) l_get_item(l);
			printf("vertex %d: %s (w: %d)\n", e->index, (char *) g->vertices[e->index]->item, e->weight);
		}
		puts("");
	}
}

/* Vertex functions */
Vertex *v_init(Item i)
{
	Vertex *new_vertex = (Vertex *) emalloc(sizeof(Vertex));
	new_vertex->item = i;
	new_vertex->adj = l_init();

	return new_vertex;
}

Vertex *v_get(Graph *g, unsigned short index)
{
	return g->vertices[index];
}

int v_find(Graph *g, Item i1, int (*cmp_item)(Item c1, Item c2))
{
	int i;
	for (i=0; i<g_get_free(g); i++)
		if (!cmp_item(g->vertices[i]->item, i1))
			return i;

	return -1;
}

Item v_get_item(Vertex *v)
{
	return v->item;
}

List *v_get_adj(Vertex *v)
{
	return v->adj;
}


/* Edge functions */
/* Initializes a single edge */
Edge *e_init(unsigned short index, unsigned short weight)
{
	Edge *new_edge = (Edge *) emalloc(sizeof(Edge));
	new_edge->index = index;
	new_edge->weight = weight;

	return new_edge;
}

/* Adds edges in both vertices */
void e_add(Graph *g, unsigned short i1, unsigned short i2, unsigned short weight)
{
	Edge *l1 = e_init(i2, weight*weight);
	Edge *l2 = e_init(i1, weight*weight);

	l_insert(&(g->vertices[i1]->adj), l1);
	l_insert(&(g->vertices[i2]->adj), l2);
}

unsigned short e_get_weight(Edge *e)
{
	return e->weight;
}

unsigned short e_get_index(Edge *e)
{
	return e->index;
}

bool e_cmp_edges(Edge *e1, Edge *e2)
{
	return (e1->weight > e2->weight);
}

void v_adj_print(Graph *g, Vertex *v)
{
	List *aux = v->adj;
	while (aux != NULL) {
		printf("adj: %s\n", (char *) g->vertices[e_get_index((Edge *) l_get_item(aux))]->item);
		aux = l_get_next(aux);
	}
}
