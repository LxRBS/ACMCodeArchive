#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define DIST(a, b) (sqrt((a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1])))
#define TRIP(a, b, walk) ((DIST(a,b))/(walk ? vw : vb))
#define HOP(a, b, c, twice) (twice ? (TRIP(a, b, true) + ts(b, c, false)) : (TRIP(a, b, false) + TRIP(b, c, true)))
double vw, vb, m[2][2], s[2][2], b[1005][2], tbl[1005][1005];
int N;

double ts(double src[2], double dest[2], bool twice) { // src-B->boundary-W->dest or src-W->bnd-B->bnd-W->dest
	double ret = 1e9;
	FOR(x, 0, 2) FOR (y, 0, 2) {
		double from = m[0][y], to = m[1][y];
		FOR(i, 0, 100) {
			double b[2] = {from + (to-from)/3, m[x][1-y]};
			double c[2] = {from + (to-from)*2/3, m[x][1-y]};
			if (y == 1) swap(b[0], b[1]), swap(c[0], c[1]);
			if (HOP(src, b, dest, twice) > HOP(src, c, dest, twice)) from = b[y];
			else to = c[y];
		}
		double p[2] = {(from + to)/2, m[x][1-y]};
		if (y == 1) swap(p[0], p[1]);
		ret = min(ret, HOP(src, p, dest, twice));
	}
	return ret;
}

int main() {
	cin >> vw >> vb;
	FOR(i, 0, 2) FOR(j, 0, 2) cin >> m[i][j];
	FOR(i, 0, 2) FOR(j, 0, 2) cin >> s[i][j];
	cin >> N;
	FOR(i, 0, N) FOR(j, 0, 2) cin >> b[i][j];

	FOR(i, 0, N) FOR(j, 0, N) tbl[i][j] = TRIP(b[i], b[j], false);
	FOR(i, 0, N) tbl[N][i] = min(TRIP(b[i], s[0], true), ts(b[i], s[0], false));
	FOR(i, 0, N) tbl[i][N+1] = min(TRIP(b[i], s[1], true), ts(b[i], s[1], false));
	double best = min(TRIP(s[0], s[1], true), ts(s[0], s[1], true));
	FOR(i, 0, N) FOR(j, 0, N) best = min(best, tbl[N][i] + tbl[i][j] + tbl[j][N+1]);

	cout << setprecision(12) << best << endl;
	return 0;
}
