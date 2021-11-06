// O(m + n*log(n))
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int n;

void prop_potential(int u, const vector<vi> &adj, vi &potential, vi &vis) {
    if (vis[u]) return;
    vis[u] = true;
    for (int v: adj[u]) {
        prop_potential(v, adj, potential, vis);
        potential[u] = min(potential[u], potential[v]-1);
    }
}

int solve(const vector<vi> &adj, const vi &e) {
    vi potential(n+1);
    for (int i = 1; i <= n; ++i)
        potential[i] = -e[i];
    vi vis(n+1, false);
    for (int i = 1; i <= n; ++i)
        prop_potential(i, adj, potential, vis);
    vi order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&potential](int i, int j) { return potential[i] < potential[j]; });
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans = max(ans, e[order[i]] + i);
    return ans;
}

int main(void) {
    scanf("%d", &n);
    vector<int> e(n+1);
    vector<vector<int>> adj(n+1);
    for (int i = 1; i <= n; ++i) {
        int indeg;
        scanf("%d%d", &e[i], &indeg);
        for (int j = 0; j < indeg; ++j) {
            int x;
            scanf("%d", &x);
            adj[x].push_back(i);
        }
    }
    printf("%d\n", solve(adj, e));
}
