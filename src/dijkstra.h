/**
 * @file dijkstra.h
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do algoritmo de Dijkstra para encontrar caminhos mais
 * curtos em grafos.
 */
#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "graph.h"
#include "item.h"

#define MAX_WT 10000000

int *shortest_path(Graph *g, int src, int dst, int *st, unsigned short max_weight);
bool d_less_pri(Item s1, Item s2);
unsigned short d_hash(Item a);

#endif
