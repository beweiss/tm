#include <stdio.h>
#include <stdlib.h>
#include <tm/state.h>
#include <tm/erring.h>

/**
 * \brief Create new #state object
 * \param out_default The ID of the default (implicit) target #state
 * \return New #state object
 */
state *state_new(edge *out_default)
{
	state *ret = state_new_exact(0, out_default, edge_list_new());

	if (!ret) {
		erring_add(CALL_FAILED_TO(state_new_exact));
		return NULL;
	}
	return ret;
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
state *state_new_exact(unsigned int id, edge *out_default, edge_list *edges)
{
	//FIXME add error handling
	state *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	state_init_exact(ret, id, out_default, edges);
	return ret;
}

void state_init(state *this, edge *out_default, edge_list *edges)
{
	state_init_exact(this, 0, out_default, edges);
}

void state_init_exact(state *this, unsigned int id, edge *out_default, edge_list *edges)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	this->id = id;
	this->out_default = out_default;
	this->edges = edges;
	this->next = NULL;
}

/**
 * \brief Copy #state object
 * \return Copy of #state object
 */
state *state_copy(state *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	state *ret = state_new_exact(this->id, this->out_default, edge_list_copy(this->edges));

	if (!ret) {
		erring_add(CALL_FAILED_TO(state_new_exact));
		return NULL;
	}
	return ret;
}

/**
 * \brief Free #state object
 */
void state_free(state *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	edge_list_free(this->edges);
	edge_free(this->out_default);
	free(this);
}

/**
 * \brief Print #state object to stdout
 */
void state_print(state *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	printf("State:\n\tID   : %u\n\tedge_list: \n", this->id);
	edge_list_print(this->edges);
	printf("\n\tdefault edges: \n");
	edge_print(this->out_default);
}
