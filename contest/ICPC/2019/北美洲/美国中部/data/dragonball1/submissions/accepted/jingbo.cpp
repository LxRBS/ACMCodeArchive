#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const long long INF = 1000000000000000000LL;
const int MAXN = 200000;

vector<pair<int, int>> adj[MAXN];

vector<long long> get_shortest_path(int start, int n)
{
    vector<long long> d;
    vector<bool> mark;
    for (int i = 0; i < n; ++ i) {
        d.push_back(INF);
        mark.push_back(false);
    }

    deque<int> q;
    d[start] = 0;
    mark[start] = true;
    q.push_back(start);
    while (q.size()) {
        int u = q.front();
        q.pop_front();
        mark[u] = false;
        for (const auto& edge : adj[u]) {
            int v = edge.second;
            int c = edge.first;
            if (d[u] + c < d[v]) {
                d[v] = d[u] + c;
                if (!mark[v]) {
                    mark[v] = true;
                    if (c == 0) {
                        q.push_front(v);
                    } else {
                        q.push_back(v);
                    }
                }
            }
        }
    }
    return d;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        -- a; -- b;
        adj[a].push_back(make_pair(c, b));
        adj[b].push_back(make_pair(c, a));
    }
    for (int i = 0; i < n; ++ i) {
        sort(adj[i].begin(), adj[i].end());
    }
    vector<int> perm;
    for (int i = 0; i < 7; ++ i) {
        int x;
        scanf("%d", &x);
        -- x;
        perm.push_back(x);
    }
    sort(perm.begin(), perm.end());
    perm.erase(unique(perm.begin(), perm.end()), perm.end());

    m = perm.size();
    long long f[m + 1][m + 1];
    for (int i = 0; i < perm.size(); ++ i) {
        vector<long long> dist = get_shortest_path(perm[i], n);
        for (int j = 0; j < perm.size(); ++ j) {
// fprintf(stderr, "%d -> %d: %d\n", perm[i], perm[j], dist[perm[j]]);
            f[i][j] = dist[perm[j]];
        }
        f[i][m] = f[m][i] = dist[0];
    }

    for (int i = 0; i < m; ++ i) {
        perm[i] = i;
    }

    long long best = INF;
    do {
        long long sum = f[m][perm[0]];
        for (int i = 1; i < m && sum < best; ++ i) {
            sum += f[perm[i - 1]][perm[i]];
        }
// fprintf(stderr, "%lld\n", sum);
        best = min(best, sum);
    } while (next_permutation(perm.begin(), perm.end()));

    if (best < INF) {
        printf("%lld\n", best);
    } else {
        puts("-1");
    }

    return 0;
}
