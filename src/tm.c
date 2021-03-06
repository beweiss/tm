#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <tm/singly_linked_list_macros.h>
#include <tm/constants.h>
#include <tm/tm.h>
#include <tm/erring.h>

static inline void __tm_compute_step(tm *this);

/**
 * \brief Create new #tm object
 *
 * - Make the following checks:
 * 	+ is argument tapes not NULL
 * 	+ is argument alph_input not NULL and subset of alph_tape<br>
 * 	  and may not contain BLANK
 * 	+ is argument alph_tape not NULL and contains BLANK
 * 	+ is every character on the input tape (very first tape) in the input<br>
 * 	  alphabet
 *
 * \param tapes tm::tapes
 * \param alph_input tm::alph_input
 * \param alph_tape tm::alph_tape
 * \return New #tm object
 */
tm *tm_new(tapes *tapes)
{
	if (!tapes) {
		erring_add(E_NULL);
		return NULL;
	}
	tm *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	ret->tapes = tapes;
	ret->states = state_list_new();

	if (!(ret->states)) {
		erring_add(CALL_FAILED_TO(state_list_new));
		free(ret);
		return NULL;
	}
	return ret;
}

tm *tm_new_with_states(tapes *tapes, unsigned int states_num)
{
	tm *ret = tm_new(tapes);
	unsigned int i = 0;

	if (!ret) {
		erring_add(CALL_FAILED_TO(tm_new));
		return NULL;
	}
	for (i = 0; i < states_num; i++) {
		tm_add_state(ret);
	}
	return ret;
}

void tm_add_state(tm *this)
{
	state *new = NULL;

	if (!this) {
		erring_add(E_NULL);
		return;
	}
	new = state_new(NULL);

	if (!new) {
		erring_add(CALL_FAILED_TO(state_new));
		return;
	}
	state_list_add_node(this->states, new);
}

/**
 * \brief Add new state to tm
 *
 * - Make the following checks
 * 	+ first state have to be a NORMAL state
 * 	+ only ONE accepting state and only ONE rejecting state
 * 	+ if type == REJECT or type == ACCEPT out_default has to be NULL<br>
 * 	  because these states may not have any outgoing edges
 *
 * \param type Type of the new state
 * \param out_default The ID of the default (implicit) target #state
 */
void tm_add_state_with_default(tm *this, edge *out_default)
{
	state *new = NULL;

	if (!this) {
		erring_add(E_NULL);
		return;
	}
	new = state_new(out_default);

	if (!new) {
		erring_add(CALL_FAILED_TO(state_new));
		return;
	}
	state_list_add_node(this->states, new);
}

/**
 * \brief Find state in tm
 * \param id ID of the wanted #state
 */
state *tm_find_state(tm *this, unsigned int id)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	return state_list_find_node(this->states, id);
}

/**
 * \brief Add edge to tm
 *
 * - Make the following checks
 * 	+ are the IDs valid
 * 	+ if src is accepting or rejecting state then do nothing
 * 	+ if there is already an edge from src to dest?
 * 	+ if one #tape_action object is NULL do nothing and return
 * 	+ check if every token in action1 , ... is in tm::alph_tape
 *
 * \param src ID of the source #state
 * \param dest ID of the destination #state
 * \param action1 First #tape_action object
 * \param ... tm::tapes::length - 1 #tape_action objects will follow
 */
void tm_add_edge(tm *this, unsigned int src, unsigned int dest, tape_actions *actions)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	state *state_src = tm_find_state(this, src);
	state *state_dest = tm_find_state(this, dest);
	edge *new_edge = NULL;

	if (!state_src) {
		erring_add("ERROR: src Node does not exist in tm");
		return;
	}
	if (!state_dest) {
		erring_add("ERROR: dest Node does not exist in tm");
		return;
	}
	if (!actions) {
		erring_add(E_NULL);
		return;
	}
	if (actions->length != this->tapes->length) {
		erring_add("ERROR: Length of tapes equals not length of actions");
		return;
	}

	new_edge = edge_new(state_dest, actions);

	if (!new_edge) {
		erring_add(CALL_FAILED_TO(edge_new));
		return;
	}
	edge_list_add_node(state_src->edges, new_edge);
}

void tm_add_edge_to_accept(tm *this, unsigned int src, tape_actions *actions)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (actions->length != this->tapes->length) {
		erring_add("ERROR: Length of tapes equals not length of actions");
		return;
	}
	state *state_src = tm_find_state(this, src);
	edge *def = NULL;

	if (!state_src) {
		erring_add("ERROR: src Node does not exist in tm");
		return;
	}
	def = edge_new_accept_reject(true, actions);

	edge_list_add_node(state_src->edges, def);
}

