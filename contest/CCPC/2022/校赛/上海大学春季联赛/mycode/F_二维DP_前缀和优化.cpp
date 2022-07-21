/**
 * ������A����T�Σ�ÿ��ѡ��һ��Ԫ�ؼ�1
 * ��������в�ͬ�Ľ�������˻��������Ƕ���
 * ��Dij�ǵ�iλ�ò�����j�εĲ�ͬ��������˻�
 * ��Dij = SIGMA{D[i-1][j-k]*(Ai+k),k=0,..,j}
 * �京�������Ai�����k�Σ�����k������ͬ�����Եõ��Ľ��һ����ͬ
 * �̶�i������Di[j-1] = SIGMA{D[i-1][j-1-k]*(Ai+k),k=0,...,j-1}
 * �任k���ɵ� D[i][j-1] = SIGMA{D[i-1][j-k]*(Ai+k-1), k=1,...,j}
 * ����, Dij - D[i][j-1] = D[i-1][j] * Ai + SIGMA{D[i-1][j-k], k=1,...,j} 
 * �� U[i][j] = SIGMA{D[i-1][j-k], k=1,...,j} = SIGMA{D[i-1][k], k=0,...,j-1}
 * �� U[i][j] = U[i][j-1] + D[i-1][j-1];
 * ��˿�����O(NT)ʱ�������D��
 * �ٿ��ǲ�ͬ������Ŀ����������Cij��ʾ����
 * Cij = SIGM{C[i-1][k], k=0,...,j}
 * �����׵õ� Cij = C[i-1][j] + C[i][j-1]
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
int const SIZE = 5;
#else
int const SIZE = 3E3+8;
#endif

using llt = long long;
llt const MOD = 998244353;

llt pow(llt a, llt n){
	llt ret = 1; a %= n;
	while(n){
		if(n & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ret;
}

inline llt inv(llt a){return pow(a, MOD-2);}

int N, T;
llt A[SIZE];

llt D[SIZE][SIZE];
llt U[SIZE][SIZE];
llt C[SIZE][SIZE];

llt proc(){
	/// ��ʼ��
	D[0][0] = 1;
	C[0][1] = C[1][0] = D[0][1] = 1;
    for(int i=1;i<=T;++i) D[1][i] = A[1] + i, C[1][i] = 1;
	for(int i=1;i<=N;++i) C[i][0] = 1, D[i][0] = (D[i-1][0] * A[i]) % MOD;

	for(int i=2;i<=N;++i){		
		for(int j=1;j<=T;++j){
            U[i][j] = (U[i][j-1] + D[i-1][j-1]) % MOD;
			D[i][j] = (D[i][j-1] + D[i-1][j] * A[i] % MOD + U[i][j]) % MOD;
			C[i][j] += (C[i][j-1] + C[i-1][j]) % MOD;
		}
	}
    return D[N][T] * inv(C[N][T]) % MOD; 
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); T = getInt();
	for(int i=1;i<=N;++i) A[i] = getInt();
	cout << proc() << endl;
    return 0;
}