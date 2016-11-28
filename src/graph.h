#ifndef _GRAPH_H
#define _GRAPH_H

#include "list.h"
#include "bool.h"

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

Vertex *v_init(Item i);
Vertex *v_get(Graph *g, unsigned short index);
int v_find(Graph *g, Item i1, int (*cmp_item)(Item c1, Item c2));
Item v_get_item(Vertex *v);
List *v_get_adj(Vertex *v);

Edge *e_init(unsigned short index, unsigned short weight);
void e_add(Graph *g, unsigned short i1, unsigned short i2, unsigned short weight);
unsigned short e_get_weight(Edge *e);
unsigned short e_get_index(Edge *e);
bool e_cmp_edges(Edge *e1, Edge *e2);

void v_adj_print(Graph *g, Vertex *v);

#endif
