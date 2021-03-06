/**
 * 给定矩形的三个顶点，求第4个。
 * 异或一下就行
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
int const SIZE = 10;
#else
int const SIZE = 3E5+5;
#endif

typedef long long llt;
typedef pair<int, int> pii;

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int x[3], y[3];
	int a = 0, b = 0;
	for(int i=0;i<3;++i){
		a ^= x[1]=getInt();
		b ^= y[1]=getInt();
	}
	cout<<a<<" "<<b<<endl;
    return 0;
}

