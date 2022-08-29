//1010, std
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
struct Point {
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	inline bool operator == (const Point &rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	inline bool operator < (const Point &rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}
	inline Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	inline Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	inline long long operator * (const Point &rhs) const {
		return 1ll * x * rhs.x + 1ll * y * rhs.y;
	}
	inline long long operator ^ (const Point &rhs) const {
		return 1ll * x * rhs.y - 1ll * y * rhs.x;
	}
	inline long long len2() {
		return 1ll * x * x + 1ll * y * y;
	}
}p[maxn];
const Point dir[4] = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)};
int n, q;
vector<Point> v;
inline int Left(const Point &a, const Point &b, const Point &c) {
	return ((b - a) ^ (c - a)) >= 0;
}
Point base;
inline vector<Point> Convex(vector<Point>a) {
	int n = a.size(), cnt = 0;
	if(n < 3)
		return a;
	base = a[0];
	for(auto p : a)
		if(make_pair(p.x, p.y) < make_pair(base.x, base.y))
			base = p;
	sort(a.begin(), a.end(), [](const Point &a, const Point &b) {
		long long d = ((a - base) ^ (b - base));
		if(d)
			return d > 0;
		return (a - base).len2() < (b - base).len2();
	});
	vector<Point>res;
	for(int i = 0; i < n; ++ i) {
		while(cnt > 1 && Left(res[cnt - 2], a[i], res[cnt - 1]))
			-- cnt, res.pop_back();
		res.push_back(a[i]), ++ cnt;
	}
	int fixed = cnt;
	for(int i = n - 2; ~i; -- i) {
		while(cnt > fixed && Left(res[cnt - 2], a[i], res[cnt - 1]))
			-- cnt, res.pop_back();
		res.push_back(a[i]), ++ cnt;
	}
	res.pop_back();
	return res;
}
long long ori, sum;
int T;
int main() {
	for(scanf("%d", &T); T --; ) {
		scanf("%d%d", &n, &q);
		v.clear();
		for(int i = 1; i <= n; ++ i) {
			scanf("%d%d", &p[i].x, &p[i].y);
			for(int j = 0; j < 4; ++ j)
				v.push_back(p[i] + dir[j]);
		}
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		v = Convex(v);
		v.push_back(v[0]);
		ori = sum = 0;
		for(int i = 0; i + 1 < (int)v.size(); ++ i)
			ori += abs((v[i] - v[0]) ^ (v[i + 1] - v[0]));
		int cnt = 0;
		for(int i = 0; i + 1 < (int)v.size(); ++ i) {
			long long dx = abs(v[i].x - v[i + 1].x), dy = abs(v[i].y - v[i + 1].y);
			sum += max(dx, dy);
			if(dx == dy)
				++ cnt;
		}
		assert(cnt == 4);
		for(int t; q --; ) {
			scanf("%d", &t);
			-- t;
			long long ans = ori + 2ll * sum * t + 4ll * t * t;
			printf("%lld.%d\n", ans >> 1, ans & 1 ? 5 : 0);
		}
	}
}