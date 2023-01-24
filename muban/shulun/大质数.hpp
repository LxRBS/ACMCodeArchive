#include <bits/stdc++.h>
using namespace std;


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

