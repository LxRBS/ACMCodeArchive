#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using std::max, std::priority_queue, std::pair;
using ll = long long;

const int maxn = 1e6 + 5;
int e[maxn << 3][3], head[maxn << 2], tot = -1;
int dep[maxn << 2], maxdep = 0, n = 0, k = 0, p = 0, s = 0, t = 0;

void addEdge(int u, int v, int w) {
    e[++tot][0] = v;
    e[tot][1] = head[u];
    e[tot][2] = w;
    head[u] = tot;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    maxdep = max(maxdep, dep[u]);
    for (int i = head[u]; ~i; i = e[i][1]) {
        if (e[i][0] == fa)
            continue;
        dfs(e[i][0], u);
    }
}

ll dis[maxn << 2];
bool vis[maxn << 2];
void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; ~i; i = e[i][1]) {
            int v = e[i][0], w = e[i][2];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.emplace(-dis[v], v);
            }
        }
    }
}

void solve() {
    memset(head, -1, sizeof(head));
    tot = -1, maxdep = 0;
    scanf("%d", &n);
    int u = 0, v = 0, w = 0;
    for (int i = 1; i <= n - 1; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w), addEdge(v, u, w);
    }
    dep[0] = -1;
    dfs(1, 0);
    scanf("%d %d", &k, &p);
    for (int i = 1; i <= n; ++i) {
        if (dep[i] != 0)
            addEdge(n + 2 * dep[i] - 1, i, p);
        if (dep[i] != maxdep)
            addEdge(n + 2 * (dep[i] + 1), i, p);
        if (dep[i] + k <= maxdep)
            addEdge(i, n + 2 * (dep[i] + k) - 1, 0);
        if (dep[i] - k >= 0)
            addEdge(i, n + 2 * (dep[i] - k + 1), 0);
    }
    scanf("%d %d", &s, &t);
    dijkstra();
    printf("%lld\n", dis[t]);
}

int main() {
    int T = 0;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas)
        solve();
    return 0;
}