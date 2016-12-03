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

/* Retorna o número de caracteres diferentes entre as strings v1 e v2,
 * assumindo que estas são do mesmo tamamnho. */
unsigned short w_diff(Item v1, Item v2, unsigned short max_perm)
{
	/* TODO: lento como nós sabemos */
	unsigned short cnt = 0;
	int i;
	char *w1 = (char *) v1;
	char *w2 = (char *) v2;

	/* TODO: Se calhar este loop pode ser hand-rolled. */
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

/* Funções acessoras */
int w_get_size(char *word)
{
	return (int) strlen(word);
}

int w_cmp(Item c1, Item c2)
{
	return strcmp((const char *) c1, (const char *) c2);
}
