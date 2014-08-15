#ifndef TAPE_H_
#define TAPE_H_

#include <stdint.h>
#include <stdbool.h>
#include <tm/word.h>
#include <tm/tape_cell_list.h>
#include <tm/tape_actions.h>

/**
 * \struct tape
 * \brief Represents an tape of the #tm
 *
 * \var tape::priv
 * Determines the read/write privileges
 * \var tape::start
 * Determines the start of the tape
 * \var tape::pos
 * Determines the current position in the tape
 */
typedef struct {
	struct tape_cell_list *start;
	struct tape_cell *pos;
} tape;

tape *tape_new(word *input);
tape *tape_copy(tape *this);
void tape_add_token(tape *this, uintptr_t token);
void tape_shift_pos(tape *this, SHIFT_DIR shift);
uintptr_t tape_get_current_token(tape *this);
//bool tape_is_descended_from(tape *this, alphabet *alph);
void tape_clear(tape *this);
void tape_add_word(tape *this, word *input);
word *tape_get_content(tape *this);
bool tape_apply_actions(tape *this, tape_actions *actions);
void tape_free(tape *this);
void tape_print(tape *this);

#endif
