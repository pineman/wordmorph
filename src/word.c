#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "utils.h"
#include "word.h"

/* TODO:
 *
 * struct _Word {
 *	char *word;
 * };
 *
*/

char *w_new(char *word)
{
	char *new_word = (char *) emalloc((strlen(word) + 1) * sizeof(char));
	strcpy(new_word, word);

	return new_word;
}

void w_free(Item word)
{
	free(word);
}

bool w_less(Item a, Item b)
{
	int less;
	less = strcmp((char *) a, (char *) b);
	if (less <= 0)
		return true;
	else
		return false;
}

unsigned int w_diff(char *w1, char *w2, unsigned int max_perm)
{
	unsigned int size, i, cnt = 0;
	if ((size = strlen(w1)) != strlen(w2)) {
		fprintf(stderr, "Erro: Tentativa de comparação de palavras de tamanos diferentes!");
		exit(EXIT_FAILURE);
	}

	for (i=0; i<size && !(cnt > max_perm); i++) {
		if (w1[i] != w2[i])
			cnt++;
	}

	return cnt;
}

/* Funções acessoras */
int w_get_size(char *word)
{
	return (int) strlen(word);
}
