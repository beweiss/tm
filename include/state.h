#ifndef STATE_H_
#define STATE_H_

typedef struct state state;

#include <stdbool.h>
#include "edge_list.h"
#include "edge.h"
#include "constants.h"

/**
 * \struct state
 * \brief Represents an state of the #tm
 *
 * This is the "Node/Entry Object" for #state_list so here are no list functions.
 *
 * \var state::id
 * ID of the #state
 * \var state::is_accept
 * Determines if #state is accepting state or not
 * \var state::is_reject
 * Determines if #state is rejecting state or not
 * \var state::out_default
 * The ID of the implicit (default) target #state 
 * \var state::edges
 * List of outgoing edges
 * \var state::next
 * This member may only set by #state_list methods so it is always NULL in this
 * context
 */
struct state {
	unsigned int id;
	//unsigned int weight;
	edge *out_default;
	edge_list *edges;
	state *next;
};

state *state_new(edge *out_default);
state *state_new_exact(unsigned int id, edge *out_default, edge_list *edges);
void state_init(state *this, edge *out_default, edge_list *edges);
void state_init_exact(state *this, unsigned int id, edge *out_default, edge_list *edges);
state *state_copy(state *this);
void state_free(state *this);
void state_print(state *this);

#endif
