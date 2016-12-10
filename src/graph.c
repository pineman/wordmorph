/**
 * @file graph.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do algoritmo de Dijkstra.
 * @details
 *
 */
#include <string.h>
#include <stdlib.h>

#include "graph.h"
#include "utils.h"
#include "bool.h"
#include "heap.h"

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
	Edge *adj;
};

struct _Edge {
	unsigned short weight;
	unsigned short index;
	struct _Edge *next;
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
		free_adj(aux->adj);
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
				/* Agora o peso entra quadraticamente. */
				e_add(g, i, j, weight*weight);
			}
		}
	}
	g->max_weight *= g->max_weight;
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

/* TODO: Print function */
void g_print(Graph *g)
{
	int i;
	Edge *l;

	for (i = 0; i < g->size; i++) {
		printf("Adjacency list for vertex %d (%s):\n", i, (char *) g->vertices[i]->item);
		for (l = g->vertices[i]->adj; l != NULL; l = l->next) {
			printf("vertex %d: %s (w: %d)\n", l->index, (char *) g->vertices[l->index]->item, l->weight);
		}
		puts("");
	}
}

/* Vertex functions */
Vertex *v_init(Item i)
{
	Vertex *new_vertex = (Vertex *) emalloc(sizeof(Vertex));
	new_vertex->item = i;
	new_vertex->adj = NULL;

	return new_vertex;
}

Vertex *v_get(Graph *g, unsigned short index)
{
	return g->vertices[index];
}

int v_find(Graph *g, Item i1, int (*cmp_item)(Item c1, Item c2))
{
	int i;

	for (i = 0; i < g_get_free(g); i++)
		if (!cmp_item(g->vertices[i]->item, i1))
			return i;

	return -1;
}

Item v_get_item(Vertex *v)
{
	return v->item;
}

Edge *v_get_adj(Vertex *v)
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
	new_edge->next = NULL;

	return new_edge;
}

void e_insert(Edge **adj, unsigned short index, unsigned short weight)
{
	Edge *new_edge = (Edge *) emalloc(sizeof(Edge));
	new_edge->index = index;
	new_edge->weight = weight;
	new_edge->next = *adj;
	*adj = new_edge;

	return;
}

/* Adds edges in both vertices */
void e_add(Graph *g, unsigned short i1, unsigned short i2, unsigned short weight)
{
	e_insert(&(g->vertices[i1]->adj), i2, weight);
	e_insert(&(g->vertices[i2]->adj), i1, weight);
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

/* TODO: Print function */
void v_adj_print(Graph *g, Vertex *v)
{
	Edge *aux = v->adj;
	while (aux != NULL) {
		printf("adj: %s\n", (char *) g->vertices[aux->index]);
		aux = aux->next;
	}
}

void free_adj(Edge *head)
{
	Edge *aux = head;
	Edge *tmp;

	while (aux) {
		tmp = aux->next;
		free(aux);
		aux = tmp;
	}
}

Edge *l_get_next(Edge *l)
{
	return l->next;
}
