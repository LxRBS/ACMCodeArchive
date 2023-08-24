/**
 * 给定数组A和B，要求统计如下两个数据：
 * 1. 所有的i的数量，满足Ai==Bi
 * 2. 所有(i, j)的数量，Ai==Bj且i!=j
 * 由于N只有1000，双重循环即可
 * 也可以使用哈希记录(值，位置)，从而在接近O(N)的时间内完成
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
int const SIZE = 15;
#else
int const SIZE = 1100+5;
#endif

typedef long long llt;
int N;
int A[SIZE], B[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
    for(int i=0;i<N;++i) A[i] = getInt();
    for(int i=0;i<N;++i) B[i] = getInt();
    int a1 = 0, a2 = 0;
    for(int i=0;i<N;++i){
        if(A[i] == B[i]) ++a1;
        for(int j=0;j<N;++j){
            if(i == j) continue;
            if(A[i] == B[j]) ++a2;
        }
    }
    cout<<a1<<endl<<a2<<endl;
    return 0;
}