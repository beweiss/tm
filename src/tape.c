#include <stdio.h>
#include <stdlib.h>
#include <tm/tape.h>
#include <tm/constants.h>
#include <tm/singly_linked_list_macros.h>
#include <tm/erring.h>

/**
 * \brief Create new #tape object
 * \param input Input #word
 * \return New #tape object
 */
tape *tape_new(word *input)
{
	/* FIXME Add error handling */
	tape *ret = malloc(sizeof(*ret));
	unsigned int i = 0;

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	ret->start = tape_cell_list_new();

	if (!(ret->start)) {
		erring_add(CALL_FAILED_TO(tape_cell_list_new));
		return NULL;
	}

	if (!input) {
EMPTY:		tape_cell_list_add_node(ret->start, tape_cell_new(BLANK));
		ret->pos = ret->start->head;
		return ret;
	}
	if (input->length == 0)
		goto EMPTY;
	for (i = 0; i < input->length; i++)
		tape_cell_list_add_node(ret->start, tape_cell_new(input->letters[i]));

	ret->pos = ret->start->head;
	return ret;
}

//FIXME CONSIDER: pos == start (new tm == new status of computation? or not???!!!)
/**
 * \brief Copy #tape object
 * \return Copy of #tape object
 */
tape *tape_copy(tape *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	tape *ret = malloc(sizeof(*ret));
	struct tape_cell *iter_old = this->start->head;
	struct tape_cell *iter_new = NULL;

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	ret->start = tape_cell_list_copy(this->start);

	if (!(ret->start)) {
		erring_add(CALL_FAILED_TO(tape_cell_list_copy));
		free(ret);
		return NULL;
	}

	iter_new = ret->start->head;

	while (iter_old) {
		if (iter_old == this->pos) {
			ret->pos = iter_new;
			break;
		}
		iter_new = iter_new->next;
		iter_old = iter_old->next;
	}
	return ret;
}

/**
 * \brief Add token to #tape
 * \param token Token which should be added
 */
void tape_add_token(tape *this, uintptr_t token)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	tape_cell_list_add_node(this->start, tape_cell_new(token));
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
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (shift == LEFT) {
		if (!this->pos->prev) {
			tape_cell_list_add_node_before(this->start, this->pos, tape_cell_new(BLANK));
		}
		this->pos = this->pos->prev;
	}
	if (shift == RIGHT) {
		if (!this->pos->next) {
			tape_cell_list_add_node_after(this->start, this->pos, tape_cell_new(BLANK));
		}
		this->pos = this->pos->next;
	}
}

/**
 * \brief Get the current token - token on tape::pos
 * \return tape::pos::token
 */
uintptr_t tape_get_current_token(tape *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	return this->pos->token;
}

/**
 * \brief Checks if every token on tape comes from given alphabet
 * \param alph Alphabet which should be the "source" of the tokens on tape
 * \return true if every token on tape is descended from given alphabet
 */
/*bool tape_is_descended_from(tape *this, alphabet *alph)
{
	struct tape_cell *iter = NULL;

	if (!this)
		return false;
	if (!alph)
		return false;
	S_FOR_EACH_ENTRY(this->start->head, iter) {
		if (!alphabet_contains(alph, iter->token))
			return false;
	}
	return true;
}*/

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
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (!input) {
		erring_add(E_NULL);
		return;
	}
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
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	unsigned int size = this->start->size;
	uintptr_t *letters = malloc(size * sizeof(uintptr_t));
	unsigned int i = 0;
	struct tape_cell *iter = this->start->head;

	if (!letters) {
		erring_add(E_MALL);
		return NULL;
	}
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
bool tape_apply_actions(tape *this, tape_actions *actions)
{
	//TODO IMPLEMENT
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	return false;
}

/**
 * \brief Free #tape object
 */
void tape_free(tape *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	tape_cell_list_free(this->start);
}

/**
 * \brief Print #tape object to stdout
 */
void tape_print(tape *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	printf("Tape:\n\t");
	tape_cell_list_print(this->start, this->pos);
}
