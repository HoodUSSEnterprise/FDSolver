#ifndef THOMAS_SOLVE_H
#define THOMAS_SOLVE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

// Thomas algorithm for tridiagonal system
/// @param n Size of the system
/// @param a Sub-diagonal coefficients (length n-1)
/// @param b Main diagonal coefficients (length n)
/// @param c Super-diagonal coefficients (length n-1)
/// @param d Right-hand side vector (length n)
/// @param x Solution vector (length n)
/*
|b[0] c[0] 0    ... 0     |   |x[0]  |   |d[0]  |
|a[0] b[1] c[1] ... 0     | * |x[1]  | = |d[1]  |
|0    a[1] b[2] ... 0     |   |x[2]  |   |d[2]  |
|...  ...  ...  ... ...   |   |...   |   |...   |
|0    0    0    ... b[n-1]|   |x[n-1]|   |d[n-1]|
*/
// Returns 0 on success, -1 on failure
int thomas_solve(int n, const double *a, const double *b, const double *c, const double *d, double *x);

#endif // THOMAS_SOLVE_H