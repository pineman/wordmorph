#ifndef _GRAPH_H
#define _GRAPH_H

#include "list.h"

typedef struct _Node Node;
typedef struct _Link Link;
typedef struct _Graph Graph;

Graph *g_init(unsigned int, unsigned int);
void g_insert(Graph *, Item);
void g_free(Graph *);
bool g_cmp_links(Link *, Link *);
Node *g_get_node(Graph *, unsigned int);
Item g_get_item(Node *);
List *g_get_adj(Node *);
unsigned int g_get_weight(Link *);
unsigned int g_get_index(Link *);
void g_update_links(Graph * , 
                    unsigned int (*calc_weight)(Item, Item, unsigned int));

/*Funções privadas*/
Node *_init_node(Item);
void _make_link (Graph *, unsigned int, unsigned int, unsigned int);
Link *_init_link(unsigned int, unsigned int); 
#endif