void tm_add_edge_to_reject(tm *this, unsigned int src, tape_actions *actions)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	if (actions->length != this->tapes->length) {
		erring_add("ERROR: Length of tapes equals not length of actions");
		return;
	}
	state *state_src = tm_find_state(this, src);
	edge *def = NULL;

	if (!state_src) {
		erring_add("ERROR: src Node does not exist in tm");
		return;
	}
	def = edge_new_accept_reject(false, actions);

	edge_list_add_node(state_src->edges, def);
}

static inline void __tm_compute_step(tm *this)
{
	//TODO IMPLEMENT!
	/*if (!current)
		return NULL;
	edge *iter = NULL;
	state *implicit = NULL;

	tape_print(&this->tapes->data[0]);

	//search for explicit edge
	S_FOR_EACH_ENTRY(current->edges->head, iter) {
		//currently only one token per outgoing edge is allowed (determinism)
		if (tapes_apply_actions(this->tapes, iter->actions)) {
			return __tm_compute(this, tm_find_state(this, iter->id_dest));
		}
	}
	//if there was no explicit edge we use the implicit edge
	implicit = tm_find_state(this, current->out_default->id_dest);
	
	if (implicit) {
		tapes_apply_default_action(this->tapes, current->out_default);
		return __tm_compute(this, implicit);
	}
	return NULL;*/
}

void tm_compute_step(tm *this)
{
	__tm_compute_step(this);
}

/**
 * \brief Start the computation of the Turing Machine
 *
 * There have to be at least one state and there have to be
 * 1 accepting state or 1 rejecting state.
 *
 * \return The last #state we reached
 */
void tm_compute(tm *this)
{
	//TODO IMPLEMENT!
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	//call __tm_compute_step in a loop
}

/**
 * \brief Generate accepted word
 * \return #word object
 */
word *tm_gen_accepted_word(tm *this)
{
	//TODO IMPLEMENT!
	/*if (!this)
		return NULL;
	return NULL;*/
}

/**
 * \brief Copy #tm object
 * \return Copy of #tm object
 */
tm *tm_copy(tm *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	tm *ret = malloc(sizeof(*ret));

	if (!ret) {
		erring_add(E_MALL);
		return NULL;
	}
	ret->states = state_list_copy(this->states);
	if (!(ret->states)) {
		erring_add(CALL_FAILED_TO(state_list_copy));
		return NULL;
	}

	ret->tapes = tapes_copy(this->tapes);
	if (!(ret->tapes)) {
		erring_add(CALL_FAILED_TO(tapes_copy));
		return NULL;
	}
	return ret;
}

/**
 * \brief Export #tm object to .dot-File
 * \param path Path of the outputted .dot-File
 */
