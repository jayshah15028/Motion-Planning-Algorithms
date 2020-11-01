# Motion-Planning-Algorithms

There are plenty of motion planning algorithms developed for finding a feasible path between 2 points in a given map. They are categorized as:
Grid-based Search Algorithms - Dijkstra, A*
Interval-based Search Algorithms
Geometric Algorithms - Visibility Graph, Cell Decomposition, Minkowski Sum
Artificial Potential Field Algorithms
Sampling Based Algorithms


# A*
A* is a grid-based approach that is essentially a variation of Dijkstra with reduced computation and faster search. It computes the path length from the start node to the current node. Further, it computes the distance from each neighbor of the current node to the goal node and sums it with the path length computed previously. This serves as a cost function which decides the next node and the algorithms goes on until the goal node is encountered. 

The implementation of A* is done with 8 neighbors, which means the object can turn at 90<sup>0</sup> and 45<sup>0</sup>. Random number of randomly generated obstacles are placed on the map and start and goal nodes are also randomly selected. The algorithm returns a plot marking all the obstacles and a path from start to finish. The scripts are written in both, MATLAB and Python. 
