/**
 * 给定数组A和B，如果Au-Av >= Bu-Bv，则u到v有一条边
 * 如此构成的有向图，问有多少个节点可以到达所有N个节点
 * 简单考虑一下可知其实无需考虑路径，只考虑边即可
 * 又易得u到v有一条边等价于 Au - Bu >= Av - Bv
 * 因此求一个差数组的最大值即可 
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
vi B;
vi A;

void proc(){
    vector<pii> d;
    for(int i=0;i<N;++i){
        d.push_back({A[i] - B[i], i + 1});
    }
    sort(d.begin(), d.end());

    int k = N - 1;
    auto anchor = d[k].first;
    while(k >= 0 and d[k].first == anchor) --k;

    cout << N - k - 1 << endl;
    for(int i=k+1;i<N;++i) cout << d[i].second << " ";
    cout << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.assign(N, 0);
        B.assign(N, 0);
        for(auto & i : A) cin >> i;
        for(auto & i : B) cin >> i;
        proc();
    }
    return 0;
}
