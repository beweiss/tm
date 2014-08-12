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
#include "../include/alphabet.h"
#include "../include/tm.h"

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
tm *tm_new(tapes *tapes, alphabet *alph_input, alphabet *alph_tape)
{
	if (!tapes)
		return NULL;
	if (!alph_input)
		return NULL;
	if (!alph_tape)
		return NULL;
	if (!alphabet_is_subset(alph_input, alph_tape))
		return NULL;
	if (alphabet_contains(alph_input, BLANK))
		return NULL;
	if (!alphabet_contains(alph_tape, BLANK))
		return NULL;
	if (!tape_is_descended_from(&tapes->tapes[0], alph_input))
		return NULL;
	/* FIXME Add error handling */
	tm *ret = malloc(sizeof(*ret));

	ret->tapes = tapes;
	//FIXME add error handling
	ret->states = state_list_new();
	ret->alph_input = alph_input;
	ret->alph_tape = alph_tape;
	ret->accept = NULL;
	ret->reject = NULL;

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
void tm_add_state(tm *this, STATE_TYPE type, edge_default *out_default)
{
	state *new = NULL;

	if (!this)
		return;
	if (!this->states->head) {
		if (type != NORMAL)
			return;
	}
	switch (type) {
	case NORMAL:
		new = state_new(out_default);
		state_list_add_node(this->states, new);
		break;
	case ACCEPT:
		if (this->accept)
			return;
		if (out_default)
			return;
		new = state_new(out_default);
		this->accept = new;
		state_list_add_node(this->states, new);
		break;
	case REJECT:
		if (this->reject)
			return;
		if (out_default)
			return;
		new = state_new(out_default);
		this->reject = new;
		state_list_add_node(this->states, new);
		break;
	}
}

/**
 * \brief Remove state from tm
 * \param id ID of the wanted #state
 */
void tm_remove_state(tm *this, unsigned int id)
{
	if (!this)
		return;
	//state_list_remove_node(this->states, id);
}

/**
 * \brief Find state in tm
 * \param id ID of the wanted #state
 */
state *tm_find_state(tm *this, unsigned int id)
{
	if (!this)
		return NULL;
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
edge *tm_add_edge(tm *this, unsigned int src, unsigned int dest, tape_action *action1, ...)
{
	state *state_src = tm_find_state(this, src);
	if (!state_src)
		return NULL;
	if (!tm_find_state(this, dest))
		return NULL;
	if (state_src == this->accept || state_src == this->reject)
		return NULL;
	if (!action1)
		return NULL;
	if (!alphabet_contains(this->alph_tape, action1->token_read))
		return NULL;
	if (!alphabet_contains(this->alph_tape, action1->token_write))
		return NULL;
	va_list arguments;
	unsigned int num = this->tapes->length;
	/* FIXME Add error handling */
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

	new_edge = edge_new(dest, actions);

	edge_list_add_node(state_src->edges, new_edge);
CLEANUP:
	va_end(arguments);
	return new_edge;
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
	if (!this)
		return NULL;
	if (!this->states->head)
		return NULL;
	if (!this->accept && !this->reject)
		return NULL;
	return __tm_compute(this, this->states->head);
}

/**
 * \brief Internal helper function of tm_compute
 * \return The last #state we reached
 */
static state *__tm_compute(tm *this, state *current)
{
	if (current == this->accept)
		return current;
	if (current == this->reject)
		return current;
	edge *iter = NULL;
	state *implicit = NULL;

	tape_print(&this->tapes->tapes[0]);

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
	return NULL;
}

/**
 * \brief Generate accepted word
 * \return #word object
 */
word *tm_gen_accepted_word(tm *this)
{
	if (!this)
		return NULL;
	return NULL;
}

/**
 * \brief Copy #tm object
 * \return Copy of #tm object
 */
tm *tm_copy(tm *this)
{
	if (!this)
		return NULL;
	/* FIXME Add error handling */
	tm *ret = malloc(sizeof(*ret));

	//ret->is_det = this->is_det;
	ret->states = state_list_copy(this->states);
	ret->tapes = tapes_copy(this->tapes);
	ret->alph_input = alphabet_copy(this->alph_input);
	ret->alph_tape = alphabet_copy(this->alph_tape);

	return ret;
}

/**
 * \brief Export #tm object to .dot-File
 * \param path Path of the outputted .dot-File
 */
void tm_export_to_dot_file(tm *this, char *path)
{
	if (!this)
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
				sprintf(id, "%u", edge_iter->actions->actions[i].token_read);
				strncat(total, id, strlen(id));
				strncat(total, ";", 1);
				sprintf(id, "%u", edge_iter->actions->actions[i].token_write);
				strncat(total, id, strlen(id));
				strncat(total, ",", 1);
				switch (edge_iter->actions->actions[i].dir) {
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
	free(total);
}

/**
 * \brief Find specific #edge in #tm
 * \param src ID of the source #state
 * \param dest ID of the destination #state
 * \param token Token of the wanted edge
 * \return The specific #edge object or NULL if it was not found
 */
edge *tm_find_edge(tm *this, unsigned int src, unsigned int dest, unsigned int token)
{
	//FIXME maybe bullshit
	if (!this)
		return NULL;
	return NULL;
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
	if (!this)
		return NULL;
	state *tmp = tm_find_state(this, src);
	edge *iter_edge = NULL;

	if (!tmp)
		return NULL;
	S_FOR_EACH_ENTRY(tmp->edges->head, iter_edge) {
		if (iter_edge->id_dest == dest)
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
	if (!this)
		return NULL;
	if (index >= this->tapes->length || index < 0)
		return NULL;
	return &this->tapes->tapes[index];
}

/**
 * \brief Free #tm object
 */
void tm_free(tm *this)
{
	if (!this)
		return;
	state_list_free(this->states);
	tapes_free(this->tapes);
	alphabet_free(this->alph_input);
	alphabet_free(this->alph_tape);
	free(this);
}

/**
 * \brief Print #tm object to stdout
 */
void tm_print(tm *this)
{
	/* FIXME Add error handling */
	if (!this)
		return;
	printf("TURING MACHINE\n");
	printf("INPUT ALPHABET\n\t");
	alphabet_print(this->alph_input);
	printf("TAPE ALPHABET\n\t");
	alphabet_print(this->alph_tape);
	printf("TAPES\n\t");
	tapes_print(this->tapes);
	printf("STATES\n\t");
	state_list_print(this->states);
}
