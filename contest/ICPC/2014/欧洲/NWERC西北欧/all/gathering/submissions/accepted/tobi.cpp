#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long int ll;
typedef ll r[4];
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define INF (2220000000LL)
ll N, D, c[2][100000], orig[2][100000], m[2];

bool cut(r &a, ll o1, ll o2, ll o3, ll o4) {
	r b = {o1, o2, o3, o4};
	FOR(i,0,2) if (a[0+2*i] > b[1+2*i] || b[0+2*i] > a[1+2*i]) return false; // empty
	FOR(i,0,2) {
		a[0+2*i] = max(a[0+2*i], b[0+2*i]);
		a[1+2*i] = min(a[1+2*i], b[1+2*i]);
	}
	return true;
}

ll dist(ll a, ll b) {
	ll total = 0;
	FOR(i, 0, N) total += abs(orig[0][i]-a) + abs(orig[1][i]-b);
	return total;
}

int main() {
	cin >> N;
	FOR(i,0,N) FOR(j,0,2) cin >> c[j][i];
	FOR(i,0,N) FOR(j,0,2) orig[j][i] = c[j][i];
	cin >> D;
	r cur = { -INF, INF, -INF, INF };
	bool poss = true;
	FOR(i, 0, N) poss &= cut(cur, c[0][i]-(c[1][i]+D), c[0][i]-(c[1][i]-D), c[0][i]+c[1][i]-D, c[0][i]+c[1][i]+D);
	if (!poss) cout << "impossible" << endl;
	else {
		FOR(i,0,2) nth_element(c[i], c[i] + N/2, c[i] + N);
		FOR(i,0,2) m[i] = c[i][N/2];
		bool inside = cut(cur, m[0]-m[1], m[0]-m[1], m[0]+m[1], m[0]+m[1]);
		if (!inside) {
			ll best = INF*INF;
			FOR(j, 0, 4) {
				ll minix = -INF;
				ll maxix = INF;
				int factor = j < 2 ? 1 : -1;
				FOR(i,0,52) {
					if (minix + 2 >= maxix) break;
					ll l = minix + (maxix-minix)/3, r = minix + ((maxix-minix)*2)/3;
					if (dist(l,factor*(l-cur[j])) > dist(r,factor*(r-cur[j]))) minix = l;
					else maxix = r;
				}
				FOR(oldx,minix,maxix+1) {
					ll newx = oldx;
					ll newy = factor*(oldx-cur[j]);
					ll newL = newx + factor*newy;
					newL = max(newL, cur[2 - 2*(j/2)]);
					newL = min(newL, cur[3 - 2*(j/2)]);
					newy = factor*(newL - cur[j]+1)/2;
					FOR(k,-1,2) { // avoid rounding issues
						ll newy2 = newy + k;
						newx = cur[j] + factor*newy2;
						r tmp = {newx-newy2, newx-newy2, newx+newy2, newx+newy2};
						if (cut(tmp, cur[0], cur[1], cur[2], cur[3])) best = min(best, dist(newx, newy2));
					}
				}
			}
			cout << best << endl;
		} else cout << dist(m[0], m[1]) << endl;
	}
	return 0;
}
