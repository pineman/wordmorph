/**
 * @file word.h
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do tipo principal Word (char *)
 * @details
 *	Este tipo é utilizado como Item dos vértices do grafo;
 *	a função w_cmp é utilizada na procura de um vértice no grafo
 *	e a função w_diff para obter o número de caracteres diferentes entre
 *	duas palavras.
 */
#ifndef _WORD_H
#define _WORD_H

#include "item.h"

Item w_new(char *word);
void w_free(Item word);

unsigned short w_diff(Item v1, Item v2, unsigned short max_perm);
int w_cmp(Item v1, Item v2);

#endif
