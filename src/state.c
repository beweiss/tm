#include <stdio.h>
#include <stdlib.h>
#include "../include/state.h"

/**
 * \brief Create new #state object
 * \param out_default The ID of the default (implicit) target #state
 * \return New #state object
 */
state *state_new(edge_default *out_default)
{
	return __state_new(0, out_default, edge_list_new());
}

/**
 * \brief Create new #state object
 *
 * TODO : Function should be project private!!!
 *
 * \param out_default The ID of the default (implicit) target #state
 * \param edges Outgoing edges in #edge_list of #state
 * \return New #state object
 */
state *__state_new(unsigned int id, edge_default *out_default, edge_list *edges)
{
	//FIXME add error handling
	state *ret = malloc(sizeof(*ret));

	ret->id = id;
	ret->out_default = out_default;
	ret->edges = edges;
	ret->next = NULL;
	return ret;
}

/**
 * \brief Copy #state object
 * \return Copy of #state object
 */
state *state_copy(state *this)
{
	if (!this)
		return NULL;
	return __state_new(this->id, this->out_default, edge_list_copy(this->edges));
}

/**
 * \brief Free #state object
 */
void state_free(state *this)
{
	edge_list_free(this->edges);
	edge_default_free(this->out_default);
	free(this);
}

/**
 * \brief Print #state object to stdout
 */
void state_print(state *this)
{
	if (!this)
		return;
	printf("State:\n\tID   : %u\n\tedge_list: \n", this->id);
	edge_list_print(this->edges);
	printf("\n\tdefault edges: \n");
	edge_default_print(this->out_default);
}
