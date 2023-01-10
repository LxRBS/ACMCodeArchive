#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

using llt = long long;
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}
/**
 * 给一个9E18的数N，已知N = p^2*q，p和q是不相等的质数，求p和q
 * p和q显然有一个数应该在N^(1/3)以内，大概是10^6量级，暴力枚举即可 
 */ 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 3500000;
#endif

llt N;

void proc(){
    for(llt i=2;i*i*i<=N;++i){
        if(N % i) continue;

        llt x = i, y = N / x;
        if(0 == y % x) return (void)printf("%lld %lld\n", x, y / x);
        if(0 == x % y) return (void)printf("%lld %lld\n", y, x / y);
        llt tmp = sqrt(x);
        if(tmp * tmp == x) return (void)printf("%lld %lld\n", tmp, y);
        return (void)printf("%lld %lld\n", (llt)sqrt(y), x);
    }   
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
	srand((unsigned)time(nullptr));
	int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		proc();
	}
    return 0;
}


