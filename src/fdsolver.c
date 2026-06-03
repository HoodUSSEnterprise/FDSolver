#include "fdsolve.h"
#include "solve_explicit.h"
#include "solve_implicit.h"
#include "solve_crank_nicolson.h"
#include "init_grid_and_initial.h"

FDResult *fd_solver(const FDSolverParams *params)
{
    // Allocate memory for the result
    FDResult *result = (FDResult *)malloc(sizeof(FDResult));
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    // Initialize the result structure with parameters
    result->nx = params->nx;
    result->nt = params->nt;
    result->dx = params->dx;
    result->dt = params->dt;
    result->x = (double *)malloc(params->nx * sizeof(double));
    if (result->x == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(result);
        return NULL;
    }
    result->t = (double *)malloc(params->nt * sizeof(double));
    if (result->t == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(result->x);
        free(result);
        return NULL;
    }
    result->T = (double *)malloc(params->nx * params->nt * sizeof(double));
    if (result->T == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(result->x);
        free(result->t);
        free(result);
        return NULL;
    }
    switch (params->solver_type)
    {
    case EXPLICIT:
        solve_explicit(result, params);
        break;
    case IMPLICIT:
        solve_implicit(result, params);
        break;
    case CRANK_NICOLSON:
        solve_crank_nicolson(result, params);
        break;
    default:
        break;
    }
    return result;
}

void free_fd_result(FDResult *result)
{
    if (result != NULL)
    {
        free(result->x);
        free(result->t);
        free(result->T);
        free(result);
    }
}

void print_fd_result(const FDResult *result)
{
    putchar('\n');
    puts("Results:");
    printf("Number of spatial points (nx):%d\n", result->nx);
    printf("Number of time steps (nt):%d\n", result->nt);
    printf("Time steps (t):%.2f\n", result->dt);
    printf("Spatial steps (x):%.2f\n", result->dx);
    puts("Temperature distribution (T):");
    for (int i = 0; i < result->nt; i++)
    {
        for (int j = 0; j < result->nx; j++)
        {
            printf("%.2f ", result->T[i * result->nx + j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void save_fd_result(const FDResult *result, const char *filename)
{
    // write the results to a file in order to draw the graph with python matplotlib
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file for writing\n");
        return;
    }
    // Write header
    fprintf(file, "nx = %d\n", result->nx);
    fprintf(file, "nt = %d\n", result->nt);
    fprintf(file, "dx = %.2f\n", result->dx);
    fprintf(file, "dt = %.2f\n", result->dt);
    // Write spatial points
    fprintf(file, "x:\n");
    for (int i = 0; i < result->nx; i++)
    {
        fprintf(file, "%.2f ", result->x[i]);
    }
    // Write time points
    fprintf(file, "\nt:\n");
    for (int i = 0; i < result->nt; i++)
    {
        fprintf(file, "%.2f ", result->t[i]);
    }
    // Write temperature distribution
    fprintf(file, "\nTemperature distribution (T):\n");
    for (int i = 0; i < result->nt; i++)
    {
        for (int j = 0; j < result->nx; j++)
        {
            fprintf(file, "%.2f ", result->T[i * result->nx + j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}