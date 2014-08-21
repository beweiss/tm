#include <stdio.h>
#include <stdlib.h>
#include <tm/word.h>
#include <tm/erring.h>

/**
 * \brief Create new #word object
 * \return New #word object
 */
word *word_new(uintptr_t *letters, unsigned int length)
{
	word *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	word_init(ret, letters, length);
	return ret;
}

void word_init(word *this, uintptr_t *letters, unsigned int length)
{
	this->letters = letters;
	this->length = length;
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
	free(this);
}

/**
 * \brief Print #word object to stdout
 *
 * \see #alphabet_print
 *
 */
void word_print(word *this)
{
	unsigned int i = 0;

	printf("{");
	for (i = 0; i < this->length - 1; i++)
		printf("%p, ", this->letters[i]);
	printf("%p}\n", this->letters[i]);
}
