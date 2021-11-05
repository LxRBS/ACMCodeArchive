/*
	Author       :	Jan
	Problem Name :
	Algorithm    :
	Complexity   :
*/

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

const double eps = 1e-9;
const double pi = 2 * acos( 0.0 );

inline bool eq(double a, double b) { return fabs( a - b ) < eps; }
inline bool eq2(double a, double b) { return fabs( a - b ) < 1e-7; }
struct point {
	double x, y;
	point() {}
	point( double xx, double yy ) { x = xx, y = yy; }
	bool operator < ( const point &b ) const {
		if( eq( x, b.x ) ) {
			if( eq( y, b.y ) ) return false;
			return y < b.y;
		}
		return x < b.x;
	}
};
struct line {
	double a, b, c;
	line() {}
	line( point p1,point p2 ) {
		a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=p1.x*p2.y-p2.x*p1.y;
	}
};
struct circle {
	point center;
	double r;
	circle() {}
	circle( point P, double rr ) { center = P; r = rr; }
};
struct segment {
	point A, B;
	segment() {}
	segment( point P1, point P2 ) { A = P1, B = P2; }
};
inline double Distance( point a, point b ) {
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}
inline double Distance( point P, line L ) {
	return fabs( L.a * P.x + L.b * P.y + L.c ) / sqrt( L.a * L.a + L.b * L.b );
}
inline double isleft( point p0, point p1, point p2 ) {
	return( ( p1.x - p0.x ) * ( p2.y - p0.y ) - ( p2.x - p0.x ) * ( p1.y - p0.y ) );
}
inline bool intersection( line L1, line L2, point &p ) {
	double det = L1.a * L2.b - L1.b * L2.a;
	if( eq ( det, 0 ) ) return false;
	p.x = ( L1.b * L2.c - L2.b * L1.c ) / det;
	p.y = ( L1.c * L2.a - L2.c * L1.a ) / det;
	return true;
}
inline bool intersection( segment L1, segment L2, point &p ) {
	if( !intersection( line( L1.A, L1.B ), line( L2.A, L2.B ), p) ) return false;
	return(eq(Distance(L1.A,p)+Distance(L1.B,p),Distance(L1.A,L1.B)) &&
		eq(Distance(L2.A,p)+Distance(L2.B,p),Distance(L2.A,L2.B)));
}
inline line findPerpendicularLine( line L, point P ) {
	line res;
	res.a = L.b, res.b = -L.a;
	res.c = -res.a * P.x - res.b * P.y;
	return res;
}
inline double Distance( point P, segment S ) {
	line L1 = line( S.A, S.B ), L2;
	point P1;
	L2 = findPerpendicularLine( L1, P );
	if( intersection( L1, L2, P1 ) )
		if( eq2 ( Distance( S.A, P1 ) + Distance( S.B, P1 ), Distance( S.A, S.B ) ) )
			return Distance(P,L1);
	return min ( Distance( S.A, P), Distance( S.B, P) );
}

const int MAX_LINE = 25;
const int MAX_CIRCLE = 25;

int n, m, L, W, sv[MAX_LINE*MAX_LINE];
segment S[MAX_LINE];
point P[MAX_LINE*MAX_LINE];
circle C[MAX_CIRCLE];

map <point, int> M;
set <point> adjLine[MAX_LINE];
vector <int> adj[MAX_LINE*MAX_LINE];
vector <bool> taken[MAX_LINE*MAX_LINE];
vector <double> res[MAX_CIRCLE];

int getId( point p ) {
	if( M.find(p) == M.end() ) {
		int N = M.size();
		M[p] = N;
		adj[N].clear();
		P[N] = p;
	}
	return M[p];
}

double areaPolygon( int sv[], int n ) {
	double area = 0;
	for( int i = 0, j = n - 1; i < n; j = i++ ) area += P[sv[j]].x * P[sv[i]].y - P[sv[j]].y * P[sv[i]].x;
	return fabs(area)/2;
}

