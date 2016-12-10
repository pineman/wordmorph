/**
 * @file word.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do tipo principal Word (char *)
 * @details
 *	Este tipo é utilizado como Item dos vértices do grafo;
 *	a função w_cmp é utilizada na procura de um vértice no grafo
 *	e a função w_diff para obter o número de carateres diferentes entre
 *	duas palavras.
 */
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "word.h"
#include "item.h"

/**
 * @brief Inicializar uma nova palavra.
 *
 * @param word Palavra a ser alocada.
 * @return Ponteiro para uma nova palavra alocada.
 */
Item w_new(char *word)
{
	char *new_word = (char *) emalloc((strlen(word) + 1) * sizeof(char));
	strcpy(new_word, word);

	return (Item) new_word;
}

/**
 * @brief Liberta uma palavra.
 *
 * @param word Palavra alocada com w_new() a libertar.
 */
void w_free(Item word)
{
	free(word);
}

/**
 * @brief Calcular o número de carateres diferentes entre duas palavras de
 *	tamanhos iguais.
 * @details Este cálculo é fulcral para a construção das arestas
 *	ponderadas do grafo, cujo peso é igual ao quadrado do número de carateres
 *	diferentes entre as duas palavras de quaisquer dois vértices.
 *	Esta função é linear com o número de carateres das palavras.
 *
 * @param v1 Palavra 1
 * @param v2 Palavra 2
 * @param max_perm O número máximo permitido de carateres diferentes.
 * @return Devolve o número de carateres diferentes entre as duas palavras,
 *	no máximo igual a max_perm.
 */
unsigned short w_diff(Item v1, Item v2, unsigned short max_perm)
{
	unsigned short cnt = 0;
	int i;
	char *w1 = (char *) v1;
	char *w2 = (char *) v2;

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
 * @brief Compara duas palavras. Wrapper para strcmp().
 *
 * @param v1 Palavra 1.
 * @param v2 Palavra 2.
 * @return Inteiro igual ao valor de strcmp().
 */
int w_cmp(Item v1, Item v2)
{
	return strcmp((const char *) v1, (const char *) v2);
}
