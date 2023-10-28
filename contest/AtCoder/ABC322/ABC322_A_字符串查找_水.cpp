#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; string s; cin >> n >> s;
    int t = s.find("ABC");
    cout << (t != string::npos ? (int)t + 1 : (int)-1) << endl;
    return 0;
}