#ifndef TAPE_ACTIONS_H_
#define TAPE_ACTIONS_H_

#include "tape_action.h"

/**
 * \struct tape_actions
 * \brief "Array Class" of #tape_action
 *
 * \var tape_actions::actions
 * Array of #tape_action objects
 * \var tape_actions::length
 * Length of the array
 */
typedef struct {
	tape_action *actions;
	unsigned int length;
} tape_actions;

tape_actions *tape_actions_new(unsigned int length, tape_action *array);
tape_actions *tape_actions_copy(tape_actions *this);
void tape_actions_free(tape_actions *this);
void tape_actions_print(tape_actions *this);

#endif
