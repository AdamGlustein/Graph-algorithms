# (Almost all) Useful Graph Algorithms

To learn more about graph theory, I decided to implement a wide range of algorithms myself. This repository contains the code for these algorithms.

In C++ under `graphs.cpp` we have:
  1. Depth-first search (DFS)
  2. Breadth-first search (BFS)
  3. Djikstra's shortest path algorithm
  4. Cycle detection using back-edges
  5. Topological sorting of directed-acyclic graphs (DAGs)
  6. Prim's minimum spanning tree (MST) algorithm
  7. Hierholzer's Eulerian path/circuit algorithm
  8. Bellman-Ford algorithm for the shortest path in a (possibly) negatively weighted graph 
  9. Floyd-Warshall all-pairs shortest path algorithm
  
In Python under `graphs.py` we have:
  1. Edmonds-Karp implementation of the Ford-Fulkeron max-flow algorithm
  2. Tarjan's algorithm for strongly-connected components (SCC)
  3. Tarjan's algorithm for articulation points and bridges
  4. Kruskal's minimum spanning tree (MST) algorithm
  
**Coming soon - NP-complete problems!**
  
  1. DP solution to the travelling salesman problem (TSP)
  2. Vertex k-centres problem
  3. Verify k-colorability
  4. Hamiltonian cycles and paths
  
All C++ algorithms have associated unit tests defined in `tests.cpp`. The graphs used can be visualized by looking at `graphs_imgs.pptx`.

All source code is original and unique to my own implementation of the algorithms.
 
