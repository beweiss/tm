#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tm.h"

#define STATES_NUM 50

void strlen_less_10_tm()
{
	unsigned int input[] = {1, 2, 3, 4, 5, 6};
	unsigned int tape[] = {0, 1, 2, 3, 4, 5, 6};
	unsigned int help[] = {1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6};
	word *word_one = word_new(help, 9);
	tapes *my_tapes = tapes_new(1, tape_new(word_one, RDWR));
	tm *machine1 = tm_new(my_tapes, alphabet_new(input, 6), alphabet_new(tape, 7));
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int x = 0;

	if (machine1 == NULL)
		printf("WTF???\n");

	for (i = 0; i < 10; i++)
		tm_add_state(machine1, NORMAL);

	tm_add_state(machine1, ACCEPT);
	tm_add_state(machine1, REJECT);
	for (i = 0; i < 10; i++) {
		x = i + 1;
		if (i == 9)
			x = 11;
		for (j = 1; j < 63; j++) {
			if (!tm_add_edge(machine1, i, x, tape_action_new(j, 0, RIGHT)))
				printf("WAAAAAAAAAAAAAAAAAAAAAS???\n");
		}
		if (!tm_add_edge(machine1, i, 10, tape_action_new(0, i, STAT)))
				printf("WAAAAAAAAAAAAAAAAAAAAAS???\n");
	}
	tape_print(tm_select_tape(machine1, 0));
	if (tm_compute(machine1)->type == ACCEPT) {
		tape_print(tm_select_tape(machine1, 0));
	}

	tm_export_to_dot_file(machine1, "/home/benedikt/tm.dot");
	tm_free(machine1);
	word_free(word_one);
}

int main(int argc, char *argv[])
{
	strlen_less_10_tm();
	return 0;
}
