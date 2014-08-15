#ifndef EDGE_LIST_H_
#define EDGE_LIST_H_

typedef struct edge_list edge_list;

#include <tm/edge.h>

/**
 * \struct edge_list
 * \brief Represents an list of edges (#edge) of a #state of the #tm
 *
 * This is the "List Class" of #edge so here are only list functions.
 *
 * \var edge_list::head
 * Head of the list
 * \var edge_list::size
 * Size of the list
 */
struct edge_list {
	edge *head;
	unsigned int size;
};

edge_list *edge_list_new();
void edge_list_init(edge_list *this);
void edge_list_add_node(edge_list *this, edge *new);
edge *edge_list_find_node(edge_list *this, unsigned int id);
edge_list *edge_list_copy(edge_list *this);
void edge_list_delete_node(edge_list *this, unsigned int id);
void edge_list_delete_node_exact(edge_list *this, edge *del);
void edge_list_free(edge_list *this);
void edge_list_print(edge_list *this);

#endif
