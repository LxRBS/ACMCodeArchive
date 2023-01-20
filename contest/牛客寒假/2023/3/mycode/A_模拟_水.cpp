/**
 * 给定一个数组，可以对一个偶数元素除以2，可以做任意次操作
 * 求最小的可能的数组和
 * 显然对正偶数操作就行了
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 130;
#else
int const SIZE = 1e7+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>; 

int N;
vi A;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0);
	// cin.tie(0); cout.tie(0);
    A.assign(N = getInt(), 0);
	for(int & i : A) i = getInt();
	llt ans = 0;
	for(int i : A){
        if(i <= 0) {ans += i; continue;}
		while(i % 2 == 0) i /= 2;
		ans += i;
	}
	cout << ans << endl;
    return 0;
}