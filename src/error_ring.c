#include <stdio.h>
#include <stdlib.h>
#include "../include/error_ring.h"

static void __error_ring_enqueue(struct error_ring *this, struct error *new);
static void __error_ring_dequeue(struct error_ring *this);

struct error_ring *error_ring_new(unsigned int size_max)
{
	struct error_ring *ret = malloc(sizeof(*ret));

	ret->size_max = size_max;
	ret->data = malloc(size_max * sizeof(struct error));
	ret->head = NULL;
	ret->tail = ret->data;

	return ret;
}

void error_ring_add(struct error_ring *this, struct error *new)
{
	if (this->tail == this->head) {
		__error_ring_dequeue(this);
	}
	__error_ring_enqueue(this, new);
}

static void __error_ring_enqueue(struct error_ring *this, struct error *new)
{
	if (!this)
		return;
	if (!new)
		return;
	if (!(this->head))
		this->head = this->data;

	*(this->tail) = *new;

	this->tail = this->tail + 1;

	if (this->tail == (this->data + this->size_max))
		this->tail = this->data;
}

static void __error_ring_dequeue(struct error_ring *this)
{
	if (!this)
		return;
	if (!(this->head))
		return;

	this->head = this->head + 1;

	if (this->head == (this->data + this->size_max))
		this->head = this->data;
}

void error_ring_print(struct error_ring *this)
{
	if (!(this->head))
		return;
	struct error *iter = this->head;

	do {
		error_print(iter);
		iter++;
		if (iter == (this->data + this->size_max))
			iter = this->data;
	} while (iter != this->tail);
	printf("\n");
}
