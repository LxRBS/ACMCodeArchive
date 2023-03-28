/**
 * 给定函数f，当x是个位数时, f([0,1,2,3,4,5,6,7,8,9]) = [1,0,0,0,1,0,1,0,2,1] 
 * 当x是多位数时 f等于 f(x的各位数字) 之和。
 * 现在给定N和K，求 f(f(f....(f(N))))，一共K次。
 * K很大，不可能直接模拟。但是注意到f(N)会迅速到达个位数，再之后就是一个周期变化
 * 因此正确处理进入周期的状态，然后取余数，再模拟即可。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

Real const EPS = 1E-14;
inline int sgn(Real x) {return x > EPS ? 1 : (x < -EPS ? -1 : 0);}
inline bool is0(Real x) {return 0 == sgn(x);}

int N, K;

const array<int, 10> F{1, 0, 0, 0, 1, 0, 1, 0, 2, 1};
const vector<pii> T{
	{0, 2}, {0, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {2, 2}, {1, 2}
};
const array<int, 10> S{0, 1, 0, 0, 1, 0, 1, 0, 0, 1};

int f(int x){
	if(0 == x) return 1;

	int ans = 0;
	while(x){
        ans += F[x%10];
		x /= 10;
	}
	return ans;
}

int proc(int x, int k){
	const auto & p = T[x];
	auto offset = p.first;
	auto t = p.second;
	if(k <= t){
		for(int i=0;i<k;++i) x = f(x);
		return x; 
	}

    k -= offset;
	x = S[x];
	int left = k % t;
    for(int i=0;i<left;++i) x = f(x);
	return x;
}

int proc(){
	for(int i=0;i<K;++i){
        auto t = f(N);
		if(t < 10) return proc(t, K - i - 1);
		N = t;
	}
	return N;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
	while(nofkase--){
        N = getInt(); K = getInt();
		printf("%d\n", proc());
	}
    return 0; 
}
