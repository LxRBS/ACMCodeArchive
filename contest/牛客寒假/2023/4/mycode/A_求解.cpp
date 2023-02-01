/**
 * 本质上就是问x的y次方和y的x次方谁大
 * x = e的时候最大。
 * 对整数而言，3最大。然后2和4一样大，均为次打。4以后显然是减函数。
 */
#include <bits/stdc++.h>
using namespace std;
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int x, y;
	cin >> x >> y;
	cout << ((3 == x || 3 == y) ? 3 : min(x, y)) << endl;
    return 0;
}