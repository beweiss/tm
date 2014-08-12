#include <stdlib.h>
#include "../include/word.h"

/**
 * \brief Create new #word object
 * \return New #word object
 */
word *word_new(unsigned int *letters, unsigned int length)
{
	/* FIXME Add error handling */
	word *ret = malloc(sizeof(*ret));

	ret->letters = letters;
	ret->length = length;
	return ret;
}

/**
 * \brief Concatenates two #word objects
 * \return New #word
 */
word *word_concat(word *this, word *obj)
{
	return NULL;
}

/**
 * \brief Free #word object
 *
 * \see #alphabet_free
 *
 */
void word_free(word *this)
{
	alphabet_free(this);
}

/**
 * \brief Print #word object to stdout
 *
 * \see #alphabet_print
 *
 */
void word_print(word *this)
{
	alphabet_print(this);
}
