/**
 * 给定一个数组A，每次操作选定Ai令Ai/=2
 * 问要经过几次操作可以将A变为严格升序
 * 从后往前枚举每个Ai，将其刚好变为小于A[i+1]即可
 * 
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
int const SIZE = 30;
#else
int const SIZE = 30;
#endif

using pii = pair<int, int>;
using vpii = vector<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
vi A;

int proc(){
	int ans = 0;
	for(int i=N-2;i>=0;--i){
		if(0 == A[i+1]) return -1;
        while(A[i] >= A[i+1]) A[i] >>= 1, ++ans;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		A.assign(N=getInt(), 0);
		for(int & i : A) i = getInt();
		printf("%d\n", proc());
	}
	return 0;
}
