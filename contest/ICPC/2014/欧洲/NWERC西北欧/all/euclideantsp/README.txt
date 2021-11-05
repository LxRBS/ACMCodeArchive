The total time is a sum of the time for running the program and flying with the jet. At the core, the problem is to minimize a function of the form c * a^x + b / x for x > 0. The function is convex on the interval (0, \infty), so we can use a ternary search to find the minimum.

Watch out for overflow!

Difficulty: 70
