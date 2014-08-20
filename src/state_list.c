#include <stdio.h>
#include <stdlib.h>
#include "../include/singly_linked_list_macros.h"
#include "../include/state_list.h"
#include "../include/erring.h"

/**
 * \brief Create new #state_list object
 * \return New #state_list object
 */
state_list *state_list_new()
{
	//FIXME add error handling
	state_list *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	state_list_init(ret);
	return ret;
}

void state_list_init(state_list *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	this->head = NULL;
	this->size = 0;
}

/**
 * \brief Add #state to #state_list
 * \param new The new #state object which should be added
 */
void state_list_add_node(state_list *this, state *new)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (!new) {
		erring_add(E_NULL);
		return;
	}
	state *last = S_LAST_ENTRY(this->head);

	//FIXME container_of(....) to avoid condition
	if (!last) {
		new->id = 0;
		this->head = new;
	}
	else {
		new->id = last->id + 1;
		last->next = new;
	}
	this->size = this->size + 1;
}

/**
 * \brief Find #state in #state_list
 * \param id ID of the searched #state
 * \return #state object or NULL if there is no #state with this ID
 */
state *state_list_find_node(state_list *this, unsigned int id)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	state *iter = NULL;

	S_FOR_EACH_ENTRY(this->head, iter) {
		if (iter->id == id)
			return iter;
	}
	return NULL;
}

/**
 * \brief Copy #state_list object
 * \return Copy of #state_list object
 */
state_list *state_list_copy(state_list *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	state_list *ret = state_list_new();
	state *iter_state = NULL;
	state *copy = NULL;

	if (!ret) {
		erring_add(CALL_FAILED_TO(state_list_new));
		return NULL;
	}

	S_FOR_EACH_ENTRY(this->head, iter_state) {
		copy = state_copy(iter_state);
		if (!copy) {
			erring_add(CALL_FAILED_TO(state_copy));
			state_list_free(ret);
			return NULL;
		}
		state_list_add_node(ret, copy);
	}
	return ret;
}

/**
 * \brief Remove #state object from #state_list
 * \param id ID of the wanted #state
 */
void state_list_delete_node(state_list *this, unsigned int id)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	state_list_delete_node_exact(this, state_list_find_node(this, id));
}

/**
 * \brief Remove #state object from #state_list
 * \param del #state we want to delete
 *
 * \see state_list_delete_node
 *
 */
void state_list_delete_node_exact(state_list *this, state *del)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (!(this->head)) {
		return;
	}
	if (!del) {
		erring_add(E_NULL);
		return;
	}
	state *iter = container_of(&this->head, state, next);
	state *prev = iter;

	while (iter) {
		prev = iter;
		iter = iter->next;
		if (iter == del) {
			prev->next = del->next;
			state_free(del);
			this->size = this->size - 1;
			break;
		}
	}
	return;
}

/**
 * \brief Free #state_list object
 */
void state_list_free(state_list *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	while (this->head)
		state_list_delete_node_exact(this, this->head);
	free(this);
}

/**
 * \brief Print #state_list object to stdout
 */
void state_list_print(state_list *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	state *iter = NULL;

	S_FOR_EACH_ENTRY(this->head, iter) {
		state_print(iter);
	}
}
