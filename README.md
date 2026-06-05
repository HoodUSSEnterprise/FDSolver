# FDSolver - A Finite Difference Solver for 1D Heat Transfer

A lightweight C implementation of finite difference methods for solving
the 1D unsteady heat conduction equation.

## Features

- **Three time schemes**: Explicit, Implicit (Backward Euler), Crank-Nicolson
- **Boundary conditions**: Dirichlet
- **Customizable source term and initial condition** via function pointers
- **Thomas algorithm** for efficient tridiagonal system solving
- **Visualization scripts** for result analysis (Python/Matplotlib)

## Equation

\[
\frac{\partial T}{\partial t} = \alpha \frac{\partial^2 T}{\partial x^2}
\]
