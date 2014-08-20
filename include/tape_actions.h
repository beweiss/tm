#ifndef TAPE_ACTIONS_H_
#define TAPE_ACTIONS_H_

#include <stdint.h>
#include "constants.h"

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
	uintptr_t **vec_read;
	uintptr_t **vec_write;
	SHIFT_DIR *vec_dirs;
	//length of each of the three members above == number of tapes
	unsigned int length;
} tape_actions;

tape_actions *tape_actions_new(unsigned int length, uintptr_t **vec_read, uintptr_t **vec_write, SHIFT_DIR *vec_dirs);
void tape_actions_init(tape_actions *this, unsigned int length, uintptr_t **vec_read, uintptr_t **vec_write, SHIFT_DIR *vec_dirs);
tape_actions *tape_actions_copy(tape_actions *this);
void tape_actions_free(tape_actions *this);
void tape_actions_print(tape_actions *this);

#endif

//tm_add_edge(tm *this, int src, int dest, {NULL, NULL, NULL}, {NULL, NULL, NULL}, {S, S, S});
