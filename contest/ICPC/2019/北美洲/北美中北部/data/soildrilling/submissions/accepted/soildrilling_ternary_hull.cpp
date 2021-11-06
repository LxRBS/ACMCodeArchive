#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

// Template code from KACTL
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef Point<double> P;
constexpr double MAXX = 1001.0;
constexpr double EPS = 1e-8;
constexpr int ITERS = 100;

double f(const vector<P>& ps, double x, double y) {
    double ans = 0.0;
    for (auto& p : ps) {
        double dx = p.x - x;
        double dy = p.y - y;
        ans = max(ans, sqrt(dx * dx + dy * dy));
    }

    return ans;
}

double f(const vector<P>& ps, double x) {
    double y_lo = -MAXX;
    double y_hi = MAXX;
    for (int iter = 0; y_hi - y_lo > EPS and iter < ITERS; ++iter) {
        double y_1 = y_lo + (y_hi - y_lo) / 3.0;
        double y_2 = y_hi - (y_hi - y_lo) / 3.0;

        if (f(ps, x, y_1) < f(ps, x, y_2)) {
            y_hi = y_2;
        } else {
            y_lo = y_1;
        }
    }

    return f(ps, x, (y_lo + y_hi) / 2.0);
}

double mec(const vector<P>& ps) {
    double x_lo = -MAXX;
    double x_hi = MAXX;
    for (int iter = 0; x_hi - x_lo > EPS and iter < ITERS; ++iter) {
        double x_1 = x_lo + (x_hi - x_lo) / 3.0;
        double x_2 = x_hi - (x_hi - x_lo) / 3.0;

        if (f(ps, x_1) < f(ps, x_2)) {
            x_hi = x_2;
        } else {
            x_lo = x_1;
        }
    }

    return f(ps, (x_lo + x_hi) / 2.0);
}

vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		trav(p, pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int main() {
    int n;
    cin >> n;
    vector<array<double, 3>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i][0] >> points[i][1] >> points[i][2];
    }

    double ans = 1e9;
    for (int d0 = 0; d0 < 3; ++d0) {
        for (int d1 = d0 + 1; d1 < 3; ++d1) {
            vector<P> projected;
            for (int i = 0; i < n; ++i) {
                projected.emplace_back(points[i][d0], points[i][d1]);
            }

            ans = min(ans, 2.0 * mec(convexHull(projected)));
        }
    }

    cout << fixed << setprecision(12) << ans << '\n';
    return 0;
}
