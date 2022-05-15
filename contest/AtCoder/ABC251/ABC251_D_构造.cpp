/**
  构造一个数组A，满足从1到1E6的任何数，
  均可以表示为最多三个不同的Ai之和
  对于一个6位数，abcdef，将其分为三段，
  每一段的取值数量都是99个，最后再加上1E6本身即可
  本质上就是100进制。最后的数组A就是：
  [1,2,3,...,99,100,200,...,9900,10000,20000,...,990000,1E6]
*/
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

using llt = long long;

llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 100+5;
#endif

using llt = long long;
using Real = long double;
using vi = vector<int>;
using pii = pair<int, int>;

int N = 300;
llt F[310];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
	cout<<298<<endl;
	for(int i=1;i<100;++i){
		cout<<i<<" "<<100*i<<" "<<10000*i<<" ";
	}
	cout<<1000000<<endl;
    return 0;
}
