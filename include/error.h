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
};

/**

	In __FILE__ in __func__ at LINE : Failed to ...

*/

void error_print(struct error *this);

#endif
