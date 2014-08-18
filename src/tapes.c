#include <stdio.h>
#include <stdlib.h>
#include "../include/tapes.h"

/**
 * \brief Create new #tapes object
 * \return New #tapes object
 */
tapes *tapes_new(unsigned int length, tape *first, ...)
{
	if (length <= 0)
		return NULL;
	if (!first)
		return NULL;
	va_list arguments;
	/* FIXME Add error handling */
	tapes *ret = malloc(sizeof(tapes));
	unsigned int i = 0;

	/* FIXME Add error handling */
	ret->length = length;

	/* Initializing arguments to store all values after length */
	va_start(arguments, first);

	if (length > 1) {
		ret->data = malloc(sizeof(tape) * length);
	} else {
		ret->data = first;
		goto END;
	}

	for (i = 0; i < length; i++) {
		ret->data[i] = *va_arg(arguments, tape*);
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
	//FIXME add error handling
	tapes *ret = malloc(sizeof(*ret));
	unsigned int i = 0;
	unsigned int num = this->length;

	//FIXME add error handling
	if (num > 1) {
		ret->data = malloc(sizeof(tape) * num);
	}
	else {
		ret->data = tape_copy(&this->data[0]);
		ret->length = num;
		return ret;
	}

	ret->length = num;
	for (i = 0; i < num; i++) {
		ret->data[i] = *tape_copy(&this->data[i]);
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

	for (i = 0; i < this->length; i++) {
		if (!tape_apply_action(&this->data[i], &actions->data[i]))
			return false;
	}
	return true;
}

void tapes_apply_default_action(tapes *this, edge_default *action)
{
	unsigned int i = 0;

	for (i = 0; i < this->length; i++) {
		tape_apply_default_action(&this->data[i], action);
	}
}

/**
 * \brief Free #tapes object
 */
void tapes_free(tapes *this)
{
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
	unsigned int i = 0;

	for (i = 0; i < this->length; i++)
		tape_print(&this->data[i]);
}
