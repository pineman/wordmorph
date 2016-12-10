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

/*TODO: error checking*/

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


/**
 * @brief Inicializar um grafo.
 * @param size Tamanho máximo do grafo.
 * @param max_weight Peso máximo das arestas.
 * 
 * @return Grafo.
 */
Graph *g_init(unsigned short size, unsigned short max_weight)
{
	Graph *g = (Graph *) emalloc(sizeof(Graph));
	g->vertices = (Vertex **) emalloc(sizeof(Vertex *) * size);
	g->free = 0;
	g->size = size;
	g->max_weight = max_weight;

	return g;
}

/**
 * @brief Liberta a memoria alocada para o grafo.
 * @param g Ponteiro para grafo.
 * @param free_item Função libertadora de items.
 */
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


/**
 * @brief Insere um item na posição livre do grafo.
 * @param g Ponteiro para grafo.
 * @param i Item a inserir.
 */
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
 

/**
 * @brief Cria ligações entre vertices.
 * @details Verifica quais os vertices cujo peso é menor que o máximo permitido
 * e insere as ligações correspondentes na lista de adjacências.
 * 
 * @param g Ponteiro para grafo.
 * @param calc_weight Ponteiro para função que calcula pesos entre arestas. 
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

/**
 * @brief Função acessora do numero máximo de vertices no grafo.
 * 
 * @param g Ponteiro para grafo.
 * @return Numero máximo de vertices no grafo.
 */
unsigned short g_get_size(Graph *g)
{
	return g->size;
}

/**
 * @brief Função acessora do numero de vertices no grafo.
 * 
 * @param g Ponteiro para grafo.
 * @return Numero de vertices no grafo.
 */
unsigned short g_get_free(Graph *g)
{
	return g->free;
}

/**
 * @brief Função acessora do peso máximo das arestas no grafo.
 * 
 * @param g Ponteiro para grafo
 * @return Peso máximo entre arestas no grafo.
 */
unsigned short g_get_max_weight(Graph *g)
{
	return g->max_weight;
}

/**
 * @brief Função acessora de um vertice i do grafo.
 * 
 * @param g Ponteiro para grafo.
 * @param i Índice do vertice.
 * 
 * @return Vertice i do grafo.
 */
Vertex *g_get_vert(Graph *g, unsigned short i)
{
	return g->vertices[i];
}

/*TODO: wrong name*/
/**
 * @brief Inicializar um vertice com item i.
 * 
 * @param i Item a inserir no vertice.
 * @return Ponteiro para o novo vertice.
 */
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


/*TODO: wrong name*/
/**
 * @brief Encontra vertice no grafo.
 * @details Procura um vertice no grafo linearmente.
 * 
 * @param g Ponteiro para grafo.
 * @param i1 Item que indentifica o vertice a encontrar
 * @param cmp_item Ponteiro para função comparadora de vertices.
 * @return Indice do vertice encontrado ou -1 em caso de insucesso.
 */
int v_find(Graph *g, Item i1, int (*cmp_item)(Item c1, Item c2))
{
	int i;

	for (i = 0; i < g_get_free(g); i++)
		if (!cmp_item(g->vertices[i]->item, i1))
			return i;

	return -1;
}

/**
 * @brief Função acessora de items no vertice
 * 
 * @param v Ponteiro para vertice
 * @return Item do vertice.
 */
Item v_get_item(Vertex *v)
{
	return v->item;
}

/**
 * @brief Função acessora de listas de adjacências.
 * 
 * @param v Ponteiro para vertice.
 * @return Lista de adjacências.
 */
Edge *v_get_adj(Vertex *v)
{
	return v->adj;
}


/*TODO: not used*/
/**
 * @brief Initialize edge
[long description]
 * 
 * @param index Indice do vertice de destino.
 * @param weight Peso da aresta.
 * 
 * @return Ponteiro para nova edge.
 */
Edge *e_init(unsigned short index, unsigned short weight)
{
	Edge *new_edge = (Edge *) emalloc(sizeof(Edge));
	new_edge->index = index;
	new_edge->weight = weight;
	new_edge->next = NULL;

	return new_edge;
}

/**
 * @brief Inserir edge na lista de adjacências.
 * 
 * @param adj Lista de adjacências.
 * @param index Indice do vertice de destino.
 * @param weight Peso da aresta.
 */
void e_insert(Edge **adj, unsigned short index, unsigned short weight)
{
	Edge *new_edge = (Edge *) emalloc(sizeof(Edge));
	new_edge->index = index;
	new_edge->weight = weight;
	new_edge->next = *adj;
	*adj = new_edge;

	return;
}

/**
 * @brief Cria arestas entre vertices.
 * @details Insere uma aresta em cada vertice da ligação.
 * 
 * @param g Ponteiro para grafo.
 * @param i1 Indice do vertice de partida.
 * @param i2 Indice do verticd de destino.
 * @param weight Peso da aresta.
 */
void e_add(Graph *g, unsigned short i1, unsigned short i2, unsigned short weight)
{
	e_insert(&(g->vertices[i1]->adj), i2, weight);
	e_insert(&(g->vertices[i2]->adj), i1, weight);
}

/**
 * @brief Função acessora do peso da aresta.
 * 
 * @param e Ponteiro para edge.
 * @return Peso da aresta
 */
unsigned short e_get_weight(Edge *e)
{
	return e->weight;
}

/**
 * @brief Função acessora do indice do vertice de destino da aresta.
 * 
 * @param e Ponteiro para aresta.
 * @return Indice do vertice de destino da aresta.
 */
unsigned short e_get_index(Edge *e)
{
	return e->index;
}

/*TODO: Not needed*/
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param e1 [description]
 * @param e2 [description]
 * 
 * @return [description]
 */
bool e_cmp_edges(Edge *e1, Edge *e2)
{
	return (e1->weight > e2->weight);
}


/**
 * @brief Liberta a lista de adjacências.
 * 
 * @param head Ponteiro para a cabeça da lista de adjacências
 */
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


/*TODO: wrong name*/
/**
 * @brief Função acessora do proximo elemento da lista de adjacências
 * 
 * @param l Ponteiro para aresta
 * @return Proximo elemento da lista de adjacências
 */
Edge *l_get_next(Edge *l)
{
	return l->next;
}
