#ifndef INIT_GRID_AND_INITIAL_H
#define INIT_GRID_AND_INITIAL_H

#include "fdsolve.h"

// Initialize grid (x,t) and set initial condition at t=0
void init_grid_and_initial(FDResult *result, const FDSolverParams *params);

#endif // INIT_GRID_AND_INITIAL_H