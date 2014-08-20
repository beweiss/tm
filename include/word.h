#ifndef WORD_H_
#define WORD_H_

#include <stdint.h>

/**
 * \typedef typedef #alphabet #word
 * \brief Represents an word
 *
 */

typedef struct word word;

struct word {
	uintptr_t *letters;
	unsigned int length;
};

word *word_new(uintptr_t *letters, unsigned int length);
void word_init(word *this, uintptr_t *letters, unsigned int length);
word *word_concat(word *this, word *obj);
void word_free(word *this);
void word_print(word *this);

#endif
