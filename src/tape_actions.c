#include <stdio.h>
#include <stdlib.h>
#include "../include/tape_actions.h"

/**
 * \brief Create new #tape_actions object
 * \param num tape_actions::num
 * \param array tape_actions::actions
 * \return New #tape_actions object
 */
tape_actions *tape_actions_new(unsigned int length, tape_action *data)
{
	/* FIXME Add error handling */
	tape_actions *ret = malloc(sizeof(*ret));

	ret->length = length;
	ret->data = data;
	return ret;
}

/**
 * \brief Copy #tape_actions object
 * \return Copy of #tape_actions object
 */
tape_actions *tape_actions_copy(tape_actions *this)
{
	return NULL;
}

/**
 * \brief Free #tape_actions object
 */
void tape_actions_free(tape_actions *this)
{
	free(this->data);
	free(this);
}

/**
 * \brief Print #tape_actions object to stdout
 */
void tape_actions_print(tape_actions *this)
{
	unsigned int i = 0;

	for (i = 0; i < this->length; i++) {
		tape_action_print(&this->data[i]);
	}
}
