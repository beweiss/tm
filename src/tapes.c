#include <stdio.h>
#include <stdlib.h>
#include "../include/tapes.h"
#include "../include/erring.h"

/**
 * \brief Create new #tapes object
 * \return New #tapes object
 */
tapes *tapes_new(unsigned int length, tape *first, ...)
{
	if (length <= 0) {
		erring_add("ERROR: Invalid parameter length: %u\n", length);
		return NULL;
	}
	if (!first) {
		erring_add(E_NULL);
		return NULL;
	}
	va_list arguments;
	tapes *ret = malloc(sizeof(tapes));
	unsigned int i = 0;
	tape *check = NULL;

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	ret->length = length;

	/* Initializing arguments to store all values after length */
	va_start(arguments, first);

	if (length > 1) {
		ret->data = malloc(sizeof(tape) * length);
		if (!(ret->data)) {
			erring_add(E_MALL);
			free(ret);
			va_end(arguments);
			return NULL;
		}
	} else {
		ret->data = first;
		goto END;
	}

	for (i = 0; i < length; i++) {
		check = va_arg(arguments, tape*);
		if (!check) {
			erring_add("ERROR: Tape pointer (arg_list) may not be NULL");
			if (length > 1)
				free(ret->data);
			free(ret);
			va_end(arguments);
			return NULL;
		}
		ret->data[i] = *check;
	}
END:	va_end(arguments);
	return ret;
}

/**
 * \brief Copy #tapes object
 * \return Copy of #tapes object
 */
tapes *tapes_copy(tapes *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	tapes *ret = malloc(sizeof(*ret));
	unsigned int i = 0;
	unsigned int num = this->length;
	tape *check = NULL;

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	if (num > 1) {
		ret->data = malloc(sizeof(tape) * num);
		if (!(ret->data)) {
			erring_add(E_MALL);
			free(ret);
			return NULL;
		}
	}
	else {
		ret->data = tape_copy(&this->data[0]);
		if (!(ret->data)) {
			erring_add(CALL_FAILED_TO(tape_copy));
			free(ret);
			return NULL;
		}
		ret->length = num;
		return ret;
	}

	ret->length = num;
	for (i = 0; i < num; i++) {
		check = tape_copy(&this->data[i]);
		if (!check) {
			erring_add(CALL_FAILED_TO(tape_copy));
			if (num > 1)
				free(ret->data);
			free(ret);
			return NULL;
		}
		ret->data[i] = *check;
	}
	return ret;
}

/**
 * \brief Apply #tape_actions on #tapes
 *
 * \see tape_apply_action
 *
 * \return true if _every_ action was performed correctly
 */
bool tapes_apply_actions(tapes *this, tape_actions *actions)
{
	unsigned int i = 0;

	if (!actions->vec_read)
		goto WRITE;

	for (i = 0; i < this->length; i++) {
		if (!actions->vec_read[i])
			continue;
		if (this->data[i].pos->token != actions->vec_read[i][0])
			return false;
	}

WRITE:	if (!actions->vec_write)
		goto SHIFT;

	for (i = 0; i < this->length; i++) {
		if (!actions->vec_write[i])
			continue;
		this->data[i].pos->token = actions->vec_write[i][0];
	}

SHIFT:	if (!actions->vec_dirs)
		goto END;

	for (i = 0; i < this->length; i++) {
		tape_shift_pos(&this->data[i], actions->vec_dirs[i]);
	}
END:	return true;
}

/**
 * \brief Free #tapes object
 */
void tapes_free(tapes *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	unsigned int i = 0;

	for (i = 0; i < this->length; i++)
		tape_free(&this->data[i]);
	free(this->data);
	free(this);
}

/**
 * \brief Print #tapes object to stdout
 */
void tapes_print(tapes *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	unsigned int i = 0;

	for (i = 0; i < this->length; i++)
		tape_print(&this->data[i]);
}
