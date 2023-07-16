/**
 * 将N个人分为T队，还给出了M对关系，存在关系的人不能分在同一个队
 * 问一共有多少种方法
 * N只有10，可以考虑深搜。
 * 数量最多的情况应该N=10,T=4,M=0的情况，一共有
 * N! * C(9, T) / T! ? 大概是这么多
 * 应该可以。
 * 另外N只有10，可以考虑状压DP。
 * 标程两种方法都给出了。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N, T, M;
vvi G;
llt Ans = 0;
vvi Team;
vvi Flag;

bool isIn(int v, const vi & vec){
    for(auto i : vec)if(i == v) return true;
    return false;
}

void dfs(int cur){
    if(N + 1 == cur){
        bool b = true;
        for(const auto & team : Team){
            if(team.empty()){
                b = false;
                break;
            }
        }
        if(b) ++Ans;
        return;
    }

    bool prev = true;
    for(int i=0;i<T;++i){
        if(!prev) break;
        auto & team = Team[i];
        if(team.empty()) prev = false;

        bool b = true;
        for(auto i : team){
            if(isIn(i, G[cur])){
                b = false;
                break;
            }
        }
        if(not b) continue;

        team.push_back(cur);
        dfs(cur + 1);
        team.pop_back();
    }
    return;
}

llt proc(){
    Team.assign(T, vi());
    Flag.assign(T, vi(N + 1, 0));
    dfs(1);
    return Ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> N >> T >> M;
    G.assign(N + 1, vi());
    for(int i=0;i<M;++i){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    cout << proc() << endl;
    return 0;
}