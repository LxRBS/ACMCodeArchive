/**
 * 给定两个字符串S和T，每次可以做如下操作：
 * 在S中找到一个子串恰好等于T，将之删除
 * 直到S中再也没有子串等于T为止
 * 问最少要多少次操作可以达成，同时问在这最少次数之下，一共有多少种不同的方法
 * S和T的长度都在500。都可以使用DP实现。
 * 令Di为从i到N的最少次数， Ui为i位置删除T的最少次数，Vi为不删除T的最少次数
 * UV只在Si等于T有效，令T的长度为n，
 * 则Ui = 1 + U[i+n], Vi = min(Uj，其中j是i之后的n-1个位置且Sj==T)
 * 根据U和V可以求出D
 * 同样可以求出方案数，令Xi是i位置删除的方案数，Yi是不删除的方案数，Zi是总数
 * 则Xi = Z[i+n]，Yi = SIGMA(Xj, 其中j是i之后的n-1个位置且Sj==T且Di==Uj)
 * 根据X和Y可以求出Z
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1000000000 + 7LL;

string S, T;
vi A;
int N;
vi D, U, V;
vector<llt> X, Y, Z;

void proc(){
    A.assign(N = S.length(), 0);
	int k = 0;
	while(1){
		auto t = S.substr(k).find(T);
		if(t == string::npos) break;
        
		t += k;
		A[t] = 1;
		if((k = t + 1) > N) break;
	}

	// for(int i : A) printf("%d ", i);
	// printf("\n");

    int n = T.length();
    U.assign(N+1, -1);
	V.assign(N+1, 0);
	D.assign(N+1, 0);
	for(int i=N-n;i>=0;--i){
        if(0 == A[i]){
			D[i] = D[i+1];
			continue;
		}

		U[i] = 1 + D[i+n];
		V[i] = -1;
		for(int j=1;j<=n-1;++j){
			if(1 == A[i+j] && -1 != U[i+j]){
				if(-1 == V[i] || V[i] > U[i+j]){
					V[i] = U[i+j];
				}
			}
		}
        int & m = D[i];
		m = U[i];
		if(-1 != V[i] && m > V[i]) {
			m = V[i]; 
		}
		assert(m != -1);
	}
    
    X.assign(N+1, 1LL);
	Y.assign(N+1, 1LL);
	Z.assign(N+1, 1LL);
    for(int i=N-n;i>=0;--i){
		if(0 == A[i]){
            Z[i] = Z[i+1]; continue; 
		}

        llt & c = Z[i];
		c = 0;
		X[i] = Z[i+n];
		if(D[i] == 1 + D[i+n]){
			(c += X[i]) %= MOD;
		}

		llt & y = Y[i]; y = 0;
		for(int j=1;j<=n-1;++j){
			if(1 == A[i+j] && D[i] == U[i+j]){
                (y += X[i+j]) %= MOD;
			}
		}

		(c += y) %= MOD;
	}

	printf("%d %lld\n", D[0], Z[0]);
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int nofkase; cin >> nofkase;
    while(nofkase--){
		cin >> S >> T;
		proc();
	}
    return 0;
}


