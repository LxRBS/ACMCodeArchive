/**
 * 给定数组P，以及数H和X，问第一个满足Pi+H>=X的i是多少
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
int H;
int X;
vi P;

int proc(){
    for(int i=0;i<N;++i){
        if(P[i] + H >= X) return i + 1;
    }
    assert(0);
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> H >> X;
    P.assign(N, 0);
    for(auto & i : P) cin >> i;
    cout << proc() << endl;
    return 0;
}