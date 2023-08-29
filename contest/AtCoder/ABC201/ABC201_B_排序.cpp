/**
 * 排序，问第二大的数
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
    vector<pair<int, string>> a;
    int n;
    cin >> n;
    a.assign(n, {});
    for(auto & p : a) cin >> p.second >> p.first;
    sort(a.begin(), a.end());
    cout << a[n-2].second << endl;
    return 0;
}