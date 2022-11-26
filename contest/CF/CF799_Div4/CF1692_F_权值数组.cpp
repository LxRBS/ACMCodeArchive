/**
 * 给一个数组，问是否能挑出三个互异的元素使得其和的个位数是3
 * 注意到只与个位数有关，而个位数一共只有10个。
 * 因此不需要O(N^3)，只需要O(10^3)即可
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
int const SIZE = 18;
#else
int const SIZE = 2E5+13;
#endif

int N;
int A[SIZE];
int C[11];

bool proc(){
    for(int tmp,i=0;i<10;++i){
        if(0 == C[i]) continue;
        --C[i];
        for(int j=0;j<10;++j){
            if(0 == C[j]) continue;

            --C[j];
            tmp = (i + j) % 10;
            tmp = (13 - tmp) % 10;
            if(C[tmp]) return true;
            ++C[j];
        }
        ++C[i];
    }      
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        memset(C, 0, sizeof(C));
        for(int i=1;i<=N;++i) ++C[A[i] = getInt() % 10];
        puts(proc()?"YES":"NO");
    }
    return 0;
}
