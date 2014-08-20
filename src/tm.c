#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/singly_linked_list_macros.h"
#include "../include/constants.h"
#include "../include/tm.h"
#include "../include/erring.h"

static state *__tm_compute(tm *this, state *current);

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
		return NULL;
	}
	return ret;
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
void tm_add_state(tm *this, edge *out_default)
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
 * \brief Remove state from tm
 * \param id ID of the wanted #state
 */
void tm_remove_state(tm *this, unsigned int id)
{
	if (!this) {
		erring_add(E_NULL);
		return;
	}
	//state_list_remove_node(this->states, id);
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
edge *tm_add_edge(tm *this, unsigned int src, unsigned int dest, tape_actions *actions)
{
	state *state_src = tm_find_state(this, src);
	state *state_dest = tm_find_state(this, dest);
	edge *new_edge = NULL;

	if (!this) {
		erring_add(E_NULL);
		return NULL;
	}
	if (!actions) {
		erring_add(E_NULL);
		return NULL;
	}
	if (!state_src) {
		erring_add("ERROR: src Node does not exist in tm");
		return NULL;
	}
	if (!state_dest) {
		erring_add("ERROR: dest Node does not exist in tm");
		return NULL;
	}

	new_edge = edge_new(state_dest, actions);

	if (!new_edge) {
		erring_add(CALL_FAILED_TO(edge_new));
		return NULL;
	}
	edge_list_add_node(state_src->edges, new_edge);
	return new_edge;

	/*va_list arguments;
	unsigned int num = this->tapes->length;
	tape_action *action_array = NULL;
	tape_actions *actions = NULL;
	tape_action *check = NULL;
	edge *new_edge = NULL;
	unsigned int i = 0;

	va_start(arguments, action1);

	if (num > 1) {
		action_array = malloc(sizeof(tape_action) * num);
		action_array[0] = *action1;
	}
	else {
		action_array = action1;
	}

	for (i = 1; i < num; i++) {
		check = va_arg(arguments, tape_action*);
		if (!check) {
			free(action_array);
			goto CLEANUP;
		}
		if (!alphabet_contains(this->alph_tape, check->token_read)
		    || !alphabet_contains(this->alph_tape, check->token_write)) {
			free(action_array);
			goto CLEANUP;
		}
		action_array[i] = *check;
	}

	actions = tape_actions_new(num, action_array);

	new_edge = edge_new(state_dest, actions);

	edge_list_add_node(state_src->edges, new_edge);
CLEANUP:
	va_end(arguments);
	return new_edge;*/
}

/**
 * \brief Start the computation of the Turing Machine
 *
 * There have to be at least one state and there have to be
 * 1 accepting state or 1 rejecting state.
 *
 * \return The last #state we reached
 */
state *tm_compute(tm *this)
{
	/*if (!this)
		return NULL;
	if (!this->states->head)
		return NULL;
	return __tm_compute(this, this->states->head);*/
}

/**
 * \brief Internal helper function of tm_compute
 * \return The last #state we reached
 */
static state *__tm_compute(tm *this, state *current)
{
	//FIXME END CONDITION
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

/**
 * \brief Generate accepted word
 * \return #word object
 */
word *tm_gen_accepted_word(tm *this)
{
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
		erring_add("ERROR: Invalid Index %u - maximum Index is %u", index, this->tapes->length);
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
