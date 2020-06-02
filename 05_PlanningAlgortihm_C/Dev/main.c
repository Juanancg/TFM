#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_ROWS  10
#define MAX_COLS  10
#define MAX_CELLS  MAX_ROWS * MAX_COLS

#define MIN_X_LIMIT  0
#define MAX_X_LIMIT  MAX_ROWS
#define MIN_Y_LIMIT  0
#define MAX_Y_LIMIT  MAX_COLS

enum e_Action {
	E_ACTION_RIGTH = 0,
	E_ACTION_UP = 1,
	E_ACTION_LEFT = 2,
	E_ACTION_DOWN = 3,
	E_MAX_ACTION = 4
};

enum e_State {
	E_STATE_NOT_CREATED,
	E_STATE_UNVISITED,
	E_STATE_UNABLE,
	E_STATE_VISITED,
	E_STATE_CONFIRMED
};

struct Cell {
	int x;
	int y;
	enum e_State state;
	enum e_Action next_direction;
};
typedef struct Cell st_Cell;

struct Cell_Path {
	struct Cell path[MAX_CELLS];
	unsigned int length;
};
typedef struct Cell_Path st_Cell_Path;

struct Queue_Element {
	struct Cell cell;
	double distance_to_dest;
};
typedef struct Queue_Element st_Queue_Element;


struct Cell_Queue {
	st_Queue_Element queue[MAX_CELLS];
	unsigned int length;
};
typedef struct Cell_Queue st_Cell_Queue;

/********************************************************/
/*					GLOBAL VARIABLES					*/
/********************************************************/
st_Cell grid[MAX_COLS][MAX_ROWS];


/********************************************************/
/*				FUNCTIONS DECLARATIONS					*/
/********************************************************/
st_Cell_Path backTracking(st_Cell_Path path);

st_Cell getNearElementToDestination(st_Cell_Queue *queue);

void printPath(const st_Cell_Path path);
void addCellToPath(const st_Cell cell, st_Cell_Path *path);

void printQueue(const st_Cell_Queue queue);
void addCellToQueue(const st_Cell cell, const st_Cell destination, st_Cell_Queue *queue);

bool isCellAvailable(const st_Cell cell);
bool markCellAsVisited(const st_Cell cell);
void fillGrid();
void printGrid();
st_Cell getNextMovement(int x, int y, enum e_Action movement);
bool checkXLimits(int x);
bool checkYLimits(int y);
double get_distance(const st_Cell point1, const st_Cell point2);


/********************************************************/
/*						MAIN							*/
/********************************************************/
int main(int argc, char *argv[]) {
	
	fillGrid(); // TODO Move to Init method of Navigation
/*	grid[9][5].state = E_STATE_UNABLE;
	grid[8][5].state = E_STATE_UNABLE;
	grid[7][5].state = E_STATE_UNABLE;
	grid[6][5].state = E_STATE_UNABLE;
	grid[5][5].state = E_STATE_UNABLE;
	grid[4][5].state = E_STATE_UNABLE;*/
	printGrid();
	
	st_Cell initial_cell = {0, 0, E_STATE_VISITED};
	st_Cell destination_cell = {5, 5, E_STATE_UNVISITED};
	
	// TODO Hacer funcion para comprobar que si el destino es alcanzable
	
	markCellAsVisited(initial_cell);

	st_Cell_Path path;
	st_Cell_Queue queue;
	path.length = 0;
	queue.length = 0;
	
	addCellToQueue(initial_cell, destination_cell, &queue);
	
	while (queue.length != 0) {
		
		st_Cell near_cell;

		near_cell = getNearElementToDestination(&queue);

		addCellToPath(near_cell, &path);
		printf("Iterating...  %d,%d\n", near_cell.x, near_cell.y);
		if (near_cell.x == destination_cell.x && near_cell.y == destination_cell.y) {
			printf("Success!!!\n");
			
			st_Cell_Path path_confirmed;
			path_confirmed = backTracking(path);
			printPath(path_confirmed);
			return 0;
		}
		
		int i = 0;
		
		// Get the possibles next cells from the current one
		for (i = 0; i < (int)E_MAX_ACTION; ++i) {
			
			enum e_Action next_action = (enum e_Action)i;
			
			st_Cell next_cell = getNextMovement(near_cell.x, near_cell.y, next_action);
			
			if (isCellAvailable(next_cell)) {
				markCellAsVisited(next_cell);
				next_cell.state = E_STATE_VISITED;
				addCellToQueue(next_cell, destination_cell, &queue);
			}
		}
		
	}
	

	printPath(path);
	printf("Bye Planning!\n");
	return 0;
}


