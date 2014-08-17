#ifndef ERROR_H_
#define ERROR_H_

#define ERR_MSG_NUM 1

static const char* ERROR_MSG_LOOKUP[ERR_MSG_NUM] =
{
	"Argument is NULL"
};

enum ERROR_TYPE {
	E_NULL
};

struct error {
	const char *file;
	const char *func;
	int line;
	const char *err_msg;
	unsigned int id;
};

/**

	In __FILE__ in __func__ at LINE : Failed to ...

*/

struct error *error_new(const char *file, const char *func, const int line, const char *err_msg);
struct error *error_new_default(const char *file, const char *func, const int line, enum ERROR_TYPE type);
void error_print(struct error *this);

#endif
