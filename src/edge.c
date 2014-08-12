#include <stdio.h>
#include <stdlib.h>
#include "../include/edge.h"

/**
 * \brief Create new #edge object
 * \param id_dest ID of the target #state
 * \param actions #tape_actions to perform on transition
 * \return New #edge object
 */
edge *edge_new(unsigned int id_dest, tape_actions *actions)
{
	//FIXME add error handling
	edge *ret = malloc(sizeof(*ret));

	ret->id_dest = id_dest;
	ret->actions = actions;
	ret->next = NULL;
	return ret;
}

/**
 * \brief Copy #edge object
 * \return Copy of #edge object
 */
edge *edge_copy(edge *this)
{
	return NULL;
}

/**
 * \brief Free #edge object
 */
void edge_free(edge *this)
{
	tape_actions_free(this->actions);
	free(this);
}

/**
 * \brief Print #edge object to stdout
 */
void edge_print(edge *this)
{
	printf("ID_DEST    : %u\n", this->id_dest);
	tape_actions_print(this->actions);
}
