/**
 * @file graph.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação da biblioteca de grafos.
 * @details
 * Implementação de grafos ponderados utilizando listas de adjacências.
 */
#ifndef _GRAPH_H
#define _GRAPH_H

#include "bool.h"
#include "item.h"

typedef struct _Vertex Vertex;
typedef struct _Edge Edge;
typedef struct _Graph Graph;

Graph *g_init(unsigned short size, unsigned short max_weight);
void g_free(Graph *g, void (free_item)(Item item));
void g_insert(Graph *g, Item i);
void g_make_edges(Graph *g, unsigned short (*calc_weight)(Item i1, Item i2, unsigned short max));
unsigned short g_get_size(Graph *g);
unsigned short g_get_free(Graph *g);
unsigned short g_get_max_weight(Graph *g);
Vertex *g_get_vertex(Graph *g, unsigned short i);
int g_find_vertex(Graph *g, Item i1, int (*cmp_item)(Item c1, Item c2));


Vertex *v_init(Item i);
Item v_get_item(Vertex *v);
Edge *v_get_adj(Vertex *v);

void e_add(Graph *g, unsigned short i1, unsigned short i2, unsigned short weight);
unsigned short e_get_weight(Edge *e);
unsigned short e_get_index(Edge *e);

void free_adj(Edge *head);
void e_insert(Edge **adj, unsigned short index, unsigned short weight);
Edge *e_get_next(Edge *l);

#endif
