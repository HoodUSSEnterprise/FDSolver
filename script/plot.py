import numpy as np
import matplotlib.pyplot as plt


def extract_fd_result(filename):
    # Load data from file
    with open(filename, "r") as file:
        lines = file.readlines()
    # Extract parameters
    params = {}
    for line in lines:
        if line.startswith("nx ="):
            params["nx"] = int(line.split("=")[1].strip())
        elif line.startswith("nt ="):
            params["nt"] = int(line.split("=")[1].strip())
        elif line.startswith("dx ="):
            params["dx"] = float(line.split("=")[1].strip())
        elif line.startswith("dt ="):
            params["dt"] = float(line.split("=")[1].strip())
    # Extract spatial points
    x_index = lines.index("x:\n") + 1
    x_line = lines[x_index]
    x = np.array([float(val) for val in x_line.split()])
    # Extract time points
    t_index = lines.index("t:\n") + 1
    t_line = lines[t_index].strip()
    t = np.array([float(val) for val in t_line.split()])
    # Extract temperature distribution
    T_index = lines.index("Temperature distribution (T):\n") + 1
    T = np.zeros((params["nt"], params["nx"]))
    for i in range(params["nt"]):
        T_line = lines[T_index + i].strip()
        T[i, :] = np.array([float(val) for val in T_line.split()])
    return params, x, t, T


def plot_fd_result(params, x, t, T):
    # Create a contour plot of the temperature distribution
    plt.figure(figsize=(10, 6))
    X, T_grid = np.meshgrid(x, t)
    plt.contourf(X, T_grid, T, levels=50, cmap="hot")
    plt.colorbar(label="Temperature (T)")
    plt.title("Temperature Distribution Over Time and Space")
    plt.xlabel("Spatial Position (x)")
    plt.ylabel("Time (t)")
    plt.savefig("../figures/fd_result_plot.png")
    plt.show()


def plot_specific_time(params, x, t, T, time_index):
    # Plot temperature distribution at a specific time
    plt.figure(figsize=(10, 6))
    plt.plot(x, T[time_index, :], marker="o")
    plt.title(f"Temperature Distribution at t = {t[time_index]:.2f} s")
    plt.xlabel("Spatial Position (x)")
    plt.ylabel("Temperature (T)")
    plt.grid()
    plt.savefig(f"../figures/fd_result_time_{time_index}.png")
    plt.show()


def plot_specific_position(params, x, t, T, position_index):
    # Plot temperature distribution at a specific position
    plt.figure(figsize=(10, 6))
    plt.plot(t, T[:, position_index], marker="o")
    plt.title(f"Temperature Distribution at x = {x[position_index]:.2f} m")
    plt.xlabel("Time (t)")
    plt.ylabel("Temperature (T)")
    plt.grid()
    plt.savefig(f"../figures/fd_result_position_{position_index}.png")
    plt.show()


if __name__ == "__main__":
    filename = "../data/fd_explicit_result.txt"
    params, x, t, T = extract_fd_result(filename)
    plot_fd_result(params, x, t, T)
    plot_specific_time(params, x, t, T, time_index=5)
    plot_specific_position(params, x, t, T, position_index=5)
    filename = "../data/fd_implicit_result.txt"
    params, x, t, T = extract_fd_result(filename)
    plot_fd_result(params, x, t, T)
    plot_specific_time(params, x, t, T, time_index=5)
    plot_specific_position(params, x, t, T, position_index=5)
    filename = "../data/fd_crank_nicolson_result.txt"
    params, x, t, T = extract_fd_result(filename)
    plot_fd_result(params, x, t, T)
    plot_specific_time(params, x, t, T, time_index=5)
    plot_specific_position(params, x, t, T, position_index=5)
