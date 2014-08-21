#ifndef TAPE_CELL_LIST_H_
#define TAPE_CELL_LIST_H_

#include <tm/tape_cell.h>
#include <tm/word.h>

/**
 * \struct tape_cell_list
 * \brief Represents the "List struct" of #tape_cell
 *
 * Internal representation of a tape of a Turing Machine.<br>
 * We use a doubly linked list for this because a tape in a Turing Machine<br>
 * is often changed (new tokens) and we must be able to move in any direction<br>
 * on the tape (see #SHIFT_DIR)<br>
 * Please be aware of the fact that this is a "doubly linked list" and not<br>
 * a "ring" - the prev pointer of the head is always NULL and the next pointer<br>
 * of the last element is also NULL.<br>
 * This is useful to determine "end" an "start" of the tape so we can<br>
 * automatically expand the list if the user moves to NULL.<br>
 *
 * \var tape_cell_list::head
 * Head of the list
 * \var tape_cell_list::tail
 * Tail of the list
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
