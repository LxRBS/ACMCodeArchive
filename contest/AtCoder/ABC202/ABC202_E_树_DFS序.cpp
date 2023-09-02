/**
 * 给定一个树，Q个询问，每次询问：u, d
 * 问深度为d且是节点u的子孙的节点一共有多少个？
 * 做一遍深搜，记录出入的时间戳，再对每个深度depth，记录进入的时间戳
 * 对每一个询问，拿出d的所有时间戳，在[INu, Outu)之间的就是深度为d且是u的后继的节点
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

int N;
vi P;
int Q;
vvi G;

vvi Depth;
vector<pii> Time;
int TimeStamp;

void dfs(int u, int depth){
    Depth[depth].push_back(Time[u].first = ++TimeStamp);
    for(int v : G[u]){
        dfs(v, depth + 1);
    }
    Time[u].second = ++TimeStamp;
}

int proc(int u, int depth){
    int a = Time[u].first, b = Time[u].second;
    const auto & vec = Depth[depth];
    auto pa = lower_bound(vec.begin(), vec.end(), a);
    auto pb = lower_bound(vec.begin(), vec.end(), b);
    int ans = pb - pa;
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    P.assign(N + 1, 0);
    G.assign(N + 1, vi());
    for(int p,i=2;i<=N;++i){
        cin >> p;
        G[p].push_back(i);
    }    

    TimeStamp = 0;
    Time.assign(N + 1, {});
    Depth.assign(N, {});
    dfs(1, 0);
    
    cin >> Q;
    for(int q=1;q<=Q;++q){
        int u, d;
        cin >> u >> d;
        cout << proc(u, d) << endl;    
    }
    return 0;
}