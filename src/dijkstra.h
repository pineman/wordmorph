#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "graph.h"
#include "item.h"

#define MAX_WT 10000000 /* TODO */

int *shortest_path(Graph *g, int src, int dst, int *st, unsigned short max_perm);
bool d_less_pri(Item s1, Item s2);
unsigned short d_hash(Item a);

#endif
