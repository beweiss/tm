#include <stdio.h>
#include <stdlib.h>
#include "__tape_list.h"
#include "singly_linked_list_macros.h"

/**
 * \brief Create new #__tape_list struct
 * \return New #__tape_list struct
 */
struct __tape_list *__tape_list_new()
{
	//FIXME add error handling
	struct __tape_list *ret = malloc(sizeof(*ret));

	ret->head = NULL;
	ret->last = NULL;
	ret->size = 0;
	return ret;
}

/**
 * \brief Add #__tape to #__tape_list
 * \param new The new #__tape struct which should be added
 */
void __tape_list_add_node(struct __tape_list *this, struct __tape *new)
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
 * \brief Add #__tape *before* given node
 * \param before This should be the successor of _new_
 * \param new The new #__tape struct which should be added before _before_
 */
void __tape_list_add_node_before(struct __tape_list *this, struct __tape *before, struct __tape *new)
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
 * \brief Add #__tape *after* given node
 * \param after This should be the predecessor of _new_
 * \param new The new #__tape struct which should be added after _after_
 */
void __tape_list_add_node_after(struct __tape_list *this, struct __tape *after, struct __tape *new)
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
 * \brief Remove #__tape struct from #__tape_list
 * \param del #__tape we want to delete
 */
void __tape_list_delete_node(struct __tape_list *this, struct __tape *del)
{
	if (!this)
		return;
	if (!this->head)
		return;
	if (!del)
		return;
	struct __tape *iter = container_of(&this->head, struct __tape, next);
	struct __tape *prev = iter;

	while (iter) {
		prev = iter;
		iter = iter->next;
		if (iter == del) {
			prev->next = del->next;
			__tape_free(del);
			this->size = this->size - 1;
			break;
		}
	}
	return;
}

/**
 * \brief Free #__tape_list object
 */
void __tape_list_free(struct __tape_list *this)
{
	while (this->head)
		__tape_list_delete_node(this, this->head);
	free(this);
}

void __tape_list_print(struct __tape_list *this, struct __tape *highlight)
{
	struct __tape *iter = NULL;

	S_FOR_EACH_ENTRY(this->head, iter) {
		if (iter == highlight) {
			printf("[->%u<-]", iter->token);
		} else
			__tape_print(iter);
	}
	printf("\n");
}
