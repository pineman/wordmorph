/**
 * @file word.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do algoritmo de Dijkstra.
 * @details
 *
 */
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "word.h"
#include "item.h"

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param word [description]
 * @return [description]
 */
Item w_new(char *word)
{
	char *new_word = (char *) emalloc((strlen(word) + 1) * sizeof(char));
	strcpy(new_word, word);

	return (Item) new_word;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param word [description]
 */
void w_free(Item word)
{
	free(word);
}

/* Retorna o número de caracteres diferentes entre as strings v1 e v2,
 * assumindo que estas são do mesmo tamanho. */
/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param v1 [description]
 * @param v2 [description]
 * @param max_perm [description]
 * @return [description]
 */
unsigned short w_diff(Item v1, Item v2, unsigned short max_perm)
{
	/* TODO: lento como nós sabemos */
	unsigned short cnt = 0;
	int i;
	char *w1 = (char *) v1;
	char *w2 = (char *) v2;

	/* TODO: Se calhar este loop pode ser hand-rolled. */
	for (i = 0; w1[i] != '\0'; i++) {
		if (w1[i] != w2[i]) {
			cnt++;
		}
		/* Otimização */
		if (cnt > max_perm) {
			break;
		}
	}

	return cnt;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param c1 [description]
 * @param c2 [description]
 * @return [description]
 */
int w_cmp(Item c1, Item c2)
{
	return strcmp((const char *) c1, (const char *) c2);
}
