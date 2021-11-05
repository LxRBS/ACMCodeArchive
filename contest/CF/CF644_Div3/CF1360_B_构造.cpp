/**
 * 把一个数组分为A、B另个子数组
 * 要求|max(A) - min(B)|最小
 * 排序以后找到相邻差最小的，一边是A一边是B即可
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

#ifndef ONLINE_JUDGE
int const SIZE =66;
#else 
int const SIZE = 66;
#endif

#define pb push_back
typedef vector<int> vi;

inline int ABS(int x){return x>=0?x:-x;}

int N;
int A[SIZE];

int proc(){
    sort(A+1, A+N+1);
	int ans = 1000000;
	for(int i=2;i<=N;++i){
        if(ans>ABS(A[i-1]-A[i])){
			ans = ABS(A[i-1]-A[i]);
		}
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
		N = getUnsigned();
		for(int i=1;i<=N;++i) A[i] = getUnsigned();
		printf("%d\n", proc());
	}
	return 0;
}