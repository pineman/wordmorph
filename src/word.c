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

unsigned short w_diff(Item v1, Item v2, unsigned short max_perm)
{
	/*unsigned int size, i*/ 
	unsigned int cnt = 0;
	char *w1 = (char *) v1;
	char *w2 = (char *) v2;
	/*size = strlen(w1);*/
	/*if ((size = strlen(w1)) != strlen(w2)) {
		fprintf(stderr, "Erro: Tentativa de comparação de palavras de tamanos diferentes!");
		exit(EXIT_FAILURE);
	}*/

	while (*w1 != '\0') {
		if (*w1 != *w2)
			cnt++;
		if (cnt > max_perm)
			break;
		w1++;  w2++;
	}

	/*for (i=0; i<size && !(cnt > max_perm); i++) {
		if (w1[i] != w2[i])
			cnt++;
	}*/

	return cnt;
}

/* Funções acessoras */
int w_get_size(char *word)
{
	return (int) strlen(word);
}

int w_cmp(Item c1, Item c2)
{
	return strcmp((const char *) c1, (const char *) c2);
}