/**
 * N行M列，放W个白车B个黑车，互相不攻击，问方案总数，N、M在50以内
 * 可以做一个四重循环，求出恰好br行bc列放黑车、wr行wc列放白车的方案数，累加即可
 * 由于白黑互相不攻击，因此方案数是独立的，所以只需取出r行r列放t个车的方案（没有空行，没有空列）
 * 令Dij为答案，则
 * Dij = C(i*j, t) - SIGMA{C(i,u)*C(j,v)*Duv,u=1..i,v=1..j,且(u,v)!=(i,j)}
 * 第一项是i行j列放t个车的方案，然后减去包含空行的方案即可
 * 空行的方案实际上就是Duv,因为u行v列就放下了t个车，剩下的行列自然是空的
 * 再加上合适的组合数即可
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
int const SIZE = 55;
#else
int const SIZE = 55;
#endif

typedef long long llt;
llt const MOD = 998244353LL;

llt power(llt a, llt n){
	llt ans = 1; a %= MOD;
	while(n){
		if(n & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ans;
}
inline llt inv(llt a){return power(a, MOD-2);}

llt Fac[SIZE*SIZE] = {1LL, 1LL};
llt IFac[SIZE*SIZE] = {1LL, 1LL};

void init(int n){
	for(int i=2;i<=n;++i){
		Fac[i] = Fac[i-1] * i % MOD;
	}
	IFac[n] = inv(Fac[n]);
	for(int i=n-1;i>1;--i){
		IFac[i] = IFac[i+1] * (i+1) % MOD;
	}
}

llt N, M, B, W;
llt BD[SIZE][SIZE], WD[SIZE][SIZE];

inline llt C(llt n, llt m){
    return Fac[n] * IFac[m] % MOD * IFac[n-m] % MOD;
}

void calc(llt total, llt (&a)[SIZE][SIZE]){
	memset(a, 0, sizeof(a));
	if(0 == total){		
		a[0][0] = 1;
		return;
	}
    /// Dij = C(i*j, t) - SIGMA{Duv*C(i,u)*C(j,v)}
    for(int i=1;i<=min(N,total);++i)for(int j=1;j<=min(M,total);++j){
		if(i*j < total){
			a[i][j] = 0; continue;
		}
        a[i][j] = C(i*j, total);
		for(int u=1;u<=i;++u)for(int v=1;v<=j;++v){
			if(u==i&&v==j) continue;
			(a[i][j] += MOD - a[u][v]*C(i, u)%MOD*C(j,v)%MOD) %= MOD;
		}
	}
}

inline llt proc(int br, int bc, int wr, int wc){
    llt ans = 1LL;
	(ans *= BD[br][bc]) %= MOD;
	(ans *= WD[wr][wc]) %= MOD;
	return ans;
}

llt proc(){
	llt ans = 0;
    for(int br=0;br<=N;++br)for(int bc=0;bc<=M;++bc){
        for(int wr=0;wr<=N-br;++wr)for(int wc=0;wc+bc<=M;++wc){
            (ans += C(N, br) * C(N-br, wr) % MOD * C(M, bc) % MOD * C(M-bc, wc) % MOD * proc(br, bc, wr, wc) % MOD) %= MOD;
		}
	}    
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif        
    N = getInt(); M = getInt();
    B = getInt(); W = getInt();
	init(N*M); calc(B, BD); calc(W, WD);
	cout<<proc()<<endl;
    return 0;
}
