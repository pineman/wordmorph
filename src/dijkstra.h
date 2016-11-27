#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "graph.h"

#define POT_DIST (wt[v] + e_get_weight(l_get_item(l)))
#define MAX_WT 10000000 /* TODO */

void shortest_path(Graph *g, int src, int *st, int *wt);

#endif
