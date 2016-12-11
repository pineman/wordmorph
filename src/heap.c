/**
 * @file heap.c
 * @authors João Pinheiro <joao.castro.pinheiro@tecnico.ulisboa.pt>
 * @authors João Freitas <joao.m.freitas@tecnico.ulisboa.pt>
 * @date 14 Dezembro 2016
 *
 * @brief Implementação da biblioteca de acervos.
 * @details
 * Implementação de uma fila prioritária utilizando acervos.
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "bool.h"
#include "utils.h"

#define CHILD1(i) ((2*(i))+1)
#define CHILD2(i) ((2*(i))+2)
#define PARENT(i) (((i)-1)/2)


/**
 * @brief Acervo.
 * @details vector: Tabela de items que respeita a condição de acervo
 * hash_table: tabela que mapeia a posição dos elementos dentro do acervo
 * free: número de elementos no acervo (posição livre)
 * size: número máximo de elementos no acervo.
 *
 */
struct _Heap {
	Item **vector;
	unsigned short *hash_table;
	unsigned short free;
	unsigned short size;
};

/**
 * @brief Inicializa a heap.
 *
 * @param size Tamanho máximo da heap.
 * @return Ponteiro para heap.
 */
Heap *h_init(unsigned short size)
{
	Heap *h = (Heap *) emalloc(sizeof(Heap));
	h->vector = (Item **) emalloc(size * sizeof(Item *));
	h->hash_table = (unsigned short *) ecalloc(size, sizeof(unsigned short));
	h->size = size;
	h->free = 0;

	return h;
}

/**
 * @brief Liberta a heap.
 *
 * @param h Ponteiro para heap.
 */
void h_free(Heap *h)
{
	free(h->vector);
	free(h->hash_table);
	free(h);
}


/**
 * @brief Actualiza a posição de uma elemento para cima na heap.
 * @details Compara sucessivamente um elemento da heap com o seu pai enquanto
 * este for menos prioritario que o filho, troca os elementos quando estes não
 * respeitam a condição de acervo.
 *
 * @param h Ponteiro para heap.
 * @param i Indice do elemento a verificar.
 * @param less_pri Ponteiro para função que compara prioridades.
 * @param hash Ponteiro para função que retorna o indice na heap de um elemento.
 */
void h_fixup(Heap *h, int i, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	while (i > 0 && less_pri(h->vector[PARENT(i)], h->vector[i])) {
		h_exch(h, i, PARENT(i), hash);
		i = PARENT(i);
	}
}

/**
 * @brief Atualiza a posição de uma elemento para baixo na heap.
 *
 * @param h Ponteiro para heap
 * @param i Indice do elemento a fazer fixdown.
 * @param less_pri Ponteiro para função que compara prioridades.
 * @param hash Ponteiro para função que retorna o indice na heap de um elemento.
 */
void h_fixdown(Heap *h, int i, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	int child;

	/* Iterar até chegar ao penúltimo nível da árvore inclusivé */
	while (2 * i < h->free - 1) {
		child = CHILD1(i);

		/* Escolher o filho com maior prioridade, para comparar com o pai */
		if (child < h->free - 1 && less_pri(h->vector[child], h->vector[child + 1])) {
			/* O outro filho tem mais prioridade! */
			child++;
		}

		/* Se o pai tiver mais (não tiver menos) prioridade que o filho,
		 * o filho está então no sítio certo na heap. */
		if (!less_pri(h->vector[i], h->vector[child])) {
			break;
		}

		/* Se não, temos de trocar o pai com o filho */
		h_exch(h, i, child, hash);

		/* Continuar a iterar a árvore para baixo, seguindo o pai antigo
		 * que agora ocupa a posição do filho antigo */
		i = child;
	}
}

/**
 * @brief Insere elemento na heap.
 *
 * @param h Ponteiro para heap.
 * @param a Item a inserir na heap.
 * @param less_pri Ponteiro para função que compara prioridades.
 * @param hash Ponteiro para função que retorna o indice na heap de um elemento.
 */
void h_insert(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	h->vector[h->free] = a;
	h->hash_table[hash(a)] = h->free;

	h_fixup(h, h->free, less_pri, hash);
	h->free++;
}

/**
 * @brief Obter o elemento na heap de maior prioridade.
 *
 * @param h Ponteiro para heap.
 * @param less_pri Ponteiro para função que compara prioridades.
 * @param hash Ponteiro para função que retorna o indice na heap de um elemento.
 * @return Elemento de maior prioridade na heap
 */
Item h_del_max_pri(Heap *h, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	/* Trocar o último elemento com o primeiro. */
	h_exch(h, 0, h->free - 1, hash);

	/* Ignorar o último elemento, pois vai ser removido. */
	h->free--;

	/* Encontrar o sítio certo do antigo último elemento
	 * (agora na posição 0) */
	h_fixdown(h, 0, less_pri, hash);

	return h->vector[h->free];
}

/**
 * @brief Encontra indice de um elemento na heap a partir de um item
 *
 * @param h Ponteiro para heap
 * @param a Item a encontrar na heap
 * @param hash Ponteiro para função que retorna o indice na heap de um elemento.
 * @return Indice do item na heap
 */
unsigned short h_find(Heap *h, Item a, unsigned short (*hash)(Item))
{
	return h->hash_table[hash(a)];
}

/**
 * @brief Atualiza a posição na heap de um elemento que aumentou a sua prioridade.
 *
 * @param h Ponteiro para heap.
 * @param a Item a atualizar a posição.
 * @param less_pri Ponteiro para função que compara prioridades.
 * @param hash Ponteiro para função que retorna o indice na heap de um elemento.
 */
void h_inc_pri(Heap *h, Item a, bool (*less_pri)(Item, Item), unsigned short (*hash)(Item))
{
	h_fixup(h, h_find(h, a, hash), less_pri, hash);
}

/**
 * @brief Troca elementos na heap
 *
 * @param h Ponteiro para heap
 * @param i1 Indice do primeiro elemento a trocar
 * @param i2 Indice do segundo elemento a trocar
 * @param hash Ponteiro para função que retorna o indice na heap de um elemento.
 */
void h_exch(Heap *h, unsigned short i1, unsigned short i2, unsigned short (*hash)(Item))
{
	Item tmp;
	unsigned short tmp_i;

	/* Atualizar hash table */
	tmp_i = h->hash_table[hash(h->vector[i2])];
	h->hash_table[hash(h->vector[i2])] = h->hash_table[hash(h->vector[i1])];
	h->hash_table[hash(h->vector[i1])] = tmp_i;

	/* Troca é fácil pois apenas trabalhamos com Items (ponteiros!) */
	tmp = h->vector[i2];
	h->vector[i2] = h->vector[i1];
	h->vector[i1] = tmp;
}

/**
 * @brief Verifica se a heap esta vazia.
 *
 * @param h Ponteiro para heap.
 * @return Verdadeiro se a heap estiver vazia e falso se não.
 */
bool h_empty(Heap *h)
{
	return !(h->free);
}