/********************************************************/
/*				FUNCTIONS DEFINITIONS					*/
/********************************************************/
st_Cell_Path backTracking(st_Cell_Path path)  {
	printf("\n");
	printPath(path);
	int i = 0;
	int x = 0;
	int delta_x = 0;
	int y = 0;
	int delta_y = 0;
	st_Cell_Path returnValue;
	returnValue.length = 0;
	
	path.path[path.length - 1].state = E_STATE_CONFIRMED; // Because it is the Goal
	x = path.path[path.length - 1].x;
	y = path.path[path.length - 1].y;
	
	for (i = path.length - 2; 0 <= i; i--) {
		delta_x = x - path.path[i].x;
		delta_y = y - path.path[i].y;
		
		if ((abs(delta_x) + abs(delta_y)) == 1) {
			path.path[i].state = E_STATE_CONFIRMED;
			x = path.path[i].x;
			y = path.path[i].y;
		
			if (delta_x == 1) {
				path.path[i].next_direction = E_ACTION_RIGTH;
			} else if (delta_x == -1) {
				path.path[i].next_direction = E_ACTION_LEFT;
			} else if (delta_y == 1) {
				path.path[i].next_direction = E_ACTION_UP;
			} else if (delta_y == -1) {
				path.path[i].next_direction = E_ACTION_DOWN;
			}
		}
	}
	

	
	for (i = 0; i < path.length; i++) {
		if (path.path[i].state == E_STATE_CONFIRMED) {
			addCellToPath(path.path[i], &returnValue);
		}
	}
	printPath(returnValue);
	printf("\n");
	return returnValue;
}
st_Cell getNearElementToDestination(st_Cell_Queue *queue) {

	st_Cell returnValue;
	double max_distance = 0;
	bool first_computed_distance = true;
	int near_index = 0;
	int i = 0;

	for (i = 0; i < queue->length && queue->length < MAX_CELLS; ++i) {
		
		if (queue->queue[i].cell.state == E_STATE_VISITED) {
						
			if (first_computed_distance || queue->queue[i].distance_to_dest < max_distance) {
				max_distance = queue->queue[i].distance_to_dest;
				near_index = i;
				first_computed_distance = false;
			}
			
		}
	}

	if (!first_computed_distance) {
	
		returnValue = queue->queue[near_index].cell;
	
		// Reset Position
		queue->queue[near_index].cell.x = 0;
		queue->queue[near_index].cell.y = 0;
		queue->queue[near_index].cell.state = E_STATE_NOT_CREATED;
		queue->queue[near_index].distance_to_dest = 0;
	
		// Move all the queue
		for (i = near_index; i < queue->length - 1; ++i) {
			queue->queue[i] = queue->queue[i + 1];
		}
	
		queue->length--;
	}

	return returnValue;	
}

void printQueue(const st_Cell_Queue queue) {
	int i = 0;
	for (i = 0; i < queue.length; i++) {
		printf("%d,%d ", queue.queue[i].cell.x, queue.queue[i].cell.y);
	}
	printf(" - Length = %d\n", queue.length);
}

void addCellToQueue(const st_Cell cell, const st_Cell destination, st_Cell_Queue *queue) {
	if (queue->length < MAX_CELLS) {
		queue->queue[queue->length].distance_to_dest = get_distance(destination, cell);
		queue->queue[queue->length].cell = cell;
		queue->length++;
	}

}

void printPath(const st_Cell_Path path) {
	int i = 0;
	for (i = 0; i < path.length; i++) {
		printf("%d,%d (", path.path[i].x, path.path[i].y);
		
		// Print State 
		if (path.path[i].state == E_STATE_VISITED) {
			printf("V-");
		} else if (path.path[i].state == E_STATE_UNVISITED) {
			printf("U-");
		} else if (path.path[i].state == E_STATE_UNABLE) {
			printf("D-");
		} else if (path.path[i].state == E_STATE_CONFIRMED) {
			printf("C-");
		}
		
		// Print Direction
		if (path.path[i].next_direction == E_ACTION_RIGTH) {
			printf("Right)  ");
		} else if (path.path[i].next_direction == E_ACTION_LEFT) {
			printf("Left)  ");
		} else if (path.path[i].next_direction == E_ACTION_UP) {
			printf("Up)  ");
		} else if (path.path[i].next_direction == E_ACTION_DOWN) {
			printf("Down)  ");
		}
	}
	printf("\n");
}

void addCellToPath(const st_Cell cell, st_Cell_Path *path) {
	if (path->length < MAX_CELLS) {
			path->path[path->length] = cell;
			path->length++;
	}

}

bool isCellAvailable(const st_Cell cell) {
	
	bool returnValue = false;

	if (cell.x < MAX_ROWS && cell.y < MAX_COLS) {
		returnValue = !(grid[cell.x][cell.y].state == E_STATE_VISITED || grid[cell.x][cell.y].state == E_STATE_UNABLE);
	}
	return returnValue;
}

bool markCellAsVisited(const st_Cell cell) { 

	bool returnValue = false;

	if (cell.x < MAX_ROWS && cell.y < MAX_COLS) {
		grid[cell.x][cell.y].state = E_STATE_VISITED;
		returnValue = true;
	}

	return returnValue;
}

void fillGrid() {

	int i = 0;
	int j = 0;
	for (i = 0; i < MAX_ROWS; ++i) {
		for (j = 0; j < MAX_COLS; ++j) {

			grid[i][j].x = i;
			grid[i][j].y = j;
			grid[i][j].state = E_STATE_UNVISITED;
		}
	}
}

void printGrid() {

	int i = 0;
	int j = 0;
	for (i = MAX_ROWS - 1; 0 <= i; --i) {
		for (j = 0; j < MAX_COLS; ++j) {
			printf("%d,%d(", grid[j][i].x, grid[j][i].y);
			if (grid[j][i].state == E_STATE_VISITED) {
				printf("V) ");
			} else if (grid[j][i].state == E_STATE_UNVISITED) {
				printf("U) ");
			} else if (grid[j][i].state == E_STATE_UNABLE) {
				printf("D) ");
			} 
		}
		printf("\n");
	}
}

st_Cell getNextMovement(int x, int y, enum e_Action movement) {

	st_Cell output;

	output.x = x;
	output.y = y;

	switch (movement) {
		case E_ACTION_RIGTH:
			if (checkXLimits(output.x + 1)) {
				output.x += 1;
			}
			break;
		case E_ACTION_UP:
			if (checkYLimits(output.y + 1)) {
				output.y += 1;
			}
			break;
		case E_ACTION_LEFT:
			if (checkXLimits(output.x - 1)) {
				output.x -= 1;
			}
			break;
		case E_ACTION_DOWN:
			if (checkYLimits(output.y - 1)) {
				output.y -= 1;
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

double get_distance(const st_Cell point1, const st_Cell point2) {

 	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}





