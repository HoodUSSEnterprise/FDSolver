#include "solve_implicit.h"

void solve_implicit(FDResult *result, const FDSolverParams *params)
{
    // Validate input parameters
    if (result == NULL || params == NULL)
    {
        fprintf(stderr, "Invalid input to solve_implicit\n");
        return;
    }
    if (result->T == NULL || result->x == NULL || result->t == NULL)
    {
        fprintf(stderr, "Result structure is not properly initialized\n");
        return;
    }
    if (params->nx <= 0 || params->nt <= 0 || params->dx <= 0 || params->dt <= 0)
    {
        fprintf(stderr, "Invalid parameters for implicit solver\n");
        return;
    }
    // Initialize spatial and time points
    init_grid_and_initial(result, params);
    // Extract parameters for easier access
    int nx = params->nx;
    int nt = params->nt;
    double dx = params->dx;
    double dt = params->dt;
    double alpha = params->alpha;
    double r = alpha * dt / (dx * dx);
    double *T = result->T;

    if (nx == 1)
    {
        return;
    }

    int m = nx - 2; // interior unknowns
    double *a = NULL, *b = NULL, *c = NULL, *d = NULL, *sol = NULL;
    if (m > 0)
    {
        a = (double *)malloc((m - 1) * sizeof(double));
        if (a == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        b = (double *)malloc(m * sizeof(double));
        if (b == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            free(a);
            return;
        }
        c = (double *)malloc((m - 1) * sizeof(double));
        if (c == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            free(a);
            free(b);
            return;
        }
        d = (double *)malloc(m * sizeof(double));
        if (d == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            free(a);
            free(b);
            free(c);
            return;
        }
        sol = (double *)malloc(m * sizeof(double));
        if (sol == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            free(a);
            free(b);
            free(c);
            free(d);
            return;
        }
    }

    for (int n = 0; n < nt; ++n)
    {
        double left_bc = 0, right_bc = 0;
        if (params->bc_type == DIRICHLET)
        {
            left_bc = params->T_left;
            right_bc = params->T_right;
        }

        if (m <= 0)
        {
            T[n * nx + 0] = left_bc;
            T[n * nx + nx - 1] = right_bc;
            continue;
        }

        for (int i = 0; i < m; ++i)
        {
            b[i] = 1.0 + 2.0 * r;
            if (i < m - 1)
            {
                a[i] = -r;
                c[i] = -r;
            }
            d[i] = T[n * nx + i + 1];
        }
        d[0] += r * left_bc;
        d[m - 1] += r * right_bc;

        thomas_solve(m, a, b, c, d, sol);

        if (n == nt - 1)
        {
            continue;
        }
        for (int i = 0; i < m; ++i)
        {
            T[(n + 1) * nx + i + 1] = sol[i];
        }
        T[(n + 1) * nx + 0] = left_bc;
        T[(n + 1) * nx + nx - 1] = right_bc;
    }
    // Free allocated memory for the tridiagonal solver
    free(a);
    free(b);
    free(c);
    free(d);
    free(sol);
}