bool intersect( circle C, int sv[], int k ) {
	vector <point> V;

	for( int i = 0; i <= k; i++ ) {
		V.push_back( P[ sv[i] ] );
		V[i].x -= C.center.x;
		V[i].y -= C.center.y;
	}
	bool flag = true;
	for( int i = 0; i < k; i++ ) {
		double dsq = V[i].x*V[i].x + V[i].y*V[i].y;
		double rsq = C.r * C.r;
		if( dsq + eps < rsq ) return true;
		if( dsq > rsq + eps ) flag = false;
	}
	if( flag ) return true;
	flag = true;
	for( int i = 0; i < k; i++ ) if( isleft( V[i], V[i+1], point(0, 0) ) < -eps ) {
		flag = false;
		break;
	}
	if( flag ) return true;

	// for all other cases, at least one edge of the polygon should intersect with the circle
	for( int i = 0; i < k; i++ ) if( Distance( point(0, 0), segment( V[i], V[i+1] ) ) + eps < C.r ) return true;
	return false;
}

void makeChain( int k ) {
	if( sv[k-1] == sv[0] ) {
		// full chain
		double area = areaPolygon( sv, k - 1 );

		for( int i = 0; i < m; i++ ) if( intersect( C[i], sv, k - 1 ) ) res[i].push_back( area );
		return;
	}
	int u = sv[k-1], j = -1;
	for( int i = 0; i < adj[u].size(); i++ ) {
		int v = adj[u][i];
		if( v == sv[k-2] ) continue;
		if( isleft( P[sv[k-2]], P[sv[k-1]], P[v] ) > eps ) {
			if( j == -1 || isleft( P[ sv[k-1] ], P[  adj[u][j] ], P[ v ] ) > eps ) j = i;
		}
	}
	if( j == -1 ) return;
	taken[u][j] = true;
	sv[k] = adj[u][j];
	makeChain( k + 1 );
}

int main() {
	//freopen("h1.in", "r", stdin);
	//freopen("h1jan.ans", "w", stdout);

	double cl = clock();

	while( scanf("%d %d %d %d", &n, &m, &L, &W) == 4 && n ) {
		for( int i = 0; i < n; i++ ) scanf("%lf %lf %lf %lf", &S[i].A.x, &S[i].A.y, &S[i].B.x, &S[i].B.y);
		for( int i = 0; i < m; i++ ) scanf("%lf %lf %lf", &C[i].center.x, &C[i].center.y, &C[i].r);

		S[n++] = segment( point( 0, 0 ), point( L, 0 ) );
		S[n++] = segment( point( 0, 0 ), point( 0, W ) );
		S[n++] = segment( point( 0, W ), point( L, W ) );
		S[n++] = segment( point( L, 0 ), point( L, W ) );

		for( int i = 0; i < n; i++ ) adjLine[i].clear();
		for( int i = 0; i < m; i++ ) res[i].clear();

		M.clear();
		for( int i = 0; i < n; i++ ) {
			for( int j = i + 1; j < n; j++ ) {
				point p;
				if( intersection( S[i], S[j], p ) ) {
					int x = getId(p);
					adjLine[i].insert(p);
					adjLine[j].insert(p);
				}
			}
		}

		for( int i = 0; i < n; i++ ) {
			vector <point> V;
			for( set <point> ::iterator s = adjLine[i].begin(); s != adjLine[i].end(); s++ ) V.push_back( *s );

			for( int j = 0; j < V.size() - 1; j++ ) {
				adj[ M[ V[j] ] ].push_back( M[ V[j + 1] ] );
				adj[ M[ V[j + 1] ] ].push_back( M[ V[j] ] );
			}
		}

		for( int i = 0; i < M.size(); i++ ) {
			taken[i].clear();
			for( int j = 0; j < adj[i].size(); j++ ) taken[i].push_back(false);
		}

		for( int i = 0; i < M.size(); i++ ) {
			for( int j = 0; j < adj[i].size(); j++ ) if( !taken[i][j] ) {
				taken[i][j] = true;
				sv[0] = i;
				sv[1] = adj[i][j];

				makeChain( 2 );
			}
		}
		for( int i = 0; i < m; i++ ) {
			printf("%d", res[i].size());
			sort( res[i].begin(), res[i].end() );
			for( int j = 0; j < res[i].size(); j++ ) printf(" %.2lf", res[i][j] + 1e-7);
			puts("");
		}
		puts("");
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
