#include <stdio.h>
#include <stdlib.h>
#include "../include/edge_default.h"

edge_default *edge_default_new(unsigned int dest, unsigned int write, SHIFT_DIR dir)
{
	edge_default *ret = malloc(sizeof(*ret));
	edge_default_init(ret, dest, write, dir);
	return ret;
}

void edge_default_init(edge_default *this, unsigned int dest, unsigned int write, SHIFT_DIR dir)
{
	this->id_dest = dest;
	this->token_write = write;
	this->dir = dir;
}

void edge_default_free(edge_default *this)
{
	free(this);
}

void edge_default_print(edge_default *this)
{
	if (!this)
		return;
	printf("\t\tID_DEST    : %u\n\t\tTOKEN_WRITE: %u\n\t\tSHIFT      : ", this->id_dest, this->token_write);
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