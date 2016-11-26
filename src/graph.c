#include "graph.h"
#include "utils.h"
#include "bool.h"


struct _Node {
    Item item;
    List *adj;
};

struct _Link {
    unsigned int weight;
    unsigned int index;
};

struct _Graph {
    Node **nodes;
    unsigned int free;
    unsigned int size;
    unsigned int max_weight;
};

Graph *g_init(unsigned int size, unsigned int max_weight)
{
    Graph *g = (Graph *) emalloc(sizeof(Graph));
    g->nodes = (Node **) emalloc(sizeof(Node *) * size);
    g->free = 0;
    g->size = size;
    g->max_weight = max_weight;

    return g;
}

void g_insert(Graph *g, Item i)
{
    Node *new_node;
    if (g->free == g->size) {
        puts("Erro: grafo esta cheio");
        exit(EXIT_FAILURE);
    }
    new_node = _init_node(i);
    g->nodes[g->free] = new_node; 
    g->free++;
}

void g_free(Graph *g)
{
    unsigned int i;
    Node *aux;
    for (i=0; i<g->size; i++) {
        aux = g->nodes[i];
        l_free(aux->adj, free);
        free(aux);
    }

    free(g->nodes);
    free(g);

    return;
}

Node *g_get_node(Graph *g, unsigned int index)
{
    if (g == NULL) {
        fprintf(stderr, "Erro: grafo não existe!");
        exit(EXIT_FAILURE);
    }
    else if (index > g->size) {
        fprintf(stderr, "Erro: index está fora dos limites do grafo!");
        exit(EXIT_FAILURE);
    }

    return g->nodes[index];
}

Item g_get_item(Node *n)
{
    if (n == NULL) {
        fprintf(stderr, "Erro: nó não existe!");
        exit(EXIT_FAILURE);
    }
    else if (n->item == NULL) {
        fprintf(stderr, "Erro: item não existe!");
        exit(EXIT_FAILURE);
    }

    return n->item;
}

List *g_get_adj(Node *n)
{
    if (n == NULL)
        puts("Error: lista não inicializada");

    return n->adj;
}

unsigned int g_get_weight(Link *l)
{
    return l->weight;
}

unsigned int g_get_index(Link *l)
{
    return l->index;
}

void g_update_links(Graph *g, unsigned int (*calc_weight)(Item i1, Item i2, 
                                                          unsigned int max))
{
    unsigned int i, j;
    unsigned int weight;
    for (i=0; i<g->free; i++)
        for (j=0; j<i; j++) {
            if ((weight = calc_weight(g->nodes[i]->item, g->nodes[j]->item, g->max_weight)) <= g->max_weight)
                _make_link(g, i, j, weight);
        }

}

void _make_link (Graph *g, unsigned int i1, unsigned int i2, 
                    unsigned int weight) 
{
    Link *l1 = _init_link(i2, weight);
    Link *l2 = _init_link(i1, weight);

    l_insert(&(g->nodes[i1]->adj), l1);
    l_insert(&(g->nodes[i2]->adj), l2);   
}

Link *_init_link(unsigned int index, unsigned int weight)
{
    Link *new_link = (Link *) emalloc(sizeof(Link));
    new_link->index = index;
    new_link->weight = weight;

    return new_link;
}

bool g_cmp_links(Link *l1, Link *l2)
{
    return (l1->weight > l2->weight);
}

Node *_init_node(Item i)
{
    Node *new_node = (Node *) ecalloc(1, sizeof(Node));
    new_node->item = i;
    new_node->adj = l_init();

    return new_node;
}


/*
 * Node getters and setters
 */