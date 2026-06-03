cmake_minimum_required(VERSION 3.15)

project(fdsolver C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(fdsolver STATIC
    src/fdsolver.c
    src/init_grid_and_initial.c
    src/solve_explicit.c
    src/solve_implicit.c
    src/solve_crank_nicolson.c
    src/thomas_solve.c
)

target_include_directories(fdsolver PUBLIC include)

add_executable(fdsolver_explicit_example
    examples/fdsolver_explicit_example.c
)
target_link_libraries(fdsolver_explicit_example fdsolver)

add_executable(fdsolver_implicit_example
    examples/fdsolver_implicit_example.c
)
target_link_libraries(fdsolver_implicit_example fdsolver)

add_executable(fdsolver_crank_nicolson_example
    examples/fdsolver_crank_nicolson.c
)
target_link_libraries(fdsolver_crank_nicolson_example fdsolver)