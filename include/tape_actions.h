#ifndef TAPE_ACTIONS_H_
#define TAPE_ACTIONS_H_

#include <stdint.h>
#include <tm/constants.h>

/**
 * \struct tape_actions
 * \brief Contains all actions linked to a transition
 *
 * Why an Array of Pointers? Because to "establish a new level" to
 * distinguish between the value of the token and the "absence of a token".
 * see #tapes_apply_actions to see how the values are evaluated
 *
 * \var tape_actions::vec_read
 * Array of uintptr_t Pointers ("read vector")
 * \var tape_actions::vec_write
 * Array of uintptr_t Pointers ("write vector")
 * \var tape_actions::vec_dirs
 * Array of SHIFT_DIR enums ("direction vector")
 * \var tape_actions::length
 * Length of all three arrays
 */
typedef struct {
	uintptr_t **vec_read;
	uintptr_t **vec_write;
	SHIFT_DIR *vec_dirs;
	unsigned int length;
} tape_actions;

tape_actions *tape_actions_new(unsigned int length, uintptr_t **vec_read, uintptr_t **vec_write, SHIFT_DIR *vec_dirs);
void tape_actions_init(tape_actions *this, unsigned int length, uintptr_t **vec_read, uintptr_t **vec_write, SHIFT_DIR *vec_dirs);
tape_actions *tape_actions_copy(tape_actions *this);
void tape_actions_free(tape_actions *this);
void tape_actions_print(tape_actions *this);

#endif

//tm_add_edge(tm *this, int src, int dest, {NULL, NULL, NULL}, {NULL, NULL, NULL}, {S, S, S});
