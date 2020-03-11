#include "Utils/basic_functions.h"
#include "Components/StateQueue.h"
#include <iostream>

int main() {

	Grid grid;
	grid.fillGrid();
	grid.printGrid();

	xState x_ini(0, 0, E_STATE_VISITED);
	const xState x_goal(4, 4, E_STATE_VISITED);
	std::cout << "State Goal = " << x_goal.x_ << ", " << x_goal.y_ << std::endl;

	grid.grid_container[0][0] = x_ini;

	StateQueue queue;
	StateQueue path;

	queue.add_state(x_ini);

	while (queue.get_length() != 0) {
		//std::cout << "Iterating... " << std::endl;
		xState x;
		x = queue.get_first();
	//	std::cout << x.x_ << ", " << x.y_ << std::endl;

		if (x.x_ == x_goal.x_ && x.y_ == x_goal.y_) {

			std::cout << "Success! Goal achieved: " << x_goal.x_ << ", " << x_goal.y_ << std::endl;
			std::cout << "########################" << std::endl;
			path.printQueue();
			return 0;
		}

		for (int i = Action::E_ACTION_RIGTH; i < Action::E_MAX_ACTION; ++i) {

			Action action = static_cast<Action>(i);
			xState x_prima = move(x, action);
			path.add_state(x_prima); // Saves the path to the goal

			if (!grid.isVisited(x_prima)) {
				grid.markStateAsVisited(x_prima);
				queue.add_state(x_prima);

			} else {
				// std::cout << "State visited" << std::endl;
			}

		}
	}

	std::cout << "Failure ..." << std::endl;

	return 0;
}
