#ifndef ERRING_H_
#define ERRING_H_

#include "../include/error.h"

#define erring_add(err_msg) __erring_add_long(__FILE__, __func__, __LINE__, (err_msg))
#define erring_add_default(type) __erring_add_long_default(__FILE__, __func__, __LINE__, (type))

/**
 * \struct tm_erring
 * \brief Short description
 *
 * Long description
 *
 * \var tm_erring::head
 * Pointer to the first entry
 * \var tm_erring::tail
 * Pointer to element *after* last entry
 * 
 */
struct erring {
	struct error *head;
	struct error *tail;
	unsigned int size_max;
	struct error *data;
};

void erring_init(unsigned int size_max);
void erring_add_long(const char *file, const char *func, const int line, const char *err_msg);
void erring_add_long_default(const char *file, const char *func, const int line, enum ERROR_TYPE type);
void erring_free();
void erring_print();

#endif
