#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "graph.h"
#include "secret.h"

#define POT_DIST (wt[v] + e_get_weight(l_get_item(l)))
#define MAX_WT 10000000 /* TODO */

int *shortest_path(Graph *g, int src, int *st);
bool cmp(Secret s1, Secret s2);

#endif
