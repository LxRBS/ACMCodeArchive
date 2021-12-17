/**
 * 给定PQ，求AB，使得 P/Q=A/B+B/A
 * 令A/B = x，则得到方程Qx^2-Px+Q=0
 * 因此 x = (P - sqrt(delta))/(2Q)
 * x为有理数，即delta是完全平方数
 * 直接用开根号即可判断，也可以二分去找整数解
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;
llt const INF = 1000000000LL;

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

llt P, Q;

void proc(){
    llt g = gcd(P, Q);
    P /= g, Q /= g;

    llt delta = P * P - 4 * Q * Q;
    if(delta < 0) return (void)puts("0 0");
    if(0 == delta) {
        llt a = P, b = Q + Q;
        g = gcd(a, b);
        return (void)printf("%lld %lld\n",a/g,b/g);
    }

    llt left = 0LL, right = sqrt(delta) + 1LL, mid;
    do{
        mid = (left + right) >> 1;
        if(mid * mid > delta) right = mid - 1;
        else left = mid + 1;
    }while(left <= right);
    if(right * right != delta) return (void)puts("0 0");

    /// 直接开根号亦可判断
    // double d = sqrt(delta);
    // llt right = d;
    // if(right * right != delta) return (void)puts("0 0");

    llt a = P - right, b = Q + Q;
    g = gcd(a, b);
    a /= g, b /= g;
    if(a<=INF&&b<=INF) return (void)printf("%lld %lld\n",a, b);
    return (void)puts("0 0");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        P = getUnsigned(); Q = getUnsigned();
        proc();
    }
    return 0;
}

