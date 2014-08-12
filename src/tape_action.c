#include <stdio.h>
#include <stdlib.h>
#include "../include/tape_action.h"

/**
 * \brief Create new #tape_action object
 * \param read tape_action::token_read
 * \param write tape_action::token_write
 * \return New #tape_action object
 */
tape_action *tape_action_new(unsigned int read, unsigned int write, SHIFT_DIR dir)
{
	//FIXME add error handling
	tape_action *ret = malloc(sizeof(*ret));

	ret->token_read = read;
	ret->token_write = write;
	ret->dir = dir;
	return ret;
}

/**
 * \brief Print #tape_action object to stdout
 */
void tape_action_print(tape_action *this)
{
	if (!this)
		return;
	printf("\t\tTOKEN_READ : %u\n\t\tTOKEN_WRITE: %u\n\t\tSHIFT      : ", this->token_read, this->token_write);
	switch (this->dir) {
		case STAT:
				printf("STATIONARY\n");
				break;
		case LEFT:
				printf("LEFT\n");
				break;
		case RIGHT:
				printf("RIGHT\n");
				break;
	}
}
