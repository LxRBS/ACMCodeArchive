/**
  给定一个有向无环图。再等概率给定一个顶点的排列P
  从P1到Pn依次处理：如果Pi的邻居没有被选过，则把Pi选出来
  问最后选出来的集合的长度期望是多少
  举个最简单的例子，假设x只与y有边，考虑x被选到集合的总次数是多少？
  因此x被选中的不同情况的总数是
  C(n, 2) * 1! * (n-2)!
  更一般的，假设x的度数是d，则x被选中的不同情况总数是
  C(n, d+1) * d! * (n-d-1)!
  没选中一次长度+1，因此从1到N累加起来再除以n!
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 1000000007LL;

llt powerMod(llt a,llt n){
    llt ret = 1;
    a %= MOD;

    while( n ){
        if ( n & 1 ) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}

inline llt inv(llt a){
    return powerMod(a, MOD-2LL);
}

int Deg[210];
llt Fac[210] = {1, 1}, InvFac[210] = {1, 1};
llt Inv[210] = {1, 1};

inline llt C(llt n, llt m){
    return Fac[n] * InvFac[n-m] % MOD * InvFac[m] % MOD;
}

int main(){
    //freopen("1.txt","r",stdin);
    /// 预处理阶乘和逆
    for(int i=2;i<=66;++i){
        Inv[i] = (MOD - MOD / i) * Inv[MOD%i] % MOD;
        //if(Inv[i]<0) Inv[i] += MOD;
        Fac[i] = Fac[i-1] * i % MOD;
        InvFac[i] = InvFac[i-1] * Inv[i] % MOD;
    }

    int n, m;
    scanf("%d%d", &n, &m);
    for(int a,b,i=0;i<m;++i){
        scanf("%d%d", &a, &b);
        ++Deg[a]; ++Deg[b];
    }
    llt ans = 0LL;
    for(int i=1;i<=n;++i){
        (ans += C(n, Deg[i]+1) * Fac[Deg[i]] % MOD * Fac[n-Deg[i]-1] % MOD) %= MOD;
    }
    cout<<ans*InvFac[n]%MOD<<endl;
    return 0;
}
