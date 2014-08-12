#ifndef TAPES_H_
#define TAPES_H_

#include <stdarg.h>
#include "tape.h"
#include "tape_actions.h"

/**
 * \struct tapes
 * \brief Represents the "Array Class" of #tape
 *
 * \var tapes::tapes
 * Array of #tape objects
 * \var tapes::length
 * Length of the array
 */
typedef struct {
	tape *tapes;
	unsigned int length;
} tapes;

tapes *tapes_new(unsigned int num, tape *first, ...);
tapes *tapes_copy(tapes *this);
bool tapes_apply_actions(tapes *this, tape_actions *actions);
void tapes_free(tapes *this);
void tapes_print(tapes *this);

#endif
