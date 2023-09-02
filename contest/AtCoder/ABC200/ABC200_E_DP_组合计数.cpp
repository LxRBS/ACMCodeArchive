/**
 * 按如下顺序排列三元组
 * (1, 1, 1)(1, 1, 2)...(1, 1, N)
 * (1, 2, 1)(1, 2, 2)...(1, 2, N)
 * ...
 * (N, N, 1)(N, N, 2)...(N, N, N)
 * 给定N和K，问第K个三元组。从1开始排名。
 * 令Dij为使用i个数和为j的三元组总数，则
 * Dij = SIGMA{D[i-1][k], k=[max(1, j-N), j-1]}
 * 上式求一个Dij的时间是O(N)的，仿造完全背包可以优化为O(1)
 * Dij = D[i][j-1] + D[i-1][j-1] - (D[i-1][j-1-N] if j-1-N > 0 else 0)
 * 求出D以后，首先根据K求出k3和s3，即整个排名第K的三元组应该是和为s3的第k3个三元组
 * 再依次判断和为s2的第k2个二元组，以及和s1的第k1个一元组
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
llt K;

void dfs(int pos, llt k, int target, const vector<vector<llt>> & d, const vector<vector<llt>> & sum, array<int, 3> & ans){
    if(pos == 3) return;

    int used = 3 - pos;
    int first = 1;
    while(first < min(N+1, target)){
        if(k > d[used - 1][target - first]) k -= d[used - 1][target - first], ++first;
        else break;
    }
    ans[pos] = first;
    dfs(pos + 1, k, target - first, d, sum, ans);
    return;
}

void proc(){
    vector<vector<llt>> d(4, vector<llt>(N+N+N+1, 0LL));
    vector<vector<llt>> sum(4, vector<llt>(N+N+N+1, 0LL));
    d[0][0] = 1;
    for(int i=1;i<=3;++i){
        auto & vec = sum[i];
        for(int j=1;j<=i*N;++j){
            d[i][j] = d[i - 1][j - 1] + d[i][j - 1];
            if(j - 1 - N >= 0) d[i][j] -= d[i - 1][j - 1 - N];
            vec[j] = vec[j - 1] + d[i][j];
        }
    }

    auto pp = equal_range(sum[3].begin(), sum[3].end(), K);
    int target_sum = 0;
    if(pp.first != pp.second) target_sum = pp.first - sum[3].begin();
    else target_sum = pp.first - sum[3].begin();
    assert(pp.first != sum[3].begin());
    auto target_k = K - *(pp.first - 1);

    array<int, 3> ans;
    dfs(0, target_k, target_sum, d, sum, ans);
    for(auto i : ans) cout << i << " ";
    cout << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    proc();
    return 0;
}