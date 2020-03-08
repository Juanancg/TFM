#include "Grid.h"


Grid::Grid() {

}


Grid::~Grid() {

}


void Grid::reset() {

	for (unsigned int i = 0; i < grid_container.size(); ++i) {
		for (unsigned int j = 0; j < grid_container[i].size(); ++j) {
			grid_container[i][j].reset();
		}
	}
}


void Grid::fillGrid() {

	for (unsigned int i = 0; i < grid_container.size(); ++i) {
		for (unsigned int j = 0; j < grid_container[i].size(); ++j) {

			grid_container[i][j].x_ = static_cast<double>(i);
			grid_container[i][j].y_ = static_cast<double>(j);
			grid_container[i][j].state_ = E_STATE_UNVISITED;
		}
	}
}


void Grid::printGrid() {

	for (int i = grid_container.size() - 1; 0 <= i; --i) {
		for (unsigned int j = 0; j < grid_container[i].size(); ++j) {
			std::cout << "  " <<  grid_container[j][i].x_ << "," <<  grid_container[j][i].y_ << "(" << grid_container[j][i].printState() << ")";
		}
		std::cout << '\n';
	}
}


bool Grid::getPosInsideGrid(const xState state, int &i_out, int &j_out) { // TODO Optimize this method

	bool returnValue = false;

	for (unsigned int i = 0; i < grid_container.size(); ++i) {
		for (unsigned int j = 0; j < grid_container[i].size(); ++j) {

			if (grid_container[i][j].x_ == state.x_ && grid_container[i][j].y_ == state.y_) {
				i_out = i;
				j_out = j;
				returnValue = true;
			}
		}
	}

	return returnValue;
}


bool Grid::markStateAsVisited(const xState state) { // TODO Optimize this method

	bool returnValue = false;
	int i = 0;
	int j = 0;

	if (getPosInsideGrid(state, i, j)) {
		grid_container[i][j].state_ = E_STATE_VISITED;
		returnValue = true;
	}

	return returnValue;
}


bool Grid::isVisited(const xState state) {

	bool returnValue = false;
	int i = 0;
	int j = 0;

	if (getPosInsideGrid(state, i, j) && grid_container[i][j].state_ == E_STATE_VISITED) {
		returnValue = true;
	}

	return returnValue;
}
