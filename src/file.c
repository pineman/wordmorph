#include <stdio.h>
#include <string.h>

#include "file.h"
#include "utils.h"
#include "const.h"
#include "graph.h"
#include "word.h"

int *find_max_perms(FILE *fpal)
{
	int *max_perms;
	char buffer[MAX_WORD_SIZE];
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	int perm=0, i;
	size_t size;

	/* Array cujos índices são os tamanhos de palavra necessários e cujos
	 * valores são o número máximo de permutações para esse tamanho. */
	max_perms = (int *) ecalloc(MAX_WORD_SIZE, sizeof(int));

	/* Ler a primeira palavra de cada linha do .pal */
	while (fgets(buffer, MAX_WORD_SIZE, fpal) != NULL) {
		sscanf(buffer, "%s %s %d", word1, word2, &perm);
		size = strlen(word1);
		/* Guardar número máximo de permutações */
		if (max_perms[size] < perm) {
			max_perms[size] = perm;
		}
	}

	for (i=0; i<MAX_WORD_SIZE; i++)
		printf("%d\n", max_perms[i]);

	printf("butterfly\n");

	return max_perms;
}

Graph **read_dic(FILE *fdic, int *max_perms)
{
	char buffer[MAX_WORD_SIZE];
	int num_words[MAX_WORD_SIZE] = {0};
	Graph **graphs;
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
	graphs = (Graph **) ecalloc(MAX_WORD_SIZE, sizeof(Graph *));
	for (i = 0; i < MAX_WORD_SIZE; i++) {
		if (max_perms[i] != 0) {
			graphs[i] = g_init(num_words[i], max_perms[i]);
		}
		else {
			graphs[i] = NULL;
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
			 * porque embora poupemos algumas comparações pelo break,
			 * introduzimos sempre a comparação dos caracteres testados
			 * com o número máximo de permutações, o que pode não valer a pena */
			g_insert(graphs[size], w_new(buffer));

			/*TODO: A criação de edges é demasiado lenta, não sei se por estar a
			 * fazer algo estupido ou se por ser uma má forma de abordar o 
			 * problema.
			 */
			g_update_links(graphs[size], w_diff);
		}
	}

	return graphs;
}

void solve_pal(FILE *fpal, FILE *fpath, Graph **graphs)
{
	char buffer[MAX_WORD_SIZE];
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	int perm;

	while (fscanf(fpal, "%s %s %d", word1, word2, &perm) == 3) {
		/* TODO:
		 * path = g_shortest_path(graphs[strlen(word1)], perm, ...);
		 * fprintf(fpath, "%s %d\n", word1, path->total_weight);
		 * for node in path: fprintf(fpath, "%s\n", node);
		 * fprintf(fpath, "\n"); */
	}
}
