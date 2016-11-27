#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "utils.h"
#include "const.h"
#include "file.h"
#include "word.h"

static const char *VALID_EXTS[] = {".dic", ".pal"};

void usage(char *prog_name);

void usage(char *prog_name)
{
	fprintf(stderr, "Uso: %s [dicionário.dic] [problemas.pal]\n", prog_name);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	FILE *fdic, *fpal, *fpath;
	char *fpath_name;
	char *test;

	int *max_perms;
	/* Array de grafos por tamanhos de palavras que contêm. */
	Graph **graphs;

	int i;

	/* Verificação dos parâmetros de entrada*/
	if (argc != 3) {
		usage(argv[0]);
	}

	/* Verificar extensões dos ficheiros */
	for (i = 0; i < 2; i++) {
		test = strrchr(argv[i+1], '.');

		if (!test || strcmp(test, VALID_EXTS[i]) != 0) {
			usage(argv[1]);
		}
	}

	/* Abrir ficheiros de entrada (efopen faz exit() em caso de erro) */
	fdic = efopen(argv[1], "r");
	fpal = efopen(argv[2], "r");
	fpath_name = change_file_ext(argv[2], OUT_EXT, OUT_EXT_SIZE);
	fpath = efopen(fpath_name, "w");
	free(fpath_name);

	/* Encontrar os tamanhos de palavras e o número máximo de permutações
	 * para cada tamanho a partir do ficheiro de problemas. */
	max_perms = find_max_perms(fpal);
	rewind(fpal);

	/* Ler o dicionário para obter os nós dos grafos. */
	graphs = read_dic(fdic, max_perms);
	fclose(fdic);
	free(max_perms);

	/* TODO: Construir grafos?? */
	/* build_graphs(graphs); */

	/* Ler e resolver problemas. */
	solve_pal(fpal, fpath, graphs);
	fclose(fpal);
	fclose(fpath);

	/* Libertar memória. */
	for (i = 0; i < MAX_WORD_SIZE; i++) {
		if (graphs[i] != NULL) {
			g_free(graphs[i], w_free);
		}
	}
	free(graphs);

	return EXIT_SUCCESS;
}
