/**
 N个人，每个人有ai个东西，这N个人排一个顺序，
 然后每个人依次拿出一个东西，最后一个人完了以后，第一个人又继续
 如果某人的东西出完了，就退出
 现在希望每个人均不会连出两次，问满足这个条件的顺序一共有多少个
 看ai的最大值，设为m，如果多个人都拥有m，答案就是N!
 设拥有第二大值的人为m2，则至少有一个m2要排在m后面，所以总数是N!*c2/(c2+1)
 其中c2为第二大值的人数
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

llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

llt const MOD = 998244353LL;

#ifndef ONLINE_JUDGE
int const SIZE =12;
#else 
int const SIZE = 200010;
#endif

llt Fac[SIZE] = {1, 1};
llt Inv[SIZE] = {0, 1};

int N, A[SIZE];

llt proc(){
    int mm = *max_element(A+1, A+N+1);
	int cnt = 0;
	int m2 = -1;
	for(int i=1;i<=N;++i){
        if(A[i] == mm){
			++cnt;
		}else if(m2 < A[i]){
			m2 = A[i];
		}
	}
    if(cnt>1) return Fac[N];
	if(mm>m2+1) return 0;

	int c2 = 0;
	for(int i=1;i<=N;++i){
		if(A[i] == m2){
			++c2;
		}
	}

    return Fac[N] * c2 % MOD * Inv[c2+1] % MOD;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    for(int i=2;i<SIZE;++i){
		Fac[i] = Fac[i-1] * i % MOD;
		Inv[i] = (MOD-MOD/i) * Inv[MOD%i] % MOD;
	}
   
    int nofkase = getUnsigned();
	while(nofkase--){
		N = getUnsigned();
		for(int i=1;i<=N;++i) A[i] = getUnsigned();
		printf("%lld\n", proc());
	}
	return 0;
}
