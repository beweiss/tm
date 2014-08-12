#include <stdio.h>
#include <stdlib.h>
#include "singly_linked_list_macros.h"
#include "edge_list.h"

/**
 * \brief Create new #edge_list object
 * \return New #edge_list object
 */
edge_list *edge_list_new()
{
	//FIXME add error handling
	edge_list *ret = malloc(sizeof(*ret));

	ret->head = NULL;
	ret->size = 0;

	return ret;
}

/**
 * \brief Add #edge to #edge_list
 * \param new The new #egde object which should be added
 */
void edge_list_add_node(edge_list *this, edge *new)
{
	if (!this)
		return;
	if (!new)
		return;
	edge *last = S_LAST_ENTRY(this->head);

	//FIXME container_of(....) to avoid condition
	if (!last) {
		this->head = new;
	}
	else {
		last->next = new;
	}
	this->size = this->size + 1;
}

/**
 * \brief Find #edge in #edge_list
 * \param id ID of the searched #edge
 * \return #edge object or NULL if there is no #edge with this ID
 */
edge *edge_list_find_node(edge_list *this, unsigned int id)
{
	edge *iter = NULL;

	S_FOR_EACH_ENTRY(this->head, iter) {
		if (iter->id_dest == id)
			return iter;
	}
	return NULL;
}

/**
 * \brief Copy #edge_list object
 * \return Copy of #edge_list object
 */
edge_list *edge_list_copy(edge_list *this)
{
	return NULL;
}

/**
 * \brief Remove #edge object from #edge_list
 * \param id ID of the wanted #edge
 */
void edge_list_delete_node(edge_list *this, unsigned int id)
{
	__edge_list_delete_node(this, edge_list_find_node(this, id));
}

/**
 * \brief Remove #edge object from #edge_list
 * \param del #edge we want to delete
 *
 * \see edge_list_delete_node
 *
 */
void __edge_list_delete_node(edge_list *this, edge *del)
{
	if (!this)
		return;
	if (!this->head)
		return;
	if (!del)
		return;
	edge *iter = container_of(&this->head, edge, next);
	edge *prev = iter;

	while (iter) {
		prev = iter;
		iter = iter->next;
		if (iter == del) {
			prev->next = del->next;
			edge_free(del);
			this->size = this->size - 1;
			break;
		}
	}
	return;
}

/**
 * \brief Free #edge_list object
 */
void edge_list_free(edge_list *this)
{
	while (this->head)
		__edge_list_delete_node(this, this->head);
	free(this);
}

/**
 * \brief Print #edge_list object to stdout
 */
void edge_list_print(edge_list *this)
{
	edge *iter = NULL;

	S_FOR_EACH_ENTRY(this->head, iter) {
		printf("\t\t");
		edge_print(iter);
	}
}
