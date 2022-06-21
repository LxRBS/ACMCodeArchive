/**
 * 给定一个数组A，2种操作:
 * 1 x v: 令Ax变成v
 * 2 x: 令Bi=SIGMA{A[1..i]}, Ci=SIGMA{B[1..i]}, Di=SIGMA{C[1..i]}，求Dx
 * 主要是第二个操作，Bx就是前缀和，而Cx=SIGMA{Ai*(x+1-i)}
 * 进一步推出Dx=SIGMA{Ai*(x+1-i)*(x+1+1-i)/2}
 * 因此 Dx=SIGMA{i*i*Ai}/2 - SIGMA{i*Ai}*(2x+3)/2 + SIGMA{Ai}*(x+1)(x+2)/2
 * 只需要维持三个前缀和即可，线段树可解。注意时刻取模。
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
using ttt = tuple<llt, llt, llt>;
llt const MOD = 998244353LL;
llt const INV2 = (MOD+1)/2;

llt St[SIZE<<2][3];

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

inline void _pushUp(int t){
	for(int i=0;i<3;++i)St[t][i]=(St[lson(t)][i]+St[rson(t)][i])%MOD;
}

void modify(int t, int s, int e, int pos, llt v){
	if(s == e){
		St[t][0] = v;
		St[t][1] = s * v % MOD;
		St[t][2] = s * v % MOD * s % MOD;
		return;
	}

	int m = (s + e) >> 1;
	if(pos <= m) modify(lson(t), s, m, pos, v);
	else modify(rson(t), m+1, e, pos, v);
	_pushUp(t);
	return; 
}

const ttt operator + (const ttt & a, const ttt & b){
	return {(get<0>(a)+get<0>(b))%MOD, (get<1>(a)+get<1>(b))%MOD, (get<2>(a)+get<2>(b))%MOD};
}

ttt query(int t, int s, int e, int a, int b){
    if(a <= s && e <= b){
		return {St[t][0], St[t][1], St[t][2]};
	}

    int m = (s + e) >> 1;
	ttt ans(0, 0, 0);
	if(a <= m) ans = ans + query(lson(t), s, m, a, b);
	if(m < b) ans = ans + query(rson(t), m+1, e, a, b);
	return ans;
}

void build(int t, int s, int e){
	if(s == e){
		St[t][0] = getInt();
		St[t][1] = s * St[t][0] % MOD;
		St[t][2] = s * St[t][1] % MOD;
		return;
	}

	int m = (s + e) >> 1;
	build(lson(t), s, m);
	build(rson(t), m+1, e);
	_pushUp(t);
	return;
}

int N, Q;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); Q = getInt();
	build(1, 1, N);
	for(int op,q=1;q<=Q;++q){
        if(1 == (op=getInt())){
            int x = getInt();
			llt v = getInt();
			modify(1, 1, N, x, v);
		}else{
            int x = getInt();
			ttt z = query(1, 1, N, 1, x);
			llt a = get<0>(z) * (x+1) % MOD * (x+2) % MOD * INV2 % MOD;
			llt b = get<1>(z) * (x+x+3) % MOD * INV2 % MOD;
			llt c = get<2>(z) * INV2 % MOD;
			llt ans = (c - b + a) % MOD;
			if(ans < 0) ans += MOD;
			printf("%lld\n", ans);
		}
	}
    return 0;
}
