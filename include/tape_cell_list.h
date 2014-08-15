#ifndef TAPE_CELL_LIST_H_
#define TAPE_CELL_LIST_H_

#include <tm/tape_cell.h>
#include <tm/word.h>

/**
 * \struct tape_cell_list
 * \brief Represents the "List Class" of #tape_cell
 *
 * Internal representation of a tape of a Turing Machine.
 * We use a doubly-linked-list for this because a tape in a Turing Machine
 * is often changed (new tokens) and both directions (left/prev and right/next)
 * are allowed. So a doubly-linked-list should be perfect for this.
 * FIXME NAMING CONVENTION!!!!
 * NO RING - JUST DOUBLY LINKED LIST
 *
 * \var tape_cell_list::head
 * Head of the list
 * \var tape_cell_list::size
 * Size of the list
 */
struct tape_cell_list {
	struct tape_cell *head;
	struct tape_cell *tail;
	unsigned int size;
};

struct tape_cell_list *tape_cell_list_new();
void tape_cell_list_add_node(struct tape_cell_list *this, struct tape_cell *new);
void tape_cell_list_add_node_before(struct tape_cell_list *this, struct tape_cell *before, struct tape_cell *new);
void tape_cell_list_add_node_after(struct tape_cell_list *this, struct tape_cell *after, struct tape_cell *new);
struct tape_cell_list *tape_cell_list_copy(struct tape_cell_list *this);
void tape_cell_list_delete_node(struct tape_cell_list *this, struct tape_cell *del);
void tape_cell_list_free(struct tape_cell_list *this);
void tape_cell_list_print(struct tape_cell_list *this, struct tape_cell *highlight);

#endif
