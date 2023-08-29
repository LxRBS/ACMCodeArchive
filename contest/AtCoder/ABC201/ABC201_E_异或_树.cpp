/**
 * 给定一个树，有边权，定义路径距离为边权的异或，求所有路径的距离之和
 * 令树根为r，对于树上的任意路径(i, j)，其距离就是(r, i) ^ (r, j)
 * 因为同一个数异或两次对结果没有影响
 * 可以很容易求出所有的(r, i)。
 * 异或运算是位运算，各位互不影响。
 * 考虑对第x位，假设N个(r, i)中该位为1的有t个，该位为0的有p个
 * 则该位为1的异或结果只有t * p个，因此对结果的贡献为 (1 << x) * t * p
 * 累加即可。O(N + N * 60)
 * 权值最大到60个二进制位
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
int const SZ = 2E5+10;
#endif

llt const MOD = 1000000000 + 7;

int N;
vector<vector<pair<int, llt>>> G;
int Root;
vector<llt> W;

void dfs(int u, int p){
    for(const auto & t : G[u]){
        if(t.first == p) continue;

        W[t.first] = W[u] ^ t.second;
        dfs(t.first, u);
    }
}

llt proc(){
    W.assign(N + 1, 0LL);
    dfs(Root = 1, 0);    

    llt ans = 0;
    for(int i=0;i<60;++i){
        llt cur = 1LL << i;
        int cnt = 0;
        for(int j=1;j<=N;++j){
            if(W[j] & cur){
                ++cnt;
            }
        }
        int tmp = N - cnt;
        ans = (ans + cur % MOD * cnt % MOD * tmp % MOD) % MOD;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    G.assign(N + 1, vector<pair<int, llt>>());
    for(int a,b, i=1;i<N;++i){
        llt w;
        cin >> a >> b >> w;
        G[a].emplace_back(b, w);
        G[b].emplace_back(a, w);
    }
    cout << proc() << endl;
    return 0;
}