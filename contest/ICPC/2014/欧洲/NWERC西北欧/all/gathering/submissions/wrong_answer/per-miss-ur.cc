/* Sample solution to gathering from NWERC'14.
 *
 * Algorithm: gather list of candidate x coordinates: x coordinates of
 * input points, x coordinates of the four vertices of polytope, and x
 * coords of points on the edge of the polytope having the Y
 * coordinate of some input point.  For each candidate x-coordinate,
 * compute range of possible y's, solve 1D problems independently
 * (given an interval of possible y positions, it is optimal to be as
 * close to median y-value as possible)
 *
 * Author: Per Austrin
 */
#include <algorithm>
#include <cstdio>

typedef long long ll;
using namespace std;
const ll oo = 1LL<<50;
int N;
ll X[200000], Y[200000], d;
ll Xsl[200000], Ysl[200000];
ll Xsr[200000], Ysr[200000];

void calc_sum(ll *v, ll *vsl, ll *vsr) {
	sort(v, v+N);
	vsl[0] = 0;
	for (int i = 1; i < N; ++i)
		vsl[i] = vsl[i-1]+(ll)i*(v[i]-v[i-1]);
	vsr[N-1] = 0;
	for (int i = N-2; i >= 0; --i)
		vsr[i] = vsr[i+1]+(ll)(N-i-1)*(v[i+1]-v[i]);
}

ll cost(ll val, ll *v, ll *vsl, ll *vsr) {
	int pos = upper_bound(v, v+N, val)-v;
	if (pos == 0) return vsr[0] + (ll)N*(v[0]-val);
	if (pos == N) return vsl[N-1]+(ll)N*(val-v[N-1]);
	return vsl[pos-1] + (ll)pos*(val-v[pos-1]) + vsr[pos] + (ll)(N-pos)*(v[pos]-val);
}

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%lld%lld", X+i, Y+i);
	scanf("%lld", &d);
	ll xpy_lb = -oo, xpy_ub = oo;
	ll xmy_lb = -oo, xmy_ub = oo;
	for (int i = 0; i < N; ++i) {
		xpy_lb = max(xpy_lb, X[i]+Y[i]-d);
		xpy_ub = min(xpy_ub, X[i]+Y[i]+d);
		xmy_lb = max(xmy_lb, X[i]-Y[i]-d);
		xmy_ub = min(xmy_ub, X[i]-Y[i]+d);
	}
	calc_sum(X, Xsl, Xsr);
	calc_sum(Y, Ysl, Ysr);
	vector<ll> X_cand(X, X+N);
	for (int b = 0; b < 2; ++b) { // polytope vertices, rounded up and down
		X_cand.push_back((xpy_lb+xmy_lb+b)/2); // left
		X_cand.push_back((xpy_ub+xmy_lb+b)/2); // top
		X_cand.push_back((xpy_lb+xmy_ub+b)/2); // bot
		X_cand.push_back((xpy_ub+xmy_ub+b)/2); // right
	}
	for (int i = 0; i < N; ++i) { // points along edges with interesting y coord
		X_cand.push_back(Y[i]+xmy_lb); // upper left
		X_cand.push_back(Y[i]+xmy_ub); // lower right
		X_cand.push_back(xpy_lb-Y[i]); // lower left
		//X_cand.push_back(xpy_ub-Y[i]); // upper right
	}
	ll res = oo;
	for (auto x: X_cand) {
		ll y_lb = max(xpy_lb-x, x-xmy_ub);
		ll y_ub = min(xpy_ub-x, x-xmy_lb);
		if (y_lb > y_ub) continue;
		ll y = y_ub >= Y[N/2] ? y_lb <= Y[N/2] ? Y[N/2] : y_lb : y_ub;
		res = min(res, cost(x, X, Xsl, Xsr) + cost(y, Y, Ysl, Ysr));
	}
	if (res == oo) printf("impossible\n");
	else printf("%lld\n", res);
	return 0;
}
