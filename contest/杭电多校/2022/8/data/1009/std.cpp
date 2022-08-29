//1009, std
#include<bits/stdc++.h>
#define mset(a, b) memset(a, b, sizeof(a))
#define mcpy(a, b) memcpy(a, b, sizeof(a))
using namespace std;
typedef long long LL;
const int MAXN = 200005;

template <typename T> inline void read(T &WOW) {
    T x = 0, flag = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') flag = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    WOW = flag * x;
}

namespace ModCalculator {
    const int MOD = 1e9 + 7;
    inline void Inc(int &x, int y) {
        x += y; if (x >= MOD) x -= MOD;
    }
    inline int Add(int x, int y) {
        Inc(x, y); return x;
    }
    inline void Dec(int &x, int y) {
        x -= y; if (x < 0) x += MOD;
    }
    inline int Sub(int x, int y) {
        Dec(x, y); return x;
    }
    inline int Mul(int x, int y) {
        return 1LL * x * y % MOD;
    }
}
using namespace ModCalculator;

int n, m, fa[MAXN], ans;
vector<int> acc[MAXN];

int tot, root[MAXN], lc[MAXN * 20], rc[MAXN * 20], prod[MAXN * 20], sum[MAXN * 20];

void pushup(int x) {
    if (!rc[x]) {
        prod[x] = prod[lc[x]];
        sum[x] = sum[lc[x]];
    } else if (!lc[x]) {
        prod[x] = prod[rc[x]];
        sum[x] = sum[rc[x]];
    } else {
        prod[x] = Mul(prod[lc[x]], prod[rc[x]]);
        sum[x] = Add(Mul(sum[lc[x]], prod[rc[x]]), sum[rc[x]]);
    }
}

void Insert(int &rt, int b, int e, int pos, int v1, int v2) {
    if (!rt) rt = ++tot;
    if (b == e) {
        prod[rt] = v1;
        sum[rt] = v2;
        return;
    }
    int mid = (b + e) >> 1;
    if (pos <= mid) Insert(lc[rt], b, mid, pos, v1, v2);
    else Insert(rc[rt], mid + 1, e, pos, v1, v2);
    pushup(rt);
}

int Merge(int x, int y) {
    if (!x || !y) return x + y;
    lc[x] = Merge(lc[x], lc[y]);
    rc[x] = Merge(rc[x], rc[y]);
    pushup(x);
    return x;
}

int Query(int rt, int b, int e, int pos, int rprod) {
    if (b == e) {
        return Mul(sum[rt], rprod);
    }
    int mid = (b + e) >> 1;
    if (pos <= mid) {
        if (rc[rt]) return Query(lc[rt], b, mid, pos, Mul(rprod, prod[rc[rt]]));
        return Query(lc[rt], b, mid, pos, rprod);
    } else {
        return Query(rc[rt], mid + 1, e, pos, rprod);
    }
}

void solve() {
	for (int i = 1; i <= tot; ++i) {
		lc[i] = rc[i] = prod[i] = sum[i] = 0;
	}
	tot = 0;
	read(n); read(m);
	for (int i = 1; i <= n; ++i) {
        acc[i].clear();
		root[i] = 0;
	}
    for (int i = 2; i <= n; ++i) {
        read(fa[i]);
    }
    for (int i = 1, x, c, p; i <= m; ++i) {
        read(x); read(c); read(p);
        Insert(root[x], 1, m, i, Sub(1, p), Mul(c, p));
        acc[x].push_back(i);
    }
    ans = 0;
    for (int i = n; i >= 1; --i) {
        Inc(ans, sum[root[i]]);
        for (auto rnk : acc[i]) {
            Dec(ans, Query(root[i], 1, m, rnk, 1));
        }
        root[fa[i]] = Merge(root[fa[i]], root[i]);
    }
    printf("%d\n", ans);
}

int main() {
    int T; read(T);
    while (T--) {
        solve();
    }
    return 0;
}
