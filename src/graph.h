#ifndef _GRAPH_H
#define _GRAPH_H

#include "list.h"

typedef struct _Vertex Vertex;
typedef struct _Edge Edge;
typedef struct _Graph Graph; 

Graph *g_init(unsigned int, unsigned int);
void g_insert(Graph *, Item);
void g_free(Graph *);
void g_update_links(Graph *, unsigned int (*calc_weight)(Item, Item, unsigned int));

Vertex *v_init(Item);
Vertex *v_get(Graph *, unsigned int);
Item v_get_item(Vertex *);
List *v_get_adj(Vertex *);

void e_add (Graph *, unsigned int, unsigned int, unsigned int) ;
Edge *e_init(unsigned int, unsigned int);
unsigned int e_get_weight(Edge *);
unsigned int e_get_index(Edge *);
bool e_cmp_edges(Edge *, Edge *);

#endif