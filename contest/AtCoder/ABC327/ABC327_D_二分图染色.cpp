/**
 * 给定两个数组A和B，问是否存在01数组X，满足
 * X[Ai] != X[Bi], 对所有的i
 * 显然每一对(Ai, Bi)必须分属不同的部分，因此就是一个二分染色的问题
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
vi A, B;
vi Flag;
vvi G;

bool dfs(int u){
    auto need = Flag[u] ^ 3;
    for(auto v : G[u]){
        if(0 == Flag[v]){
            Flag[v] = need;
            auto b = dfs(v);
            if(not b) return false;
        }
        if(Flag[v] != need) return false;
    }
    return true;
}

bool proc(){
    G.assign(N + 1, vi());
    for(int a,b,i=0;i<M;++i){
        a = A[i]; b = B[i];
        G[a].push_back(b);
        G[b].push_back(a);
    }

    Flag.assign(N + 1, 0);
    for(int i=1;i<=N;++i){
        if(0 == Flag[i]){
            Flag[i] = 1;
            auto b = dfs(i);
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
    cin >> N >> M;
    A.assign(M, 0);
    B.assign(M, 0);
    for(auto & i : A) cin >> i;
    for(auto & i : B) cin >> i;
    cout << (proc() ? "Yes" : "No") << endl;
    return 0;
}