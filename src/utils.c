#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void *emalloc(const size_t size)
{
	void *p = malloc(size);
	if (p == NULL) {
		fprintf(stderr, "Erro: impossível alocar memória.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

void *ecalloc(const size_t nmemb, const size_t size)
{
	void *p = calloc(nmemb, size);
	if (p == NULL) {
		fprintf(stderr, "Erro: impossível alocar memória.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

FILE *efopen(const char *filename, const char *mode)
{
	FILE *fp = fopen(filename, mode);
	if (fp == NULL) {
		fprintf(stderr, "Erro: impossível abrir ficheiro %s.\n", filename);
		exit(EXIT_FAILURE);
	}
	return fp;
}

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
