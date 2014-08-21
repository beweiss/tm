#ifndef TM_H_
#define TM_H_

#include <stdbool.h>
#include <stdarg.h>
#include <tm/tapes.h>
#include <tm/state_list.h>
#include <tm/constants.h>
#include <tm/word.h>

/**
 * \brief Represent the current state of a #tm
 * \var tm_cur_state::state_cur
 * Pointer to the current state (set by the compute functions)
 * \var tm_cur_state::tapes_cur
 * Pointer to the current state of the tapes and perform COW
 * if change is detected
 */
typedef struct {
	state *state_cur;
	tapes *tapes_cur;
} tm_cur_state;


/**
 * \struct tm
 * \brief Represents the Turing Machine
 *
 * Turing machine is defined as a 8-tuple \f$M = (Q, A_i, A_t, b, \delta, q_0, F_a, F_r)\f$
 * -\f$Q\f$ is a finite, non-empty set of states
 * 	+ Implementation: tm::states
 * -\f$A_i\f$ is a finite, non-empty set of the input alphabet/symbols
 * 	+ it (has to be) is a strict subset of the tape alphabet \f$A_t\f$
 * 	+ It contains _all_ symbols which are allowed as the very first initiate
 * 	  word on the first tape! (it may not contain the blank symbol!)
 * 	+ Implementation: None. This is user defined.
 * - \f$A_t\f$ is a finite, non-empty set of symbols
 * 	+ It determines all allowed symbols on the tape! (input and output)
 * 	+ It has to be a strict superset of \f$A_i\f$
 * 	  because \f$b \in A_t\f$ and \f$b \ni A_i\f$
 * 	+ Implementation: None. This is user defined.
 * - \f$b\f$ is the blank symbol
 * 	+ the only symbol allowed to occur on the tape infinitely often at
 * 	  any step during the computation
 * 	+ Implementation: Fixed Value #BLANK
 * - \f$\delta: Q \setminus (F_a \cup F_r) \times A_t \rightarrow Q \times A_t \times \{L,S,R\}\f$
 * 	+ is a partial function called the transition function
 * 	+ Implementation: #tape_actions in each #edge
 * - \f$q_0 \in Q\f$ is the initial state
 * 	+ The start of the computation
 * 	+ Implementaion: By default the first #state in tm::states
 * - \f$F_a \subseteq Q\f$ is the set of final or accepting states.
 * 	+ If one of these states is reached the computation ends successfully
 * 	  => the input word is accepted by the Turing Machine
 * 	+ Implementation: Only *one* accepting state
 * - \f$F_r \subseteq Q\f$ is the set of final or rejecting states.
 * 	+ If one of these states is reached the computation ends unsuccessfully
 * 	  => the input word is rejected by the Turing Machine
 * 	+ Implementation: Only *one* rejecting state
 *
 * \var tm::states
 * The list of states
 * \var tm::tapes
 * The tapes of the tm
 * \var tm::current
 * The current state of the tm
 */
typedef struct {
	state_list *states;
	tapes *tapes;
	//tm_states *states; instead of state_list *states
	tm_cur_state *current;
} tm;

/*
typedef struct tm_states tm_states
struct tm_states {
	bool array_list;
	union {
		states *array;
		state_list *list;
	};
};




*/

tm *tm_new(tapes *tapes);
tm *tm_new_with_states(tapes *tapes, unsigned int states_num);
void tm_add_state(tm *this);
void tm_add_state_with_default(tm *this, edge *out_default);
state *tm_find_state(tm *this, unsigned int id);
void tm_add_edge(tm *this, unsigned int src, unsigned int dest, tape_actions *actions);
void tm_add_edge_to_accept(tm *this, unsigned int src, tape_actions *actions);
void tm_add_edge_to_reject(tm *this, unsigned int src, tape_actions *actions);
tm *tm_copy(tm *this);
void tm_compute(tm *this);
void tm_compute_step(tm *this);

word *tm_gen_accepted_word(tm *this);

void tm_export_to_dot_file(tm *this, char *path);
edge *tm_find_edge(tm *this, unsigned int src, unsigned int dest, uintptr_t token);
edge *tm_find_edge_inexact(tm *this, unsigned int src, unsigned int dest);
tape *tm_select_tape(tm *this, unsigned int index);
void tm_free(tm *this);
void tm_print(tm *this);

#endif
