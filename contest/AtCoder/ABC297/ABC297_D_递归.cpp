/**
 * 给定a、b，如果a>b，就令a -= b
 * 如果a<b，就令 b-= a
 * 如果a==b，停止
 * 问一共能操作多少次
 * 使用递归完成即可。类似辗转相除
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;

using llt = long long;
using vi = vector<int>;
using vs = vector<string>;

llt proc(llt a, llt b){
	if(0 == b or a == b) return 0;
	if(a < b) swap(a, b);
	if(0 == a % b) return a / b - 1;
    return a / b + proc(b, a % b);
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    llt a, b; cin >> a >> b;
	cout << proc(a, b) << endl;
    return 0; 
}
