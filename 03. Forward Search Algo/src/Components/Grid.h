#ifndef COMPONENTS_GRID_H_
#define COMPONENTS_GRID_H_

#include <array>

#include "Types.h"
#include "xState.h"

class Grid {
public:

	std::array<std::array<xState, MAX_COLS>, MAX_ROWS> grid_container;

	Grid();
	virtual ~Grid();

	void printGrid();
	bool markStateAsVisited(const xState state);
	bool isVisited(const xState state); // todo continue here
	void fillGrid();
	void reset();

private:
	bool getPosInsideGrid(const xState state, int &i_out, int &j_out);
};

#endif /* COMPONENTS_GRID_H_ */
