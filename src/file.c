#include <stdio.h>
#include <string.h>

#include "file.h"
#include "utils.h"
#include "const.h"
#include "graph.h"
#include "word.h"
#include "dijkstra.h"

int *find_max_perms(FILE *fpal)
{
	int *max_perms;
	char buffer[MAX_WORD_SIZE];
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	int perm = 0;
	size_t size;

	/* Array cujos índices são os tamanhos de palavra necessários e cujos
	 * valores são o número máximo de permutações para esse tamanho. */
	max_perms = (int *) ecalloc(MAX_WORD_SIZE, sizeof(int));

	/* Ler cada linha do .pal */
	while (fgets(buffer, MAX_WORD_SIZE, fpal) != NULL) {
		sscanf(buffer, "%s %s %d", word1, word2, &perm);
		size = strlen(word1);
		/* Guardar número máximo de permutações */
		if (max_perms[size] < perm) {
			max_perms[size] = perm;
		}
	}

	return max_perms;
}

Graph **read_dic(FILE *fdic, int *max_perms)
{
	char buffer[MAX_WORD_SIZE];
	int num_words[MAX_WORD_SIZE] = {0};
	Graph **graphs;
	size_t size;
	int i;

	/* Ler o dicionário uma primeira vez para saber quantos vértices
	 * de cada tamanho de palavra alocar, para construir os grafos. */
	while (fscanf(fdic, "%s", buffer) == 1) {
		num_words[strlen(buffer)]++;
	}

	rewind(fdic);

	/* Array de MAX_WORD_SIZE grafos, em que apenas alocamos
	 * grafos cujos índices no array correspondem a tamanhos de palavra
	 * que precisamos (os outros ficam a NULL) */
	graphs = (Graph **) emalloc(MAX_WORD_SIZE * sizeof(Graph *));
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
			g_insert(graphs[size], w_new(buffer));
			/*TODO: A criação de edges é demasiado lenta, não sei se por estar a
			 * fazer algo estupido ou se por ser uma má forma de abordar o
			 * problema.
			 */
		}
	}

	/* Construir as arestas entre cada palavra, com pesos até o quadrado
	 * do número máximo de permutações para cada tamanho. */
	for (i = 0; i < MAX_WORD_SIZE; i++)
		if (max_perms[i] != 0)
			g_make_edges(graphs[i], w_diff);

	return graphs;
}

void solve_pal(FILE *fpal, FILE *fpath, Graph **graphs)
{
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	int max_perm;
	int i; /* indíce do vértice de origem do grafo. */
	size_t size;
	int *st = NULL, *wt = NULL;

	while (fscanf(fpal, "%s %s %d", word1, word2, &max_perm) == 3) {
		size = strlen(word1);
		/* Encontrar indice do vértice de origem no grafo. */
		for (i = 0; i < g_get_free(graphs[size]) &&
			 strcmp(word1, (char *) v_get_item(v_get(graphs[size], i))); i++);

		/* Árvore do caminho. */
		st = realloc(st, g_get_free(graphs[size]) * sizeof(int));
		wt = shortest_path(graphs[size], i, st, max_perm);
		for (i = 0; i < g_get_free(graphs[size]); i++)
			printf("%i\n", st[i]);

		/* TODO:
		 * path = g_shortest_path(graphs[strlen(word1)], ...);
		 * walk tree
		 * fprintf(fpath, "%s %d\n", word1, path->total_weight);
		 * for node in path: fprintf(fpath, "%s\n", node);
		 * fprintf(fpath, "\n"); */
	}
	free(wt);
	free(st);
}
