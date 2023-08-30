/**
 * 给定有向图，问有多少点对(u, v)满足u可到v
 * N、M均在2000，对每一个点做一个BFS即可。
 * O(N^2)量级。
 * 做SCC速度快一些，但此题没有必要
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

int N, M;
vvi G;

int proc(int u){
    vi flag(N + 1, 0);
    queue<int> q;
    q.push(u);
    flag[u] = 1;
    int ans = 0;
    while(not q.empty()){
        auto h = q.front(); q.pop();
        ++ans;
        for(auto i : G[h]){
            if(1 == flag[i]) continue;

            flag[i] = 1;
            q.push(i);
        }
    }
    return ans;
}

int proc(){
    int ans = 0;
    for(int i=1;i<=N;++i){
        ans += proc(i);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    G.assign(N + 1, {});
    for(int a,b,i=0;i<M;++i){
        cin >> a >> b;
        G[a].push_back(b);
    }
    cout << proc() << endl;
    return 0;
}