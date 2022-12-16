/**
 * N个人过河，船最多做M个人。过去以后需要1个人把船开回来
 * 船跨河一次需要1个单位时间，问最少需要多少时间
 * 1和2的情况要特判一下
 * 其他除一下余一下即可
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

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 55;
#endif

llt M, N;

llt f(llt n){
	if(n<=M) return 1;
	return 2 + f(n-M+1);
}

llt proc(){
	if(1 == N) return 1;
    if(1 == M) return -1;
	if(N <= M) return 1;

	if(2 == M){
		return N + N - 3;
	}

	llt t = N / (M - 1);
	llt left = N % (M - 1);
	if(left > 1){
		return t + t + 1;
	}
	if(left == 1){
		return t + t - 1;
	}
	return t + t - 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
		printf("%lld\n", proc());
    }
    return 0;
}
