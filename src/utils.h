/* Utils.c
 * Authors: João Pinheiro e João Freitas
 * Description:
 *  Tools for error checking:
 *      emalloc, ecalloc, efopen
 *  String manipulation:
 *      change_file_ext
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void *emalloc(const size_t size);
void *ecalloc(const size_t nmemb, const size_t size);
FILE *efopen(const char *filename, const char *mode);
char *change_file_ext(const char *orig_file_name, const char *new_ext, const size_t ext_size);

#endif
