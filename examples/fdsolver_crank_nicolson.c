#include "fdsolver.h"

int main(void)
{
    FDSolverParams params = {
        .alpha = 0.01,
        .L = 1.0,
        .T0 = 100.0,
        .T_left = 30,
        .T_right = 30,
        .nx = 10,
        .nt = 100,
        .dx = 0.1,
        .dt = 0.1,
        .bc_type = DIRICHLET,
        .solver_type = CRANK_NICOLSON};
    printf("11111\n");
    FDResult *result = fd_solver(&params);
    if (result == NULL)
    {
        fprintf(stderr, "Failed to solve the finite difference problem\n");
        return EXIT_FAILURE;
    }
    print_fd_result(result);
    save_fd_result(result, "../data/fd_crank_nicolson_result.txt");
    free_fd_result(result);
    return 1;
}