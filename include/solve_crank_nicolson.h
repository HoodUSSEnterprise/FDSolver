#ifndef SOLVE_CRANK_NICOLSON_H
#define SOLVE_CRANK_NICOLSON_H

#include "fdsolve.h"
#include "init_grid_and_initial.h"
#include "thomas_solve.h"

void solve_crank_nicolson(FDResult *result, const FDSolverParams *params);

#endif // SOLVE_CRANK_NICOLSON_H