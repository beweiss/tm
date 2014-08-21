#include <stdio.h>
#include <stdlib.h>
#include <tm/tape_cell.h>
#include <tm/erring.h>

/**
 * \brief Create new #tape_cell struct
 * \param token Set token in #tape_cell
 * \return New #tape_cell struct
 */
struct tape_cell *tape_cell_new(uintptr_t token)
{
	/* FIXME Add error handling */
	struct tape_cell *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	ret->token = token;
	ret->next = NULL;
	ret->prev = NULL;

	return ret;
}

/**
 * \brief Copy #tape_cell struct
 * \return Copy of #tape_cell struct
 */
struct tape_cell *tape_cell_copy(struct tape_cell *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	return tape_cell_new(this->token);
}

/**
 * \brief Free #tape_cell struct
 */
void tape_cell_free(struct tape_cell *this)
{
	free(this);
}

/**
 * \brief Print #tape_cell struct to stdout
 */
void tape_cell_print(struct tape_cell *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	printf("[%u]", this->token);
}
