/**
 * 给定一个数组A，2种操作:
 * 1 x v: 令Ax变成v
 * 2 x: 令Bi=SIGMA{A[1..i]}, Ci=SIGMA{B[1..i]}, Di=SIGMA{C[1..i]}，求Dx
 * 主要是第二个操作，Bx就是前缀和，而Cx=SIGMA{Ai*(x+1-i)}
 * 进一步推出Dx=SIGMA{Ai*(x+1-i)*(x+1+1-i)/2}
 * 因此 Dx=SIGMA{i*i*Ai}/2 - SIGMA{i*Ai}*(2x+3)/2 + SIGMA{Ai}*(x+1)(x+2)/2
 * 只需要维持三个前缀和即可，树状数组可解。注意时刻取模。
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
int const SIZE = 13;
#else
int const SIZE = 2E5+5;
#endif

using llt = long long int;
llt const MOD = 998244353LL;
llt const INV2 = (MOD+1)/2;

struct bit_t{

int n;
llt c[SIZE];

static int lowbit(int x){return x & -x;}

void init(int n){
	memset(c, 0, sizeof(c));
	this->n = n;
}

void modify(int pos, llt d){
	while(pos <= n) (c[pos] += d) %= MOD, pos += lowbit(pos);
}

llt query(int pos){
	llt ans = 0;
	while(pos > 0) (ans += c[pos]) %= MOD, pos -= lowbit(pos);
	return ans;
}

}A, B, C;

int N, Q;
llt Z[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    assert(INV2 * 2 % MOD == 1);
    N = getInt(); Q = getInt();
	A.init(N); B.init(N); C.init(N);

	for(int a, i=1;i<=N;++i){
        Z[i] = a = getInt();
		A.modify(i, a);
		B.modify(i, (llt)i*a%MOD);
		C.modify(i, (llt)i*i%MOD*a%MOD);
	}

	for(int op,x,v,q=1;q<=Q;++q){
        if(1 == (op=getInt())){
            x = getInt(); v = getInt();
			llt d = v - Z[x];
			Z[x] = v;
			A.modify(x, d%MOD);
			B.modify(x, (llt)x*d%MOD);
			C.modify(x, (llt)x*x%MOD*d%MOD);
		}else{       
			x = getInt();     
			llt a = A.query(x) * (x + 1) % MOD * (x + 2) % MOD * INV2 % MOD;
			llt b = B.query(x) * (x + x + 3) % MOD * INV2 % MOD;
			llt c = C.query(x) * INV2 % MOD;
			llt ans = (c - b + a) % MOD;
			if(ans < 0) ans += MOD;
			printf("%lld\n", ans);
		}
	}
    return 0;
}
