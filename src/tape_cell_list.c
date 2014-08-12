#include <stdio.h>
#include <stdlib.h>
#include "../include/tape_cell_list.h"
#include "../include/singly_linked_list_macros.h"

/**
 * \brief Create new #tape_cell_list struct
 * \return New #tape_cell_list struct
 */
struct tape_cell_list *tape_cell_list_new()
{
	//FIXME add error handling
	struct tape_cell_list *ret = malloc(sizeof(*ret));

	ret->head = NULL;
	ret->last = NULL;
	ret->size = 0;
	return ret;
}

/**
 * \brief Add #tape_cell to #tape_cell_list
 * \param new The new #tape_cell struct which should be added
 */
void tape_cell_list_add_node(struct tape_cell_list *this, struct tape_cell *new)
{
	/*if (!this->head) {
		this->head = new;
		return;
	}
	new->next = this->head;
	new->prev = this->head->prev;
	new->prev->next = new;
	this->head->prev = new;*/

	if (!this->head) {
		this->head = new;
		this->last = this->head;
		this->size = this->size + 1;
		return;
	}
	new->prev = this->last;
	this->last->next = new;
	this->last = new;
	this->size = this->size + 1;
}

/**
 * \brief Add #tape_cell *before* given node
 * \param before This should be the successor of _new_
 * \param new The new #tape_cell struct which should be added before _before_
 */
void tape_cell_list_add_node_before(struct tape_cell_list *this, struct tape_cell *before, struct tape_cell *new)
{
	if (!this->head)
		return;
	if (!new)
		return;
	if (!before)
		return;
	new->next = before;
	new->prev = before->prev;
	if (before == this->head) {
		this->head->prev = new;
		this->head = new;
		this->size = this->size + 1;
		return;
	}
	before->prev->next = new;
	before->prev = new;
	this->size = this->size + 1;
}

/**
 * \brief Add #tape_cell *after* given node
 * \param after This should be the predecessor of _new_
 * \param new The new #tape_cell struct which should be added after _after_
 */
void tape_cell_list_add_node_after(struct tape_cell_list *this, struct tape_cell *after, struct tape_cell *new)
{
	if (!this->head)
		return;
	if (!new)
		return;
	if (!after)
		return;
	new->next = after->next;
	new->prev = after;
	if (after == this->head) {
		this->head->next = new;
		if (this->head == this->last)
			this->last = this->last->next;
		this->size = this->size + 1;
		return;
	}
	if (after == this->last) {
		after->next = new;
		this->last = new;
		this->size = this->size + 1;
		return;
	}
	after->next->prev = new;
	after->next = new;
	this->size = this->size + 1;
}

/**
 * \brief Remove #tape_cell struct from #tape_cell_list
 * \param del #tape_cell we want to delete
 */
void tape_cell_list_delete_node(struct tape_cell_list *this, struct tape_cell *del)
{
	if (!this)
		return;
	if (!this->head)
		return;
	if (!del)
		return;
	struct tape_cell *iter = container_of(&this->head, struct tape_cell, next);
	struct tape_cell *prev = iter;

	while (iter) {
		prev = iter;
		iter = iter->next;
		if (iter == del) {
			prev->next = del->next;
			tape_cell_free(del);
			this->size = this->size - 1;
			break;
		}
	}
	return;
}

/**
 * \brief Free #tape_cell_list object
 */
void tape_cell_list_free(struct tape_cell_list *this)
{
	while (this->head)
		tape_cell_list_delete_node(this, this->head);
	free(this);
}

void tape_cell_list_print(struct tape_cell_list *this, struct tape_cell *highlight)
{
	struct tape_cell *iter = NULL;

	S_FOR_EACH_ENTRY(this->head, iter) {
		if (iter == highlight) {
			printf("[->%u<-]", iter->token);
		} else
			tape_cell_print(iter);
	}
	printf("\n");
}
