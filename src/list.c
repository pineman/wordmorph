#include <stdlib.h>

#include "list.h"
#include "utils.h"

struct _List {
    Item item;
    struct _List *next;
};

/**
 * @brief Initialize empty list
 * @return Pointer to list
 */
List *l_init(void)
{
    return NULL;
}


 /**
  * @brief Insert new node on the list's head
  *
  * @param head address of pointer to list's head
  * @param item new node's payload
  */
void l_insert(List **head, Item item)
{
    List *new_node = (List *) emalloc(sizeof(List));
    new_node->item = item;

    new_node->next = *head;
    *head = new_node;
    return;
}

/**
 * @brief Free all the list nodes
 * @param head List pointer
 * @param free_im Payload of new node
 */
void l_free(List *head, void (*free_item)(Item))
{
    List *aux = head;
    List *tmp;

    while (aux) {
        tmp = aux->next;
        free_item(aux->item);
        free(aux);
        aux = tmp;
    }

    return;
}

/**
 * @brief get next element in the list
 *
 * @param l list node
 * @return next node
 */
List *l_get_next(List *l)
{
    return l->next;
}

/**
 * @brief get the node's payload
 *
 * @param l list node
 * @return payload
 */
Item l_get_item(List *l)
{
    return l->item;
}

/**
 * @brief define the next node in the list
 *
 * @param l list node
 * @param next new next node
 */
void l_set_next(List *l, List *next)
{
    l->next = next;
}

