// Solution to Racetrack
// Author: Thomas Beuman

// Time complexity: O(n^3)
// Memory: O(n^2)

// Expected result: accepted

/* Solution method:
 * 
 * Find the rightmost vertex R of the inner polygon; this vertex is surely on the shortest tour.
 * Draw a half-line from R, in the direction opposite to the next vertex,
 *   to serve as a "finish line".
 * For each pair of vertices, see if it's possible to go from one to the other in a straight line.
 * This straight line is not allowed to cross the finish line, except at R.
 * Duplicate R; a line segment between X and R is understood to connect to either R or R',
 *   depending on which side of the finish line X is on.
 * Find the shortest path from R to R' using Dijkstra.
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 50;

const double infty = 1e9;

int X[2*N+1], Y[2*N+1];

double Dis[2*N+1][2*N+1];
bool Seen[2*N+1];

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
{	int n1, n2, i, j, k, q, m, r, s;
	double d;
	bool intersection, inside, outside, crossfinish;
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
	s = (r+1)%n1; // Next vertex
	m = n1+n2;
	for (i = 0; i <= m; i++)
		for (j = 0; j <= m; j++)
			Dis[i][j] = infty;
	// Explore all pairs of vertices
	for (i = 1; i < m; i++)
		for (j = 0; j < i; j++)
		{	intersection = inside = outside = crossfinish = false;
			// Check if the line segment intersects another segment
			for (k = 0; k < m; k++)
			{	q = (k == n1-1 ? 0 : k == m-1 ? n1 : k+1);
				if (intersect(i,j,k,q))
					intersection = true;
			}
			// Check if it crosses/touches the "finish line" (= half-line from r, away from s)
			if (area2(i,r,s)*area2(j,r,s) <= 0 &&
			    (area2(i,j,r)*area2(i,r,s) > 0 || area2(i,j,r)*area2(j,r,s) < 0))
				crossfinish = true;
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
			if (!intersection && !inside && !outside && !crossfinish)
			{	k = (i == r && area2(r,s,j) > 0 ? m : i);
				q = (j == r && area2(r,s,i) > 0 ? m : j);
				Dis[k][q] = Dis[q][k] = sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
			}
		}
	// DEBUG OUTPUT
	/*for (i = 0; i <= m; i++)
	{	for (j = 0; j <= m; j++)
			printf("%6.3lf  ", Dis[i][j] == infty ? 0 : Dis[i][j]);
		printf("\n");
	}//*/
	// Dijkstra from r to m
	Dis[r][r] = 0;
	memset(Seen, false, sizeof(Seen));
	while (true)
	{	j = -1;
		d = infty;
		for (i = 0; i <= m; i++)
			if (!Seen[i] && Dis[r][i] < d)
				d = Dis[r][j = i];
		if (j == -1) // Not supposed to happen
		{	printf("Fail!\n");
			return 0;
		}
		if (j == m)
			break;
		Seen[j] = true;
		for (i = 0; i <= m; i++)
			Dis[r][i] = min(Dis[r][i], Dis[r][j] + Dis[j][i]);
	}
	printf("%lf\n", Dis[r][m]);
	return 0;
}
