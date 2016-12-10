/**
 * @file utils.h
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Funções de utilidade genérica.
 * @details
 * 	Wrappers de funções com verificação de erros:
 * 		emalloc(), ecalloc(), efopen()
 *
 * 	Manipulação de strings:
 * 		change_file_ext()
 */
#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>

void *emalloc(const size_t size);
void *ecalloc(const size_t nmemb, const size_t size);
FILE *efopen(const char *filename, const char *mode);
char *change_file_ext(const char *orig_file_name, const char *new_ext);

#endif
