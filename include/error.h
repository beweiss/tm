#ifndef ERROR_H_
#define ERROR_H_

struct error {
	const char *file;
	const char *func;
	int line;
	char *err_msg;
};

/**

	In __FILE__ in __func__ at LINE : Failed to ...

*/

void error_init(struct error *this, const char *file, const char *func, int line, char *err_msg);
void error_free(struct error *this);
void error_print(struct error *this);

#endif
