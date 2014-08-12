#ifndef TAPE_ACTION_H_
#define TAPE_ACTION_H_

/*! This enum contains the possible shift directions on a tape */
typedef enum {
	STAT = 0, /*!< Do not move on the tape */
	LEFT = -1,/*!< Move left on the tape */
	RIGHT = 1 /*!< Move right on the tape */
} SHIFT_DIR;

/**
 * \struct tape_action
 * \brief Represents an tape-action on an Turing Machine.
 *
 * Every #edge in #edge_list in #tm contains tm::tapes::length (tm::tapes)
 * objects of #tape_action - stored in the array-object #tape_actions
 * 
 *
 * \var tape_action::token_read
 * This token will be read from the tape
 * \var tape_action::token_write
 * This token will be written to the tape
 * \var tape_action::dir
 * This enum value sets the shift direction on the tape
 */
typedef struct {
	unsigned int token_read;
	unsigned int token_write;
	SHIFT_DIR dir;
} tape_action;

tape_action *tape_action_new(unsigned int read, unsigned int write, SHIFT_DIR dir);
void tape_action_print(tape_action *arg);

#endif
