/**
 * 给定一个数组A，要求进行若干次插入操作
 * 使得所有Ai满足Ai<=i。问最少操作次数是多少
 * 从前往后，如果Ai=i，则不需要操作，如果Ai>i，则前面需要插入Ai-i次。
 * 但这之后不能再用Ai-i，而应该用当前已经达到的次数
 * 还有另外一种更简便的方法，对于每一个Ai>i，至少需要Ai-i次操作，
 * 因此找到最大值即可。
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
int const SIZE = 21;
#else 
int const SIZE = 1000010;
#endif

#define fi first
#define se second

typedef long long llt;

int A[SIZE];
int N;

llt proc(){
	llt ans = 0;
	int now = 1;
	for(int i=1;i<=N;++i){
		if(A[i] > now){
			ans += A[i] - now;
			now = A[i] + 1;
		}else{
			++now;
		}
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		printf("%lld\n", proc());
	}
	return 0;
}