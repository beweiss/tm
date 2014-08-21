#ifndef ERROR_H_
#define ERROR_H_

/**
 * \struct error
 * \brief Represents the "node struct" of erring to save error messages
 *
 * \var error::file
 * The name of the file in which the error occured
 * \var error::func
 * The name of the function in which the error occured
 * \var error::line
 * The line numer in which the error occured
 * \var error::err_msg
 * The error message - a "printed" format string
 */
struct error {
	const char *file;
	const char *func;
	int line;
	char *err_msg;
};

void error_init(struct error *this, const char *file, const char *func, int line, char *err_msg);
void error_free(struct error *this);
void error_print(struct error *this);

#endif
