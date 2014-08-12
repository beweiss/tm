#include "__tape.h"

/**
 * \struct __tape_list
 * \brief Represents the "List Class" of #__tape
 *
 * Internal representation of a tape of a Turing Machine.
 * We use a doubly-linked-list for this because a tape in a Turing Machine
 * is often changed (new tokens) and both directions (left/prev and right/next)
 * are allowed. So a doubly-linked-list should be perfect for this.
 * FIXME NAMING CONVENTION!!!!
 * NO RING - JUST DOUBLY LINKED LIST
 *
 * \var __tape_list::head
 * Head of the list
 * \var __tape_list::size
 * Size of the list
 */
struct __tape_list {
	struct __tape *head;
	struct __tape *last;
	unsigned int size;
};

struct __tape_list *__tape_list_new();
void __tape_list_add_node(struct __tape_list *this, struct __tape *new);
void __tape_list_add_node_before(struct __tape_list *this, struct __tape *before, struct __tape *new);
void __tape_list_add_node_after(struct __tape_list *this, struct __tape *after, struct __tape *new);
void __tape_list_delete_node(struct __tape_list *this, struct __tape *del);
void __tape_list_free(struct __tape_list *this);
void __tape_list_print(struct __tape_list *this, struct __tape *highlight);
