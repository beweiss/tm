#ifndef EDGE_H_
#define EDGE_H_

#include "tape_actions.h"

typedef struct edge edge;

/**
 * \struct edge
 * \brief Represents an edge of the #tm
 *
 * This is the "Node/Entry - Class" of #edge_list so here are no list functions.
 *
 * \var edge::id_dest
 * ID of the target #state
 * \var edge::actions
 * "Array Object" of #tape_action and contains #::tm::tapes::length objects!
 * One #tape_action per every #tape!
 * \var edge::next
 * This member may only set by #edge_list methods so it is always NULL in the
 * context of this class
 */
struct edge {
	unsigned int id_dest;
	tape_actions *actions;
	edge *next;
};

edge *edge_new(unsigned int id_dest, tape_actions *actions);
void edge_init(edge *this, unsigned int id_dest, tape_actions *actions);
edge *edge_copy(edge *this);
void edge_free(edge *this);
void edge_print(edge *this);

#endif