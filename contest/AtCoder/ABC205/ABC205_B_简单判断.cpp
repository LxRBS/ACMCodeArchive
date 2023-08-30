/**
 * 给定N个数，判断是否恰好构成N的排列
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



int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vi cnt(n + 1, 0);
    for(int i=0;i<n;++i){
        int t; cin >> t;
        ++cnt[t];
    }
    bool flag = true;
    for(int i=1;i<=n;++i){
        if(1 != cnt[i]){
            flag = false;
            break;
        }
    }
    cout << (flag ? "Yes" : "No") << endl;
    return 0;
}