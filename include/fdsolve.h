#ifndef FDSOLVE_H
#define FDSOLVE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef DEBUG
#define DEBUG_LOG(fmt, ...) \
    printf("[FILE:%s, FUNCTION:%s, LINE:%d] " fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_LOG(fmt, ...) ((void)0)
#endif

typedef enum BoundaryConditionType
{
    DIRICHLET,
    NEUMANN,
    ROBIN
} BoundaryConditionType;

typedef enum FDSolverType
{
    EXPLICIT,
    IMPLICIT,
    CRANK_NICOLSON
} FDSolverType;

typedef struct FDSolverParams
{
    double alpha;                  // thermal diffusivity
    double L;                      // length of the rod
    double T0;                     // initial temperature
    double T_left;                 // boundary condition at x=0
    double T_right;                // boundary condition at x=L
    int nx;                        // number of spatial points
    int nt;                        // number of time steps
    double dx;                     // spatial step size
    double dt;                     // time step size
    BoundaryConditionType bc_type; // type of boundary condition
    FDSolverType solver_type;      // type of finite difference solver
} FDSolverParams;

typedef struct FDResult
{
    double *T;
    double *x;
    double *t;
    int nx;
    int nt;
    double dx;
    double dt;
} FDResult;

#endif // FDSOLVE_H