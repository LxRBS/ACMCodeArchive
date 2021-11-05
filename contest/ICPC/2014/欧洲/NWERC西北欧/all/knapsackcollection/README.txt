Given are angles of objects.
The space is rotating.
Shoot at objects until no objects are remaining.
After each shoot you have to wait some time.
The problem is to calculate the minimal, maximal and average time of this process. (It depends on which object is choosen to be the first one)

We need an O(N*N*log(N)) algorithm.
(or maybe faster)

Expected difficulty: 65
[I expect only 35% of the teams solving this task]

Idea:
Simulate the process for each starting point using a clever data structure.

Algorithm:
Possibility 1:
Calculate for each position which is next after recharge (if all objects are available).
Circular data structure with path compression to find next object to shoot (without regarding recharge).
Runtime is a little bit more than O(N*N).
Possibility 2: (maybe it will decided that this possibility is too slow)
Keep a set of remaining objects.
Find the next in O(log(N)).
Remove the object if you do not have to shoot again on this object.
Runtime is O(N*N*log(N)).
