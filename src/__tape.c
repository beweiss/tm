#include <stdio.h>
#include <stdlib.h>
#include "__tape.h"

/**
 * \brief Create new #__tape struct
 * \param token Set token in #__tape
 * \return New #__tape struct
 */
struct __tape *__tape_new(unsigned int token)
{
	/* FIXME Add error handling */
	struct __tape *ret = malloc(sizeof(*ret));

	ret->token = token;
	ret->next = NULL;
	ret->prev = NULL;

	return ret;
}

/**
 * \brief Copy #__tape struct
 * \return Copy of #__tape struct
 */
struct __tape *__tape_copy(struct __tape *this)
{
	return __tape_new(this->token);
}

/**
 * \brief Free #__tape struct
 */
void __tape_free(struct __tape *this)
{
	free(this);
}

/**
 * \brief Print #__tape struct to stdout
 */
void __tape_print(struct __tape *this)
{
	printf("[%u]", this->token);
}
