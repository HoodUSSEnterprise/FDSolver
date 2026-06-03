#ifndef SOLVE_IMPLICIT_H
#define SOLVE_IMPLICIT_H

#include "fdsolve.h"
#include "init_grid_and_initial.h"
#include "thomas_solve.h"

void solve_implicit(FDResult *result, const FDSolverParams *params);

#endif // SOLVE_IMPLICIT_H