void tm_export_to_dot_file(tm *this, char *path)
{
	/*if (!this)
		return;
	if (!path)
		return;
	char *dot1 = 	"digraph turing_machine {\n\trankdir=LR\n\t"
			"size=\"50\"\n\n\tnode [shape = point] qi\n\t";
	char *dot2 = 	"node [shape = doublecircle, color=red] ";
	char *total = malloc(100000);
	char *id = malloc(10);
	edge *edge_iter = NULL;
	unsigned int i = 0;
	int fd = 0;

	state *iter = NULL;

	total[0] = 0;

	strncat(total, dot1, strlen(dot1));

	if (this->states->head) {
		strncat(total, dot2, strlen(dot2));
	}

	S_FOR_EACH_ENTRY(this->states->head, iter) {
		if (iter == this->reject) {
			strncat(total, "q", 1);
			sprintf(id, "%u", iter->id);
			strncat(total, id, strlen(id));
			strncat(total, " ", 1);
		}
	}
	strncat(total, "\n\tnode [shape = doublecircle, color=green] ", strlen("\n\tnode [shape = doublecircle, color=green] "));
	S_FOR_EACH_ENTRY(this->states->head, iter) {
		if (iter == this->accept) {
			strncat(total, "q", 1);
			sprintf(id, "%u", iter->id);
			strncat(total, id, strlen(id));
			strncat(total, " ", 1);
		}
	}
	strncat(total, "\n\tnode [shape = circle, color=black]\n\tqi -> q0\n", strlen("\n\tqi -> q0\n\tnode [shape = circle, color=black]\n\tqi -> q0\n"));

	S_FOR_EACH_ENTRY(this->states->head, iter) {
		if (iter->out_default) {
			strncat(total, "\tq", 2);
			sprintf(id, "%u", iter->id);
			strncat(total, id, strlen(id));
			strncat(total, " -> q", 5);

			sprintf(id, "%u", iter->out_default->id_dest);
			strncat(total, id, strlen(id));

			strncat(total, "[label = \"*;", strlen("[label = \"*;"));
			sprintf(id, "%u", iter->out_default->token_write);
			strncat(total, id, strlen(id));
			strncat(total, ",", 1);
			switch (iter->out_default->dir) {
			case STAT:
				strncat(total, "S", strlen("S"));
				break;
			case LEFT:
				strncat(total, "L", strlen("L"));
				break;
			case RIGHT:
				strncat(total, "R", strlen("R"));
				break;
			}
			strncat(total, "\"]\n", strlen("\"]\n"));
		}
		S_FOR_EACH_ENTRY(iter->edges->head, edge_iter) {
				strncat(total, "\tq", 2);
				sprintf(id, "%u", iter->id);
				strncat(total, id, strlen(id));
				strncat(total, " -> q", 5);

				sprintf(id, "%u", edge_iter->id_dest);
				strncat(total, id, strlen(id));

				strncat(total, "[label = \"", strlen("[label = \""));
			for (i = 0; i < edge_iter->actions->length; i++) {
				sprintf(id, "%u", edge_iter->actions->data[i].token_read);
				strncat(total, id, strlen(id));
				strncat(total, ";", 1);
				sprintf(id, "%u", edge_iter->actions->data[i].token_write);
				strncat(total, id, strlen(id));
				strncat(total, ",", 1);
				switch (edge_iter->actions->data[i].dir) {
					case STAT:
							strncat(total, "S", strlen("S"));
							break;
					case LEFT:
							strncat(total, "L", strlen("L"));
							break;
					case RIGHT:
							strncat(total, "R", strlen("R"));
							break;
				}
				if (i < edge_iter->actions->length - 1)
					strncat(total, "/", 1);
			}
			strncat(total, "\"]\n", strlen("\"]\n"));
		}
	}
	strncat(total, "}\n", 2);

	fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);

	write(fd, total, strlen(total));

	fsync(fd);
	close(fd);
	free(id);
	free(total);*/
}

/**
 * \brief Find specific #edge in #tm
 * \param src ID of the source #state
 * \param dest ID of the destination #state
 * \param token Token of the wanted edge
 * \return The specific #edge object or NULL if it was not found
 */
edge *tm_find_edge(tm *this, unsigned int src, unsigned int dest, uintptr_t token)
{
	//FIXME maybe bullshit
	/*if (!this)
		return NULL;
	return NULL;*/
}

/**
 * \brief Find #edge in #tm
 *
 * Unlike tm_find_edge this function only checks if there is an edge between src and dest
 * There may be more than one edges with different tokens.
 *
 * \param src ID of the source #state
 * \param dest ID of the destination #state
 * \return The very first #edge object matching the requirements or NULL if it was not found
 */
edge *tm_find_edge_inexact(tm *this, unsigned int src, unsigned int dest)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	state *tmp = tm_find_state(this, src);
	edge *iter_edge = NULL;

	edge_list *x = tmp->edges;

	if (!tmp) {
		erring_add("ERROR: src Node is not in tm");
		return NULL;
	}
	S_FOR_EACH_ENTRY(tmp->edges->head, iter_edge) {
		if (iter_edge->target->id == dest)
			return iter_edge;
	}
	return NULL;
}

/**
 * \brief Select #tape of #tm
 * \param index Index of #tape object in tm::tapes::tapes
 * \return tm::tapes::tapes[index] or NULL if index is invalid
 */
tape *tm_select_tape(tm *this, unsigned int index)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	if (index >= this->tapes->length) {
		erring_add("ERROR: Invalid Index %u - maximum Index is %u", index, this->tapes->length - 1);
		return NULL;
	}
	return &this->tapes->data[index];
}

/**
 * \brief Free #tm object
 */
void tm_free(tm *this)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	state_list_free(this->states);
	tapes_free(this->tapes);
	free(this);
}

/**
 * \brief Print #tm object to stdout
 */
void tm_print(tm *this)
{
	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	printf("TURING MACHINE\n");
	printf("TAPES\n\t");
	tapes_print(this->tapes);
	printf("STATES\n\t");
	state_list_print(this->states);
}
