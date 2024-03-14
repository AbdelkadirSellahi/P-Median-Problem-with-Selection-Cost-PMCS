# P-Median Problem with Selection Cost (PMCS)

This repository contains C++ code to solve the p-median problem with selection cost (PMCS) using two different approaches:

1. **Simulated Annealing Algorithm**

2. **Lower Bound Calculation Algorithm**


## Project Configuration

| Configuration Item         | Options           |
|-----------------------------|-------------------|
| Use of Emojis               | Disabled          |
| Programming Paradigm        | Procedural        |
| Language                    | C++               |
| Project Type                | General Purpose   |
| Comment Style               | Descriptive       |
| Code Structure              | Modular           |
| Error Handling Strategy     | Basic             |

These configurations guide the development and contribution process for this project, ensuring consistency and clarity in its development.

## Problem Description

The p-median problem is a classic problem in `combinatorial optimization` where the objective is to select a subset of vertices from a graph in such a way as to minimize the total cost of assignment and selection. In the PMCS variant of this problem, each vertex is associated with both a selection cost and assignment cost. The goal is to select `p` vertices while minimizing both costs.
  
## Repository Structure

- `Instance/`: Contains different PMCS instances.
  - `PMCS-200.txt`
  - `PMCS-300.txt`
  - `PMCS-400.txt`
  - `PMCS-800.txt`
  - `PMCS-1000.txt`
  - `PMCS-12000.txt`

- `Result/`: Contains the results for each instance in the `Instance/` folder.
  - `Result-200.txt`
  - `Result-300.txt`
  - `Result-400.txt`
  - `Result-800.txt`
  - `Result-1000.txt`
  - `Result-12000.txt`

- `Source-Code-SA/`: Contains the C++ code for the Simulated Annealing algorithm.
  - `solution.cpp`

- `Lower-Bound/`: Contains the C++ code for the Lower Bound calculation algorithm.
  - `Solution.cpp`

## Instance Description

Each instance file in the `Instance/` folder represents a specific PMCS problem instance. These files contain the following information:
- Number of vertices
- Selection costs for each vertex
- Assignment costs for each arc (connection between vertices)

## Result Description

Each result file in the `Result/` folder corresponds to a solution obtained for a particular PMCS instance. These files contain the following information:
- Selected vertices (centers)
- Total cost of the solution

## Simulated Annealing Algorithm

The Simulated Annealing Algorithm is a stochastic optimization technique inspired by the process of annealing in metallurgy. It is particularly useful for solving combinatorial optimization problems, such as the PMCS problem.

### Algorithm Steps:

1. **Initialization**: Start with an initial solution, often generated randomly.

2. **Temperature Initialization**: Set the initial temperature (`T`) and define parameters such as the cooling rate (`alpha`) and maximum number of iterations.

3. **Main Loop**:
   - Perform transitions between solutions by perturbing the current solution. This can involve swapping vertices or making small modifications to the selected vertices.
   - Evaluate the quality of the new solution using an objective function, which calculates the total cost of the solution.
   - Accept the new solution with a probability based on the change in cost and the current temperature. The probability of accepting worse solutions decreases as the temperature decreases.
   - Update the current solution if the new solution is accepted.

4. **Cooling Schedule**: Reduce the temperature according to a cooling schedule (e.g., geometric or exponential cooling) after a certain number of iterations.

5. **Termination**: Repeat the main loop until a termination condition is met, such as reaching a maximum number of iterations or a predefined temperature threshold.

## Lower Bound Calculation Algorithm

The Lower Bound Calculation Algorithm provides an estimate of the lower bound for the total cost of the PMCS problem instance. It does not necessarily provide an optimal solution but serves as a reference point for evaluating the quality of heuristic or exact algorithms.

### Algorithm Steps:

1. **Sorting Locations**: Sort the locations (vertices) based on their selection costs in ascending order.

2. **Total Selection Cost**: Calculate the total selection cost by summing the costs of the first `p` locations (vertices).

3. **Total Assignment Cost**: Compute the total assignment cost for each non-selected vertex by finding the minimum cost among the arcs connected to each vertex. Sort these costs in ascending order.

4. **Lower Bound Calculation**: Compute the lower bound of the total cost as the sum of the total selection cost and the total assignment cost for the remaining vertices.

## Contributing

We welcome contributions! If you're interested in improving the PMCS Solver or have suggestions, please feel free to fork the repository, make your changes, and submit a pull request.

## Authors
- [**ABDELKADIR Sellahi**](https://github.com/AbdelkadirSellahi)
