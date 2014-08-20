#include <stdio.h>
#include <stdlib.h>
#include "../include/error.h"

void error_init(struct error *this, const char *file, const char *func, int line, const char *err_msg)
{
	this->file = file;
	this->func = func;
	this->line = line;
	this->err_msg = err_msg;
}

void error_print(struct error *this)
{
	printf("In %s in %s at Line %d: %s\n", this->file, this->func, this->line, this->err_msg);
}
