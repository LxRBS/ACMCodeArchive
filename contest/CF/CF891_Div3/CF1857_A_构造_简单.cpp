/**
 * 给定数组，问能不能把元素分成两拨，且两拨各自的和奇偶相同
 * 关键看奇数的数量。 
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
vi A;

bool proc(){
    int c[2] = {0, 0};
    for(auto i : A){
        ++c[i & 1];
    }
    if(c[1] & 1) return true;
    return false;
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
        for(auto & i : A) cin >> i;
        cout << (!proc()?"YES":"NO") << endl;
    }
    return 0;
}

