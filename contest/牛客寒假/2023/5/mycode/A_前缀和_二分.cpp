/**
 * 基本的前缀和与二分操作。 
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
int const SIZE = 810;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<llt>;

int N;
int M;
int Q;
vi A;
vll S;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt();
    Q = getInt();
    A.assign(N + 1, 0);
    S.assign(N + 1, 0LL);
    for(int i=1;i<=N;++i)A[i] = getInt();
    sort(A.begin(), A.end());
    for(int i=1;i<=N;++i) S[i] = S[i - 1] + A[i];

    for(int k,x,q=1;q<=Q;++q){
        k = getInt(); x = getInt();
        auto pos = upper_bound(A.begin(), A.end(), x) - A.begin() - 1;
        auto tmp = S[pos];
        auto t2 = 0LL;
        if(pos >= k) t2 = S[pos - k];
        printf("%lld\n", tmp - t2);
    }
    return 0;
}