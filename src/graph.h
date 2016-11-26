#ifndef _GRAPH_H
#define _GRAPH_H

#include "list.h"

typedef struct _Vertex Vertex;
typedef struct _Edge Edge;
typedef struct _Graph Graph;


Graph *g_init(unsigned short size, unsigned short max_weight);
void g_free(Graph *g, void (free_item)(Item item));

void g_insert(Graph *g, Item i);
void g_update_links(Graph *g, unsigned short (*calc_weight)(Item i1, Item i2, unsigned short max));

unsigned short g_get_size(Graph *g);
unsigned short g_get_free(Graph *g);

Vertex *v_init(Item i);
Vertex *v_get(Graph *g, unsigned short index);
Item v_get_item(Vertex *v);
List *v_get_adj(Vertex *v);


Edge *e_init(unsigned short index, unsigned short weight);
void e_add(Graph *g, unsigned short i1, unsigned short i2, unsigned short weight);
unsigned short e_get_weight(Edge *e);
unsigned short e_get_index(Edge *e);
bool e_cmp_edges(Edge *e1, Edge *e2);

void v_adj_prshort(Graph *g, Vertex *v);

#endif
