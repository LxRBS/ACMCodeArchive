#include <bits/stdc++.h>
using namespace std;

namespace SHULUN{

struct NormalSieve{

using llt = int;

vector<bool> isComp; // isComp[i]表示i是否为合数
vector<llt> primes; // primes[i]是第i个质数

NormalSieve(int SZ = 35000){
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


struct Sieve{ // 线性筛法

using llt = int;
vector<bool> isComp; // isComp[i]表示i是否为合数
vector<llt> primes; // primes[i]是第i个质数
vector<llt> Euler;  // Euler[i]表示i的欧拉函数
vector<int> Mobius; // 莫比乌斯函数

Sieve(int SZ = 35000){
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

        for(int j=0,n=primes.size();j<n&&(tmp=i*(long long)primes[j])<SZ;++j){
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


}
