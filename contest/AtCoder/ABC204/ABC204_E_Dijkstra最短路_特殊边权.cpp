/**
 * 无向图，每条边的边权为 C + D / (t + 1)
 * 其中t为进入该边的时刻。
 * 问从1到N的最短时间。
 * 进入某边的时刻为t，则通过该边后的时刻为 T = t + D / (t + 1) + C
 * 显然 T >= 2sqrt(D) + C - 1， 当且仅当 (t + 1) ^ 2 == D 时取最小值
 * 因此对每个时刻，检查是否可以取最小值即可
 * Dijkstra。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 101;
#else
int const SZ = 110;
#endif

llt const INF = 1E18;

llt f(llt c, llt d, llt now){
    llt x = sqrt(d * 1.L) - 1;
    llt ans = now + c + d / (now + 1);
    for(llt i=max(now, x-3);i<=x+3;++i){
        ans = min(ans, i + c + d / (i + 1));
    }    
    return ans;
}

int N, M;
vector<vector<pair<int, pair<llt, llt>>>> G;

llt proc(){
    __gnu_pbds::priority_queue<pair<int, llt>, function<bool(const pair<int, llt> &, const pair<int, llt> &)>> q(
        [](const pair<int, llt> & a, const pair<int, llt> & b){
            if(a.second != b.second) return a.second > b.second;
            return a.first > b.first;
        }
    );

    vector<llt> d(N + 1, INF);
    vi flag(N + 1, 0);
    q.push({1, d[1] = 0LL});
    while(1){
        while(not q.empty() and 1 == flag[q.top().first]) q.pop();
        if(q.empty()) break;

        auto h = q.top(); q.pop();
        int u = h.first;
        llt now = h.second;
        flag[u] = 1;

        for(const auto & p : G[u]){
            int v = p.first;
            llt c = p.second.first;
            llt w = p.second.second;
            if(1 == flag[v]) continue;

            llt nxt = f(c, w, now);
            if(nxt < d[v]){
                q.push({v, d[v] = nxt});
            }
        }
    }
    return d[N] != INF ? d[N] : -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    G.assign(N + 1, {});
    for(int i=0;i<M;++i){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        // if(a == b) continue;
        G[a].push_back({b, {c, d}});
        G[b].push_back({a, {c, d}});
    }
    cout << proc() << endl;
    return 0;
}