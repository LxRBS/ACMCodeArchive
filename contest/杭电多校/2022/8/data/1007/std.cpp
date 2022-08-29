//1007, std
#include<bits/stdc++.h>
#define mset(a, b) memset(a, b, sizeof(a))
#define mcpy(a, b) memcpy(a, b, sizeof(a))
using namespace std;
typedef long long LL;
const int MAXN = 50005;

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

int n, p[MAXN], pos[MAXN], ufs[MAXN];

int getf(int x) {
    return (ufs[x] == x)? x : ufs[x] = getf(ufs[x]);
}

struct Edge {
    int u, v, nxt;
} e[MAXN * 460];
int first[MAXN], eCnt;

inline void AddEdge(int w, int u, int v) {
    e[++eCnt].u = u;
    e[eCnt].v = v;
    e[eCnt].nxt = first[w];
    first[w] = eCnt;
}

void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(p[i]);
        pos[p[i]] = i;
        ufs[i] = i;
        first[i] = 0;
    }
    eCnt = 0;
    int m = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= i + m && j <= n; ++j) {
            int tmp = (j - i) * abs(p[j] - p[i]);
            if (tmp < n) {
                AddEdge(tmp, i, j);
            }
            tmp = (j - i) * abs(pos[j] - pos[i]);
            if (tmp < n) {
                AddEdge(tmp, pos[i], pos[j]);
            }
        }
    }
    LL ans = 0;
    int cnt = n - 1;
    for (int i = 1; i < n; ++i) {
        for (int j = first[i]; j; j = e[j].nxt) {
            int u = getf(e[j].u), v = getf(e[j].v);
            if (u == v) continue;
            ufs[u] = v;
            ans += i;
            --cnt;
        }
        if (cnt == 0) break;
    }
    printf("%lld\n", ans);
}

int main() {
    int T; read(T);
    while (T--) {
        solve();
    }
    return 0;
}
