#include "alphabet.h"

/**
 * \typedef typedef #alphabet #word
 * \brief Represents an word
 *
 * #word is a typedef from #alphabet
 */
typedef alphabet word;

word *word_new(unsigned int *letters, unsigned int length);
void word_init(word *this, unsigned int *letters, unsigned int length);
word *word_concat(word *this, word *obj);
void word_free(word *this);
void word_print(word *this);
