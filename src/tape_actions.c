#include <stdio.h>
#include <stdlib.h>
#include <tm/tape_actions.h>
#include <tm/erring.h>

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
	if (!this) {
		return;
	}
	unsigned int i = 0;

	printf("\t\t\tTape actions: \n\t\t\t");
	for (i = 0; i < this->length; i++) {
		if (!(this->vec_read[i]))
			printf("ANY, ");
		else
			printf("%u, ", this->vec_read[i][0]);
		if (!(this->vec_write[i]))
			printf("NOTHING, ");
		else
			printf("%u, ", this->vec_write[i][0]);
		switch (this->vec_dirs[i]) {
			case LEFT:
				printf("LEFT, ");
				break;
			case RIGHT:
				printf("RIGHT, ");
				break;
			case STAT:
				printf("STAT, ");
				break;
			default:
				erring_add("WARNING: Wrong value for direction!");
				break;
		}
	}
	printf("\n");
}
