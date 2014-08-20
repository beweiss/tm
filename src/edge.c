#include <stdio.h>
#include <stdlib.h>
#include "../include/edge.h"
#include "../include/erring.h"

static void __edge_init(edge *this, state *target, bool accept_reject, tape_actions *actions);

/**
 * \brief Create new #edge object
 * \param id_dest ID of the target #state
 * \param actions #tape_actions to perform on transition
 * \return New #edge object
 */
edge *edge_new(state *target, tape_actions *actions)
{
	edge *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	if (edge_init(ret, target, actions) == -1) {
		erring_add(E_NULL ": target may not be NULL if target state is NORMAL");
		free(ret);
		return NULL;
	}
	return ret;
}

edge *edge_new_accept_reject(bool accept_reject, tape_actions *actions)
{
	edge *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	edge_init_accept_reject(ret, accept_reject, actions);
	return ret;
}

int edge_init(edge *this, state *target, tape_actions *actions)
{
	if (!this) {
		erring_add(E_NULL);
		return -1;
	}
	if (!target) {
		erring_add(E_NULL ": target may not be NULL if target state is NORMAL");
		return -1;
	}
	__edge_init(this, target, 0, actions);
	return 0;
}

void edge_init_accept_reject(edge *this, bool accept_reject, tape_actions *actions)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	__edge_init(this, NULL, accept_reject, actions);
}

static void __edge_init(edge *this, state *target, bool accept_reject, tape_actions *actions)
{
	this->target = target;
	this->accept_reject = accept_reject;
	this->actions = actions;
	this->next = NULL;
}

/**
 * \brief Copy #edge object
 * \return Copy of #edge object
 */
edge *edge_copy(edge *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	/*
	edge *ret = malloc(sizeof(*ret));

	edge_init(state_copy(target), tape_actions_copy(this->actions), this->accept_reject);
	*/
	return NULL;
}

/**
 * \brief Free #edge object
 */
void edge_free(edge *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	tape_actions_free(this->actions);
	free(this);
}

/**
 * \brief Print #edge object to stdout
 */
void edge_print(edge *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (this->target)
		printf("ID_DEST    : %u\n", this->target->id);
	else {
		if (this->accept_reject)
			printf("ID_DEST    : ACCEPT\n");
		else
			printf("ID_DEST    : REJECT\n");
	}
	tape_actions_print(this->actions);
}
