#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../include/tm.h"
#include "../../include/erring.h"
#include <stdint.h>

bool my_is_in_alph(uinptr_t)
{
	if (uinptr_t >= 0 && uinptr_t <= 20)
		return true;
	return false;
}

void strlen_less_10_tm()
{
	uintptr_t help[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5};
	word *word_one = word_new(help, 12);
	tapes *my_tapes = tapes_new(1, tape_new(word_one));
	tm *machine1 = tm_new_with_states(my_tapes, my_is_in_alph, 10);
	uintptr_t *read_vector[] = {NULL};
	uintptr_t *write_vector[] = {&help[0]};
	SHIFT_DIR dirs[] = {RIGHT};
	SHIFT_DIR stand[] = {STAT};
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int x = 0;
	uintptr_t **helper = malloc(sizeof(uintptr_t *) * 10);

	if (machine1 == NULL) {
		printf("WTF???\n");
		exit(0);
	}

	for (i = 0; i < 9; i++) {
		helper[i] = (uintptr_t *) &help[i];
		tm_add_edge(machine1, i, i + 1, tape_actions_new(1, read_vector, write_vector, dirs));
		tm_add_edge_to_accept(machine1, i, tape_actions_new(1, write_vector, &helper[i], stand));
	}

	helper[i] = (uintptr_t *) &help[i];
	tm_add_edge_to_reject(machine1, i, tape_actions_new(1, read_vector, write_vector, stand));
	tm_add_edge_to_accept(machine1, 9, tape_actions_new(1, write_vector, &helper[i], stand));

	tm_print(machine1);
	tm_free(machine1);
	word_free(word_one);
	free(helper);
}

void add_mult_par_term_tm()
{
	/*unsigned int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	unsigned int tape[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	unsigned int help[] = {1, 1, 2, 4, 2, 3, 4, 2, 3};
	word *word_one = word_new(help, 9);
	tapes *my_tapes = tapes_new(3, tape_new(word_one, RDWR), tape_new(word_one, RDWR), tape_new(word_one, RDWR));
	tm *machine1 = tm_new(my_tapes, alphabet_new(input, 9), alphabet_new(tape, 10));
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int x = 0;

	if (machine1 == NULL) {
		printf("WTF???\n");
		exit(0);
	}

	tm_add_state(machine1, NORMAL, edge_default_new(3, BLANK, STAT));
	tm_add_state(machine1, NORMAL, edge_default_new(3, BLANK, STAT));
	tm_add_state(machine1, ACCEPT, NULL);
	tm_add_state(machine1, REJECT, NULL);

	tm_add_edge(machine1, 0, 0, tape_action_new(1, BLANK, RIGHT), tape_action_new();
	tm_add_edge(machine1, 0, 1, tape_action_new(2, BLANK, RIGHT));
	tm_add_edge(machine1, 1, 1, tape_action_new(3, BLANK, RIGHT));
	tm_add_edge(machine1, 1, 0, tape_action_new(4, BLANK, RIGHT));
	tm_add_edge(machine1, 1, 2, tape_action_new(BLANK, BLANK, STAT));
	tm_add_edge(machine1, 0, 2, tape_action_new(BLANK, BLANK, STAT));

	state *check = tm_compute(machine1);

	if (check) {
		printf("Jop\n");
		if (check == machine1->accept) {
			printf("JAAAAAAAAAAAAAA\n");
		}
	}

	tape_print(&machine1->tapes->tapes[0]);

	tm_export_to_dot_file(machine1, "/home/benedikt/tm_term.dot");
	//tm_print(machine1);
	tm_free(machine1);
	word_free(word_one);*/

	
}

int main(int argc, char *argv[])
{
	unsigned int x = 12345;
	strlen_less_10_tm();
//	add_mult_par_term_
	return 0;
}
