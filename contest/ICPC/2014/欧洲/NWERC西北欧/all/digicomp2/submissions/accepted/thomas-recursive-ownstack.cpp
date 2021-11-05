// Solution to Digi Comp II
// Author: Thomas Beuman

// Time complexity: O(n)
// Memory: O(n)

// Expected result: accepted

// Solution method: Recursion (from bottom to top) with own stack

#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

const int M = 500000;

char State[M+1];
vector<int> Parent[M+1];
vector<bool> First[M+1];

bool Seen[M+1], Processed[M+1];
stack<int> S;
long long Visits[M+1];

long long visits (int i)
{	int j;
	if (Seen[i])
		return Visits[i];
	Seen[i] = true;
	for (j = Parent[i].size()-1; j >= 0; j--)
		Visits[i] += (visits(Parent[i][j]) + (First[i][j]?1:0)) / 2;
	return Visits[i];
}

int main()
{	int m, c1, c2, i, j;
	long long n;
	scanf("%lld %d\n", &n, &m);
	for (i = 1; i <= m; i++)
	{	scanf("%c %d %d\n", &State[i], &c1, &c2);
		Parent[c1].push_back(i);
		First[c1].push_back(State[i] == 'L');
		Parent[c2].push_back(i);
		First[c2].push_back(State[i] == 'R');
	}
	memset(Visits, 0, sizeof(Visits));
	memset(Seen, false, sizeof(Seen));
	Processed[1] = true;
	Visits[1] = n;
	S.push(0);
	while (!S.empty())
	{	i = S.top();
		if (Processed[i])
			S.pop();
		else if (Seen[i])
		{	for (j = Parent[i].size()-1; j >= 0; j--)
				Visits[i] += (Visits[Parent[i][j]] + (First[i][j]?1:0)) / 2;
			S.pop();
			Processed[i] = true;
		}
		else
		{	for (j = Parent[i].size()-1; j >= 0; j--)
				S.push(Parent[i][j]);
			Seen[i] = true;
		}
	}
	//visits(0);
	for (i = 1; i <= m; i++)
		printf("%c", Visits[i]&1 ? 'L'+'R'-State[i] : State[i]);
	printf("\n");
	return 0;
}
