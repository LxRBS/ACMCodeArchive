/**
 * 给定1E4个点，坐标绝对值也在1E4，从1依次走到N，记录距离总和为f
 * 可以忽略某些点，如果忽略C个点，则 f += 2 ^ C
 * 问从1到N的最小f是多少
 * 考虑到 2 ^ 32 是 4E9，而N个点的大总距离之和的最大可能大约也是这么多
 * 因此忽略的点数不会超过30这个量级
 * 令Dij为从i到N忽略j个点的最小距离，采用刷表法
 * 在Dij已经求出的情况下:
 *   Dij + Disk(k, i) - Pj + P[j+i-k-1] 
 * 会影响到 D[k][j+i-k-1]
 * j/k都只需要循环30量级即可，复杂度为O(900N)
 * BTW, 数学库函数pow很耗时
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

Real const EPS = 1E-7;
Real const INF = 1E11;
int const LIMIT = 31;

inline void mymin(Real & x, Real y){
    if(x > y) x = y;
}

int N;
vector<pair<Real, Real>> A;

Real dist(int i, int j){
    auto x = A[i].first - A[j].first;
    auto y = A[i].second - A[j].second;
    return sqrt(x * x + y * y);
}

array<Real, LIMIT> P = {0, 1};

Real proc(){
    vector<vector<Real>> d(N + 1, vector<Real>(min(N - 1, LIMIT), INF));
    int const limit = d[0].size();

    d[N][0] = 0;
    d[N - 1][0] = dist(N - 1, N);
    for(int i=N-1;i>=1;--i){
        for(int j=0;j<limit;++j){
            if(j > N - i - 1) break;
            
            const auto & dij = d[i][j];
            for(int k=max(0, j+i-limit);k<i;++k){       
                // cout << "k = " << k << endl;         
                mymin(d[k][j+i-k-1], dij + dist(k, i) - P[j] + P[j+i-k-1]);
            }
        }
    }
    Real ans = *min_element(d[1].begin(), d[1].end());
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for(int i=2,n=P.size();i<n;++i) P[i] = P[i - 1] * 2;
    cin >> N;
    A.assign(N + 1, {});
    for(int i=1;i<=N;++i) cin >> A[i].first >> A[i].second;
    cout << fixed << setprecision(12) << proc() << endl;
    return 0;
}
