#include <string.h>
#include "item.h"

void exch(Item *i1, Item *i2) 
{
    Item tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;

    return;
}

/**
 * @brief Finds the Item with the smaller priority
 * @details cmp_item Should return true if i1 is bigger than i2, but the 
 * item with the highest priority is the smaller one    
 * 
 * @param i1 First item to compare
 * @param i2 Second item to compare
 * @param cmp_item Compare items function
 * @return True if i1 is more prioritary than i2, false if not
 */
bool less_pri(Item i1, Item i2, bool (cmp_item)(Item, Item))
{
    return !(cmp_item(i1, i2));
}

unsigned int calc_weight(Item i1, Item i2, unsigned int max)
{
    int dif = *((int*)i1) - *((int*)i2);

    return (dif > 0) ? dif : -dif;
}
