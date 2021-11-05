Difficulty: 25% of the teams will solved it.

Solution:

Inserting N balls flips vertex 1 exactly N times (so it stays the same if N
is even and flips L<->R if N is odd).

These balls move on to vertices L1 (N/2 round up or down depending on the
initial state) and R1 (also N/2 round the other way around).

Iterate this over the vertices in topological sort order.
