#ifndef BASIC_FUNCTIONS_H_
#define BASIC_FUNCTIONS_H_

#include "Components/Grid.h"

xState move(const xState x_state, Action u);
bool checkXLimits(int x);
bool checkYLimits(int y);


#endif /* BASIC_FUNCTIONS_H_ */
