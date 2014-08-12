//FIXME new name: token!
/**
 * \struct __tape
 * \brief Represents the "Node/Entry Class" of #__tape_list
 *
 * \var __tape::token
 * Token in __tape list
 * \var __tape::next
 * Next-Pointer
 * \var __tape::prev
 * Prev-Pointer
 */
struct __tape {
	unsigned int token;
	struct __tape *next;
	struct __tape *prev;
};

struct __tape *__tape_new(unsigned int token);
struct __tape *__tape_copy(struct __tape *this);
void __tape_free(struct __tape *this);
void __tape_print(struct __tape *this);
