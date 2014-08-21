#ifndef WORD_H_
#define WORD_H_

#include <stdint.h>

typedef struct word word;

/**
 * \struct word
 * \brief Represents a word
 *
 * This data structure is used to "summarize" a tuple of tokens
 *
 * \var word::letters
 * The "letters" of the word. An array of tokens
 * \var word::length
 * The length of the array
 */
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
