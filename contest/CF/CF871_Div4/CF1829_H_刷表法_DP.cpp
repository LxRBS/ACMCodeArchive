/**
 * 给定数组A，元素值在[0, 63]，给定K，在[0, 6]
 * 问A中存在多少个不同的子序列使得与和的结果的二进制表示恰好有K个1
 * 显然不要直接求K个1，而是考虑计算结果恰好为j的数量
 * 子序列一般用DP做，因此
 * 令 Dij 为到i位置与和结果为j的数量，则
 * Dij = 1 + D[i - 1][j] + D[i - 1][x | x&Ai == j]
 * 其中第三部分x不好求，因此使用刷表法完成
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

llt const MOD = 1000000000 + 7;

int N, K;
vi A;

llt proc(){
    static const int LIMIT = 64;
    vector<vector<llt>> d(N, vector<llt>(LIMIT, 0));
    d[0][A[0]] = 1;
    for(int i=1;i<N;++i){
        d[i][A[i]] = 1;
        for(int j=0;j<LIMIT;++j){
            (d[i][j] += d[i - 1][j]) %= MOD;
            (d[i][j & A[i]] += d[i - 1][j]) %= MOD;            
        }
    }
    llt ans = 0;
    for(int i=0;i<LIMIT;++i){
        if(__builtin_popcount(i) == K){
            ans = (ans + d[N - 1][i]) % MOD;
        }
    }
    return ans;
} 

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> K;
        A.assign(N, 0);
        for(int & i : A) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}

