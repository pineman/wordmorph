#include <stdio.h>
#include <string.h>

#include "file.h"
#include "utils.h"
#include "const.h"

int *find_max_perms(FILE *fpal)
{
	int *max_perms;
	char buffer[MAX_WORD_SIZE];
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	int perm;
	size_t size;

	/* Array cujos índices são os tamanhos de palavra necessários e cujos
	 * valores são o número máximo de permutações para esse tamanho. */
	max_perms = (int *) ecalloc(MAX_WORD_SIZE, sizeof(int));

	/* Ler a primeira palavra de cada linha do .pal */
	while (fgets(buffer, MAX_WORD_SIZE, fpal) != NULL) {
		sscanf(buffer, "%s %s %d\n", word1, word2, &perm);
		size = strlen(word1);
		/* Guardar número máximo de permutações */
		if (max_perms[size] < perm) {
			max_perms[size] = perm;
		}
	}

	return max_perms;
}

Graph *read_dic(FILE *fdic, int *max_perms)
{
	char buffer[MAX_WORD_SIZE];
	int *num_words[MAX_WORD_SIZE] = {0};
	Graph *graphs;
	size_t size;
	int i;

	/* Ler o dicionário uma primeira vez para saber quantos nós
	 * de cada tamanho de palavra alocar, para construir os grafos. */
	while (fscanf(fdic, "%s", buffer) == 1) {
		num_words[strlen(buffer)]++;
	}

	rewind(fdic);

	/* Array de MAX_WORD_SIZE grafos, em que apenas alocamos
	 * grafos cujos índices no array correspondem a tamanhos de palavra
	 * que precisamos (os outros ficam a NULL) */
	graphs = (Graph *) ecalloc(MAX_WORD_SIZE * sizeof(Graph));
	for (i = 0; i < MAX_WORD_SIZE; i++) {
		if (max_perms[i] != 0) {
			graphs[i] = g_init(num_words[i]);
		}
	}

	/* Reler o dicionário para construir os grafos. */
	while (fscanf(fdic, "%s", buffer) == 1) {
		size = strlen(buffer);
		/* Ignorar palavras cujos tamanhos já sabemos que não precisamos. */
		if (max_perms[size] != 0) {
			/* TODO: Atualizar logo as listas de adjacências dos outros nós
			 * ou construi-las todas depois?
			 *
			 * Fazer isso na função new_node ou noutra função?
			 *
			 * Uma possível otimização para a construção das adjacências
			 * é fazer break quando já se testou mais chars do que o
			 * número máximo de permutações.
			 *
			 * Depende do número de caracteres em relação ao número de permutações
			 * porque embora poupamos algumas comparações pelo break,
			 * introduzimos sempre a comparação dos caracteres testados
			 * com o número máximo de permutações, o que pode não valer a pena */
			g_new_node(graphs[size], buffer, max_perms[size]);
		}
	}

	return graphs;
}
