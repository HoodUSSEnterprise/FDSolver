#include "solve_explicit.h"

// our T is stored in a 1D array, so we need to calculate the index of T[i][j] in the 1D array
// i means time index, j means spatial index
/// @param indext Time index
/// @param indexx Spatial index
/// @param T 1D array storing the temperature values
/// @param nx Number of spatial steps (used to calculate the index in the 1D array)
static double get_Tvalue(int indext, int indexx, double *T, int nx)
{
    if (T == NULL || indext < 0 || indexx < 0)
    {
        fprintf(stderr, "Invalid parameters\n");
        return 0.0;
    }
    return T[indext * nx + indexx];
}

void solve_explicit(FDResult *result, const FDSolverParams *params)
{
    // Validate input parameters
    if (result == NULL || params == NULL)
    {
        fprintf(stderr, "Invalid input to solve_explicit\n");
        return;
    }
    if (result->T == NULL || result->x == NULL || result->t == NULL)
    {
        fprintf(stderr, "Result structure is not properly initialized\n");
        return;
    }
    if (params->nx <= 0 || params->nt <= 0 || params->dx <= 0 || params->dt <= 0)
    {
        fprintf(stderr, "Invalid parameters for explicit solver\n");
        return;
    }
    // Initialize spatial and time points and set initial condition at t=0
    init_grid_and_initial(result, params);
    // Extract parameters for easier access
    int nx = params->nx;
    int nt = params->nt;
    double dx = params->dx;
    double dt = params->dt;
    double alpha = params->alpha;
    double r = alpha * dt / (dx * dx);
    if (r >= 0.5)
    {
        fprintf(stdin, "Warning: The explicit method may be unstable (r = %.2f >= 0.5)\n", r);
    }
    double *T = result->T;

    if (nx == 1)
    {
        return;
    }
    for (int n = 0; n < nt; ++n)
    {
        if (params->bc_type == DIRICHLET)
        {
            T[n * nx + 0] = params->T_left;
            T[n * nx + nx - 1] = params->T_right;
        }
        if (n == nt - 1)
        {
            continue; // No need to calculate the next time step for the last time step
        }
        for (int i = 1; i < nx - 1; ++i)
        {
            T[(n + 1) * nx + i] = get_Tvalue(n, i, T, nx) + r * (get_Tvalue(n, i + 1, T, nx) - 2.0 * get_Tvalue(n, i, T, nx) + get_Tvalue(n, i - 1, T, nx));
        }
    }
}
