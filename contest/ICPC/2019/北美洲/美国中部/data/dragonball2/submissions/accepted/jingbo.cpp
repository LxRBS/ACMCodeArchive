#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
const long long INF = 1000000000000000000LL;

long long f[MAXN][1 << 7];
bool mark[MAXN][1 << 7];
vector<pair<int, int>> adj[MAXN];

bool bySecond(const pair<int, int>& a, const pair<int, int>& b)
{
    return a.second < b.second;
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        -- a; -- b;
        adj[a].push_back(make_pair(b, c));
        adj[b].push_back(make_pair(a, c));
    }

    for (int i = 0; i < n; ++ i) {
        sort(adj[i].begin(), adj[i].end(), bySecond);
    }

    vector<int> city(k), color(k);
    for (int i = 0; i < k; ++ i) {
        scanf("%d%d", &city[i], &color[i]);
        -- city[i];
        -- color[i];
    }

    long long answer = INF;
    // 7^7 / 7! = 163.4013888888889
    // let's do it three times more --> should be enough
    for (int iter = 0; iter < 163 * 6; ++ iter) {
        vector<int> mapping(n, 0), item(n, 0);
        for (int i = 0; i < n; ++ i) {
            mapping[i] = rand() % 7;
            // mapping[i] = i;
        }
        for (int i = 0; i < k; ++ i) {
            item[city[i]] |= 1 << mapping[color[i]];
        }
        int all = 0;
        for (int i = 0; i < n; ++ i) {
// fprintf(stderr, "%d %d\n", i, item[i]);
            all |= item[i];
        }
        if (all != (1 << 7) - 1) {
            continue;
        }

        memset(f, -1, sizeof(f));
        memset(mark, false, sizeof(mark));
        f[0][item[0]] = 0;
        deque<pair<int, int>> q;
        q.push_back(make_pair(0, item[0]));
        long long cost = INF;
        while (q.size()) {
            int u = q.front().first;
            int mask = q.front().second;
// fprintf(stderr, "%d %d %d\n", u, mask, f[u][mask]);
            q.pop_front();
            mark[u][mask] = false;

            if (f[u][mask] > cost) {
                continue;
            }
            if (mask == (1 << 7) - 1) {
                cost = f[u][mask];
            } else {
                for (const auto& edge : adj[u]) {
                    int v = edge.first;
                    int c = edge.second;
                    int new_mask = mask | item[v];
                    if (f[v][new_mask] == -1 || f[u][mask] + c < f[v][new_mask]) {
                        f[v][new_mask] = f[u][mask] + c;
                        if (!mark[v][new_mask]) {
                            mark[v][new_mask] = true;
                            if (q.size() && f[v][new_mask] < f[q.front().first][q.front().second]) {
                                q.push_front(make_pair(v, new_mask));
                            } else {
                                q.push_back(make_pair(v, new_mask));
                            }
                        }
                    }
                }
            }
        }

        answer = min(answer ,cost);
    }
    if (answer == INF) {
        puts("-1");
    } else {
        printf("%lld\n", answer);
    }
    return 0;
}
