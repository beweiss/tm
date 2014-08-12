#ifndef TAPE_H_
#define TAPE_H_

#include "word.h"
#include "tape_cell_list.h"
#include "tape_action.h"
#include "edge_default.h"

/**
 * \enum ACCESS
 * \brief Possible privileges for #tape
 *
 * NOTICE: READ|WRITE is also acceptable
 *
 * \var ACCESS::READ
 * If set read access to #tape is granted
 * \var ACCESS::WRITE
 * If set write access to #tape is granted
 */
typedef enum {
	READ = 1,
	WRITE = 2,
	RDWR = 3
} ACCESS;

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
	ACCESS priv;
	struct tape_cell_list *start;
	struct tape_cell *pos;
} tape;

tape *tape_new(word *input, ACCESS priv);
tape *tape_new_empty(ACCESS priv);
tape *tape_copy(tape *this);
void tape_add_token(tape *this, unsigned int token);
void tape_shift_pos(tape *this, SHIFT_DIR shift);
unsigned int tape_get_current_token(tape *this);
bool tape_is_descended_from(tape *this, alphabet *alph);
void tape_clear(tape *this);
void tape_add_word(tape *this, word *input);
word *tape_get_content(tape *this);
bool tape_apply_action(tape *this, tape_action *action);
void tape_apply_default_action(tape *this, edge_default *action);
void tape_free(tape *this);
void tape_print(tape *this);

#endif
