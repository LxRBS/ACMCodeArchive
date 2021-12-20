/**
 * 给定一个数组a，要求找到d，满足：
 * 1. 将a中所有元素，是d的倍数的染成红色，其他染成蓝色
 * 2. 相邻元素颜色不同
 * 对两组数求一个gcd，然后判断即可
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

llt getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 110;
#endif

int N;
llt A[SIZE];

bool check(llt g, int start){
    for(int i=start;i<N;i+=2){
        if(A[i]%g==0) return false;
    }
    return true;
}

llt proc(){
    llt g0 = A[0];
    for(int i=2;i<N;i+=2) g0 = gcd(g0, A[i]);

    llt g1 = A[1];
    for(int i=3;i<N;i+=2) g1 = gcd(g1, A[i]);

    if(check(g0, 1)) return g0;
    if(check(g1, 0)) return g1;
    return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        for(int i=0;i<N;++i) A[i] = getUnsigned();
        printf("%lld\n", proc());
    }
    return 0;
}

