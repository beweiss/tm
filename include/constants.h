#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define BLANK 0

/*! This enum contains the possible shift directions on a tape */
typedef enum {
	STAT = 0, /*!< Do not move on the tape */
	LEFT = -1,/*!< Move left on the tape */
	RIGHT = 1 /*!< Move right on the tape */
} SHIFT_DIR;

#endif
