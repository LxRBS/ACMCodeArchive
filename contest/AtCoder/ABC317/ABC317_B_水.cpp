/**
 * 有N+1个连续的数，现在给出其中N个，求缺失的数
 * 保证答案唯一
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
vi P;

int proc(){
    sort(P.begin(), P.end());
    for(int i=1;i<N;++i){
        if(P[i - 1] + 1 != P[i]){
            return P[i - 1] + 1;
        }
    }
    assert(0);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    P.assign(N, 0);
    for(auto & i : P) cin >> i;
    cout << proc() << endl;
    return 0;
}