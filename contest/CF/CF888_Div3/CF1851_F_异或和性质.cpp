/**
 * 给定K和数组A，Ai均小于2^K
 * 要求找出Ai,Aj和x，使得 (Ai ^ x) & (Aj ^ x) 最大
 * 可以令x恰好与Ai互补，则 Ai ^ x 为全1，因此就是求 Aj ^ x 最大
 * 可以证明，只需要考虑Aj最近的数即可。
 * 即将数组A排序，只需考虑Aj相邻即可。
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
int K;
vector<pii> A;

void proc(){
    sort(A.begin(), A.end());

    int sum = INT32_MAX;
    int k = 0;
    for(int i=1;i<N;++i){
        auto t = A[i-1].first ^ A[i].first;
        if(t < sum){
            sum = t;
            k = i;
        }
    }
    cout << A[k - 1].second << " " << A[k].second << " " << (((1 << K) -1) ^ A[k].first) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> K;
        A.assign(N, {});
        for(int i=0;i<N;++i){
            cin >> A[i].first;
            A[i].second = i + 1;
        }
        proc();
    }
    return 0;
}
