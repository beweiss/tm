#include <stdio.h>
#include <stdlib.h>
#include "../include/error.h"

void error_init(struct error *this, const char *file, const char *func, int line, char *err_msg)
{
	if (!this)
		return;
	this->file = file;
	this->func = func;
	this->line = line;
	this->err_msg = err_msg;
}

void error_free(struct error *this)
{
	if (!this)
		return;
	free(this->err_msg);
}

/**
 * \brief Print error struct in specific format
 *
 * Format: "In __FILE__ in __func__ at Line __LINE__: err_msg\n"
 *
 */
void error_print(struct error *this)
{
	printf("In %s in %s at Line %d: %s\n", this->file, this->func, this->line, this->err_msg);
}
