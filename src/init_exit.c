#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <error.h>
#include <errno.h>
#include "../include/erring.h"

#define MAX_ERRING_SIZE 1000

__attribute__((constructor))
void tm_init()
{
	char *env_size = getenv("TM_ERRING_SIZE");
	unsigned int size = 100;

	if (env_size) {
		unsigned int ret = strtoul(env_size, NULL, 10);

		if (ret <= MAX_ERRING_SIZE && ret)
			size = ret;
	}
	erring_init(size);
}

__attribute__((destructor))
void tm_exit()
{
	erring_print();
	erring_free();
}
