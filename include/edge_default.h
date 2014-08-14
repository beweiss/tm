#ifndef EDGE_DEFAULT_H_
#define EDGE_DEFAULT_H_

#include "constants.h"

typedef struct {
	unsigned int id_dest;
	unsigned int token_write;
	SHIFT_DIR dir;
} edge_default;

edge_default *edge_default_new(unsigned int dest, unsigned int write, SHIFT_DIR dir);
void edge_default_init(edge_default *this, unsigned int dest, unsigned int write, SHIFT_DIR dir);
void edge_default_free(edge_default *this);
void edge_default_print(edge_default *this);

#endif
