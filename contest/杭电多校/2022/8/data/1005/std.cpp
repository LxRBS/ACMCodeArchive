//1005, std
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

int n, m, a[MAXN], b[MAXN], clean[MAXN], tim;
int L[MAXN], R[MAXN];

int pr[MAXN], pcnt, vis[MAXN], low[MAXN];
vector<int> pos[MAXN];

bool Check(int p, int l, int r) {
    if (!pos[p].size() || pos[p].back() < l) return 0;
    int x = *lower_bound(pos[p].begin(), pos[p].end(), l);
    return (x <= r);
}

void sieve() {
    n = 200000;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            pr[++pcnt] = i;
            low[i] = i;
        }
        for (int j = 1; j <= pcnt && i * pr[j] <= n; ++j) {
            vis[i * pr[j]] = 1;
            low[i * pr[j]] = pr[j];
            if (i % pr[j] == 0) break;
        }
    }
}

void solve() {
    read(n); read(m);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    for (int i = 1; i < n; ++i) {
        read(b[i]);
    }
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        while (x > 1) {
            int nowp = low[x];
            while (nowp == low[x]) {
                x /= nowp;
            }
            if (clean[nowp] != tim) {
                pos[nowp].clear();
                clean[nowp] = tim;
            }
            pos[nowp].push_back(i);
        }
    }
    ++tim;

    for (int i = n; i >= 1; --i) {
        R[i] = i;
        while (R[i] < n && Check(b[R[i]], i, R[i])) {
            R[i] = R[R[i] + 1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (i > 1 && R[i - 1] >= i) {
            if (Check(b[i - 1], i, R[i])) {
                L[i] = L[i - 1];
                R[i] = R[i - 1];
            } else {
                L[i] = i;
            }
        } else {
            L[i] = i;
            while (1) {
                bool flag = 0;
                while (R[i] < n && Check(b[R[i]], L[i], R[i])) {
                    flag = 1;
                    R[i] = R[R[i] + 1];
                }
                while (L[i] > 1 && Check(b[L[i] - 1], L[i], R[i])) {
                    flag = 1;
                    L[i] = L[L[i] - 1];
                }
                if (!flag) break;
            }
        }
//cerr << L[i] << ' ' << R[i] << endl;
    }

    for (int i = 1, x, y; i <= m; ++i) {
        read(x); read(y);
        if (L[x] <= y && y <= R[x]) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
}

int main() {
    sieve();
    int T; read(T);
    while (T--) {
        solve();
    }
    return 0;
}
