#include "basic_functions.h"

xState move(const xState x_state, Action u) {

	xState output = x_state;

	switch (u) {
		case Action::E_ACTION_RIGTH:
			if (checkXLimits(output.x_ + 1)) {
				output.x_ += 1;
			}
			break;
		case Action::E_ACTION_UP:
			if (checkYLimits(output.y_ + 1)) {
				output.y_ += 1;
			}
			break;
		case Action::E_ACTION_LEFT:
			if (checkXLimits(output.x_ - 1)) {
				output.x_ -= 1;
			}
			break;
		case Action::E_ACTION_DOWN:
			if (checkYLimits(output.y_ - 1)) {
				output.y_ -= 1;
			}
			break;
		default:
			break;
	}

	return output;

}


bool checkXLimits(int x) {

	bool returnValue = false;

	if (MIN_X_LIMIT < x) {
		if (x < MAX_X_LIMIT) {
			returnValue = true;
		}
	}

	return returnValue;
}


bool checkYLimits(int y) {

	bool returnValue = false;

	if (MIN_Y_LIMIT < y) {
		if (y < MAX_Y_LIMIT) {
			returnValue = true;
		}
	}

	return returnValue;
}
