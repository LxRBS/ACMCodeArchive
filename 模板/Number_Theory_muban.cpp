
/// 普通筛法, O(NlogN), 可以同时求出所有数的质因子
namespace NormalSieve{

using llt = int;

enum{SZ = 35000}; // 一般只筛到30000+即可

vector<bool> isComp; // isComp[i]表示i是否为合数
vector<llt> primes; // primes[i]是第i个质数

void run(){
    primes.reserve(SZ);
    isComp.assign(SZ, false);

    for(int i=2;i<SZ;++i){
        if(isComp[i]) continue;

        primes.push_back(i);
        for(long long j=i*i;j<SZ;j+=i){
            isComp[j] = true;
        }
    }
}

};

/// 线性筛, O(N), 可以同时筛出欧拉函数和莫比乌斯函数
namespace Sieve{
using llt = int;
enum{SZ = 35000}; // 一般只筛到30000+即可

vector<bool> isComp; // isComp[i]表示i是否为合数
vector<llt> primes; // primes[i]是第i个质数
vector<llt> Euler;  // Euler[i]表示i的欧拉函数
vector<int> Mobius; // 莫比乌斯函数

void run(){
    primes.reserve(SZ);
    isComp.assign(SZ, false);    

    Euler.assign(SZ, 0);
    Euler[1] = 1;
    
    Mobius.assign(SZ, 0);
    Mobius[1] = 1;

    long long tmp;
    for(int i=2;i<SZ;++i){
        if(!isComp[i]){
            primes.push_back(i);
            Euler[i] = i - 1;
            Mobius[i] = -1;
        }

        for(int j=0,n=primes.size();j<n&&(tmp=i*primes[j])<SZ;++j){
            isComp[tmp] = true;

            if(0 == i % primes[j]){
                Euler[tmp] = Euler[i] * primes[j];
                Mobius[tmp] = 0;
                break;
            }else{
                Euler[tmp] = Euler[i] * (primes[j] - 1);
                Mobius[tmp] = -Mobius[i];
            }
        }
    }
}

};


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
/// 当n接近64位时，中间的乘法要转128位
llt PollardRho(llt n){
    llt s = 0, t = 0;
    llt c = rand() % (n - 1) + 1;
    int step = 0, goal = 1;
    llt val = 1;
    llt ans;
    for(goal=1;;goal<<=1,s=t,val=1){
        for(step=1;step<=goal;++step){
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
llt largest_prime_factor;

void dfsLargestPrimeFactor(llt x){
    if(x <= largest_prime_factor) return;
    if(MillerRabin(x)) return (void)(largest_prime_factor = x);

    llt p;
    while((p = PollardRho(x)) >= x);
    while(0 == x % p) x /= p;
    dfs(x); dfs(p);      
}

llt getLargestPrimeFactor(llt n){
    largest_prime_factor = 0;
    dfsLargestPrimeFactor(n);
    return largest_prime_factor;
}

}
