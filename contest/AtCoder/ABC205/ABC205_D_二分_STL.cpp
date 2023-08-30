/**
 * 给定数组A，Q个询问，每次不在A中的第k小的数是多少
 * 首先求一个B数组，Bi表示Ai之前有多少个不在A中的数。
 * 然后对每次询问的k，在B上二分。根据找到的位置进行判断即可
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
int const SZ = 61;
#else
int const SZ = 61;
#endif

int N, Q;
vector<llt> A;
vector<llt> B;

llt proc(llt k){
    auto pp = equal_range(B.begin(), B.end(), k);
    if(pp.first != B.end()){
        if(*pp.first == k){
            auto offset = pp.first - B.begin();
            return A[offset] - 1;
        }
        if(pp.first == B.begin()){
            return k;
        }
        --pp.first;
        auto base = A[pp.first - B.begin()];
        return base + k - *pp.first;
    }
    return A.back() + k - B.back();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    A.assign(N, 0LL);
    for(auto & i : A) cin >> i;
    B.assign(N, 0LL);
    B[0] = A[0] - 1;
    for(int i=1;i<N;++i){
        B[i] = B[i - 1] + A[i] - A[i - 1] - 1;
    }
    for(int q=1;q<=Q;++q){
        llt k; cin >> k;
        cout << proc(k) << endl;
    }
    return 0;
}