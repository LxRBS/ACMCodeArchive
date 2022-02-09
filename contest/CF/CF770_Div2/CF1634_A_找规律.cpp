/**
 * 给定字符串s，进行k次操作，操作有2种：
 * 1 s = s + rev(s)
 * 2 s = rev(s) + s
 * 问k次操作后，可能得到的不同的字符串有多少个
 * 如果s是回文串，则两种操作无区别
 * 如果s不是回文串，则一次操作后必然得到2个不同的回文串
 * 因此发现答案
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
int const SIZE = 11;
#else
int const SIZE = 155;
#endif

int N, K;
char A[SIZE];

bool f(){
    for(int i=0;i<N/2;++i){
        if(A[i] != A[N-1-i]) return false;
    }
    return true;
}

int proc(){
    if(f()){
        return 1;
    }
    return K ? 2 : 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%s", &N, &K, A);
        printf("%d\n", proc());
    }
    return 0;
}
