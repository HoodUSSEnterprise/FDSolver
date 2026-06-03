#ifndef FDSOLVER_H
#define FDSOLVER_H

#include "fdsolve.h"
#include "solve_explicit.h"
#include "solve_implicit.h"
#include "solve_crank_nicolson.h"
#include "init_grid_and_initial.h"
#include "thomas_solve.h"

FDResult *fd_solver(const FDSolverParams *params);

void free_fd_result(FDResult *result); // free memory allocated for FDResult

void print_fd_result(const FDResult *result); // print the results to console

void save_fd_result(const FDResult *result, const char *filename); // save the results to a file in order to draw the graph with python matplotlib

#endif // FDSOLVER_H