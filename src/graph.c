#include "graph.h"
#include "utils.h"
#include "bool.h"


struct _Node {
    Item item;
    List *adj;
};

struct _Link {
    int weight;
    int index;
};

struct _Graph {
    Node **nodes;
    int free;
    int size;
};

Graph *g_init(unsigned int size)
{
    Graph *graph = (Graph *) emalloc(sizeof(Graph));
    graph->free = size;
    graph->size = size;

    return graph;
}

void g_insert(Graph *graph, Item item)
{
    Node *new_node = _init_node(item);
    graph->nodes[graph->free] = new_node; 
    (graph->free)--;
}

void g_free(Graph *graph)
{
    int i;
    Node *aux;
    for (i=0; i<graph->size; i++) {
        aux = graph->nodes[i];
        l_free(aux->adj, free);
        free(aux);
    }

    free(graph->nodes);
    free(graph);

    return;
}

bool g_cmp_links(Link *l1, Link *l2)
{
    return (l1->weight > l2->weight);
}

Node *_init_node(Item item)
{
    Node *new_node = (Node *) ecalloc(1, sizeof(Node));
    new_node->item = item;
    new_node->adj = l_init();

    return new_node;
}

