#include <stdlib.h>

#include "list.h"
#include "utils.h"

struct _List {
    Item item;
    struct _List *next;
};

/**
 * @brief Initialize empty list
 *
 * @return Pointer to list
 */
List *l_init(void)
{
    return NULL;
}


/**
 * @brief Insert new node on the list's head
 *
 * @param head Pointer to list's head
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
 * @brief Free the list
 *
 * @param head Pointer to list's head
 * @param free_item Pointer to function that frees Item
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
 * @brief Get next element in the list
 *
 * @param l List node
 *
 * @return next Next node
 */
List *l_get_next(List *l)
{
    return l->next;
}

/**
 * @brief Get the node's payload
 *
 * @param l List node
 *
 * @return node's payload
 */
Item l_get_item(List *l)
{
    return l->item;
}

/**
 * @brief Set a node's next node
 *
 * @param l List node
 * @param next New next node
 */
void l_set_next(List *l, List *next)
{
    l->next = next;
}

