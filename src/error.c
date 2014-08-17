#include <stdio.h>
#include <stdlib.h>
#include "../include/error.h"

struct error *error_new(const char *file, const char *func, const int line, const char *err_msg)
{
	if (!err_msg)
		return NULL;

	struct error *ret = malloc(sizeof(*ret));

	ret->file = file;
	ret->func = func;
	ret->line = line;
	ret->err_msg = err_msg;

	return ret;
}

struct error *error_new_default(const char *file, const char *func, const int line, enum ERROR_TYPE type)
{
	if (type >= ERR_MSG_NUM)
		return NULL;
	if (type < 0)
		return NULL;

	return error_new(file, func, line, ERROR_MSG_LOOKUP[type]);
}

void error_print(struct error *this)
{
	printf("In %s in %s at Line %d: %s\n", this->file, this->func, this->line, this->err_msg);
}
