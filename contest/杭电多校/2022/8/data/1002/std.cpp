//1002, std
#include<bits/stdc++.h>
#define mset(a, b) memset(a, b, sizeof(a))
#define mcpy(a, b) memcpy(a, b, sizeof(a))
#define lc (rt << 1)
#define rc (rt << 1) | 1
using namespace std;
typedef long long LL;
const int MAXN = 300005;

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
    const int MOD = 998244353;
    inline void Inc(int &x, int y) {
        x += y; if (x >= MOD) x -= MOD;
    }
    inline int Add(int x, int y) {
        Inc(x, y); return x;
    }
}
using namespace ModCalculator;

int n, a[MAXN], dp[MAXN], stk1[MAXN], top1, stk2[MAXN], top2;

struct SegmentTree {
    int mx[MAXN << 2], tag[MAXN << 2], sum[MAXN << 2];

    inline void puttag(int rt, int tg) {
        mx[rt] += tg;
        tag[rt] += tg;
    }

    inline void pushdown(int rt) {
        if (tag[rt]) {
            puttag(lc, tag[rt]);
            puttag(rc, tag[rt]);
            tag[rt] = 0;
        }
    }

    inline void pushup(int rt) {
        mx[rt] = max(mx[lc], mx[rc]);
        sum[rt] = 0;
        if (mx[rt] == mx[lc]) {
            Inc(sum[rt], sum[lc]);
        }
        if (mx[rt] == mx[rc]) {
            Inc(sum[rt], sum[rc]);
        }
    }

    void Build(int rt, int b, int e) {
        mx[rt] = tag[rt] = sum[rt] = 0;
        if (b == e) return;
        int mid = (b + e) >> 1;
        Build(lc, b, mid);
        Build(rc, mid + 1, e);
    }

    void Insert(int rt, int b, int e, int pos, int val) {
        if (b == e) {
            sum[rt] = val;
            return;
        }
        int mid = (b + e) >> 1;
        pushdown(rt);
        if (pos <=  mid) Insert(lc, b, mid, pos, val);
        else Insert(rc, mid + 1, e, pos, val);
        pushup(rt);
    }

    void Update(int rt, int b, int e, int l, int r, int v) {
        if (l <= b && e <= r) {
            puttag(rt, v);
            return;
        }
        int mid = (b + e) >> 1;
        pushdown(rt);
        if (l <= mid) Update(lc, b, mid, l, r, v);
        if (r > mid) Update(rc, mid + 1, e, l, r, v);
        pushup(rt);
    }
} seg[2];

void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    seg[0].Build(1, 1, n);
    seg[1].Build(1, 1, n);
    top1 = top2 = 0;
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        seg[(i & 1)].Insert(1, 1, n, i, dp[i - 1]);
        while (top1 && a[i] > a[stk1[top1]]) {
            seg[(stk1[top1] & 1)].Update(1, 1, n, stk1[top1 - 1] + 1, stk1[top1], -1);
            --top1;
        }
        stk1[++top1] = i;
        seg[(i & 1)].Update(1, 1, n, stk1[top1 - 1] + 1, i, 1);
        while (top2 && a[i] < a[stk2[top2]]) {
            seg[(stk2[top2] & 1) ^ 1].Update(1, 1, n, stk2[top2 - 1] + 1, stk2[top2], -1);
            --top2;
        }
        stk2[++top2] = i;
        seg[(i & 1) ^ 1].Update(1, 1, n, stk2[top2 - 1] + 1, i, 1);
        dp[i] = 0;
        if (seg[0].mx[1] == 2) {
            Inc(dp[i], seg[0].sum[1]);
        }
        if (seg[1].mx[1] == 2) {
            Inc(dp[i], seg[1].sum[1]);
        }
    }
    printf("%d\n", dp[n]);
}

int main() {
    int T; read(T);
    while (T--) {
        solve();
    }
    return 0;
}
