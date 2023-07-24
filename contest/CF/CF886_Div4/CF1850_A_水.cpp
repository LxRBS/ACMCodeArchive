/**
 * 给定3个数问是否存在2个数其和大于等于10
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        int a[3]; for(int & i : a) cin >> i;
        sort(a, a + 3);
        cout << (a[1] + a[2] >= 10 ? "YES" : "NO") << endl;
    }
    return 0;
}

