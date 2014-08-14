#ifndef ALPHABET_H_
#define ALPHABET_H_

#include <stdbool.h>

/**
 * \struct alphabet
 * \brief Represents an alphabet
 * \var alphabet::letters
 * Array of unsigned ints (token == letter)
 * \var alphabet::length
 * Length of letters
 */
typedef struct {
	unsigned int *letters;
	unsigned int length;
} alphabet;

alphabet *alphabet_new(unsigned int *letters, unsigned int length);
void alphabet_init(alphabet *this, unsigned int *letters, unsigned int length);
alphabet *alphabet_copy(alphabet *this);
alphabet *alphabet_concat(alphabet *this, alphabet *obj);
alphabet *alphabet_unite(alphabet *this, alphabet *obj);
alphabet *alphabet_intersect(alphabet *this, alphabet *obj);
bool alphabet_is_subset(alphabet *this, alphabet *obj);
bool alphabet_is_superset(alphabet *this, alphabet *obj);
bool alphabet_contains(alphabet *this, unsigned int token);
void alphabet_free(alphabet *this);
void alphabet_print(alphabet *this);

#endif
