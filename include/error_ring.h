#ifndef ERROR_RING_H_
#define ERROR_RING_H_

#include "../include/error.h"

/**
 * \struct tm_error_ring
 * \brief Short description
 *
 * Long description
 *
 * \var tm_error_ring::head
 * Pointer to the first entry
 * \var tm_error_ring::tail
 * Pointer to element *after* last entry
 * 
 */
struct error_ring {
	struct error *head;
	struct error *tail;
	unsigned int size_max;
	struct error *data;
};

struct error_ring *error_ring_new();
void error_ring_add(struct error_ring *this, struct error *new);
void error_ring_print(struct error_ring *this);

#endif
