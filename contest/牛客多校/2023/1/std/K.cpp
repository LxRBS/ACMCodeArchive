#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> G(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<int> dis(n + 1, -1);
    vector<int> par(n + 1);
    vector<int> inner(n + 1);
    queue<int> q;
    q.push(1), dis[1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v: G[u]) {
            if (dis[v] != -1) continue;
            q.push(v);
            dis[v] = dis[u] + 1;
            par[v] = u;
            inner[u] = 1;
        }
    }

    ll ans = 1;
    for (int u = 2; u <= n; ++u) {
        if (dis[u] == -1 || dis[u] > k) continue;
        ll cnt = 0;
        for (auto v: G[u]) {
            if (v == par[u] || par[v] == u) continue;
            ++cnt;
        }
        if (!inner[u]) cnt = max(cnt, 1ll);
        ans += (k - dis[u]) * cnt + 1;
    }

    cout << ans << endl;
    return 0;
}
