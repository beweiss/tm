#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/tm.h"

void strlen_less_10_tm()
{
	unsigned int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	unsigned int tape[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	unsigned int help[] = {1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6};
	word *word_one = word_new(help, 8);
	tapes *my_tapes = tapes_new(1, tape_new(word_one, RDWR));
	tm *machine1 = tm_new(my_tapes, alphabet_new(input, 9), alphabet_new(tape, 10));
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int x = 0;

	if (machine1 == NULL)
		printf("WTF???\n");

	for (i = 0; i < 9; i++)
		tm_add_state(machine1, NORMAL, edge_default_new(i + 1, 0, RIGHT));

	tm_add_state(machine1, NORMAL, edge_default_new(11, 0, STAT));
	tm_add_state(machine1, ACCEPT, NULL);
	tm_add_state(machine1, REJECT, NULL);

	for (i = 0; i < 10; i++) {
		if (!tm_add_edge(machine1, i, 10, tape_action_new(0, i, STAT)))
			printf("WAAAAAAAAAAAAAAAAAAAAAS???\n");	
	}

	state *check = tm_compute(machine1);

	if (check) {
		printf("Jop\n");
		if (check->type == ACCEPT) {
			printf("JAAAAAAAAAAAAAA\n");
		}
	}

	tape_print(&machine1->tapes->tapes[0]);

	tm_export_to_dot_file(machine1, "/home/benedikt/tm_short.dot");
	tm_print(machine1);
	tm_free(machine1);
	word_free(word_one);
}

int main(int argc, char *argv[])
{
	strlen_less_10_tm();
	return 0;
}
