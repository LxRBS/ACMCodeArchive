// Solution to Digi Comp II
// Author: Thomas Beuman

// Time complexity: O(n)
// Memory: O(n)

// Expected result: accepted

// Solution method: Topological sort using own stack

#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const int M = 500000;

int Child[M+1][2];
char State[M+1];

bool Seen[M+1], Processed[M+1];
stack<int> S;
int TopOrder[M];
long long Visits[M+1];

int main()
{	int m, i, j, k, idx;
	long long n, v;
	// Read input
	scanf("%lld %d\n", &n, &m);
	for (i = 1; i <= m; i++)
		scanf("%c %d %d\n", &State[i], &Child[i][0], &Child[i][1]);
	// Topological sort
	memset(Seen, false, sizeof(Seen));
	memset(Processed, false, sizeof(Processed));
	Processed[0] = true;
	idx = m;
	S.push(1);
	while (!S.empty())
	{	i = S.top();
		if (Processed[i]) // Already assigned index
			S.pop();
		else if (Seen[i]) // Returned for the first time: assign index
		{	TopOrder[--idx] = i;
			S.pop();
			Processed[i] = true;
		}
		else // Encountered for the first time: add children to stack
		{	for (k = 0; k < 2; k++)
				S.push(Child[i][k]);
			Seen[i] = true;
		}
	}
	memset(Visits, 0, sizeof(Visits));
	Visits[1] = n;
	// Process switches in topological order
	for (j = idx; j < m; j++)
	{	i = TopOrder[j];
		v = Visits[i];
		k = (State[i] == 'L' ? 0 : 1);
		Visits[Child[i][k]] += (v+1)/2;
		Visits[Child[i][1-k]] += v/2;
		if (v&1) // Odd number of visits: switch
			State[i] = (k ? 'L' : 'R');
	}
	// Output states
	for (i = 1; i <= m; i++)
		printf("%c", State[i]);
	printf("\n");
	return 0;
}
