The problem is to determine whether ceil(N/2) points lie on the same line

We need an O(N) or O(N log(N)) algorithm.

Expected difficulty: 85
[I expect only 15% of the teams solving this task]

Idea:
probabilistic approach to receive possible lines

Possible Algorithm:
1.: sample much pairs of points and remember their gradient
2.: for all gradients which occur more than 10% do
		Check whether half of the points lie on the same line with current gradient.
		O(N) if hashing of scalar product with orthogonal vector of gradient is used.

If such a line exist then the correct gradient is sampled in at least 25% of the sampled pairs.
Therefore 10% is a good bound whether to check the current gradient or not.
It will be quite uncertain that less than 10% appear if the number of samples is choosen large enough.

There are much other ideas which lead to an algorithm with suitable runtime.
