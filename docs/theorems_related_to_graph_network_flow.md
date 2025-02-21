# Theorem's related to Network flow in Graphs

## Bipartite Matching
A bipartite graph can be represented by coloring alternative vertices red and blue.
Bipartite matching is a subset of the pairs of vertices of a given graph where in each pair, one vertex is red, the other is blue and there is an edge between the vertices such that no two pairs share their vertices.
### Perfect matching
A perfect matching is a form of bipartite matching where either all the red vertices have a corresponding blue vertex, or all the blue vertices have a corresponding red vertex.
### Hall's theorem
Let $X_i$ be a subset of red vertices, and $f(X_i)$ represent the subset of all the blue vertices that are connected to the red vertices in the subset $X_i$
Given a bipartite graph, it is possible to construct a perfect matching for red vertices if for each subset of the red vertices $X_i$, the following holds:
$$|X_i| \leq |f(X_i)|$$

Let $Y_i$ be a subset of blue vertices, and $f(Y_i)$ represent the subset of all the red vertices that are connected to the blue vertices in the subset $Y_i$
Given a bipartite graph, it is possible to construct a perfect matching for blue vertices if for each subset of the blue vertices $Y_i$, the following holds:
$$|Y_i| \leq |f(Y_i)|$$

### Minimum vertex cover
A minimum vertex cover is a minimal set $X$ of vertices in a graph such that each edge in the graph has either its head vertex or its tail vertex in the set $X$.

### König's theorem
König's theorem states that the number of vertices in the minimum vertex cover of a bipartite graph equals the maximum matchings in the bipartite graph.

It is very important to note that König's theorem only works for bipartite graphs and for general graphs, finding minimum vertex covers is an NP-hard problem.

The nodes that do not belong to the minimum vertex cover form a set called maximum independent vertex set. This is the largest possible set of nodes such that no two nodes in the set are connected with an edge. Finding this in a general graph is again an NP-hard problem.

### Dilworth's theorem
An antichain is a set of nodes of a graph such that there is no path from any node to another node using the edges of the graph. Dilworth’s theorem states that in a directed acyclic graph, the size of a minimum general path cover equals the size of a maximum antichain.
