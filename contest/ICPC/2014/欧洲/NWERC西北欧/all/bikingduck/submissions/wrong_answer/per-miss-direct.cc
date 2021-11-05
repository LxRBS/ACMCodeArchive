/* Sample solution to Underground from NWERC'14
 *
 * Algorithm: try all possible combinations of boundary lines and
 * existing subway stations, ternary search for best points along
 * boundaries
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

struct point {
	double x, y;
	point(double x=0, double y=0): x(x), y(y) {}
	point operator-(point p) { return point(x-p.x, y-p.y); }
	void rot(int H) { y = H-y; swap(x, y); }
	double dist() { return sqrt(x*x+y*y); }
};

double vw, vu;

double walk_time(double WL, double WR, double H, double H0) {
	return sqrt(WL*WL+H0*H0)/vw + sqrt(WR*WR+(H-H0)*(H-H0))/vu;
}

// single choice point
pair<double,double> split(double WL, double WR, double H) {
	double lo = 0, hi = H;
	for (int i = 0; i < 100; ++i) {
		double a = (2*lo+hi)/3, b = (lo+2*hi)/3;
		double ra = walk_time(WL, WR, H, a);
		double rb = walk_time(WL, WR, H, b);
		if (ra < rb) hi = b;
		else lo = a;
	}
	return make_pair(lo, walk_time(WL, WR, H, lo));
}

// subway stations on opposite sides
double split_opp(double WL, double WM, double WR, double H) {
	double y0 = 0, y1 = 0;
	for (int i = 0; i < 100; ++i) {
		y1 = split(WR, WM, H-y0).first;
		y0 = split(WL, WM, H-y1).first;
	}
	return split(WR, WM, H-y0).second + sqrt(WL*WL + y0*y0)/vw;
}

// subway stations on neighboring sides
double split_adj(double W1, double W2, double H1, double H2) {
	double y = 0, x = 0;
	for (int i = 0; i < 100; ++i) {
		x = split(H2, H1-y, W2).first;
		y = split(W1, W2-x, H1).first;
	}
	return split(H2, H1-y, W2).second + sqrt(W1*W1+y*y)/vw;
}

// subway stations on same side
double split_same(double x1, double x2, double H) {
	double y1 = x1*vw/sqrt(vu*vu-vw*vw);
	double y2 = x2*vw/sqrt(vu*vu-vw*vw);
	if (y1+y2 > H) return 1e30;
	return (sqrt(x1*x1+y1*y1)+sqrt(x2*x2+y2*y2))/vw + (H-y1-y2)/vu;
}

int n;
double W, H;
point S, T, P[2000], LB, DIM;

double solve() {
	double r = min(split_opp(S.x, DIM.x, DIM.x-T.x, fabs(S.y-T.y)),
				   min(split_adj(S.x, T.x, S.y, T.y),
					   split_same(S.x, T.x, fabs(S.y-T.y))));
	for (int i = 0; i < n; ++i)
		r = min(r, split(S.x, P[i].x, fabs(S.y-P[i].y)).second + (P[i]-T).dist()/vw);;
	return r;
}

int main(void) {
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%d",
		  &vw, &vu, &LB.x, &LB.y, &DIM.x, &DIM.y, &S.x, &S.y, &T.x, &T.y, &n);
	DIM = DIM - LB;
	S = S - LB;
	T = T - LB;
	for (int i = 0; i < n; ++i) scanf("%lf%lf", &P[i].x, &P[i].y), P[i] = P[i]-LB;
	double res = 1e30;//(S-T).dist()/vw;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			res = min(res, ((S-P[i]).dist()+(T-P[j]).dist())/vw + (P[i]-P[j]).dist()/vu);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j, swap(S, T))
			res = min(res, solve());
		S.rot(DIM.y);
		T.rot(DIM.y);
		for (int j = 0; j < n; ++j) P[j].rot(DIM.y);
		swap(DIM.x, DIM.y);
	}
	printf("%.9lf\n", res);
	return 0;
}
