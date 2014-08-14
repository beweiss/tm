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
	edge_init(ret, id_dest, actions);
	return ret;
}

void edge_init(edge *this, unsigned int id_dest, tape_actions *actions)
{
	this->id_dest = id_dest;
	this->actions = actions;
	this->next = NULL;
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
