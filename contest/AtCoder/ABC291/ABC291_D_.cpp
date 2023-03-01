/**
 * 给定AB两个数组。对每一个i都可以令Ai、Bi互换，也可以不换，则一共有2^N次方种可能
 * 问在这所有可能性中，有多少种方案可以使得相邻Ai不相等。
 * 令Ui为以i结尾且不换的方案数，Vi是以i结尾且换的方案数
 * 若 Ai != A[i-1] 且 Ai != B[i-1]，则 Ui = U[i-1] + V[i-1]
 * 若 Ai != A[i-1] 且 Ai = B[i-1]，则 Ui = U[i-1]
 * 依次类推，讨论清楚即可
 * 最后答案为 U[N] + V[N]
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N;
vector<array<int, 2>> A;
vll U, V;

llt proc(){
    U.assign(N, 0); V.assign(N, 0);
	U[0] = V[0] = 1LL;
	for(int i=1;i<N;++i){
		const auto & pre = A[i - 1];
		const auto & nxt = A[i];
		if(pre[0] != nxt[0]){
			if(pre[1] != nxt[0]){
                U[i] = (U[i - 1] + V[i - 1]) % MOD;
			}else{
                U[i] = U[i - 1];
			}			
		}else{
			if(pre[1] != nxt[0]){
				U[i] = V[i - 1];
			}else{
				U[i] = 0;
			}
		}

		if(pre[0] != nxt[1]){
			if(pre[1] != nxt[1]){
				V[i] = (U[i - 1] + V[i - 1]) % MOD;
			}else{
				V[i] = U[i - 1];
			}
		}else{
			if(pre[1] != nxt[1]){
				V[i] = V[i - 1];
			}else{
				V[i] = 0;
			}
		}
	}	
	return (U[N - 1] + V[N - 1]) % MOD;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    N = getInt();
	A.assign(N, {});
	for(auto & a : A) a[0] = getInt(), a[1] = getInt();
	cout << proc() << endl;
    return 0; 
}