#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tup;
const int N = 1000005;
int n, m, cross[N][4], dis[N][4];
bool vis[N][4];
unordered_map<int, int> id[N];
int st1, st2, en1, en2;
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> cross[i][j];
            if (cross[i][j]) id[i][cross[i][j]] = j;
        }
    }
    cin >> st1 >> st2 >> en1 >> en2;
    memset(dis, 0x3f, sizeof(dis));
    int idx = id[st2][st1];
    dis[st2][idx] = 0;
    priority_queue<tup, vector<tup>, greater<tup>> PQ;
    PQ.push({0, st2, idx});
    while (!PQ.empty()) {
        auto [d, u, x] = PQ.top();
        PQ.pop();
        if (vis[u][x]) continue;
        vis[u][x] = true;
        for (int i = 0; i < 4; i++) {
            int delta = (i != (x + 1) % 4);
            int v = cross[u][i];
            if (!v) continue;
            int j = id[v][u];
            if (d + delta < dis[v][j]) {
                dis[v][j] = d + delta;
                PQ.push({dis[v][j], v, j});
            }
        }
    }
    int ans = dis[en2][id[en2][en1]];
    if (ans > n * 4) {
        ans = -1;
    }
    cout << ans; 
}