/**
 * @file word.h
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do algoritmo de Dijkstra.
 * @details
 *
 */
#ifndef _WORD_H
#define _WORD_H

#include "item.h"

Item w_new(char *word);
void w_free(Item word);

unsigned short w_diff(Item w1, Item w2, unsigned short max_perm);
int w_cmp(Item c1, Item c2);

#endif
