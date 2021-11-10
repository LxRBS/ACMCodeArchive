#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define rep(i, s, t) for(int i = s, i##end = t; i <= i##end; ++i)
#define per(i, s, t) for(int i = t, i##end = s; i >= i##end; --i)
#define repo(i, s, t) for(int i = s, i##end = t; i < i##end; ++i)
#define debug(x) cerr << #x << " : " << x << endl

const int MAXN = 5005;

int n;
vector <int> g[MAXN];
bool G[MAXN][MAXN];
int X[MAXN], Y[MAXN];

int inputDep = 0, stdDep = 0;

namespace chkInput {
	int fa[MAXN], dep[MAXN], deg[MAXN];
	int getfa(int x) {
		if (fa[x] == x) return x;
		else {
			return fa[x] = getfa(fa[x]);
		}
	}
	void solve() {
		rep (i, 1, n) fa[i] = i, deg[i] = 0;
		per (i, 1, n - 1) {
			int x = X[i], y = Y[i];
			deg[x]++, deg[y]++;
			if (deg[x] > 3 || deg[y] > 3) quitf(_wa, "edge");
			if (!G[x][y]) {
				//ERROR
				quitf(_wa, "edge");
			}
			x = getfa(x), y = getfa(y);
			if (x == y) {
				//ERROR
				quitf(_wa, "edge");
			}
			dep[y] = max(dep[x], dep[y]) + 1;
			inputDep = dep[y];
			fa[x] = y;
		}
		if (deg[1] > 2) quitf(_wa, "edge");
	}
}

namespace BFZ {
	const int INF = 1e9;
	int num, Ea, Eb;
	int sz[MAXN], mark[MAXN][MAXN];
	void getroot(int x,int fa,int sum) {
		sz[x] = 1;
		for (int t : g[x]) {
			if (!mark[x][t] && t != fa) {
				getroot(t, x, sum);
				sz[x] += sz[t];
				int mxsz = max(sz[t], sum - sz[t]);
				if (mxsz < num || (mxsz == num && min(x, t) < min(Ea, Eb)) ||
                    (mxsz == num && min(x, t) == min(Ea, Eb) && max(x, t) < max(Ea, Eb))) {
					num = mxsz;
					Ea = x, Eb = t;
				}
			}
		}
	}
	int partation(int x,int sum) {
	    num = INF;
	    getroot(x, 0, sum);
	    if(num == INF) {
	        return 0;
	    }
	    mark[Ea][Eb] = mark[Eb][Ea] = true;

	    int A = Ea, B = Eb, SA = sum - sz[Eb], SB = sz[Eb];
	    return 1 + max(
	    	partation(A, SA),
	    	partation(B, SB)
	    );
	}
	void solve() {
		stdDep = partation(1, n);
	}
}

int main(int argc, char* argv[]) {
  	registerTestlibCmd(argc, argv);

	n = ouf.readInt(0, 5000, "sum of numbers");

	rep (i, 1, n - 1) {
		int x, y;
		x = ouf.readInt(1, n, "x");
		y = ouf.readInt(1, n, "y");
		X[i] = x, Y[i] = y;

		g[x].push_back(y);
		g[y].push_back(x);
		G[x][y] = G[y][x] = true;
	}
	chkInput::solve();
	BFZ::solve();
//	debug(inputDep);
//	debug(stdDep);
	if (inputDep + 1 < stdDep) {
		quitf(_ok, "");
	}
	else {
		quitf(_wa, "dep");
	}

	return 0;
}

