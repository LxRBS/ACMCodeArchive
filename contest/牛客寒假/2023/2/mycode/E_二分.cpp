/**
 * 给定N，L，R，令f(x) = x - 1 + ((N / x)向下取整)
 * 求[L, R]中的最小的x使得f(x)最小
 * 显然如果是实数函数则x=sqrt(N)取到最小。对于整数而言，在sqrt(N)附近的一个区间内都有可能取到最小。
 * 令sqrt(N)向下取整记作u, 可以确定[L, u]的最小值必然是f(u)且能够取到最小值的区间必然是连续的，因此可以二分。
 * 还要注意检测一下f(u+1)。然后考虑一下u与[L, R]的相对位置。
 * 注意不能用三分，因为f函数在某些地方不是单调的。但是没有找出具体实例。
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

	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 130;
#else
int const SIZE = 1.1E6+10;
#endif

int const LIMIT = 100;

llt N, L, R;

inline llt f(llt x){
	return N / x + x - 1LL;
}

llt proc(llt s, llt e){
	llt level = f(e);
	llt left = s, right = e, mid;
	do{
        mid = (left + right) >> 1;
		if(f(mid) != level) left = mid + 1;
		else right = mid - 1;
	}while(left <= right);
	return left;
}

llt proc(){
    if(1 == R || L == R) return R;
	if(N <= L) return L;

	llt x = sqrt(N);
	if(L <= x && x <= R){
		if(x == R){
			auto tmp = proc(L, R);
			return tmp;
		}else if(f(x + 1) < f(x)){
			return x + 1;
		}
		auto tmp = proc(L, x);
		return tmp;
	}
	if(x < L){
		auto tmp = L;
		return tmp;
	}
	if(x > R){
		auto tmp = proc(L, R);
		return tmp;
	}
	assert(0);
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
    while(nofkase--){
		N = getInt();
		L = getInt();
		R = getInt();
		printf("%lld\n", proc());
	}
    return 0;
}

