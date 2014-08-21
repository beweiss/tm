#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <error.h>
#include <errno.h>
#include "../include/erring.h"

__attribute__((constructor))
void tm_init()
{
	char *env_size = getenv("TM_ERRING_SIZE");
	unsigned int size = ERRING_SIZE_DEFAULT;

	if (env_size) {
		unsigned int ret = strtoul(env_size, NULL, 10);

		if (ret <= ERRING_SIZE_MAX && ret)
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
