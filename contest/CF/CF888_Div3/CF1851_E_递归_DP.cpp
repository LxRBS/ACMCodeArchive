/**
 * N种药，每种药可以有两种获取方式
 * 1. 直接买，价格为ci
 * 2. 由另外mi种药合成，保证合成不会形成环
 * 初始时已经拥有了其中K种。
 * 问对每一种药，想要获取的最低价格
 * 用自顶向下的DP实现即可
 * Di = min(ci, SIGMA{Dj})
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

int N, K;
vector<llt> Price;
set<int> Have;
vvi Mix;
vector<llt> D;

llt dfs(int u){
    if(D[u] != -1) return D[u];

    llt ans = Price[u];
    llt tmp = -1;
    if(!Mix[u].empty()){
        tmp = 0;
        for(auto i : Mix[u]) tmp += dfs(i);
    }
    if(-1 == tmp) return D[u] = ans;
    return D[u] = min(ans, tmp);
}

void proc(){
    D.assign(N, -1);
    for(int i : Have) D[i] = 0;

    for(int i=0;i<N;++i) cout << dfs(i) << " ";
    return (void)(cout << endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> K;
        Price.assign(N, 0);
        for(auto & i : Price) cin >> i;
        Have.clear();
        for(int a,i=0;i<K;++i){
            cin >> a;
            Have.insert(a - 1);
        }
        Mix.assign(N, vi());
        for(auto & vec : Mix){
            int sz; cin >> sz;
            for(int a,i=0;i<sz;++i){
                cin >> a;
                vec.push_back(a - 1);
            }
        }
        proc();
    }
    return 0;
}
