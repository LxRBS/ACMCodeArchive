#include <bits/stdc++.h>
using namespace std;
typedef double D;
const D eps = 1e-9;
struct P {
	D x, y;
	P() {}
	P(D x, D y) : x(x), y(y) {}
	P rot90() { return P(-y, x); }
	D len2() { return x * x + y * y; }
	D len() { return sqrt(len2()); }
	int dim() {
		if (y > eps || (fabs(y) < eps && x > 0)) return 0;
		return 1;
	}
};
P operator + (P a, P b) { return P(a.x + b.x, a.y + b.y); }
P operator - (P a, P b) { return P(a.x - b.x, a.y - b.y); }
P operator / (P a, D b) { return P(a.x / b, a.y / b); }
P operator * (P a, D b) { return P(a.x * b, a.y * b); }
D dot(P a, P b) { return a.x * b.x + a.y * b.y; }
D det(P a, P b) { return a.x * b.y - a.y * b.x; }
pair<P, P> point_circle_tan(P o, D r, P p = P(0, 0)) {
	D d = (o - p).len();
	D a = r * r / d;
	D b = r / d * sqrt((o - p).len2() - r * r);
	P dir = (p - o) / d;
	P t1 = o + dir * a + dir.rot90() * b;
	P t2 = o + dir * a + dir.rot90() * (-b);
	return make_pair(t1, t2);
}
vector<P> circle_circle(P o, D r, P p, D dd) {
	D d = (o - p).len();
	if (d - dd > r) return (vector<P>) {};
	if (dd - d > r) return (vector<P>) {P(), P(), P()};
	D a = (r * r - dd * dd + (o - p).len2()) / (2 * d);
	D b = sqrt(r * r - a * a);
	P dir = (p - o) / d;
	P t1 = o + dir * a + dir.rot90() * b;
	P t2 = o + dir * a + dir.rot90() * (-b);
	return (vector<P>) {t1, t2};
}
const int N = 1e4 + 5;
P o[N];
D r[N];
bool cmp(pair<P, int> a, pair<P, int> b) {
	if (a.first.dim() != b.first.dim()) return a.first.dim() < b.first.dim();
	if (fabs(det(a.first, b.first)) > eps) return det(a.first, b.first) > 0;
	return a.second < b.second;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		int x, y, r;
		scanf("%d%d%d", &x, &y, &r);
		o[i] = P(x, y);
		::r[i] = r;
	}
	int b, dd;
	scanf("%d%d", &b, &dd);
	vector<pair<P, P>> seg;
	for (int i = 0; i < n; ++ i) {
		r[i] += b;
		auto t = point_circle_tan(o[i], r[i]);
		if (det(t.first, t.second) < 0) swap(t.first, t.second);
		auto s = circle_circle(o[i], r[i], P(0, 0), dd);
		if (s.empty()) {
			continue;
		}
		else if ((int) s.size() > 2) {
			seg.push_back(make_pair(t.first, t.second));
		}
		else {
			if (det(s[0], s[1]) < 0) swap(s[0], s[1]);
			if (t.first.len2() > (long long) dd * dd) {
				seg.push_back(make_pair(s[0], s[1]));
			}
			else {
				seg.push_back(make_pair(t.first, t.second));
			}
		}
	}
	int cnt = 0;
	P las = P(1, 0);
	vector<pair<P, int>> signal;
	signal.push_back(make_pair(P(1, 0), 0));
	signal.push_back(make_pair(P(-1, 0), 0));
	for (auto p : seg) {
		if (cmp(make_pair(p.second, 0), make_pair(p.first, 0))) cnt ++;
		signal.emplace_back(p.second, -1);
		signal.emplace_back(p.first, 1);
	}
	sort(signal.begin(), signal.end(), cmp);
	signal.push_back(make_pair(P(1, 0), 0));
	D ans = 0;
	for (auto p : signal) {
		if (cnt == 0) {
			ans += acos(dot(las, p.first / p.first.len()));
		}
		cnt += p.second;
		las = p.first / p.first.len();
	}
	printf("%.10f\n", ans / 2 / acos(-1.));
}

