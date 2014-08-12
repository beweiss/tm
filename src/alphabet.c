#include <stdio.h>
#include <stdlib.h>
#include "alphabet.h"

static int compare_int(const void *a, const void *b)
{
	unsigned int a_int = *((unsigned int *) a);
	unsigned int b_int = *((unsigned int *) b);

	if (a_int > b_int)
		return 1;
	if (a_int < b_int)
		return -1;
	return 0;
}

/**
 * \brief Create new #alphabet object
 *
 * letters may only contain different elements
 * So we sort the letters and check for two equal consecutive entries
 * FIXME what about the remaining space???
 *
 * \param letters The letters of the #alphabet
 * \param length The length of the #alphabet
 * \return New #alphabet object with sorted letters
 */
alphabet *alphabet_new(unsigned int *letters, unsigned int length)
{
	/* FIXME Add error handling */
	alphabet *ret = malloc(sizeof(alphabet));
	unsigned int i = 0;
	unsigned int new_length = length;
	unsigned int j = 0;

	qsort(letters, length, sizeof(int), compare_int);
	for (i = 0; i < length - 1; i++) {
		if (letters[i] == letters[i + 1])
			new_length--;
		else
			j++;
		letters[j] = letters[i + 1];
	}
	ret->letters = letters;
	ret->length = new_length;
	return ret;
}

/**
 * \brief Copy #alphabet object
 * \return Copy of #alphabet object
 */
alphabet *alphabet_copy(alphabet *this)
{
	//FIXME add error handling
	unsigned int i = 0, length = this->length;
	unsigned int *letters_new = malloc(sizeof(int) * length);

	for (i = 0; i < length; i++) {
		letters_new[i] = this->letters[i];
	}
	return alphabet_new(letters_new, length);
}

/**
 * \brief Concatenates two #alphabet objects
 *
 * \return New #alphabet
 */
alphabet *alphabet_concat(alphabet *this, alphabet *obj)
{
	return NULL;
}

/**
 * \brief Unites two #alphabet objects
 *
 * \return New #alphabet
 */
alphabet *alphabet_unite(alphabet *this, alphabet *obj)
{
	return NULL;
}

/**
 * \brief Intersects two #alphabet objects
 *
 * \return New #alphabet
 */
alphabet *alphabet_intersect(alphabet *this, alphabet *obj)
{
	return NULL;
}

/**
 * \brief Checks if alphabet is subset of another alphabet
 *
 * First check that first alphabet::length is less than or equal to second alphabet::length
 *
 * \return true if first alphabet is subset of second alphabet
 */
bool alphabet_is_subset(alphabet *this, alphabet *obj)
{
	if (!this)
		return false;
	if (!obj)
		return false;
	if (obj->length < this->length)
		return false;
	unsigned int i = 0;
	unsigned int matches = 0;

	for (i = 0; i < obj->length; i++) {
		if (this->letters[matches] == obj->letters[i]) {
			matches++;
			if (matches == this->length)
				return true;
		}
	}
	return false;
}

/**
 * \brief Checks if alphabet is superset of another alphabet
 *
 * Do not confuse this with "strict superset"!
 *
 * \return true if first alphabet is superset of second alphabet
 */
bool alphabet_is_superset(alphabet *this, alphabet *obj)
{
	return alphabet_is_subset(obj, this);
}

/**
 * \brief Checks if given #alphabet contains given token
 *
 * \return true if #alphabet contains token or false if not
 */
bool alphabet_contains(alphabet *this, unsigned int token)
{
	unsigned int i = 0;

	for (i = 0; i < this->length; i++) {
		if (this->letters[i] == token)
			return true;
	}
	return false;
}

/**
 * \brief Free #alphabet object
 */
void alphabet_free(alphabet *this)
{
	free(this);
}

/**
 * \brief Print #alphabet object to stdout
 */
void alphabet_print(alphabet *this)
{
	unsigned int i = 0;

	printf("{");
	for (i = 0; i < this->length - 1; i++)
		printf("%u, ", this->letters[i]);
	printf("%u}\n", this->letters[i]);
}
