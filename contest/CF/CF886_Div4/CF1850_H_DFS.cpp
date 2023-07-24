/**
 * 数轴上有N个点，M个条件，(N在1E5, M<=N)
 * 每个条件格式为: a b w
 * 表示 a坐标 + w == b坐标
 * 问是否存在满足所有条件的点的坐标
 * 直接使用差分约束会超时 T^T
 * 注意到全是等于关系，直接深搜即可
 * 注意图很有可能是不连通的 T^T
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

llt const INF = 0x3F3F3F3FFFFFFFFF;

int S;
int N, M;
vector<vector<pair<int, llt>>> G;
map<int, llt> X;

bool dfs(int u, int p){
    auto x = X[u];
    for(const auto & pp : G[u]){
        if(pp.first == p) continue;

        auto it = X.find(pp.first);
        if(it == X.end()){
            it = X.insert(it, {pp.first, x + pp.second});
            bool b = dfs(pp.first, u);
            if(not b) return false;
        }else{
            if(it->second != x + pp.second) return false;
        }
    }
    return true;
}

bool proc(){
    X.clear();
    for(int i=1;i<=N;++i){
        auto it = X.find(i);
        if(it == X.end()){
            it = X.insert(it, {i, 0});
            bool b = dfs(i, 0);
            if(not b) return false;
        }
    }    
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;    
    while(nofkase--){
        cin >> N >> M;
        G.assign(N + 1, vector<pair<int, llt>>());
        for(int a,b,w,i=0;i<M;++i){
            cin >> a >> b >> w;
            G[a].emplace_back(b, w);
            G[b].emplace_back(a, -w);
        }

        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}

