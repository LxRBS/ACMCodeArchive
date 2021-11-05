// Author: Alexander Rass
// Idea: use ternary search where stations at the border are
// maybe precision can be an issue!!
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

const int TERNARY_ITERATIONS = 50;
const int MAXN = 1024;
double x[MAXN][2]; // positions of stations
double X1[2], X2[2]; // Bounding box
double X[2]; // moved bounding box;
double x_se[2][2]; // start / end position
double x_edges[4][2][2]; // the start end end point of the four bounding segments
double dist_se[2][MAXN];
int N;
double v_walk, v_under;


double directDist(double *p1, double* p2){
	return sqrt( pow( p1[0] - p2[0], 2 ) + pow( p1[1] - p2[1], 2) );
}

double walkOn2edges_evaluate(int segId1, double f1, int segId2, double f2){
	double x_station[2][2];
	FOR(d,0,2){
		x_station[0][d] = x_edges[segId1][0][d] + (x_edges[segId1][1][d] - x_edges[segId1][0][d]) * f1;
		x_station[1][d] = x_edges[segId2][0][d] + (x_edges[segId2][1][d] - x_edges[segId2][0][d]) * f2;
	}
	return directDist(x_se[0], x_station[0]) / v_walk
			+ directDist(x_station[0], x_station[1]) / v_under
			+ directDist(x_station[1], x_se[1]) / v_walk;
}

double walkOn2edges_ternarysearch2(int segId1, double f1, int segId2){
	double lo = 0.0, hi = 1.0;
	FOR(iterations, 0, TERNARY_ITERATIONS){
		double mid1 = lo + (hi - lo) * 0.4;
		double mid2 = lo + (hi - lo) * 0.6;
		double val1 = walkOn2edges_evaluate(segId1, f1, segId2, mid1);
		double val2 = walkOn2edges_evaluate(segId1, f1, segId2, mid2);
		if(val1 < val2) hi = mid2;
		else lo = mid1;
	}
	return walkOn2edges_evaluate(segId1, f1,  segId2, (lo + hi) * 0.5);
}
double walkOn2edges_ternarysearch1(int segId1, int segId2){
	double lo = 0.0, hi = 1.0;
	FOR(iterations, 0, TERNARY_ITERATIONS){
		double mid1 = lo + (hi - lo) * 0.4;
		double mid2 = lo + (hi - lo) * 0.6;
		double val1 = walkOn2edges_ternarysearch2(segId1, mid1, segId2);
		double val2 = walkOn2edges_ternarysearch2(segId1, mid2, segId2);
		if(val1 < val2) hi = mid2;
		else lo = mid1;
	}
	return walkOn2edges_ternarysearch2(segId1, (lo + hi) * 0.5, segId2);
}
double walkOn2edges(){
	double res = 1e100;
	FOR(i,0,4)FOR(j,0,4){
		res = min(res, walkOn2edges_ternarysearch1(i, j));
	}
	return res;
}
double distToStation_evaluate(double *p,  double* s, int segId, double f){
	double position[2];
	FOR(d,0,2){
		position[d] = x_edges[segId][0][d] + (x_edges[segId][1][d] - x_edges[segId][0][d]) * f;
	}
	return directDist(p, position) / v_walk + directDist(position, s) / v_under;
}
double distToStation_ternarysearch(double *p, double* s, int segId){
	double lo = 0.0, hi = 1.0;
	FOR(iterations, 0, TERNARY_ITERATIONS){
		double mid1 = lo + (hi - lo) * 0.4;
		double mid2 = lo + (hi - lo) * 0.6;
		double val1 = distToStation_evaluate(p, s, segId, mid1);
		double val2 = distToStation_evaluate(p, s, segId, mid2);
		if(val1 < val2) hi = mid2;
		else lo = mid1;
	}
	return distToStation_evaluate(p, s, segId, (lo + hi) * 0.5);
}
double distToStation(double *p, double *s){
	double res = directDist(p, s) / v_walk;
	FOR(i,0,4){
		res = min(res, distToStation_ternarysearch( p, s, i));
	}
	return res;
}
int main() {
	cin >> v_walk >> v_under;
	{
		cin >> X1[0] >> X1[1] >> X2[0] >> X2[1];
		FOR(d,0,2){
			X[d] = X2[d] - X1[d];
		}
		FOR(i,0,2){
			FOR(d,0,2){
				cin >> x_se[i][d];
				x_se[i][d] -= X1[d];
			}
		}
	}
	cin >> N;
	FOR(i,0,N)FOR(d,0,2){
		cin >> x[i][d];
		x[i][d] -= X1[d];
	}
	FOR(i,0,4){
		x_edges[i][0][0] = ((i&2)?0.0:X[0]);
		x_edges[i][0][1] = ((i&2)?0.0:X[1]);
		x_edges[i][1][0] = ((i&1)?0.0:X[0]);
		x_edges[i][1][1] = ((i&1)?X[1]:0.0);
	}
	double res = directDist(x_se[0], x_se[1]) / v_walk; // just walk
	res = min(res, walkOn2edges()); // walk on two edges
	FOR(i,0,2)FOR(n,0,N){
		dist_se[i][n] = distToStation(x_se[i], x[n]);
	}
	// use one station
	FOR(n,0,N)res = min(res, dist_se[0][n] + dist_se[1][n]);
	// use two stations
	FOR(n1,0,N)FOR(n2,0,N){
		res = min(res, dist_se[0][n1] + directDist(x[n1], x[n2]) / v_under + dist_se[1][n2]);
	}
	printf("%.9lf\n", res);
	return 0;
}
