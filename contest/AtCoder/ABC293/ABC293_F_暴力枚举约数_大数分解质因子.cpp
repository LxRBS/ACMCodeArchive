/**
 * 给定N，假设在某一进制下，N的表示法只含0或者1，则称该进制是满足条件的
 * 问对N而言一共有多少个进制是满足条件的
 * case数量为1000， N在1E18
 * 简单思考即可发现只有可能是 N 或者 N-1 的约数
 * 由于1E18以内约数最多的数为 897612484786617600 ，共有103680个约数，
 * 因此可以考虑求出所有约数，再除一下。
 * 用PollardRho求所有质因子在O(N^(1/4))，然后利用质因子求出所有约数，也在O(N^(1/4))?
 * 令f(N)为N的所有约数数量，因此为O(1000*(N^(1/4) + f(N)*logN))
 * 然后再记录一下出现过的答案防止重复询问。 没有这个会T两个点。
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


using llt = long long;
llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;	
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;

namespace SHULUN{

using llt = long long;
using int128 = __int128_t;
// using int128 = llt;

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
	// const auto & vec = TWELVE;
	
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

struct Sieve{ // 线性筛法

using llt = int;
vector<bool> isComp; // isComp[i]表示i是否为合数
vector<llt> primes; // primes[i]是第i个质数

Sieve(int SZ = 35000){
    primes.reserve(SZ);
    isComp.assign(SZ, false);    

    long long tmp;
    for(int i=2;i<SZ;++i){
        if(!isComp[i]){
            primes.push_back(i);
        }

        for(int j=0,n=primes.size();j<n&&(tmp=i*(long long)primes[j])<SZ;++j){
            isComp[tmp] = true;

            if(0 == i % primes[j]){
                break;
            }else{
            }
        }
    }
}

};

}

llt N;
map<llt, int> Ans;

SHULUN::Sieve SIEVE;

bool check(llt n, llt base){
	while(n){
		auto t = n % base;
		if(t != 1 and t != 0) return false;
		n /= base;
	}
	return true;
}

vector<pair<llt, int>> proc(llt n){
	vector<pair<llt, int>> ans;

	vll vec;
	SHULUN::allFactors(n, vec);
	ans.reserve(vec.size());
	for(llt pi : vec){
		assert(0 == n % pi);
		int k = 0;
		while(n % pi == 0) n /= pi, ++k;
		ans.emplace_back(pi, k);
	}
	assert(1 == n and vec.size() == ans.size());
	return ans;
}

void gen(const vector<pair<llt, int>> & a, vll & b){
	b.clear();
	b.push_back(1LL);
	for(const auto & p : a){
		int sz = b.size();
		llt k = 1;
		for(int i=1;i<=p.second;++i){
			k *= p.first;
			for(int j=0;j<sz;++j){
                b.push_back(k * b[j]);
			}
		}
	}
	sort(b.begin(), b.end());
	return;
}

int proc(){
	if(2 == N) return 1;
	if(3 == N) return 2;
	if(4 == N) return 3;

	auto a = proc(N);
	auto b = proc(N - 1);
	vll aa, bb;

	gen(a, aa); 
	gen(b, bb);

	vll c;
	set_union(aa.begin(), aa.end(), bb.begin(), bb.end(), back_inserter(c));

	int ans = 0;
    for(int i=1,n=c.size();i<n;++i){
		if(check(N, c[i])){
			++ans;
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    int nofkase = getInt();
	while(nofkase--){
        auto it = Ans.find(N = getLL());
		if(it == Ans.end()) it = Ans.insert(it, {N, proc()});
		printf("%d\n", it->second);
	}
    return 0; 
}
