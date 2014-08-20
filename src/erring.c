#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <stdarg.h>
#include "../include/erring.h"

static void __erring_enqueue(struct error *new);
static void __erring_dequeue();
static void __erring_add(struct error *new);

struct erring __erring;

struct erring *erring = &__erring;

void erring_init(unsigned int size_max)
{
	erring->size_max = size_max;
	erring->data = malloc(size_max * sizeof(struct error));

	if (!(erring->data)) {
		error_at_line(0, errno, __FILE__, __LINE__, CE_MALL " in %s", __func__);
		erring = NULL;
		return;
	}
	erring->head = NULL;
	erring->tail = erring->data;

}

void erring_add_long(const char *file, const char *func, const int line, const char *err_format, ...)
{
	if (!erring)
		return;
	struct error x;
	unsigned int size = 0;
	char *buf = NULL;
	va_list arguments;

	va_start(arguments, err_format);
	size = vsnprintf(buf, size, err_format, arguments);
	va_start(arguments, err_format);
	buf = malloc(size + 1);

	if (!buf) {
		error_at_line(0, errno, __FILE__, __LINE__, CE_MALL " in %s", __func__);
		va_end(arguments);
		return;
	}

	vsnprintf(buf, size + 1, err_format, arguments);
	va_end(arguments);

	error_init(&x, file, func, line, buf);
	__erring_add(&x);
}

void erring_free()
{
	if (!erring)
		return;
	unsigned int i = 0;
	for (i = 0; i < erring->size_max; i++)
		error_free(&erring->data[i]);
	free(erring->data);
}

void erring_print()
{
	if (!erring)
		return;
	if (!(erring->head))
		return;
	struct error *iter = erring->head;

	do {
		error_print(iter);
		iter++;
		if (iter == (erring->data + erring->size_max))
			iter = erring->data;
	} while (iter != erring->tail);
}

static void __erring_add(struct error *new)
{
	if (!erring)
		return;
	if (erring->tail == erring->head) {
		__erring_dequeue();
	}
	__erring_enqueue(new);
}

static void __erring_enqueue(struct error *new)
{
	if (!new)
		return;
	if (!(erring->head))
		erring->head = erring->data;

	error_init(erring->tail, new->file, new->func, new->line, new->err_msg);

	erring->tail = erring->tail + 1;

	if (erring->tail == (erring->data + erring->size_max))
		erring->tail = erring->data;
}

static void __erring_dequeue()
{
	if (!(erring->head))
		return;

	erring->head = erring->head + 1;

	if (erring->head == (erring->data + erring->size_max))
		erring->head = erring->data;
}
