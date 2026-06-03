#ifndef SOLVE_EXPLICIT_H
#define SOLVE_EXPLICIT_H

#include "fdsolve.h"
#include "init_grid_and_initial.h"

void solve_explicit(FDResult *result, const FDSolverParams *params);

#endif // SOLVE_EXPLICIT_H