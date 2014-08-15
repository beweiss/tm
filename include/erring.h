#ifndef ERRING_H_
#define ERRING_H_

#include <tm/error.h>

#define E_CRIT "CRITICAL "

#define E_NULL "ERROR: Argument is NULL"
#define E_MALL "ERROR: Call to malloc() failed"

#define CE_MALL E_CRIT E_MALL

#define CALL_FAILED_TO(function) "ERROR: Call to " #function " failed"

#define erring_add(err_msg, ...) erring_add_long(__FILE__, __func__, __LINE__, (err_msg), ##__VA_ARGS__)

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
void erring_add_long(const char *file, const char *func, const int line, const char *err_format, ...);
void erring_free();
void erring_print();

#endif
