// O((n+m)*log(n)) [n = #vertices, m = #edges]
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int n;

void prop_deadline(int u, const vector<vi> &adj, vi &deadline, vi &vis) {
    if (vis[u]) return;
    vis[u] = true;
    for (int v: adj[u]) {
        prop_deadline(v, adj, deadline, vis);
        deadline[u] = min(deadline[u], deadline[v]-1);
    }
}

bool ok(int maxlen, const vector<vi> &adj, const vi &e) {
    vi deadline(n+1);
    for (int i = 1; i <= n; ++i)
        deadline[i] = maxlen - e[i];
    vi vis(n+1, false);
    for (int i = 1; i <= n; ++i)
        prop_deadline(i, adj, deadline, vis);
    vi deadline_f(n, 0);
    for (int i = 1; i <= n; ++i) {
        if (deadline[i] < 0) return false;
        if (deadline[i] < n) ++deadline_f[deadline[i]];
    }
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        tot += deadline_f[i];
        if (tot > i+1) return false;
    }
    return true;
}

int main(void) {
    scanf("%d", &n);
    vector<int> e(n+1);
    vector<vector<int>> adj(n+1);
    int lo = 0, hi = 0;
    for (int i = 1; i <= n; ++i) {
        int indeg;
        scanf("%d%d", &e[i], &indeg);
        for (int j = 0; j < indeg; ++j) {
            int x;
            scanf("%d", &x);
            adj[x].push_back(i);
        }
        lo = max(lo, e[i]-1);
    }
    hi = lo + n;
    while (hi-lo > 1) {
        int m = (lo+hi)/2;
        (ok(m, adj, e) ? hi : lo) = m;
    }
    printf("%d\n", hi);
}
