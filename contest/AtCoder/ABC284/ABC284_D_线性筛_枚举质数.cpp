/**
 * 给一个9E18的数N，已知N = p^2*q，p和q是不相等的质数，求p和q
 * 注意到p和q必然有一个在N^(1/3)之内，大约200万多一点，所以先筛出该范围的质数
 * 再枚举
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

namespace Sieve{
using llt = int;
enum{SZ = 2080090}; // 一般只筛到30000+即可

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

llt N;

void proc(){
    for(llt p : Sieve::primes){
        if(N % p) continue;

        llt x = p, y = N / p;
        if(0 == y % x) return (void)printf("%lld %lld\n", x, y / x);
        return (void)printf("%lld %lld\n", (llt)sqrt(y), x);
    }
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
	Sieve::run();
	int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		proc();
	}
    return 0;
}


