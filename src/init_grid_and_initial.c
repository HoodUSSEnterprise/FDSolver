#include "init_grid_and_initial.h"

// Initialize grid (x,t) and set initial condition at t=0
void init_grid_and_initial(FDResult *result, const FDSolverParams *params)
{
    for (int i = 0; i < params->nx; ++i)
    {
        result->x[i] = i * params->dx;
    }
    for (int n = 0; n < params->nt; ++n)
    {
        result->t[n] = n * params->dt;
    }
    for (int i = 0; i < params->nx * params->nt; ++i)
    {
        result->T[i] = params->T0;
    }
    if (params->bc_type == DIRICHLET)
    {
        if (params->nx >= 1)
        {
            result->T[0] = params->T_left;
        }
        if (params->nx >= 2)
        {
            result->T[params->nx - 1] = params->T_right;
        }
    }
}
