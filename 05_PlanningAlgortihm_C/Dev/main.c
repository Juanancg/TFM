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

struct st_Cell_Queue {
	struct Cell queue[MAX_CELLS];
	unsigned int length;
};


st_Cell grid[MAX_COLS][MAX_ROWS];


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
	
	st_Cell celda, celda_nueva;
	enum e_Action accion;
	accion = E_ACTION_LEFT;
	celda.x = 0;
	celda.state = E_STATE_VISITED;
	
	printf("Hello Planning!\n");
	if (celda.state == E_STATE_VISITED) {
		printf("Estado VISITED\n");
	}
	
	celda_nueva = getNextMovement(celda.x, celda.y, accion);

	
	printf("%d, %d\n", celda_nueva.x, celda_nueva.y);
	
	fillGrid();
	printGrid();
	printf("Bye Planning!\n");
	return 0;
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
				printf("E_ACTION_RIGTH\n");
				output.x += 1;
			}
			break;
		case E_ACTION_UP:
			if (checkYLimits(output.y + 1)) {
				printf("E_ACTION_UP\n");
				output.y += 1;
			}
			break;
		case E_ACTION_LEFT:
			if (checkXLimits(output.x - 1)) {
				printf("E_ACTION_LEFT\n");
				output.x -= 1;
			}
			break;
		case E_ACTION_DOWN:
			if (checkYLimits(output.y - 1)) {
				printf("E_ACTION_DOWN\n");
				output.y -= 1;
			}
			break;
		default:
			printf("default\n");
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





