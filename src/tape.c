#include <stdio.h>
#include <stdlib.h>
#include "tape.h"
#include "constants.h"
#include "singly_linked_list_macros.h"

/**
 * \brief Create new #tape object
 * \param input Input #word
 * \param priv #ACCESS privileges
 * \return New #tape object
 */
tape *tape_new(word *input, ACCESS priv)
{
	/* FIXME Add error handling */
	tape *ret = malloc(sizeof(*ret));
	unsigned int i = 0;

	ret->priv = priv;

	/* FIXME Add error handling */
	ret->start = __tape_list_new();

	if (!input) {
EMPTY:		__tape_list_add_node(ret->start, __tape_new(BLANK));
		ret->pos = ret->start->head;
		return ret;
	}
	if (input->length == 0)
		goto EMPTY;
	for (i = 0; i < input->length; i++)
		__tape_list_add_node(ret->start, __tape_new(input->letters[i]));

	ret->pos = ret->start->head;
	return ret;
}

/**
 * \brief Create new #tape object without input #word
 *
 * \see tape_new
 *
 * \return New #tape object
 */
tape *tape_new_empty(ACCESS priv)
{
	return tape_new(NULL, priv);
}

//FIXME CONSIDER: pos == start (new tm == new status of computation? or not???!!!)
/**
 * \brief Copy #tape object
 * \return Copy of #tape object
 */
tape *tape_copy(tape *this)
{
	return NULL;
}

/**
 * \brief Add token to #tape
 * \param token Token which should be added
 */
void tape_add_token(tape *this, unsigned int token)
{
	__tape_list_add_node(this->start, __tape_new(token));
}

/**
 * \brief Shift position pointer on tape
 * \param shift #SHIFT_DIR determines shift direction
 *
 * + If there is no left or right token on the tape (list end) the list will
 * automatically enlarged
 * - Left Shift and list ends then add BLANK before tape::pos
 * - Right Shift and list ends then add BLANK after tape::pos
 *
 */
void tape_shift_pos(tape *this, SHIFT_DIR shift)
{
	if (shift == LEFT) {
		if (!this->pos->prev) {
			__tape_list_add_node_before(this->start, this->pos, __tape_new(BLANK));
		}
		this->pos = this->pos->prev;
	}
	if (shift == RIGHT) {
		if (!this->pos->next) {
			__tape_list_add_node_after(this->start, this->pos, __tape_new(BLANK));
		}
		this->pos = this->pos->next;
	}
}

/**
 * \brief Get the current token - token on tape::pos
 * \return tape::pos::token
 */
unsigned int tape_get_current_token(tape *this)
{
	return this->pos->token;
}

/**
 * \brief Checks if every token on tape comes from given alphabet
 * \param alph Alphabet which should be the "source" of the tokens on tape
 * \return true if every token on tape is descended from given alphabet
 */
bool tape_is_descended_from(tape *this, alphabet *alph)
{
	struct __tape *iter = NULL;

	if (!this)
		return false;
	if (!alph)
		return false;
	S_FOR_EACH_ENTRY(this->start->head, iter) {
		if (!alphabet_contains(alph, iter->token))
			return false;
	}
	return true;
}

/**
 * \brief Clear tape
 */
void tape_clear(tape *this)
{

}

/**
 * \brief Add word to tape
 * \param input The word we want to add
 */
void tape_add_word(tape *this, word *input)
{
	unsigned int i = 0;

	for (i = 0; i < input->length; i++) {
		tape_add_token(this, input->letters[i]);
	}
}

/**
 * \brief Get content of the tape in an #word object
 * \return #word object with content of tape
 */
word *tape_get_content(tape *this)
{
	unsigned int size = this->start->size;
	unsigned int *letters = malloc(size * sizeof(int));
	unsigned int i = 0;
	struct __tape *iter = this->start->head;

	for (i = 0; i < size; i++) {
		letters[i] = iter->token;
		iter = iter->next;
	}
	return word_new(letters, size);
}

/**
 * \brief Apply #tape_action on #tape
 *
 * The current actions will be performed:
 * 1. check if tape_action::token_read is on current position (tape::pos)
 * 2. if 1. is true then write tape_action::token_write to current position (tape::pos)
 * 3. move tape::pos on #tape in tape_action::dir
 *
 * \return true if 1. was true
 */
bool tape_apply_action(tape *this, tape_action *action)
{
	//FIXME privileges!!!!!!
	if (this->pos->token != action->token_read)
			return false;
	this->pos->token = action->token_write;
	tape_shift_pos(this, action->dir);
	return true;
}

/**
 * \brief Free #tape object
 */
void tape_free(tape *this)
{
	__tape_list_free(this->start);
}

/**
 * \brief Print #state object to stdout
 */
void tape_print(tape *this)
{
	//FIXME add error handling
	if (!this)
		return;
	printf("Tape:\n\tPRIV: ");
	switch (this->priv) {
		case READ:
				printf("READ\n");
				break;
		case WRITE:
				printf("WRITE\n");
				break;
		case RDWR:
				printf("READ|WRITE\n");
				break;
	}
	printf("\t");
	__tape_list_print(this->start, this->pos);
}
