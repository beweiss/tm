#ifndef ERRING_H_
#define ERRING_H_

#include "../include/error.h"

/**
 * Useful error string constants for erring_add macro
 */

#define E_CRIT "CRITICAL "

#define E_NULL "ERROR: Argument is NULL"
#define E_MALL "ERROR: Call to malloc() failed"

#define CE_MALL E_CRIT E_MALL

#define CALL_FAILED_TO(function) "ERROR: Call to " #function " failed"

/**
 * \brief Add format string error message to erring
 *
 * Interesting: This functionality is *only* possible through a macro because
 * so we can add the __FILE__, __func__ and __LINE__ macros and the user
 * does not have to write them by himself.
 *
 * \param err_msg The format string
 * \param ... The variable argument list
 */
#define erring_add(err_msg, ...) erring_add_long(__FILE__, __func__, __LINE__, (err_msg), ##__VA_ARGS__)

/**
 * \struct erring
 * \brief Represents the global structure to save error messages
 *
 * This is a ring buffer and the only "special" thing is that _always_
 * the last erring::size_max entries are stored so the "outer functions"
 * (or "calling functions") are always above the "inner functions"
 * (the "called functions")
 * I like that because no one wants to know the error messages of
 * things like malloc() *first*.
 *
 * \var erring::head
 * Pointer to the first entry
 * \var erring::tail
 * Pointer to element *after* last entry
 * \var erring::size_max
 * Maximum size of ring buffer - is set by constant MAX_ERRING_SIZE or by
 * the user - see tm_init(). This is the length of erring::data
 * \var erring::data
 * The array of error structs
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
