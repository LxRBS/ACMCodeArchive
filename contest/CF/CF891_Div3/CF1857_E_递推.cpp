/**
 * 数轴上给定一系列坐标，记作 Xi
 * 再给定一个坐标，记作s，于是s与xi可以形成N条线段（单点也可以看作线段）
 * 再令 f(p) = p坐标被这N条线段覆盖的次数
 * 最后要求计算:
 * SIGMA{f(p), p=1,...,1E9, 当s取某个Xi时}
 * N个SIGMA值均要计算
 * 简单推导一下可知 只需要考虑在[Xmin, Xmax]之间的坐标即可
 * 其次在这些坐标中一共分为N段，每一段中的所有节点的f值是相等的，且很容递推算到。
 * 再次考虑s分别取X1和X2,发现只有两段f值是不同的，其他f全都一样。后续相邻的Xi均类似。
 * 因此首先计算s取X1时的SIGMA{f}的值，然后在递推计算s取{X2,X3,...}时的SIGMA值即可
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
int M;
vector<pii> A;

void proc(){
    sort(A.begin(), A.end());
    vector<llt> d(N, 0LL);

    auto & d0 = d[0];
    d0 += N;
    for(int i=1;i<N;++i){
        d0 += (0LL + N - i) *(A[i].first - A[i - 1].first);
    }

    for(int i=1;i<N;++i){
        d[i] = d[i - 1] - (0LL + N - i) * (A[i].first - A[i - 1].first) + (i + 0LL) * (A[i].first - A[i - 1].first);
    }

    vector<llt> ans(N, 0LL);
    for(int i=0;i<N;++i) ans[A[i].second] = d[i];

    for(auto i : ans) cout << i << " ";
    cout << endl;
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.assign(N, {});
        int k = 0;
        for(auto & i : A) cin >> i.first, i.second = k++;
        proc();
    }
    return 0;
}
