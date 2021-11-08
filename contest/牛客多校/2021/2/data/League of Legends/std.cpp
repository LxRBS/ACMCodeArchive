#include <bits/stdc++.h>

using namespace std;

#define MS(a, b) memset(a, b, sizeof(a))
#define REP(a, b, c) for (register int a = b, _n = c; a <= _n; ++a)
#define DREP(a, b, c) for (register int a = b, _n = c; a >= _n; --a)
#define FOR(a, b, c) for (register int a = b, _n = c; a < _n; ++a)
#define EREP(a, b) for (register int a = head[b]; a; a = edge[a].nxt)

inline int rd () {
    int x = 0; char c = getchar(); bool f = 0;
    while (c < '0' && c != '-') c = getchar();
    if (c == '-') f = 1, c = getchar();
    while (c >= '0') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return f ? -x : x;
}

const int SIZE = 4005;

int n, m, K;
struct Node {
    int L, R;
    bool operator < (const Node& x1) const {
        if (L == x1.L) return R > x1.R;
        return L < x1.L;
    }
} a[SIZE], b[SIZE];

int dp[SIZE][SIZE];

int Q[SIZE], hed, tal;
int len[SIZE], N;
void main () {
    n = rd(), K = rd();
    REP (i, 1, n) a[i].L = rd(), a[i].R = rd();

    sort(a + 1, a + n + 1);
    int mi = 2e9;
    DREP (i, n, 1) {
        if (mi <= a[i].R) len[++N] = a[i].R - a[i].L;
        else mi = a[i].R, b[++m] = a[i];
    }
    sort(len + 1, len + N + 1, greater<int>());


    MS(dp, -1);
    dp[0][0] = 0;

    reverse(b + 1, b + m + 1);
    REP (i, 1, K) {
        hed = 1, tal = 0;
        REP (j, 1, m) {
            if (~dp[i - 1][j - 1]) {
                while (hed <= tal && dp[i - 1][Q[tal]] + b[Q[tal] + 1].R <= dp[i - 1][j - 1] + b[j].R) --tal;
                Q[++tal] = j - 1;
            }
            while (hed <= tal && b[Q[hed] + 1].R <= b[j].L) ++hed;
            if (hed <= tal) dp[i][j] = dp[i - 1][Q[hed]] + b[Q[hed] + 1].R - b[j].L;
        }
    }

    int ans = 0, sum = 0;
    REP (i, 0, min(K, N)) {
        sum += len[i];
        if (~dp[K - i][m]) ans = max(ans, sum + dp[K - i][m]);
    }

    printf ("%d\n", ans);
}

