/**
 * 给一个9E18的数N，已知N = p^2*q，p和q是不相等的质数，求p和q
 * 用PollardRho方法，分解质因子即可
 * 注意过程中存在超范围的地方，要转int128，否则会TLE
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

using llt = long long;
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
int const SIZE = 23;
#else
int const SIZE = 3500000;
#endif

namespace PollardRho{

using llt = long long;

llt powerMod(llt a, llt n, llt mod){
    llt ret = 1;
    a %= mod;
    while(n){
        if(n & 1) ret = (__int128_t)ret * a % mod;
        n >>= 1;
        a = (__int128_t)a * a % mod;
    }
    return ret;
}

/// 判断n是否为质数，repeat为重复判断的次数
bool MillerRabin(llt n, int repeat=10){
    if(1 == n) return false;
    if(2 == n || 3 == n) return true;

    llt d = n - 1, r = 0;
    while(!(d & 1)) ++r, d >>= 1;

    while(repeat--){
        llt a = rand() % (n - 2) + 2;
        llt x = powerMod(a, d, n);
        if(1 == x || n - 1 == x) continue;

        for(int i=0;i<r-1;++i){
            x = (__int128_t)x * x % n;
            if(n - 1 == x) break;
        }
        if(n - 1 != x) return false;
    }
    return true;
}

/// 返回n的一个因子，有可能返回本身
llt PollardRho(llt n){
    llt s = 0, t = 0;
    llt c = rand() % (n - 1) + 1;
    int step = 0, goal = 1;
    llt val = 1;
    llt ans;
    for(goal=1;;goal<<=1,s=t,val=1){
        for(step=1;step<=goal;++step){
            /// 要转int128，否则会超范围变慢
            t = ((__int128)t * t % n + c) % n;
            val = (__int128)val * abs(t - s) % n;
            if(0 == step % 127){
                if((ans = __gcd(val, n)) > 1){
                    return ans;
                }
            }   
            if((ans = __gcd(val, n)) > 1){
                return ans;
            }
        }
    }
}

vector<llt> factors;

void dfs(llt x){
    if(1 == x) return;
    if(MillerRabin(x)) return (void)factors.push_back(x);

    llt p;
    while((p = PollardRho(x)) >= x);
    while(0 == x % p) x /= p;
    dfs(x); dfs(p);    
}

const vector<llt> & getPrimeFactors(llt n){
    factors.clear();
    dfs(n);
    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());
    return factors;
}

}


using llt = long long;
llt N;


void proc(){
    auto ans = PollardRho::getPrimeFactors(N);
	assert(ans.size() == 2);
    if(N % (ans[0] * ans[0])) swap(ans[0], ans[1]);
    llt x = ans[0], y = ans[1];
	printf("%lld %lld\n", ans[0], ans[1]);
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
	srand((unsigned)time(nullptr));
	int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		proc();
	}
    return 0;
}


