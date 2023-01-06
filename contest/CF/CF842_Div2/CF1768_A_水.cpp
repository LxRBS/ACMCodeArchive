/**
 * 给定K(>=2)，求最大的x使得x!+(x-1)!是k的倍数
 * 显然(K-1)!+(K-2)!=(K-2)!*K，所以就是K-1
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
int const SIZE = 2e5+5;
#endif

using Real = long double; 
using llt = long long;
using vi = vector<int>; 
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int N;
int proc(){
	return N - 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		printf("%d\n", proc());
    }
    return 0;
}