#ifndef TAPE_CELL_H_
#define TAPE_CELL_H_

#include <stdint.h>

/**
 * \struct tape_cell
 * \brief Represents the "Node/Entry struct" of #tape_cell_list
 *
 * Internal representation of a tape cell of a tape of a Turing Machine.
 *
 * \var tape_cell::token
 * Token in tape_cell list
 * \var tape_cell::next
 * Next-Pointer
 * \var tape_cell::prev
 * Prev-Pointer
 */
struct tape_cell {
	uintptr_t token;
	struct tape_cell *next;
	struct tape_cell *prev;
};

struct tape_cell *tape_cell_new(uintptr_t token);
struct tape_cell *tape_cell_copy(struct tape_cell *this);
void tape_cell_free(struct tape_cell *this);
void tape_cell_print(struct tape_cell *this);

#endif
