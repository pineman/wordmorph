#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>

int *find_max_perms(FILE *fpal);

Graph *read_dic(FILE *fdic, int *max_perms);

#endif
