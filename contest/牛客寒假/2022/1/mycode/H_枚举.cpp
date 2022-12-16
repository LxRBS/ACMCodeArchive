/**
 * 给定数组A，求
 * SIGMA{i从1到N, SIGMA{j=i到N, |Ai+Aj-1000|}}
 * 注意到N有1E6，而Ai的取值范围为1E3，
 * 因此可以写一个1E6*1E3的枚举
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
int const SIZE = 11;
#else
int const SIZE = 1000055;
#endif

typedef long long llt;

int N;
llt A[SIZE];
llt Cnt[1010] = {0};

inline llt ABS(llt x){return x>=0?x:-x;}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int i=1;i<=N;++i) ++Cnt[A[i] = getInt()];
	llt ans = 0;
    for(int i=1;i<=N;++i){
		for(int j=0;j<=1000;++j){
			ans += ABS(A[i]+j-1000) * Cnt[j];
		}
		--Cnt[A[i]];
	}
	cout<<ans<<endl;
    return 0;
}
