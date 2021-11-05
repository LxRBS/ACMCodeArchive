/**
   按如下方式填表
   1 2 5
   4 3 6
   9 8 7
    给定k，问应该填在哪里。
   很明显要找到一个数c，使得c*c+1<=k<=(c+1)*(c+1)
   然后再计算一下即可
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

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        llt n = getUnsigned();
        llt c = sqrt(n);
        while(c*c<n) ++c;
        --c;
        llt start = c*c+1;
        llt cha = n - start + 1;
        if(cha<=c){
            printf("%lld %lld\n", cha, c+1);
            continue;
        }
        printf("%lld %lld\n", 1+c, c+c-cha+2);
    }
    return 0;
}

