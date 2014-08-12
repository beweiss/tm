#ifndef TM_H_
#define TM_H_

#include <stdbool.h>
#include <stdarg.h>
#include "tapes.h"
#include "state_list.h"

//FIXME also mention the "More than one tape"-story in this documentation...
/*TODO IMPLEMENT:

		void tape_apply_action(tape *this, tape_action *action);
 FIXME current dummy edges....to reject
*/

/**
 * \struct tm
 * \brief Represents the Turing Machine
 *
 * Turing machine is defined as a 8-tuple \f$M = (Q, A_i, A_t, b, \delta, q_0, F_a, F_r)\f$
 * -\f$Q\f$ is a finite, non-empty set of states (tm::states)
 * -\f$A_i\f$ (Alphabet Input) is a finite, non-empty set of the input alphabet/symbols
 * 	+ it (has to be) is a strict subset of the tape alphabet \f$A_t\f$
 * 	+ It contains _all_ symbols which are allowed as the very first initiate
 * 	word on the first tape! (it may not contain the blank symbol!)
 * 	+ tm::alph_input
 * - \f$At\f$ (Alphabet Tape) is a finite, non-empty set of symbols
 * 	+ It determines all allowed symbols on the tape! (input and output)
 * 	+ It has to be a strict superset of \f$A_i\f$
 * 	+ tm::alph_tape
 * - \f$b\f$ is the blank symbol (the only symbol allowed to occur on the tape
 * 	+ infinitely often at any step during the computation)
 * 	+ #BLANK
 * - \f$\delta: Q \setminus (F_a \cup F_r) \times A_t \rightarrow Q \times A_t \times \{L,S,R\}\f$
 * 	+ is a partial function called the transition function
 * - \f$q_0 \in Q\f$ is the initial state
 * 	+ Always first #state in tm::states
 * - \f$F_a \subseteq Q\f$ is the set of final or accepting states.
 * 	+ Coded in state::type
 * - \f$F_r \subseteq Q\f$ is the set of final or rejecting states.
 *	+ Coded in state::type
 *
 * \var tm::states
 * The list of states
 * \var tm::tapes
 * An array of #tape objects
 * \var tm::alph_input
 * Is the "Input Alphabet" of the Turing Machine
 * \var tm::alph_tape
 * Is the "Tape Alphabet" of the Turing Machine
 */
typedef struct {
	state_list *states;
	tapes *tapes;
	alphabet *alph_input;
	alphabet *alph_tape;
	//state *current;
	//TODO Later.....
	//bool is_det;
} tm;

tm *tm_new(tapes *tapes, alphabet *alph_input, alphabet *alph_tape);
void tm_add_state(tm *this, STATE_TYPE type);
void tm_remove_state(tm *this, unsigned int id);
state *tm_find_state(tm *this, unsigned int id);
//FIXME maybe no variable arg list and ONE tape_actions
edge *tm_add_edge(tm *this, unsigned int src, unsigned int dest, tape_action *action1, ...);
bool tm_is_reachable(tm *this, unsigned int id);
tm *tm_copy(tm *this);
state *tm_compute(tm *this);

//check circles!!!!!
word *tm_gen_accepted_word(tm *this);

void tm_clear_tape(tm *this, tape *obj);
void tm_write_word_to_tape(tm *this, word *input);
void tm_export_to_dot_file(tm *this, char *path);
edge *tm_find_edge(tm *this, unsigned int src, unsigned int dest, unsigned int token);
edge *tm_find_edge_inexact(tm *this, unsigned int src, unsigned int dest);
tape *tm_select_tape(tm *this, unsigned int index);
void tm_free(tm *this);
void tm_print(tm *this);

#endif