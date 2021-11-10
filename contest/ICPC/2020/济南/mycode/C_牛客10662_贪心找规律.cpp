/**
 * 给定a1、a2、a3分别表示石子数量为1、2、3的堆数
 * 每次操作可以任选两堆进行合并，代价为(x%3) * (y%3)
 * x和y是两堆石子的数量
 * 问将所有堆合并的最小代价是多少
 * 简单推理就知道a3是不起作用的，即与3的倍数的合并顺序是不影响结果的
 * 因此只考虑1和2即可。再测试若干数据感觉要优先合并1和2
 * 然后剩下的自己和自己合并即可。因为达到3的倍数顺序就不重要了。
 * 所以剩下的3个3个一合即可。最后考虑余数。
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
int const SIZE = 21;
#else 
int const SIZE = 100010;
#endif

#define fi first
#define se second

typedef long long llt;
llt A[4];

inline llt f1(llt n){
	return n / 3LL * 3LL + (n%3==2 ? 1LL : 0LL);
}

inline llt f2(llt n){
	return n / 3LL * 6LL + (n%3==2 ? 4LL : 0LL);
}
llt proc(){
	llt ans = 0;
	if(A[1] >= A[2]){
		A[1] -= A[2];
		ans += A[2] * 2LL;
		return ans += f1(A[1]);
	}

	A[2] -= A[1];
	ans += A[1] * 2LL;
    return ans += f2(A[2]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A[1] = getInt();
	A[2] = getInt();
	A[3] = getInt();
	cout<<proc()<<endl;
	return 0;
}
