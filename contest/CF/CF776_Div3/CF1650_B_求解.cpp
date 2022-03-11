/**
 * 定义函数fa(x)=x/a+x%a；给定a，求该函数在[L, R]上的最大值
 * 令x=pa+q,则f(x)=p+q，令p+q尽可能大即可
 * q最大可以到a-1，而p要加1就需要多a，因此优先满足q
 * 所以令x=na-1，求最大的n即可
 * 要注意上述格式可能比L小，那x直接取R即可
 * 另一种情况是a取1或2的情况，也可以直接取R
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
int const SIZE = 15;
#else
int const SIZE = 2E5+5;
#endif

typedef long long llt;
llt A, L, R;

llt proc(){
    llt ans = R / A + R % A;
    llt n = R / A;
    llt tmp = n * A - 1;
    if(tmp >= L){
        ans = max(ans, A - 1 + n - 1);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        L = getInt(); R = getInt(); A = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}
