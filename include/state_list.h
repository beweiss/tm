#ifndef STATE_LIST_H_
#define STATE_LIST_H_

#include <tm/state.h>

/**
 * \struct state_list
 * \brief Represents an list of states (#state) of the #tm
 *
 * This is the "List Class" of #state so here are only list functions.
 *
 * \var state_list::head
 * Head of the list
 * \var state_list::size
 * Size of the list
 */
typedef struct {
	state *head;
	unsigned int size;
} state_list;

state_list *state_list_new();
void state_list_init(state_list *this);
void state_list_add_node(state_list *this, state *new);
state *state_list_find_node(state_list *this, unsigned int id);
state_list *state_list_copy(state_list *this);
void state_list_delete_node(state_list *this, unsigned int id);
void state_list_delete_node_exact(state_list *this, state *del);
void state_list_free(state_list *this);
void state_list_print(state_list *this);

#endif
