// Testdata checker for Racetrack
// Author: Thomas

// Checks for intersections, correct orientation, etc.

#include <cstdio>
#include <set>
using namespace std;

const int N = 50;

int X[2*N], Y[2*N];
set<pair<int,int> > S;

int polygonarea (int n, int X[], int Y[])
{	int a = 0, i, j;
	for (i = 0; i < n; i++)
	{	j = (i == n-1 ? 0 : i+1);
		a += X[i]*Y[j] - X[j]*Y[i];
	}
	return a;
}

long long area2 (int a, int b, int c)
{	return X[a]*Y[b] - X[b]*Y[a] + X[b]*Y[c] - X[c]*Y[b] + X[c]*Y[a] - X[a]*Y[c];
}

// Returns whether line segments AB and CD intersect
// If one vertex touches the other line segment, it counts as an intersection
// Two vertices touching does not count
// Assumes that A!=B and C!=D
bool intersect (int a, int b, int c, int d)
{	long long a1 = area2(a,b,c), a2 = area2(a,b,d), a3 = area2(a,c,d), a4 = area2(b,c,d);
	if (a1 || a2 || a3 || a4) // Not all points collinear
	{	long long p1 = a1*a2, p2 = a3*a4;
		return p1 <= 0 && p2 <= 0 && (p1 < 0 || p2 < 0);
	}
	int *Z = (X[a1] == X[a2] ? Y : X);
	return (Z[c]-Z[a])*(Z[c]-Z[b]) < 0 || (Z[d]-Z[a])*(Z[d]-Z[b]) < 0;
}

int main()
{	int n1, n2, i, j, k, q, m, a1, a2;
	scanf("%d", &n1);
	for (i = 0; i < n1; i++)
		scanf("%d %d", &X[i], &Y[i]);
	scanf("%d", &n2);
	for (i = 0; i < n2; i++)
		scanf("%d %d", &X[n1+i], &Y[n1+i]);
	m = n1+n2;
	for (i = 0; i < m; i++)
		if (!S.insert(make_pair(X[i], Y[i])).second)
			printf("Identical vertices found!\n");
	for (i = 0; i < m; i++)
	{	j = (i == n1-1 ? 0 : i == m-1 ? n1 : i+1);
		// Check if the line segment intersects another segment
		for (k = 0; k < m; k++)
		{	q = (k == n1-1 ? 0 : k == m-1 ? n1 : k+1);
			if (intersect(i,j,k,q))
			{	printf("Intersecting edges found!\n");
				return 0;
			}
		}
	}
	a1 = polygonarea(n1, X, Y);
	a2 = polygonarea(n2, X+n1, Y+n1);
	if (a1 < 0)
	{	printf("Inner polygon is oriented clockwise!\n");
		return 0;
	}
	if (a2 < 0)
	{	printf("Outer polygon is oriented clockwise!\n");
		return 0;
	}
	if (a1 > a2)
	{	printf("Inner polygon is larger than outer polygon!\n");
		return 0;
	}
	return 0;
}
