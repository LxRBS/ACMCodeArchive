/**
 * 给定目标点，从原点向目标点方向前进1个距离单位，问此时点的坐标
 * 用atan2求一个角度即可
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
typedef double Real;

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    Real a, b;
	cin>>a>>b;
	Real angle = atan2(b, a);
	cout<<fixed<<setprecision(12)<<cos(angle)<<" "<<sin(angle)<<endl;
    return 0;
}

