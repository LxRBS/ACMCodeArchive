// Solution to Orienteering
// Author: Thomas Beuman

// Time complexity: O(n!)
// Memory: O(n^2+2^n)

// Expected result: time limit exceeded

// Solution method: Try all permutations with recursion

#include <cstdio>
using namespace std;

const int nmax = 14;

long long Dis[nmax][nmax];
int last;

bool possible (int prev, int left, long long d)
{	if (left == 0)
		return Dis[prev][last] == d;
	if (d < 0)
		return false;
	int i, m, s;
	// Loop over all remaining points
	for (s = left; s; s ^= m)
	{	i = __builtin_ctz(m = s & -s);
		if (possible(i, left^m, d - Dis[prev][i]))
			return true;
	}
	return false;
}

int main()
{	int n, i, j, first;
	long long L;
	scanf("%d %lld", &n, &L);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%lld", &Dis[i][j]);
	if (n == 2)
	{	printf("%spossible\n", 2*Dis[0][1] == L ? "" : "im");
		return 0;
	}
	for (first = 1; first < n; first++)
		for (last = first+1; last < n; last++)
			if (possible(first, (1<<n) - 2 - (1<<first) - (1<<last), L - Dis[0][first] - Dis[last][0]))
			{	printf("possible\n");
				return 0;
			}
	printf("impossible\n");
	return 0;
}
