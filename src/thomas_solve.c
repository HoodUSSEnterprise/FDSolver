#include "thomas_solve.h"

// Returns 0 on success, -1 on failure
int thomas_solve(int n, const double *a, const double *b, const double *c, const double *d, double *x)
{
    if (a == NULL || b == NULL || c == NULL || d == NULL || x == NULL || n <= 0)
    {
        fprintf(stderr, "Invalid parameters\n");
        return -1;
    }
    double *cp = (double *)malloc(n * sizeof(double));
    if (cp == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    double *dp = (double *)malloc(n * sizeof(double));
    if (dp == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(cp);
        return -1;
    }
    cp[0] = c[0] / b[0];
    dp[0] = d[0] / b[0];
    for (int i = 1; i < n; ++i)
    {
        double denom = b[i] - a[i - 1] * cp[i - 1];
        if (i < n - 1)
        {
            cp[i] = c[i] / denom;
        }
        dp[i] = (d[i] - a[i - 1] * dp[i - 1]) / denom;
    }
    x[n - 1] = dp[n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        x[i] = dp[i] - cp[i] * x[i + 1];
    }
    free(cp);
    free(dp);
    return 0;
}
