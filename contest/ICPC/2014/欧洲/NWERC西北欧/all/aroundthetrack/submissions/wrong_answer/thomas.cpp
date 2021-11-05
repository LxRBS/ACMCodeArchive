// Solution to Racetrack
// Author: Thomas Beuman

// Time complexity: O(n^3)
// Memory: O(n^2)

// Expected result: wrong answer

/* Solution method:
 * 
 * For each pair of vertices, see if it's possible to go from one to the other in a straight line.
 * Find the vertices on the convex hull of the inner polygon;
 *   these vertices are surely on the shortest tour.
 * Find the shortest path between consecutive hull vertices using Dijkstra, add it all together.
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 50;

const double infty = 1e9;

int X[2*N], Y[2*N];
double Len[2*N][2*N];
int Hull[N];

bool Seen[2*N];
double Dis[2*N];

// Dijkstra from r to m
double dijkstra (int start, int finish, int n)
{	int i, j;
	double d;
	for (i = 0; i < n; i++)
		Dis[i] = infty;
	Dis[start] = 0;
	memset(Seen, false, sizeof(Seen));
	while (true)
	{	j = -1;
		d = infty;
		for (i = 0; i < n; i++)
			if (!Seen[i] && Dis[i] < d)
				d = Dis[j = i];
		if (j == -1) // Not supposed to happen
		{	printf("Fail!\n");
			return 0;
		}
		if (j == finish)
			return d;
		Seen[j] = true;
		for (i = 0; i < n; i++)
			Dis[i] = min(Dis[i], Dis[j] + Len[j][i]);
	}
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
{	int n1, n2, i, j, k, q, m, nc, r;
	double d;
	bool intersection, inside, outside;
	scanf("%d", &n1);
	for (i = 0; i < n1; i++)
		scanf("%d %d", &X[i], &Y[i]);
	scanf("%d", &n2);
	for (i = 0; i < n2; i++)
		scanf("%d %d", &X[n1+i], &Y[n1+i]);
	// Find rightmost vertex of inner polygon
	r = 0;
	for (i = 1; i < n1; i++)
		if (X[i] > X[r] || (X[i] == X[r] && Y[i] < Y[r]))
			r = i;
	m = n1+n2;
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
			Len[i][j] = infty;
	// Explore all pairs of vertices
	for (i = 1; i < m; i++)
		for (j = 0; j < i; j++)
		{	intersection = inside = outside = false;
			// Check if the line segment intersects another segment
			for (k = 0; k < m; k++)
			{	q = (k == n1-1 ? 0 : k == m-1 ? n1 : k+1);
				if (intersect(i,j,k,q))
					intersection = true;
			}
			// Check if the line segment lies entirely inside the inner polygon
			if (i < n1 && j < n1)
			{	k = (i == n1-1 ? 0 : i+1);
				q = (i == 0 ? n1-1 : i-1);
				if ((area2(q,i,k) >= 0 && area2(i,k,j) > 0 && area2(i,j,q) > 0) ||
				    (area2(q,i,k) < 0 && (area2(i,k,j) > 0 || area2(i,j,q) > 0)))
					inside = true;
			}
			// Check if the line segment lies entirely outside the outer polygon
			if (i >= n1 && j >= n1)
			{	k = (i == m-1 ? n1 : i+1);
				q = (i == n1 ? m-1 : i-1);
				if ((area2(q,i,k) <= 0 && area2(i,k,j) < 0 && area2(i,j,q) < 0) ||
				    (area2(q,i,k) > 0 && (area2(i,k,j) < 0 || area2(i,j,q) < 0)))
					outside = true;
			}
			// Add line segment
			if (!intersection && !inside && !outside)
				Len[i][j] = Len[j][i] = sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
		}
	// Gift wrap algorithm
	Hull[0] = r;
	for (nc = 1; true; nc++)
	{	j = (Hull[nc-1] == 0 ? 1 : 0);
		for (i = 0; i < n1; i++)
			if (area2(Hull[nc-1], i, j) > 0)
				j = i;
		if (j == r)
			break;
		Hull[nc] = j;
	}
	d = 0;
	// Dijkstra between consecutive vertices on the hull
	for (i = 0; i < nc; i++)
		d += dijkstra(Hull[i], Hull[(i+1)%nc], m);
	printf("%lf\n", d);
	return 0;
}
