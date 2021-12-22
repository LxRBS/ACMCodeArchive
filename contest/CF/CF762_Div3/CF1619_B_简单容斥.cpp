/**
   令平方数或者立方数为OK数，问n以内OK数有多少
   简单容斥即可
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

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 140;
#else
int const SIZE = 1010010;
#endif

llt N;

inline llt pow(llt a, int n){
	llt ans = 1LL;
	for(int i=0;i<n;++i) ans *= a;
	return ans;
}

llt root(llt a, int n){
	llt ans = 1LL;
	while(pow(ans, n) <= a) ++ans;
	return --ans;
}

llt proc(){
	llt cnt2 = sqrt(N);
	llt cnt3 = root(N, 3);
	llt cnt6 = root(N, 6);
	return cnt2+cnt3-cnt6;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getUnsigned();
	while(nofkase--){
	    N = getUnsigned();
		printf("%lld\n", proc());	
	}
    return 0;
}
