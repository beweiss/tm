#include <stdio.h>
#include <stdlib.h>
#include "../include/tape_cell_list.h"
#include "../include/singly_linked_list_macros.h"
#include "../include/erring.h"

/**
 * \brief Create new #tape_cell_list struct
 * \return New #tape_cell_list struct
 */
struct tape_cell_list *tape_cell_list_new()
{
	//FIXME add error handling
	struct tape_cell_list *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}

	ret->head = NULL;
	ret->tail = NULL;
	ret->size = 0;
	return ret;
}

/**
 * \brief Add #tape_cell to #tape_cell_list
 * \param new The new #tape_cell struct which should be added
 */
void tape_cell_list_add_node(struct tape_cell_list *this, struct tape_cell *new)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (!new) {
		erring_add(E_NULL);
		return;
	}
	if (!this->head) {
		this->head = new;
		this->tail = this->head;
		this->size = this->size + 1;
		return;
	}
	new->prev = this->tail;
	this->tail->next = new;
	this->tail = new;
	this->size = this->size + 1;
}

/**
 * \brief Add #tape_cell *before* given node
 * \param before This should be the successor of _new_
 * \param new The new #tape_cell struct which should be added before _before_
 */
void tape_cell_list_add_node_before(struct tape_cell_list *this, struct tape_cell *before, struct tape_cell *new)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (!new) {
		erring_add(E_NULL);
		return;
	}
	if (!before) {
		erring_add(E_NULL);
		return;
	}
	if (!this->head) {
		erring_add("ERROR: Head may not be NULL in this function! (List is empty)");
		return;
	}
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
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (!new) {
		erring_add(E_NULL);
		return;
	}
	if (!after) {
		erring_add(E_NULL);
		return;
	}
	if (!this->head) {
		erring_add("ERROR: Head may not be NULL in this function! (List is empty)");
		return;
	}
	new->next = after->next;
	new->prev = after;
	if (after == this->head) {
		this->head->next = new;
		if (this->head == this->tail)
			this->tail = this->tail->next;
		this->size = this->size + 1;
		return;
	}
	if (after == this->tail) {
		after->next = new;
		this->tail = new;
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
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (!this->head) {
		erring_add("ERROR: Head may not be NULL in this function! (List is empty)");
		return;
	}
	if (!del) {
		erring_add(E_NULL);
		return;
	}
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

struct tape_cell_list *tape_cell_list_copy(struct tape_cell_list *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	struct tape_cell_list *ret = tape_cell_list_new();
	struct tape_cell *iter_old = this->head;

	if (!ret) {
		erring_add(CALL_FAILED_TO(tape_cell_list_new));
		return NULL;
	}

	while (iter_old) {
		tape_cell_list_add_node(ret, tape_cell_copy(iter_old));
		iter_old = iter_old->next;
	}
	return ret;
}

/**
 * \brief Free #tape_cell_list object
 */
void tape_cell_list_free(struct tape_cell_list *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	while (this->head)
		tape_cell_list_delete_node(this, this->head);
	free(this);
}

void tape_cell_list_print(struct tape_cell_list *this, struct tape_cell *highlight)
{
	struct tape_cell *iter = NULL;

	if (!this) {
		erring_add(E_NULL);
		return;
	}
	S_FOR_EACH_ENTRY(this->head, iter) {
		if (iter == highlight) {
			printf("[->%u<-]", iter->token);
		} else
			tape_cell_print(iter);
	}
	printf("\n");
}
