/**
 * 给定字符串S和T，根据S是否为T的前、后缀进行输出
 * 暴力即可
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    if(n > m) return cout << 3 << endl, 0;

    int st = 0;
    if(t.substr(0, n) == s) st |= 1;
    if(t.substr(m - n, n) == s) st |= 2;

    if(3 == st) return cout << 0 << endl, 0;
    if(0 == st) return cout << 3 << endl, 0;
    cout << st << endl;
    return 0;
}