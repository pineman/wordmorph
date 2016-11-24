#ifndef _LIST_H
#define _LIST_H

#include "item.h"

typedef struct _List List;

List *l_init(void);
void l_free(List *lp, void (*free_item)(Item));

void l_insert(List **head, Item item);

Item l_get_item(List *l);
List *l_get_next(List *l);
void l_set_next(List *l, List *next);

#endif
