PROBLEM SYNOPSIS
----------------

Given two simple polygons where one is completely inside the other, find the shortest tour that lies completely in between the two polygons.


ESTIMATED DIFFICULTY LEVEL
--------------------------

90


SOLUTION
--------

Method 1:

Let P be the (a) vertex of the inner polygon with the largest x-coordinate (for example). This vertex will definitely be on the tour.
From P, draw an imaginary horizontal half-line to the right, to serve as a start/finish line. Duplicate the vertex P: one copy is understood to be above the finish line and the other below.
For every pair of vertices, check if the line segment connecting them is completely between the two polygons. (This can be done by checking every edge to see if it intersects the line segment. One also needs to check that the segment is not completely contained inside the inner polygon or completely outside the outer polygon.) The line segment is also not allowed to cross the finish line. If all conditions are met, calculate the length of the line segment and add this as an edge to a graph.
When the graph is built, find the shortest path from one copy of P to the other.


Method 2:

Start from the convex hull of the inner polygon (this would be the shortest path if the outer polygon weren't there).
For every edge of the hull, check if it is intersected by edges from the outer polygon and identify the vertices that are inside the hull. Take the "concave hull" of these vertices and insert them between the two vertices that mark the edge of the convex hull.
For every edge in the newly added concave parts of the tour, check if it is intersected by edges from the inner polygon. Identify the vertices that are outside the tour, take the convex hull and insert those vertices.
Recursively repeat this process until there are no more intersections.


COMPLEXITY
----------

n = #vertices (max 2*50)

Method 1:
  Memory: O(n^2)
  Time: O(n^3)

Method 2:
  Memory: ? (not much)
  Time: O(n^2 log n)? (edges in tour * all edges * max recursion depth)
