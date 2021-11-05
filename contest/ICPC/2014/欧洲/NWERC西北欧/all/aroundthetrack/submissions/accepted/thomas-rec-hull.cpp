// Solution to Race Track
// Author: Thomas Beuman

// Time complexity: O(n^3) ?
// Memory: O(n)

// Expected result: accepted

// Solution method: recursive convex hull

#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const int N = 50;

const double infty = 1e9;

int n1, n2;
int X1[N], Y1[N], X2[N], Y2[N];
int X[2*N+3], Y[2*N+3];

long long area2 (int a, int b, int c)
{	return X[a]*Y[b] - X[b]*Y[a] + X[b]*Y[c] - X[c]*Y[b] + X[c]*Y[a] - X[a]*Y[c];
}

// Returns whether line segments AB and CD intersect
// If C or D touches AB, it counts iff the other vertex is to the left of AB
bool intersect (int a, int b, int c, int d)
{	long long a1 = area2(a,b,c), a2 = area2(a,b,d), a3 = area2(a,c,d), a4 = area2(b,c,d);
	long long p1 = a1*a2, p2 = a3*a4;
	return p2 <= 0 && (p1 < 0 || (p1 == 0 && a1+a2 < 0));
}

// Returns index of rightmost vertex
int rightmost (int x[], int y[], int n)
{	int	r = 0, i;
	for (i = 1; i < n; i++)
		if (x[i] > x[r] || (x[i] == x[r] && y[i] < y[r]))
			r = i;
	return r;
}

// Manhattan distance
int manhdis (int i, int j)
{	return abs(X[i]-X[j]) + abs(Y[i]-Y[j]);
}

// Returns distance of path from from to to,
//   checking for vertices of inner/outer polygon that are in the way 
double dis (int from, int to, bool checkinner)
{	int m = checkinner ? n1 : n1+n2;
	int i, j, n, prev;
	long long a;
	bool initial = (from == 0 && to == n1-1);
	// Find obstructing vertices
	vector<int> Obs;
	if (initial)
	{	for (i = 1; i < n1-1; i++)
			Obs.push_back(i);
	}
	else
	{	bool inside = false;
		for (i = (checkinner ? 0 : n1); i < m; i++)
		{	if (inside)
				Obs.push_back(i);
			inside ^= intersect(from, to, i, i+1);
		}
	}
	n = Obs.size();
	// Base case: no obstructions
	if (n == 0)
		return sqrt((X[from]-X[to])*(X[from]-X[to])+(Y[from]-Y[to])*(Y[from]-Y[to]));
	// Determine convex path
	vector<int> Path(1, prev = from);
	while (true)
	{	// Find the rightmost vertex; in case of a tie, take the farthest one
		j = (initial && Path.size() == 1 ? Obs[0] : to);
		for (i = 0; i < n; i++)
		{	a = area2(prev, Obs[i], j);
			if (a > 0 || (a == 0 && manhdis(prev, Obs[i]) > manhdis(prev, j)))
				j = Obs[i];
		}
		Path.push_back(prev = j);
		if (j == to)
			break;
		if (Path.size() > N)
		{	fprintf(stderr, "Something is wrong!\n");
			break;
		}
	}
	n = Path.size();
	// Investigate path segments
	double d = 0;
	for (i = 1; i < n; i++)
		d += dis(Path[i], Path[i-1], !checkinner);
	return d;
}

int main()
{	int i, r;
	vector<int> V, Path;
	// Read input
	scanf("%d", &n1);
	for (i = 0; i < n1; i++)
		scanf("%d %d", &X1[i], &Y1[i]);
	scanf("%d", &n2);
	for (i = 0; i < n2; i++)
		scanf("%d %d", &X2[i], &Y2[i]);
	// Find rightmost vertex of inner polygon
	r = rightmost(X1, Y1, n1);
	// Rotate to give this vertex index zero and duplicate
	for (i = 0; i <= n1; i++)
	{	X[i] = X1[(r+i)%n1];
		Y[i] = Y1[(r+i)%n1];
	}
	n1++;
	// Same for outer polygon
	r = rightmost(X2, Y2, n2);
	// Append
	for (i = 0; i <= n2; i++)
	{	X[n1+i] = X2[(r+i)%n2];
		Y[n1+i] = Y2[(r+i)%n2];
	}
	n2++;
	printf("%lf\n", dis(0, n1-1, true));
	return 0;
}
