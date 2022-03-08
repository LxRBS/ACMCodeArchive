/**
 * 给定一个长度为N的数组A，下标从0到N-1，令X初始为0，重复K次操作，每次操作：
 * 令  X += A[X%N]
 * 求最后的X。N为2E5，K为1E12。
 * 很明显，不能直接for K，需要找规律。因为是对N取模，所以只要X%N的某个值重复出现，则后面就会呈现周期变化。
 * 只需要找到这个周期就可。
 * 操作序号： 1 2 3 4 5 6 7 8 9 ... K-2, K-1 K
 * 假设第9次操作时，发现X9%N==X3%N，于是就找到一个长度为6的循环节为[3, 8]， 
 * 再假设整除循环节后，最后还剩3个，于是可以把整个K看做是前5个，后面全部是m个长度为6的完整循环节
 * 计算一下和即可
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
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 200030;
#endif  

llt N, K;
llt A[SIZE];
bool Flag[SIZE];
vector<int> Vec;

llt proc(){
	if(K <= 10000000){
		llt ans = 0LL;
		for(int i=0;i<K;++i){
			ans += A[ans%N];
		}
		return ans;
	}
	// llt ans = 0;
	// for(int i=0;i<K;++i){
	// 	printf("add A[%d]\n", ans%N);
	// 	ans += A[ans%N];
	// }
	Vec.reserve(N);
    fill(Flag, Flag+N, false);
	llt total = 0;
    Vec.push_back(0);
	Flag[0] = true;
	while(1){
		(total += A[Vec.back()%N]) %= N;
		if(Flag[total]){
            break;
		}
		Vec.push_back(total);
		Flag[total] = true;
	}

	int k = 0;
	while(k<Vec.size() && Vec[k] != total) ++k;
	assert(k < Vec.size());
    
	int len = Vec.size() - k;
	llt r = (K - k) / len;
	int left = (K - k) % len;
	llt ans = 0LL;
	for(int i=0,n=k+left;i<n;++i){
		ans += A[Vec[i]];
	}
	llt unit = 0LL;
	for(int i=k;i<Vec.size();++i){
		unit += A[Vec[i]];
	}
	ans = ans + unit * r;
	return ans;
} 

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); K = getInt();
	for(int i=0;i<N;++i) A[i] = getInt();
	printf("%lld\n", proc());
    return 0;
}

