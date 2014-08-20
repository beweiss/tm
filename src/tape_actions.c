#include <stdio.h>
#include <stdlib.h>
#include "../include/tape_actions.h"
#include "../include/erring.h"

/**
 * \brief Create new #tape_actions object
 * \param num tape_actions::num
 * \param array tape_actions::actions
 * \return New #tape_actions object
 */
tape_actions *tape_actions_new(unsigned int length, uintptr_t **vec_read, uintptr_t **vec_write, SHIFT_DIR *vec_dirs)
{
	tape_actions *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	tape_actions_init(ret, length, vec_read, vec_write, vec_dirs);
}

void tape_actions_init(tape_actions *this, unsigned int length, uintptr_t **vec_read, uintptr_t **vec_write, SHIFT_DIR *vec_dirs)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	this->length = length;
	this->vec_read = vec_read;
	this->vec_write = vec_write;
	this->vec_dirs = vec_dirs;
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
	free(this);
}

/**
 * \brief Print #tape_actions object to stdout
 */
void tape_actions_print(tape_actions *this)
{
	/*unsigned int i = 0;

	for (i = 0; i < this->length; i++) {
		tape_action_print(&this->data[i]);
	}*/
}
