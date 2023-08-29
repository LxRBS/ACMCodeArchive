/**
 * 给定三个数，问是否形成等差数列
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


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int a[3];
    for(auto & i : a) cin >> i;
    sort(a, a + 3);
    cout << (a[0] + a[2] == a[1] + a[1] ? "Yes" : "No") << endl;
    return 0;
}