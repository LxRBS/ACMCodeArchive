// Solution to Not A Single Cent
// Author: Thomas Beuman

// Time complexity: O(n^2*d)
// Memory: O(n*d)

// Expected result: accepted

// Solution method: DP

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 2000, D = 20;
const int infty = 1<<30;

int Prize[N];
int Cost[N+1][D+1];

int rnd (int p)
{	return 10*((p+5)/10);
}

int main()
{	int n, d, i, j, k, s;
	scanf("%d %d\n", &n, &d);
	for (i = 0; i < n; i++)
		scanf("%d", &Prize[i]);
	for (i = 0; i <= n; i++)
		for (j = 0; j <= d; j++)
		{	if (i == 0)
				Cost[i][j] = 0;
			else if (j == 0)
			{	s = 0;
				for (k = 0; k < i; k++)
					s += Prize[k];
				Cost[i][j] = rnd(s);
			}
			else
			{	s = 0;
				Cost[i][j] = infty;
				for (k = i-1; k >= 0; k--)
				{	s += Prize[k];
					Cost[i][j] = min(Cost[i][j], rnd(s) + Cost[k][j-1]);
				}
			}
		}
	printf("%d\n", Cost[n][d]);
	return 0;
}
