/* Sample solution to findline from NWERC'14.
 *
 * Algorithm: divide and conquer: find all lines with at least p
 * fraction points in both halves and extend.  There can be O(1/p)
 * such lines and the running time is O(N*log(N)/p).
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <cmath>
#include <map>

using namespace std;
typedef long long ll;

struct point {
	ll x, y;
	point(ll x=0, ll y=0): x(x), y(y) {}
	point operator-(const point &p) const {return point(x-p.x, y-p.y); }
	ll cross(const point &p) const { return x*p.y - y*p.x; }
};

struct line {
	point p0, dp;
	line(const point A, const point B): p0(A), dp(B-A) {
		if (dp.x < 0 || dp.x == 0 && dp.y < 0) dp.x = -dp.x, dp.y = -dp.y;
	}
	bool on(const point &p) const { return dp.cross(p-p0) == 0; }
	bool operator<(const line &l) const {
		if (dp.cross(l.dp) != 0) return dp.cross(l.dp) < 0;
		return dp.cross(l.p0-p0) < 0;
	}
};

typedef map<line, int> mli;

int p;
point P[1<<20];

bool findlines(int l, int r, mli &lines) {
	if (r-l < 3) return true;
	if (r-l <= 10) {
		for (int i = l; i < r; ++i)
			for (int j = l; j < i; ++j)
				++lines[line(P[i], P[j])];
		for (auto &lc: lines) lc.second = int((1.0+sqrt(1.0+8.0*lc.second))/2.0+0.5);
	} else {
		mli lines2;
		findlines(l, (l+r)/2, lines);
		findlines((l+r)/2, r, lines2);
		for (auto &lc: lines)
			for (int i = (l+r)/2; i < r; ++i)
				lc.second += lc.first.on(P[i]);
		for (auto &lc: lines2)
			if (lines.find(lc.first) == lines.end()) {
				for (int i = l; i < (l+r)/2; ++i)
					lc.second += lc.first.on(P[i]);
				lines[lc.first] += lc.second;
			}
	}
	for (mli::iterator it = lines.begin(); it != lines.end(); )
		if (100*it->second < p*(r-l)) it = lines.erase(it++);
		else ++it;
	return !lines.empty();
}

int main(void) {
	int n;
	scanf("%d%d", &n, &p);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &P[i].x, &P[i].y);
	mli lines;
	printf("%spossible\n", findlines(0, n, lines) ? "" : "im");
	return 0;
}
