#include <bits/stdc++.h>
using namespace std;

namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}


namespace SHULUN{



using llt = long long;
using int128 = __int128_t;
// using int128 = llt;

template<typename T> T ABS(const T& a){return a>=0?a:-a;}

llt powerMod(llt a, llt n, llt mod){
    llt ret = 1;
    a %= mod;
    while(n){
        if(n & 1){
			ret = (int128)ret * a % mod;
			// (ret *= a) %= mod;
		} 
        n >>= 1;
        a = (int128)a * a % mod;
		// (a *= a) %= mod;
    }
    return ret;
}



/// 判断n是否为质数，直接用费尔马小定理，选择基底可以保证在64位整数下正确
bool MillerRabin(llt n, int repeat = 3){
    if(1 == n) return false;
    if(2 == n || 3 == n) return true;

	static const std::vector<long long> SEVEN = {
        2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL
	};

	static const std::vector<long long> TWELVE = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
	};


    llt d = n - 1;
	int r = 0;
    while(!(d & 1)) ++r, d >>= 1;

    const auto & vec = SEVEN;
	
	// while(repeat--){
    //     llt a = rand() % (n - 2) + 2;
	for(auto a : vec){
		if(a > n && 0 == (a %= n)) continue;
		llt x = powerMod(a, d, n);
		if(1 == x || n - 1 == x) continue;

		for(int i=1;i<r;++i){
            x = (int128)x * x % n;
			if(n - 1 == x) break;  			
		}
		if(n - 1 != x) return false;
	}
	return true;
}

/// 返回n的一个因子，有可能返回本身
/// 当n接近64位时，中间的乘法要转128位
llt PollardRho(llt n){
    llt s = 0, t = 0;
    llt c = rand() % (n - 1) + 1;
    int step = 0, goal = 1;
    llt val = 1;
    llt ans;
    for(goal=1;;goal<<=1,s=t,val=1){
        for(step=1;step<=goal;++step){
            t = ((int128)t * t % n + c) % n;
            val = (int128)val * abs(t - s) % n;
            if(0 == step % 127){
                if((ans = __gcd(val, n)) > 1){
                    return ans;
                }
            }               
        }
		if((ans = __gcd(val, n)) > 1){
            return ans;
        }
    }

    assert(0);
	return 0;
}

/// 找n的最大的质因子
llt largestFactor(llt n){
    llt ans = 0;
    function<void(llt)> __dfs = [&ans, &__dfs](llt x){
        if(x <= ans || 1 == x) return;
		if(MillerRabin(x)) return (void)(ans = x);
		llt p;
		while((p = PollardRho(x)) >= x) ;
		while(0 == x % p) x /= p;
		__dfs(x); __dfs(p);
	};
    __dfs(n);
    return ans;
}

/// 找到所有的互异的质因子
void allFactors(llt n, vector<llt> & fac){
    fac.clear();
    function<void(llt)> __dfs = [&fac, &__dfs](llt x){
        if(1 == x) return;
        if(MillerRabin(x)) return (void)fac.emplace_back(x);
		llt p;
		while((p = PollardRho(x)) >= x) ;
		while(0 == x % p) x /= p;
		__dfs(x); __dfs(p);
    };
	__dfs(n);
    sort(fac.begin(), fac.end());
    fac.erase(unique(fac.begin(), fac.end()), fac.end());
    return;
}

}

using llt = long long;

llt N;
vector<llt> V;

inline void proc(){
	SHULUN::allFactors(N, V);  
	if(V.back() == N) return (void)printf("Prime\n");
	return (void)printf("%lld\n", V.back());
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    srand((unsigned)time(nullptr));
	using namespace IO;
    int nofkase = getInt();
	while(nofkase--){
		N = getLL();
		proc();
	}
	return 0;
}