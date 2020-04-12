#include "xState.h"

xState::xState() {
	reset();
}

xState::~xState() {
	// TODO Auto-generated destructor stub
}


xState::xState(double x, double y, State state) :
		x_(x), y_(y), state_(state) {
}

void xState::reset() {
	x_ = 0.0;
	y_ = 0.0;
	state_ = E_STATE_NOT_CREATED;
}

char xState::printState() {
	char returnValue = '?';

	switch (state_) {
		case State::E_STATE_UNVISITED:
			returnValue = 'U';
			break;
		case State::E_STATE_UNABLE:
			returnValue = 'D';
			break;
		case State::E_STATE_VISITED:
			returnValue = 'V';
			break;
		default:
			break;
	}

	return returnValue;
}
