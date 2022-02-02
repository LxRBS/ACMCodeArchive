/**
 * 给定一个整数，每次操作可以修改其中一个位置，用最少的操作数量将其修改为
 * 无前导零且是7的倍数的数，输出修改后的数
 * 直接对7取余数即可，要么加要么减
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

int N;

int proc(){
	if(0 == N%7) return N;
	if(N < 10) return 7;
	int left = N % 7;
	int t = N % 10;
	if(t>=left) return N - left;
	return N + 7 - left;
}

int main() {
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
