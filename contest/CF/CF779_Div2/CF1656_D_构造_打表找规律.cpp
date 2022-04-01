/**
 * 给定N，问N能否分解成K个数的和，且这K个数模K的结果各不相同。
 * 如果有多个答案，返回任意一个即可
 * 解题报告没太看懂，观察找规律
 * 首先奇数结果肯定为2
 * 进一步的如果本身足够大又含有相对小的奇数因子，则答案就是这个奇数
 * 打表以后还发现如果是如果n=2*奇数，则K可以为4
 * 如果n=4*奇数，则K可以为8
 * 如果n是2的幂，则为-1
 * 于是猜测答案。最后想到n分为两部分，2的幂和一个奇数因子，应该取小的那个
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long llt;
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
int const SIZE = 10;
#else
int const SIZE = 1E5+5;
#endif

typedef pair<int, int> pii;

bool f(int n, int k){
    function<bool(int, int)> dfs = [&](int depth, int left)->bool{
        if(depth == k){
			return 0 == left;
		}
		for(int i=depth;i<=left;i+=k){
            bool b = dfs(depth+1, left-i);
			if(b) return true;
		}
		return false;
	};
	bool ans = dfs(0, n);
	return ans;
}

int Flag[200] = {
    0,2,-1,2,-1,2,3,2,-1,2,
	4,2,3,2,4,2,-1,2,3,2,
	5,2,4,2,3,2,4,2,7,2,
	3,2,-1,2,4,2,3,2,4,2,
	5,2,3,2,8,2,4,2,3,2,
	4,2,8,2,3,2,7,2,4,2,
	3,2,4,2,-1,2,3,2,8,2,
	4,2,3,2,4,2,8,2,3,2,
	5,2,4,2,3,2,4,2,11,2,
	3,2,8,2,4,2,3,2,4,2,
	5,2,3,2,13,2,4,2,3,2,4,2,7,2,3,
	2,8,2,4,2,3,2,4,2,8,2,3,2,-1,2,
	4,2,3,2,4,2,16,2,3,2,5,2,4,2,3,2,
	4,2,8,2,3,2,16,2,4,2,3,2,4,2,5,2,3,
	2,8,2,4,2,3,2,4,2,8,2,3,2,11,2,4,2,3,2,4,2,16,2,3,2,8,2,4,2,3,2,4,2,7,2,3,2
};
llt N;
llt proc(){
	if(N & 1) return 2;
	if(0 == N%3) return 3;
	if(0 == (N & (N-1LL))) return -1;
	if(N < 200) return Flag[N];
	if(N % 7 == 0) return 7;
	if(N % 5 == 0) return 5;
	if(N % 11 == 0) return 11;
    llt ans = 2;
	while(0 == (N&1)){
		N >>= 1;
		ans <<= 1;
	}
	if(ans > N) return N;
	return ans;
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		printf("%lld\n", proc());
	}
    return 0;
}
