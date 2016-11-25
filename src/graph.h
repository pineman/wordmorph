#ifndef _GRAPH_H
#define _GRAPH_H

#include "list.h"

typedef struct _Node Node;
typedef struct _Link Link;
typedef struct _Graph Graph;

Graph *g_init(unsigned int);
void g_insert(Graph, Item);
void g_free(Graph);



#endif