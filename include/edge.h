#ifndef EDGE_H_
#define EDGE_H_

typedef struct edge edge;

#include <stdbool.h>
#include <tm/state.h>
#include <tm/tape_actions.h>

/**
 * \struct edge
 * \brief Represents an edge of the #tm
 *
 * This is the "Node/Entry struct" of #edge_list so here are no list functions.
 *
 * \var edge::target
 * Pointer to the target #state
 * \var edge::accept_reject
 * Is *only* considered if edge::target is NULL<br>
 * If true then the target is the accepting state (no actual state)<br>
 * If false then the taget is the rejecting state (no actual state)<br>
 * \var edge::actions
 * Determines the transition actions (read, write, move)
 * \var edge::next
 * This member may only set by #edge_list functions so it is always NULL in the<br>
 * context of this struct
 */
struct edge {
	state *target;
	bool accept_reject;
	tape_actions *actions;
	edge *next;
};

edge *edge_new(state *target, tape_actions *actions);
edge *edge_new_accept_reject(bool accept_reject, tape_actions *actions);
int edge_init(edge *this, state *target, tape_actions *actions);
void edge_init_accept_reject(edge *this, bool accept_reject, tape_actions *actions);
edge *edge_copy(edge *this);
void edge_free(edge *this);
void edge_print(edge *this);

#endif
