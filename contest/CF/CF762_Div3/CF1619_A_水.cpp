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
int const SIZE = 1010;
#endif

char A[SIZE];
bool proc(){
	int n = strlen(A);
	if(n%2) return false;
	n /= 2;
	for(int i=0;i<n;++i){
		if(A[i] != A[i+n]) return false;
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%s", A);
		puts(proc()?"YES":"NO");
	}
    return 0;
}
