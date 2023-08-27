/**
 * 给定数组A，问存在多少对(i, j)使得Ai - Aj是200的倍数
 * 对200取模处理一下即可
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

int N;
vi A;

llt proc(){
    map<int, int> cnt;
    for(int i=0;i<N;++i){
        ++cnt[A[i] % 200];
    }
    llt ans = 0;
    for(const auto & p : cnt){
        if(1 == p.second) continue;
        ans += (p.second - 1LL) * p.second / 2LL;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, 0);
    for(auto & i : A)cin >> i;
    cout << proc() << endl;
    return 0;
}