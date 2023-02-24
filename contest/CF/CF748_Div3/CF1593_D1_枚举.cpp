/**
 * 给定N元素的数组A，再选定一个K，每次选择一个Ai令Ai-=K
 * 最后要求使得所有的Ai相等，操作次数不限。
 * 问最大的可能的K是多少，如果K可以任意大，则输出-1
 * 
 * 首先只有初始值全相等才输出-1.
 * 令最终结果为d，则Ai-miK=d, Aj-mjK=d
 * 所以 Ai-Aj = (mi-mj)K
 * 说明K必然是二者之差的约数
 * 所以K最大是两两之差的gcd
 * N在40，暴力枚举即可
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

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 50;
#endif

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int N;
int A[SIZE];

int proc(){
    sort(A+1, A+N+1);
	N = unique(A+1, A+N+1) - A - 1;

	if(1 == N) return -1;

	int ans = A[2] - A[1];
	for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        ans = gcd(ans, A[j] - A[i]);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		printf("%d\n", proc());
	}
    return 0;
}