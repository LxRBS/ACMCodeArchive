/* Sample solution to racetrack from NWERC'14.
 *
 * Algorithm: start with inner track, then repeat the following:
 * - optimistically remove turns which make the track longer (right
 *   turns at an inner vertex or left turns at an outer vertex)
 * - look for outer vertices that are inside the track/inner vertices
 *   outside the track, and add them to the track at the appropriate
 *   positions
 *
 * Author: Per Austrin
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

const double pi = 2.0*acos(0.0);

struct point {
	int x, y;
	bool outer;
	point(int x=0, int y=0): x(x), y(y) {}
	int cross(const point p) const { return x*p.y - y*p.x; }
	point operator-(const point p) const { return point(x-p.x, y-p.y); }
	int dot(const point p) const { return x*p.x + y*p.y; }
	double dist() { return sqrt(dot(*this)); }
	double angle(const point p) const {
		double r = atan2(p.y, p.x)-atan2(y, x);
		if (r < -pi) r += pi;
		if (r > pi) r -= pi;
		return r;
	}
};

typedef vector<point> vp;
vp inner, outer;

void read(vp &p, bool outer=false) {
	int n;
	scanf("%d", &n);
	p.resize(n);
	for (int i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y), p[i].outer = outer;
}

bool on(point p, point A, point B) {
	return (B-A).cross(p-A) == 0 && (B-A).dot(p-A) >= 0 && (B-A).dot(p-B) <= 0;
}

int inside(point p, const vp &P) {
	double theta = 0;
	for (int i = 0, j = P.size()-1; i < P.size(); j = i++) {
		if (on(p, P[j], P[i])) return 0;
		theta += (P[j]-p).angle(P[i]-p);
	}
	return fabs(theta) > pi/2 ? -1 : 1;
}

double perimeter(const vp &P) {
	double res = 0;
	for (int i = 0, j = P.size()-1; i < P.size(); j = i++)
		res += (P[j]-P[i]).dist();
	return res;
}

bool line_isect(point p1, point p2,
				point q1, point q2) {
	point dp = p2-p1, dq = q2-q1;
	int c = dp.cross(dq), s = dp.cross(p1-q1), t = dq.cross(p1-q1);
	if (c == 0) return false;
	if (c < 0) c = -c, s = -s, t = -t;
	return s > 0 && s <= c && t > 0 && t <= c;
}


int find_pos(vp &P, point a, point b) {
	for (int i = 0, j = P.size()-1; i < P.size(); j = i++)
		if (line_isect(a, b, P[i], P[j])) return i;
	assert(0);
}

bool simplify(vp &P) {
	bool changed = false;
	int n = P.size();
	for (int i = 0; i < n; ++i) {
		int t = (P[i]-P[(i+n-1)%n]).cross(P[(i+1)%n]-P[i]);
		if (t != 0 && (t < 0 ^ P[i].outer)) {
			P.erase(P.begin()+i);
			--n;
			i = max(i-2, -1);
			changed = true;
		}
	}
	return changed;
}

bool extend(vp &P, vp &edge, int sgn) {
	bool changed = false;
	for (int a = 0, b = edge.size()-1; a < edge.size(); b = a++)
		if (inside(edge[a], P) == sgn && inside(edge[b], P) != sgn) {
			P.insert(P.begin()+find_pos(P, edge[a], edge[b]), edge[a]);
			changed = true;
		}
	return changed;
}

int main(void) {
	read(inner);
	read(outer, true);
	vp P = inner;
	while (simplify(P) || extend(P, outer, -1) || extend(P, inner, 1));
	printf("%.9lf\n", perimeter(P));
	for (auto p: P)
		fprintf(stderr, "%d %d\n", p.x, p.y);
	return 0;
}
