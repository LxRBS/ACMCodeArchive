The problem is to solve a sort of maximum edge coloring problem in a connected tree. Given a connected undirected simple tree T = (V,E), how do we color the edges in E with a maximum number of colors under the constraint that for every vertex in V, we may only use at most two colors. Actually, the problem statement only asks for the maximum number of colors, not an actual coloring.

Let us call a vertex in the tree an internal vertex iff it has degree at least two. (So, if a tree is just an edge, then it has no internal vertices.) The set of internal vertices, V_in, is a vertex cover of T and it is not to hard to see that the maximum number of colors is |V_in| + 1. If T is just an edge then |V_in| = 0 and we can only use one color. Otherwise, we can root the tree at an arbitrary internal vertex and use the following algorithm to find a maximum coloring:

(1) For the edges incident to the root, assign to them two colors;
(2) Processs the remaining internal nodes from top to down, from left to right.
    For the current node, assign one new unused color to all the edges from it
    to its children;
(3) When all the internal nodes are processed, all the edges are colored.

Difficulty: 30
