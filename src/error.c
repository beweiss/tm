#include <stdio.h>
#include <stdlib.h>
#include "../include/error.h"

void error_print(struct error *this)
{
	printf("In %s in %s at Line %d: %s\n", this->file, this->func, this->line, this->err_msg);
}
