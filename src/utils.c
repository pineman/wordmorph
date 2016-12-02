/* Utils.c
 * Authors: João Pinheiro e João Freitas
 * Description:
 *	Tools for error checking:
 *		emalloc, ecalloc, efopen
 *	String manipulation:
 *		change_file_ext
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * @brief malloc wrapper with error checking
 *
 * @param  size of memory to alloc
 *
 * @return	return pointer to unitialized memory
 */
void *emalloc(const size_t size)
{
	void *p = malloc(size);
	if (p == NULL) {
		fprintf(stderr, "Erro: impossível alocar memória.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

/**
 * @brief ecalloc wrapper with error checking
 *
 * @param  nmemb number of elements to alloc
 * @param  size	 size of each element
 *
 * @return		 pointer to 0 initialized memory
 */
void *ecalloc(const size_t nmemb, const size_t size)
{
	void *p = calloc(nmemb, size);
	if (p == NULL) {
		fprintf(stderr, "Erro: impossível alocar memória.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

/**
 * @brief fopen wrapper with erro checking
 *
 * @param  filename string with the path of the file
 * @param  mode of interacting with the file
 *
 * @return	 pointer to the file
 */
FILE *efopen(const char *filename, const char *mode)
{
	FILE *fp = fopen(filename, mode);
	if (fp == NULL) {
		fprintf(stderr, "Erro: impossível abrir ficheiro %s.\n", filename);
		exit(EXIT_FAILURE);
	}
	return fp;
}

/**
 * @brief change file name extension
 *
 * @param  orig_file_name string with the original name with extension
 * @param  new_ext		  string with the new extension
 * @param  ext_size		  size of the new extension
 *
 * @return return string with the new file name
 */
char *change_file_ext(const char *orig_file_name, const char *new_ext, const size_t ext_size)
{
	char *new_file_name;
	size_t file_name_size;
	char *ext;

	ext = strrchr(orig_file_name, '.');
	file_name_size = ext - orig_file_name;

	new_file_name = (char *) ecalloc(file_name_size + ext_size + 1, sizeof(char));

	strncpy(new_file_name, orig_file_name, file_name_size);
	strcat(new_file_name, new_ext);

	return new_file_name;
}
