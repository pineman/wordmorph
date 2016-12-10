/**
 * @file file.h
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Funções de I/O.
 * @details
 *	Construir grafos e imprimir caminhos.
 */
#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>

#include "graph.h"

unsigned short *find_max_perms(FILE *fpal);

Graph **read_dic(FILE *fdic, unsigned short *max_perms);

void solve_pal(FILE *fpal, FILE *fpath, Graph **graphs);

void fprint_path(FILE *fpath, Graph *g, int *st, int *wt, int dst);

#endif
