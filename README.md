# Algorithm Design - Project 2

## p1

The graph is read from the file and the adjacencies are kept in an adjacency list. At the same time, an adjacency list is also created for the graph if it was undirected.

The weakly connected components of the graph are found by doing a DFS using the undirected adjacency list.

For each component, it is checked whether it contains a cycle or not. If it does not contain a cycle, the edges needed for this component are n (number of nodes in the component) - 1. If it contains a cycle, n edges are needed.

The total number of edges is the sum of the number of edges needed for each component.

## p2

## p3

The graph is read from the file, the adjacencies being kept in an adjacency matrix.

The minimum cost cycle passing through each node is calculated. This is done by the modified Floyd-Warshall algorithm. The distance from a node to itself is infinite instead of 0.

The cost of the cycles through each node is iterated through and the lowest cost is chosen."