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
int const SIZE = 11;
#else
int const SIZE = 200010;
#endif

int N;
char A[SIZE];

int proc(){
	N = strlen(A);
	int c[2] = {0};
	for(char const *p=A;*p;++p)++c[*p-'0'];
	if(c[0] < c[1]) return c[0];
	if(c[0] > c[1]) return c[1];
	return c[0] - 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%s", A);
		printf("%d\n", proc());
	}
    return 0;
}
