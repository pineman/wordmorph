/**
 * @file file.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação do algoritmo de Dijkstra.
 * @details
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "utils.h"
#include "const.h"
#include "graph.h"
#include "word.h"
#include "dijkstra.h"


/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param fpal [description]
 * @return [description]
 */
unsigned short *find_max_perms(FILE *fpal)
{
	unsigned short *max_perms;
	char buffer[MAX_WORD_SIZE];
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	unsigned short perm;
	size_t size;

	/* Array cujos índices são os tamanhos de palavra necessários e cujos
	 * valores são o número máximo de permutações para esse tamanho. */
	max_perms = (unsigned short *) ecalloc(MAX_WORD_SIZE, sizeof(unsigned short));

	/* Ler cada linha do .pal */
	while (fgets(buffer, MAX_WORD_SIZE, fpal) != NULL) {
		sscanf(buffer, "%s %s %hu", word1, word2, &perm);
		size = strlen(word1);
		/* Guardar número máximo de permutações */
		if (max_perms[size] < perm && w_diff(word1, word2, 1) > 1) {
			max_perms[size] = perm;
		}
	}

	return max_perms;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param fdic [description]
 * @param short [description]
 *
 * @return [description]
 */
Graph **read_dic(FILE *fdic, unsigned short *max_perms)
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
	for (i = 0; i < MAX_WORD_SIZE; i++) {
		if (max_perms[i] != 0) {
			g_make_edges(graphs[i], w_diff);
		}
	}

	return graphs;
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param fpal [description]
 * @param fpath [description]
 * @param graphs [description]
 */
void solve_pal(FILE *fpal, FILE *fpath, Graph **graphs)
{
	Graph *g;
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	unsigned short max_perm;
	int i, j; /* indíce do vértice de origem do grafo. */
	int *st = NULL, *wt = NULL;
	int diff;

	while (fscanf(fpal, "%s %s %hu", word1, word2, &max_perm) == 3) {
		if ((diff = w_diff(word1, word2, 1)) <= 1) {
			/* Solução trivial */
			fprintf(fpath, "%s %d\n%s\n\n", word1, diff, word2);
			continue;
		}

		g = graphs[strlen(word1)];
		i = g_find_vertex(g, word1, w_cmp);
		j = g_find_vertex(g, word2, w_cmp);

		st = realloc(st, g_get_free(g) * sizeof(int));
		wt = shortest_path(g, i, j, st, max_perm*max_perm);

		if (st[j] == -1) {
			fprintf(fpath, "%s %d\n%s\n", word1, -1, word2);
		}
		else {
			fprintf(fpath, "%s %d\n", (char *) v_get_item(g_get_vertex(g, i)), wt[j]);
			walk_tree(g, st, wt, st[j], fpath);

			fprintf(fpath, "%s\n", (char *) v_get_item(g_get_vertex(g, j)));
		}

		fprintf(fpath, "\n");
	}

	free(wt);
	free(st);
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param g [description]
 * @param st [description]
 * @param wt [description]
 * @param dst [description]
 * @param path [description]
 */
void walk_tree(Graph *g, int *st, int *wt, int dst, FILE *path)
{
	if (st[dst] != -1) {
		walk_tree(g, st, wt, st[dst], path);
		fprintf(path, "%s\n", (char *) v_get_item(g_get_vertex(g, dst)));
	}
	return;
}
