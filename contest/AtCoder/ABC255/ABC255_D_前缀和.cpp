/**
  给一个数组A，再给定Q个询问，每次询问给定一个X
  问把所有的Ai全都变成X，最少需要多少次操作，每次操作只能把一个Ai加一或者减一
  对给定的x，比x小的Ai用x减，比x大的Ai就减去x即可。
  首先排序，然后求前缀和。然后二分搜索出x的位置，之前的用x去减，之后的减去x即可
  O(NlogN+QlogN)
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
using Real = long double;
using vi = vector<int>; 

int N, Q;
int A[SIZE];
llt S[SIZE];

llt proc(int x){
	llt k = lower_bound(A, A+N, x) - A;
    
	llt ans = k * x;
    ans -= S[k-1];

	ans += S[N-1] - S[k-1] - (llt)(N - k) * x;
	return ans; 
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); Q = getInt();
	for(int i=0;i<N;++i) A[i] = getInt();

	sort(A, A+N);
	S[0] = A[0];
	for(int i=1;i<N;++i) S[i] = S[i-1] + A[i];

	for(int x,q=1;q<=Q;++q){
        x = getInt();
		printf("%lld\n", proc(x));
	}
    return 0;
}
