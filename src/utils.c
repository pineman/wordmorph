/**
 * @file utils.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * @brief Wrapper da função malloc() com verificação de erros.
 *
 * @param size Número de bytes a alocar.
 * @return Ponteiro para a memória alocada (não inicializada).
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
 * @brief Wrapper da função calloc() com verificação de erros.
 *
 * @param nmemb Número de itens a alocar.
 * @param size Tamanho de cada item.
 * @return Ponteiro para a memória alocada (inicializada a 0x0).
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
 * @brief Wrapper da função fopen() com verificação de erros.
 *
 * @param filename Nome do ficheiro.
 * @param mode Modo de abertura do ficheiro.
 * @return Ponteiro para o ficheiro.
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
 * @brief Mudar a extensão de uma string que representa o nome de um ficheiro.
 *
 * @param orig_file_name O nome original com extensão.
 * @param new_ext A nova extensão.
 * @return Ponteiro para string alocada com a nova extensão.
 */
char *change_file_ext(const char *orig_file_name, const char *new_ext)
{
	char *new_file_name;
	size_t file_name_size;
	char *ext;

	ext = strrchr(orig_file_name, '.');
	file_name_size = ext - orig_file_name;

	new_file_name = (char *) ecalloc(file_name_size + strlen(new_ext) + 1, sizeof(char));

	strncpy(new_file_name, orig_file_name, file_name_size);
	strcat(new_file_name, new_ext);

	return new_file_name;
}
