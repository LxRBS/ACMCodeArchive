/**
 * 给定数X，要求每次操作使得：
 *    X -= X的某个约数
 * 且：同一个数最多只能被减2次
 * 问能否通过如此操作令X到达1，给出具体方案
 * 考虑二进制位，令X记作:
 *    xxxxx1000000
 * 则 lowbit(X) 肯定是X的约数，令 X -= lowbit(X)
 * 如此直到 X = 10000....00，即X是2的幂
 * 此时显然每次减去当前的一半即可
 * 并且可以保证每个数最多减2次。
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

llt X;

void proc(){
    llt origin = X;
    vi ans;    
    int limit = 0;
    while((1 << limit) < X) ++limit;
    --limit;

    for(int i=0;i<limit;++i){
        if((1 << i) & X){
            ans.push_back(1 << i);
            X ^= (1 << i);
        }
    }

    assert(0 == (X & X - 1));

    while(1){
        X >>= 1;
        if(0 == X) break;
        ans.push_back(X);
    }
    
    cout << ans.size() + 1 << endl;
    cout << origin;
    for(auto i : ans) cout << " " << (origin -= i);
    cout << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> X;
        proc();
    }
    return 0;
}