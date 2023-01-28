#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;


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

struct Sieve{ // 线性筛法

using llt = int;
vector<bool> isComp; // isComp[i]表示i是否为合数
vector<llt> primes; // primes[i]是第i个质数
vector<llt> Euler;  // Euler[i]表示i的欧拉函数
vector<int> Mobius; // 莫比乌斯函数

Sieve(int SZ = 35000){
    primes.reserve(SZ);
    isComp.assign(SZ, false);    

    // Euler.assign(SZ, 0);
    // Euler[1] = 1;
    
    // Mobius.assign(SZ, 0);
    // Mobius[1] = 1;

    long long tmp;
    for(int i=2;i<SZ;++i){
        if(!isComp[i]){
            primes.push_back(i);
            // Euler[i] = i - 1;
            // Mobius[i] = -1;
        }

        for(int j=0,n=primes.size();j<n&&(tmp=i*(long long)primes[j])<SZ;++j){
            isComp[tmp] = true;

            if(0 == i % primes[j]){
                // Euler[tmp] = Euler[i] * primes[j];
                // Mobius[tmp] = 0;
                break;
            }else{
                // Euler[tmp] = Euler[i] * (primes[j] - 1);
                // Mobius[tmp] = -Mobius[i];
            }
        }
    }
}

};


}

// SHULUN::Sieve sieve(1e8);

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
	int n = getInt();
	int q = getInt();
	// int n, q;
	// scanf("%d%d", &n, &q);	

    SHULUN::Sieve sieve(n+1);
	while(q--){
		printf("%d\n", sieve.primes[getInt() - 1]);
	}

	return 0;
}