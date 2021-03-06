#ifndef STATE_H_
#define STATE_H_

typedef struct state state;

#include <stdbool.h>
#include <tm/edge_list.h>
#include <tm/constants.h>

/**
 * \struct state
 * \brief Represents an state of the #tm
 *
 * This is the "Node/Entry struct" for #state_list so here are no list functions.
 *
 * \var state::id
 * ID of the #state
 * \var state::out_default
 * The default (implicit) outgoing edge with its default #tape_actions
 * \var state::edges
 * List of explicit outgoing edges
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
