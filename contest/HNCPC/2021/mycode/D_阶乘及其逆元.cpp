/**
 * 求和，经过简单变换发现就是求
 * SIGMA{(M+i)!/i!, i从0到N-1}
 * 预处理阶乘及其逆元即可
 * N和M在1E6
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 1000000000LL + 7LL;

llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

inline llt inv(llt a,llt p){
    llt x,y;
    llt r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

int const SIZE = 2000010;
llt Fac[SIZE] = {1, 1};
llt IFac[SIZE] = {1, 1};

inline void init(){
    for(int i=2;i<SIZE;++i){
		Fac[i] = Fac[i-1] * i % MOD;
	}	
	IFac[SIZE-1] = inv(Fac[SIZE-1], MOD);
	for(int i=SIZE-2;i>1;--i){
        IFac[i] = IFac[i+1] * (i+1) % MOD;
	}
}

int N, M;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    init();
    while(2 == scanf("%d%d", &N, &M)){
		llt ans = 0LL;
		for(int i=0;i<N;++i){
			(ans += Fac[M+i] * IFac[i]) %= MOD;
		}
		printf("%lld\n", ans);
	}
    return 0;
}