#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "../include/erring.h"

static void __erring_enqueue(struct error *new);
static void __erring_dequeue();
static void __erring_add(struct error *new);

struct erring erring;

void erring_init(unsigned int size_max)
{
	erring.size_max = size_max;
	//FIXME add error handling - critical error!
	erring.data = malloc(size_max * sizeof(struct error));

	if (!(erring.data))
		error_at_line(0, errno, __FILE__, __LINE__, "CRITICAL ERROR in %s", __func__);

	erring.head = NULL;
	erring.tail = erring.data;

}

void erring_add_long(const char *file, const char *func, const int line, const char *err_msg)
{
	struct error x = {file, func, line, err_msg};

	__erring_add(&x);
}

void erring_add_long_default(const char *file, const char *func, const int line, enum ERROR_TYPE type)
{
	if (type >= ERR_MSG_NUM)
		return;
	if (type < 0)
		return;

	struct error x = {file, func, line, ERROR_MSG_LOOKUP[type]};

	__erring_add(&x);
}

void erring_free()
{
	if (!(erring.data))
		return;
	free(erring.data);
}

void erring_print()
{
	if (!(erring.data))
		return;
	if (!(erring.head))
		return;
	struct error *iter = erring.head;

	do {
		error_print(iter);
		iter++;
		if (iter == (erring.data + erring.size_max))
			iter = erring.data;
	} while (iter != erring.tail);
}

static void __erring_add(struct error *new)
{
	if (!(erring.data))
		return;
	if (erring.tail == erring.head) {
		__erring_dequeue();
	}
	__erring_enqueue(new);
}

static void __erring_enqueue(struct error *new)
{
	if (!new)
		return;
	if (!(erring.head))
		erring.head = erring.data;

	erring.tail->file = new->file;
	erring.tail->func = new->func;
	erring.tail->line = new->line;
	erring.tail->err_msg = new->err_msg;

	erring.tail = erring.tail + 1;

	if (erring.tail == (erring.data + erring.size_max))
		erring.tail = erring.data;
}

static void __erring_dequeue()
{
	if (!(erring.head))
		return;

	erring.head = erring.head + 1;

	if (erring.head == (erring.data + erring.size_max))
		erring.head = erring.data;
}
