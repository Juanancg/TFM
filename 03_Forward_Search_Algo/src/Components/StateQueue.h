#ifndef COMPONENTS_STATEQUEUE_H_
#define COMPONENTS_STATEQUEUE_H_

#include <array>
#include "xState.h"
#include "Types.h"

class StateQueue {

public:

	StateQueue();
	virtual ~StateQueue();

	void add_state(xState x);
	xState get_first();
	unsigned int get_length();
	void printQueue();
	void reset();

private:
	std::array<xState, MAX_COLS * MAX_ROWS> queue_;
	unsigned int length_;
};

#endif /* COMPONENTS_STATEQUEUE_H_ */
