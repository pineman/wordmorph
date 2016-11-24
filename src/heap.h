#ifndef HEAD_H
#define HEAD_H

#include "bool.h"
#include "item.h"

void FixUp(int Idx);
void FixDown(int Idx, int N);
void h_init();
bool h_empty();
void h_insert(Item);
/*Item h_delmax();*/




#endif