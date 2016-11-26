#ifndef _GRAPH_H
#define _GRAPH_H

#include "list.h"

typedef struct _Vertex Vertex;
typedef struct _Edge Edge;
typedef struct _Graph Graph;


Graph *g_init(unsigned int size, unsigned int max_weight);
void g_free(Graph *g, void (free_item)(Item item));

void g_insert(Graph *g, Item i);
void g_update_links(Graph *g, unsigned int (*calc_weight)(Item i1, Item i2, unsigned int max));


Vertex *v_init(Item i);
Vertex *v_get(Graph *g, unsigned int index);
Item v_get_item(Vertex *v);
List *v_get_adj(Vertex *v);


Edge *e_init(unsigned int index, unsigned int weight);
void e_add(Graph *g, unsigned int i1, unsigned int i2, unsigned int weight);
unsigned int e_get_weight(Edge *e);
unsigned int e_get_index(Edge *e);
bool e_cmp_edges(Edge *e1, Edge *e2);

#endif
