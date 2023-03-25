/**
 * 给定数组，每次询问，将[s, e]区间的元素全部改为K，问改过之后的数组元素之和的奇偶性
 * 每次询问是独立的。使用前缀和即可。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

int N;
vi A;
int Q;
vi S;

bool proc(int s, int e, int k){
    int n = e - s + 1;
	int tmp = (n & 1) & (k & 1);

    int a = S[s - 1];
	int b = S[N] ^ S[e];
	return a ^ b ^ tmp;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int nofkase; scanf("%d", &nofkase);
	// int nofkase; cin >> nofkase;
    while(nofkase--){
        A.assign((N = getInt()) + 1, 0);
		Q = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();

		S.assign(N + 2, 0);
		for(int i=1;i<=N;++i){
			S[i] = (S[i - 1] + A[i]) & 1;
		}
		S[N+1] = S[N];
		for(int s,e,k,q=1;q<=Q;++q){
            s = getInt(); e = getInt(); k = getInt();
			puts(proc(s, e, k)?"YES":"NO");
		}
	}
    return 0; 
}


