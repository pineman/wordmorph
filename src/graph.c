#include "graph.h"
#include "utils.h"

struct _Node {
    Item item;
    List *adj;
};

struct _Link {
    int weight;
    int index;
};

struct _Graph {
    Node *nodes;
    int free;
    int size;
};

Graph *g_init(unsigned int size)
{
    Graph graph = (Graph) emalloc(sizeof(Graph));
    graph->free = size;
    graph->size = size;

    return graph;

}

void g_insert(Graph *graph, Item item);
{
    Node *new_node = (Node *) ecalloc(sizeof(Node));
    new_node->item = item;

    graph->nodes[free] = new_node; 
}

void g_free(Graph)
{
    int i;
    for (i=0; i<size; i++)

}

void node_free(Node *node)
{
    Node *aux = node;
    while (aux != NULL) {
        free(aux)
    }
}
