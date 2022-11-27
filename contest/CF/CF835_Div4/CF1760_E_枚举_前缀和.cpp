/**
 * 给定01数组，最多操作一次，选定某个Ai将其取反
 * 问最多能获得的逆序对是多少
 * 做两个前缀和，分别记录0和1的数量
 * 枚举每个位置，看修改哪个位置能够增加的逆序对最多
 * 
 */
#include <assert.h>
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
int const SIZE = 2E5+13;
#endif
using llt = long long;
int N;
int A[SIZE];
int B[SIZE];
int C[SIZE];

llt proc(){
    C[N+1] = 0;
    for(int i=1;i<=N;++i){
        if(A[i]) B[i] = B[i-1] + 1, C[i] = C[i-1];
        else B[i] = B[i-1], C[i] = C[i-1] + 1;
    }

    llt ans = 0;
    for(int i=1;i<=N;++i){
        if(A[i]){
            ans = max(ans, (llt)B[i-1] - (C[N] - C[i]));
        }else{
            ans = max(ans, (llt)(C[N] - C[i]) - B[i-1]);
        }
    }
    llt ret = ans;
    for(int i=1;i<=N;++i){
        if(A[i]) ret += (C[N] - C[i]);
    }
    return ret;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        printf("%lld\n", proc());
	}
    return 0;
}
