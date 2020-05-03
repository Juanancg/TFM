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
	E_STATE_VISITED
};

struct Cell {
	int x;
	int y;
	enum e_State state;
};
typedef struct Cell st_Cell;

struct Cell_Queue {
	struct Cell queue[MAX_CELLS];
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
st_Cell getNearElementToDestination(const st_Cell destination, st_Cell_Queue *queue);
void printQueue(const st_Cell_Queue queue);
void addCellToQueue(const st_Cell cell, st_Cell_Queue *queue);
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
	
	fillGrid();
	
	st_Cell initial_cell = {0, 0, E_STATE_VISITED};
	st_Cell destination_cell = {5, 7, E_STATE_UNVISITED};
	
	markCellAsVisited(initial_cell);
	
	st_Cell_Queue path;
	st_Cell_Queue queue;
	path.length = 0;
	queue.length = 0;
	
	addCellToQueue(initial_cell, &queue);
	
	while (queue.length != 0) {
		
		st_Cell temp_cell;
		
		temp_cell = getNearElementToDestination(destination_cell, &queue);
		
		addCellToQueue(temp_cell, &path);
		
		if (temp_cell.x == destination_cell.x && temp_cell.y == destination_cell.y) {
			printf("Success!!!");
			printQueue(path);
			return 0;
		}
		
		int i = 0;
		
		// Get the possibles next cells from the current one
		for (i = 0; i < (int)E_MAX_ACTION; ++i) {
			
			enum e_Action next_action = (enum e_Action)i;
			
			st_Cell next_cell = getNextMovement(temp_cell.x, temp_cell.y, next_action);
			
			if (isCellAvailable(next_cell)) {
				markCellAsVisited(next_cell);
				next_cell.state = E_STATE_VISITED;
				addCellToQueue(next_cell, &queue);
			}
		}
		
	}
	

	
	printf("Bye Planning!\n");
	return 0;
}


/********************************************************/
/*				FUNCTIONS DEFINITIONS					*/
/********************************************************/
st_Cell getNearElementToDestination(const st_Cell destination, st_Cell_Queue *queue) {
	
	st_Cell returnValue;
	double distance = 0;
	double temp_distance = 0;
	bool first_computed_distance = true;
	int near_index = 0;
	int i = 0;
	
	for (i = 0; i < queue->length && queue->length < MAX_CELLS; ++i) {
		
		if (queue->queue[i].state == E_STATE_VISITED) {
			
			temp_distance = get_distance(destination, queue->queue[i]);
			
			if (first_computed_distance || temp_distance < distance) {
				distance = temp_distance;
				near_index = i;
				first_computed_distance = false;
			}
			
		}
	}
	
	returnValue = queue->queue[near_index];
	queue->queue[near_index].x = 0;
	queue->queue[near_index].y = 0;
	queue->queue[near_index].state = E_STATE_NOT_CREATED;
	
	queue->length--;
	
	return returnValue;	
}

void printQueue(const st_Cell_Queue queue) {
	int i = 0;
	for (i = 0; i < queue.length; i++) {
		printf("%d,%d ", queue.queue[i].x, queue.queue[i].y);
	}
	printf("\n");
}

void addCellToQueue(const st_Cell cell, st_Cell_Queue *queue) {
	if (queue->length < MAX_CELLS) {
			queue->queue[queue->length] = cell;
			queue->length++;
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





