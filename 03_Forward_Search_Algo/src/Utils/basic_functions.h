#ifndef BASIC_FUNCTIONS_H_
#define BASIC_FUNCTIONS_H_

#include "src/Components/Grid.h"

xState move(const xState x_state, Action u);
bool checkXLimits(int x);
bool checkYLimits(int y);
double get_distance(const xState point1, const xState point2);

#endif /* BASIC_FUNCTIONS_H_ */
