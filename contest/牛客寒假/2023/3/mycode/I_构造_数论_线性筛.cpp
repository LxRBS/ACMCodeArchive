/**
 * 定义S(x)为x的所有约数之和，但不包括x自身。
 * 给定N,求x满足S(x) = N
 * 如果N是偶数保证N-1或者N-3是质数
 * 考虑这个条件，可以发现，如果令N-1==p， 则S(p^2) = N
 * 进一步考虑N-3=p， 则S(2p) = N
 * 据此类似考虑N是奇数，考虑两个质数p和q，满足 p + q = N - 1，
 * 则S(pq) = N。 而不太大的偶数总能拆成两个质数之和。
 * 还需要注意特判较小的数，特别是7。
 */
#include <bits/stdc++.h>
using namespace std;
 
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 450;
#endif

namespace Sieve{
using llt = long long;
#ifndef ONLINE_JUDGE
int const SZ = 23;
#else
int const SZ = 1000100;
#endif

vector<bool> isComp; // isComp[i]表示i是否为合数
vector<llt> primes; // primes[i]是第i个质数

void run(){
    primes.reserve(SZ);
    isComp.assign(SZ, false);    

    long long tmp;
    for(int i=2;i<SZ;++i){
        if(!isComp[i]){
            primes.push_back(i);
        }

        for(int j=0,n=primes.size();j<n&&(tmp=i*primes[j])<SZ;++j){
            isComp[tmp] = true;

            if(0 == i % primes[j]){
                break;
            }
        }
    }
}

};

using llt = long long;
llt N;

llt proc(){
    if(1 == N) return 2;
    if(3 == N) return 4;
    if(4 == N) return 9;
    if(N <= 5) return -1;
    if(7 == N) return 8;
    if(!Sieve::isComp[N - 1]){
        return (N - 1) * (N - 1);
    }
    if(!Sieve::isComp[N - 3]){
        return (N - 3) * 2;
    }
    auto n = N - 1;
    llt q;
    for(auto p : Sieve::primes){
        if(p + p >= n) break;
        if(p == (q = n - p) || Sieve::isComp[q]) continue;
        return p * q;
    }
    // assert(0);
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    Sieve::run();
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}


