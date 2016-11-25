#include <stdio.h>

#include "file.h"
#include "utils.h"
#include "const.h"

int *find_max_perms(FILE *fpal)
{
	char buffer[MAX_WORD_SIZE];
	char word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
	int perm;
	size_t size;
	/* Array cujos índices são os tamanhos de palavra necessários e cujos
	 * valores são o número máximo de permutações para esse tamanho. */
	int *max_perms = (int *) ecalloc(MAX_WORD_SIZE, sizeof(int));

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
