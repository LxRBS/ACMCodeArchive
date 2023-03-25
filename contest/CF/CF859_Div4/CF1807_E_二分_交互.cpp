/**
 * 一共有N段石头，第i堆的石头质量是i，除了某一个第j堆，其质量是j+1，每一次允许询问：任意k堆的质量和
 * 要求在30次询问之内找出这个j。很明显的二分。
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
vector<llt> S;

llt ask(int s, int e){
    int k = e - s + 1;
    printf("? %d", k);
	for(int i=s;i<=e;++i)printf(" %d", i);
	printf("\n");
	fflush(stdout); 
	llt x;
	scanf("%lld", &x);
	return x;
}

bool check(int s, int e){
	auto t = ask(s, e);
	if(t == S[e] - S[s - 1]) return true;
	return false;
}

void proc(){
    S.assign(N + 1, 0LL);
	for(int i=1;i<=N;++i) S[i] = S[i - 1] + A[i];

	int left = 1, right = N, mid;
	do{
        mid = (left + right) >> 1;
		if(check(left, mid)) left = mid + 1;
		else right = mid;
	}while(left < right);
	printf("! %d\n", left);
	fflush(stdout); 
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int nofkase; scanf("%d", &nofkase);
	// int nofkase; cin >> nofkase;
    while(nofkase--){
		scanf("%d", &N);
        A.assign(N + 1, 0);
		for(int i=1;i<=N;++i) scanf("%d", &A[i]);
		proc();
	}
    return 0; 
}


