#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
int n, q;
vector<int> e[N];
vector<int> a, b, c;
int l[N], r[N];
int cnt;

namespace lca {
    int dep[N], son[N], sz[N], top[N], fa[N];
    void dfs1(int x) {
        sz[x] = 1;
        son[x] = -1;
        for (auto p : e[x]) {
            if (p == fa[x]) continue;
            fa[p] = x; dep[p] = dep[x] + 1;
            dfs1(p);
            sz[x] += sz[p];
            if (son[x] == -1 || sz[son[x]] < sz[p])
                son[x] = p;
        }
    }
    void dfs2(int x, int tv) {
        top[x] = tv;
        if (son[x] == -1) return;
        dfs2(son[x], tv);
        for (auto p : e[x]) {
            if (p == fa[x] || p == son[x]) continue;
            dfs2(p, p);
        }
    }
    void init(int s) {
        fa[s] = -1; dep[s] = 0;
        dfs1(s);
        dfs2(s, s);
    }
    int lca(int x, int y) {
        while (top[x] != top[y])
            if (dep[top[x]] >= dep[top[y]]) x = fa[top[x]];
            else y = fa[top[y]];
        return dep[x] < dep[y] ? x : y;
    }
}

void dfs(int x) {
    l[x] = ++cnt;
    for (int p : e[x]) {
        dfs(p);
    }
    r[x] = cnt;
}

int calc(vector<int> &a, const vector<int> &c) {
    sort(a.begin(), a.end(), [](int x, int y) {
        return l[x] < l[y];
    });
    int left = 0, res = 0;
    for (int cc : c) {
        while (left < (int)a.size() && l[a[left]] < l[cc]) {
            left++;
        }
        int right = left;
        while (right < (int)a.size() && l[a[right]] <= r[cc]) {
            right++;
        }
        for (int i = left; i < right; i++) {
            res += lca::dep[a[i]] - lca::dep[cc] + 1;
        }
        for (int i = left; i < right - 1; i++) {
            res -= lca::dep[lca::lca(a[i], a[i + 1])] - lca::dep[cc] + 1;
        }

        left = right;
    }

    return res;
}

void solve() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        e[i].clear();
    }
    cnt = 0;

    for (int i = 2; i <= n; i++) {
        int fa;
        scanf("%d", &fa);
        e[fa].push_back(i);
    }
    dfs(1);
    lca::init(1);

    while (q--) {
        {
            int A, B, C;
            scanf("%d%d%d", &A, &B, &C);
            a.assign(A, 0);
            b.assign(B, 0);
            c.assign(C, 0);
        }
        for (int i = 0; i < (int)a.size(); i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < (int)b.size(); i++) {
            scanf("%d", &b[i]);
        }
        for (int i = 0; i < (int)c.size(); i++) {
            scanf("%d", &c[i]);
        }

        sort(c.begin(), c.end(), [](int x, int y) {
            return l[x] < l[y];
        });
        int pre = 0;
        for (int i = 1; i < (int)c.size(); i++) {
            if (l[c[pre]] <= l[c[i]] && l[c[i]] <= r[c[pre]]) {}
            else {
                pre++;
                c[pre] = c[i];
            }
        }
        c.erase(c.begin() + pre + 1, c.end());

        int ans = calc(a, c) + calc(b, c);
        for (int i : b) {
            a.push_back(i);
        }
        ans -= calc(a, c);
        printf("%d\n", ans);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}