#ifndef STATE_H_
#define STATE_H_

#include <stdbool.h>
#include "edge_list.h"

/*! This enum contains the possible types of states */
typedef enum {
	NORMAL = 0,/*!< Normal state */
	ACCEPT = 1,/*!< Accepting state */
	REJECT = 2 /*!< Rejecting state */
} STATE_TYPE;

typedef struct state state;

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
 * \var state::edges
 * List of outgoing edges
 * \var state::next
 * This member may only set by #state_list methods so it is always NULL in this
 * context
 */
struct state {
	unsigned int id;
	//unsigned int weight;
	STATE_TYPE type;
	//unsigned int id_default;
	edge_list *edges;
	state *next;
};

state *state_new(STATE_TYPE type);
state *__state_new(unsigned int id, STATE_TYPE type, edge_list *edges);
state *state_copy(state *this);
void state_free(state *this);
void state_print(state *this);

#endif
