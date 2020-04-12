#ifndef COMPONENTS_XSTATE_H_
#define COMPONENTS_XSTATE_H_

#include "src/Components/Types.h"

class xState {
public:

	double x_;
	double y_;
	State state_;

	xState();
	xState(double x, double y, State state);
	virtual ~xState();

	void reset();
	char printState();
};

#endif /* COMPONENTS_XSTATE_H_ */
