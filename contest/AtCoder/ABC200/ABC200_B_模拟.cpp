/**
 * 给定N，K，操作K次：
 * 1. 200的倍数就除以200
 * 2. 否则将200接在后面
 * 模拟即可
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

llt N;
int K;

llt proc(){
    llt ans = N;
    for(int i=0;i<K;++i){
        if(ans % 200 == 0){
            ans /= 200;
        }else{
            ans = ans * 1000 + 200;
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    cout << proc() << endl;
    return 0;
}