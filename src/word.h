#ifndef _WORD_H
#define _WORD_H

#include "bool.h"
#include "item.h"

/* TODO:
 * typedef struct _Word Word
 */

char *w_new(char *word);
void w_free(Item word);
bool w_less(Item a, Item b);

unsigned int w_diff(Item w1, Item w2, unsigned int max_perm);

int w_get_size(char *word);

#endif
