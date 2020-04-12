#ifndef TYPES_H_
#define TYPES_H_

#include <array>
#include <iostream>

constexpr unsigned int MAX_ROWS = 10;
constexpr unsigned int MAX_COLS = 10;
constexpr unsigned int MAX_CELLS = MAX_ROWS * MAX_COLS;

constexpr int MIN_X_LIMIT = 0;
constexpr int MAX_X_LIMIT = MAX_ROWS;
constexpr int MIN_Y_LIMIT = 0;
constexpr int MAX_Y_LIMIT = MAX_COLS;

enum Action {
	E_ACTION_RIGTH,
	E_ACTION_UP,
	E_ACTION_LEFT,
	E_ACTION_DOWN,
	E_MAX_ACTION
};

enum State {
	E_STATE_NOT_CREATED,
	E_STATE_UNVISITED,
	E_STATE_UNABLE,
	E_STATE_VISITED
};

#endif /* TYPES_H_ */
