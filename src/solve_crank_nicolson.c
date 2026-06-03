#include "solve_crank_nicolson.h"

void solve_crank_nicolson(FDResult *result, const FDSolverParams *params)
{
    // Validate input parameters
    if (result == NULL || params == NULL)
    {
        fprintf(stderr, "Invalid input to solve_crank_nicolson\n");
        return;
    }
    if (result->T == NULL || result->x == NULL || result->t == NULL)
    {
        fprintf(stderr, "Result structure is not properly initialized\n");
        return;
    }
    if (params->nx <= 0 || params->nt <= 0 || params->dx <= 0 || params->dt <= 0)
    {
        fprintf(stderr, "Invalid parameters for crank nicolson solver\n");
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
    int m = nx - 2;
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

    for (int n = 0; n < nt - 1; ++n)
    {
        double left_bc, right_bc;
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
            b[i] = 1.0 + r;
            if (i < m - 1)
            {
                a[i] = -r / 2.0;
                c[i] = -r / 2.0;
            }
            int gi = i + 1;
            double tm = (gi - 1 >= 0) ? T[n * nx + gi - 1] : left_bc;
            double tp = (gi + 1 < nx) ? T[n * nx + gi + 1] : right_bc;
            d[i] = (r / 2.0) * tm + (1.0 - r) * T[n * nx + gi] + (r / 2.0) * tp;
        }

        thomas_solve(m, a, b, c, d, sol);
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