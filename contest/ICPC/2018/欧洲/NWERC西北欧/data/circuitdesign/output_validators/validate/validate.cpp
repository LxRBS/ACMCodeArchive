#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

const long double EPS = 1e-9;

// Output requirement bounds from problem statement:
const long double MAX_COORD = 3000;
const long double P2P_TOLERANCE = 1e-4;
const long double E2E_TOLERANCE = 1e-6;
const long double LENGTH_TOLERANCE = 1e-6;

struct point {
	long double x, y;
};

point operator -(const point &a, const point &b) {
	point c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

long double dist(point a, point b) {
	return hypotl(a.x-b.x,a.y-b.y);
}

long double dot(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

long double cross(point a, point b) {
	return a.x * b.y - b.x * a.y;
}

// returns:  0 if c is within distance EPS of line a->b, otherwise:
//          +1 if c is to the left of line a->b
//          -1 if c is to the right of line a->b
int ccw(point a, point b, point c) {
    long double proj = cross(b-a,c-b) / dist(a, b);
	return fabsl(proj) < EPS ? 0 : (proj > 0 ? 1 : -1);
}

long double segment_point_dist(point a, point b, point c) {
	if (dot(c-b,b-a) > 0) return dist(b,c);
	if (dot(c-a,a-b) > 0) return dist(a,c);
	return fabsl(cross(b-a,c-a) / dist(a, b));
}


long double segment_segment_dist(point a1, point a2, point b1, point b2) {
	if (ccw(a1,a2,b1)*ccw(a1,a2,b2) < 0 && ccw(b1,b2,a1)*ccw(b1,b2,a2) < 0)
		return 0;
	return min(min(segment_point_dist(a1, a2, b1),
				   segment_point_dist(a1, a2, b2)),
			   min(segment_point_dist(b1, b2, a1),
				   segment_point_dist(b1, b2, a2)));
}

void read_coord(long double &x) {
	if (!(cin >> x)) {
		wrong_answer("Failed to read coordinate (premature EOF? nan/inf values?)\n");
	}

	if (fabsl(x) > MAX_COORD) {
		wrong_answer("Coordinate out of range.\n");
	}
}

void read_point(point &p) {
	read_coord(p.x);
	read_coord(p.y);
}

int main(int argc, char **argv) {
	init_io(argc,argv);

	int n;
	judge_in >> n;

	vector<int> a(n-1), b(n-1);
	vector<pair<int,int>> edges;
	for (int i = 0; i < n-1; i++) {
		judge_in >> a[i] >> b[i];
		a[i]--, b[i]--;
	}

	vector<point> p(n);
	for (int i = 0; i < n; i++) {
		read_point(p[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			long double dst = dist(p[i],p[j]);
			if (dst * (1 + EPS) < P2P_TOLERANCE) {
				wrong_answer("Points %d and %d are too close: %.9Lf.\n", i+1, j+1, dst);
			}
		}
	}

	for (int i = 0; i < n-1; i++) {
		point u = p[a[i]], v = p[b[i]];

		long double dst = dist(u, v);
		if (fabsl(dst-1.0) > LENGTH_TOLERANCE + EPS) {
			wrong_answer("Length of edge %d incorrect: %.9Lf.\n", i+1, dist);
		}

		for (int j = i+1; j < n-1; j++) {
			//  Skip incident edges
			if(a[i] == a[j] || a[i] == b[j] || b[i] == a[j] || b[i] == b[j]) {
				continue;
			}

			point c = p[a[j]], d = p[b[j]];
			long double dst = segment_segment_dist(u, v, c, d);
			if (dst * (1 + EPS) < E2E_TOLERANCE) {
				wrong_answer("Edges %d-%d and %d-%d are too close: %.9Lf.\n", a[i]+1, b[i]+1, a[j]+1, b[j]+1, dst);
			}
		}
	}

	string junk;
	if (cin >> junk) {
		wrong_answer("Trailing output\n");
	}

	accept();
}
