/**
   如果有一个偶数N，然后1与N/2一对，2与N/2+1一对，...，N/2-1与N一对
   现在给定a/b/c，表示在某个偶数情况下a与b一对，问与c配对的数是多少
   如果不存在，输出-1.
   规律很明显，注意不存在的判定条件即可。
*/
#include<bits/stdc++.h>
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

typedef long long llt;

llt f(llt a,llt b,llt c){
    if(a>b) swap(a, b);
    llt n = b - a;
    if(a>n&&b>n) return -1;
    if(c>n+n) return -1;
    return c > n ? c - n : c + n;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int a = getUnsigned();
        int b = getUnsigned();
        int c = getUnsigned();
        printf("%lld\n", f(a,b,c));
    }
    return 0;
}

