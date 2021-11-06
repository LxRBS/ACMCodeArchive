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
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}

P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

pair<P, double> mec(vector<P> ps) {
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	rep(i,0,sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
		o = ps[i], r = 0;
		rep(j,0,i) if ((o - ps[j]).dist() > r * EPS) {
			o = (ps[i] + ps[j]) / 2;
			r = (o - ps[i]).dist();
			rep(k,0,j) if ((o - ps[k]).dist() > r * EPS) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = (o - ps[i]).dist();
			}
		}
	}
	return {o, r};
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

            ans = min(ans, 2.0 * mec(projected).second);
        }
    }

    cout << fixed << setprecision(12) << ans << '\n';
    return 0;
}
