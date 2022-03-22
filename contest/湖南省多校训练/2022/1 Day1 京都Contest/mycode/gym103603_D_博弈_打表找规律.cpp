/**
 * 若干对石子，每堆石子数量ai，且有一个参数bi，
 * 每一次只能取bi^k个其中k为非负整数。不能取者为负。问先手的胜负
 * 显然是SG函数，又由于ai和bi都很大，要打表找规律
 * 最后发现bi为奇数时，sg函数为01的循环
 * bi为偶数时，sg函数以bi+1长度为循环节，最后一个数是2，前面是01的循环
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 37;
#else
int const SIZE = 1E5+10;
#endif

typedef long long llt;
int N;
int A[SIZE], B[SIZE];

int f(llt a, llt b){
    if(b&1){
		return a&1 ? 1 : 0;
	}
	llt left = a % (b + 1);
	if(left == b) return 2;
	return left & 1 ? 1 : 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	int ans = 0;
	for(int i=0;i<N;++i){
		A[i] = getInt(); B[i] = getInt();
		ans ^= f(A[i], B[i]);
	}	
	puts(ans?"Alice":"Bob");
    return 0;
}
