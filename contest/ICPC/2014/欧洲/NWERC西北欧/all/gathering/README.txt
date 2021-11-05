PROBLEM SYNOPSIS
----------------

Given a number n of locations in a square grid, find a location P that minimizes the sum of the Manhattan distances (|x1-x2|+|y1-y2|) to all given locations, with the constraint that all distances should not exceed a given threshold d.


ESTIMATED DIFFICULTY LEVEL
--------------------------

70


SOLUTION
--------

For each location, the distance threshold implies that P must lie within a square (rotated by 45 degrees) around that location. The intersection of all those squares is a rectangle. (If the intersection is empty, the answer is "impossible".)
If there was no distance threshold (d = inf), the optimal location would be given by the median of all the x-coordinates and that of all the y-coordinates (if n is even, any value between the two center values will do). If this location (or any such location, in the case n = even) lies inside the rectangle, calculate the total distance to this location and you are done.
Otherwise, the (an) optimal location will lie on the border of the rectangle; this is because the total distance can only increase the farther away you go from the optimal spot. This leaves O(d) locations to check.
The sum of all Manhattan distances can be split into separate sums for the x- and y-coordinates. Each sum can be calculated efficiently by noting that, going from xp to xp+1, the x-sum increases by the number of locations for which x<=xp and decreases by the number of locations for which x>xp. By sorting all coordinates, one can thus determine the first sum in O(n) time, but all subsequent sums in constant time.


COMPLEXITY
----------

n = #locations (max 10^5)
d = maximum distance (max 2*10^6)
Memory: O(n) (or O(n+d))
Time: O(n log n + d)


TIMELIMIT
---------

- Calculating total distances in O(n) per location [O(nd)]
- In the bordercase, one can deduce that the (an) optimal location must share an x- or y-coordinate with some location. This reduces the number of locations to check to O(n), but this is still O(n^2).


WRONG ANSWER
------------

- Answer can be too large for a 32-bit integer.
