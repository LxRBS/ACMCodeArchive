/**
 * 给定一些先修要求，问修到1的顺序
 * 题目没说，但看起来保证有解
 * 先从1搜一遍所有相关节点，然后做一个拓扑排序即可
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
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

int N;
vvi G, Ig;

void proc(){
    vi nodes;
    nodes.reserve(N);
    vi flag(N + 1, 0);
    flag[1] = 1;
    queue<int> q;
    q.push(1);

    while(not q.empty()){
        auto h = q.front(); q.pop();
        nodes.push_back(h);
        for(auto v : G[h]){
            if(flag[v]) continue;
            flag[v] = 1;
            q.push(v);
        }
    }

    vi deg(N + 1, 0);
    for(auto i : nodes)
    {
        if(0 == (deg[i] = G[i].size())){
            q.push(i);
        }
    }

    vi ans;
    while(not q.empty()){
        auto h = q.front(); q.pop();
        ans.push_back(h);
        for(auto v : Ig[h]){
            if(0 == --deg[v]){
                q.push(v);
            }
        } 
    }
    assert(ans.back() == 1);
    ans.pop_back();
    for(auto i : ans) cout << i << " ";
    return (void)(cout << endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    G.assign(N + 1, vi());
    Ig.assign(N + 1, vi());
    for(int c,p,i=1;i<=N;++i){
        cin >> c;
        for(int j=0;j<c;++j){
            cin >> p;
            G[i].push_back(p);
            Ig[p].push_back(i);
        }
    }
    proc();
    return 0;
}
