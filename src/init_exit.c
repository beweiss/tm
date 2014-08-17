#include "../include/erring.h"

__attribute__((constructor))
void tm_init()
{
	//FIXME maybe use here environment variable as option
	erring_init(100);
}

__attribute__((destructor))
void tm_exit()
{
	erring_free();
}
