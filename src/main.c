#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "const.h"
#include "file.h"

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
	int *max_perms;
	char *test;
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

	free(max_perms);
	fclose(fdic);
	fclose(fpal);
	fclose(fpath);

	return EXIT_SUCCESS;
}
