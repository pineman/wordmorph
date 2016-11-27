#ifndef _DJIKSTRA_H
#define _DJIKSTRA_H

#include <stdlib.h>
#include "graph.h"
#include "heap.h"

#define POT_DIST (wt[v] + e_get_weight(l_get_item(l)))
#define MAX_WT 10000000 /* TODO */

void shortest_path(Graph *g, int src, int *st, int *wt);
void exch(Secret *i1, Secret *i2);

#endif