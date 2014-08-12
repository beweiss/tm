//FIXME new name: token!
/**
 * \struct tape_cell
 * \brief Represents the "Node/Entry Class" of #tape_cell_list
 *
 * \var tape_cell::token
 * Token in tape_cell list
 * \var tape_cell::next
 * Next-Pointer
 * \var tape_cell::prev
 * Prev-Pointer
 */
struct tape_cell {
	unsigned int token;
	struct tape_cell *next;
	struct tape_cell *prev;
};

struct tape_cell *tape_cell_new(unsigned int token);
struct tape_cell *tape_cell_copy(struct tape_cell *this);
void tape_cell_free(struct tape_cell *this);
void tape_cell_print(struct tape_cell *this);
