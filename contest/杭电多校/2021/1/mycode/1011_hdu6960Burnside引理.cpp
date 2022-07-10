/**
 * N个珠子染3种颜色，绿色不超过k且相邻异色的方案数是多少，考虑旋转不变性。
 * 有限制的染色方案总数，Burnside引理
 * ans = SIGMA{e(g)}/|G|
 * 其中|G|表示置换群中所有置换的数量，e(g)表示对每一个具体的置换g的不变元的数量
 * 很明显一共有N个旋转，假设旋转r表示旋转r格的置换，则需要考虑旋转r情况下的不变数量有多少。
 * 很容易得知旋转r情况下一共会分为gcd(N, r)段，则每个循环节的长度为N/gcd(N, r)
 * 实际上就是说循环节长度必须为N的因子，令某个循环节长度为L，
 * 只需要考虑L的染色方案总数即可，所有的N/L个片段均照此染色，就能构成一个不变元
 * 因此题目变为绿色不超过k，且相邻异色，长度为L的染色方案数量
 * 再将题目细化为绿色数量为i且相邻异色长度为L的染色方案数量
 * 注意到相邻异色且相当于是环，所以i个绿必然将整个L分成i段，
 * 然后这i段每一段可以单独染色，但实际上每一段只有2种染色方案，因为剩下的两种颜色仍然要相邻异色
 * 再考虑L个中间选i个分成i段的方案数，一共两种情况，使用隔板法很容易得到
 * 如果不选头，共有C(L-i, i)种，如果选头共有C(L-i-1, i-1)种
 * 注意绿色为0的时候要单算。
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 998244353LL;

inline void addAssMul(llt&a, llt b, llt c){a+=b*c;a%=MOD;}

int const SIZE = 1000001;//TODO
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
void sieve(){
    llt tmp;
    for(llt i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1;

        for(int j=0;j<PCnt&&(tmp=i*P[j])<SIZE;++j){
            isComp[tmp] = true;

            if ( 0 == i % P[j] ){
                Euler[tmp] = Euler[i] * P[j];
                break;
            }else{
                Euler[tmp] = Euler[i] * ( P[j] - 1 );
            }
        }
    }
}

llt InvFac[SIZE] = {1LL, 1LL};
llt Fac[SIZE] = {1LL, 1LL};
llt Inv[SIZE] = {1LL, 1LL};
void initFac(){
    for(int i=2;i<SIZE;++i){
        Inv[i] = (MOD-MOD/i) * Inv[MOD%i] % MOD;
        Fac[i] = Fac[i-1] * i % MOD;
        InvFac[i] = InvFac[i-1] * Inv[i] % MOD;
    }
}

/// 求组合数
llt C(int n, int m){
    return Fac[n] * InvFac[m] % MOD * InvFac[n-m] % MOD;
}

llt powerMod(llt a, llt n){
    llt ans = 1LL;
    while(n){
        if(n&1) ans = ans * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ans;
}

llt f(llt n, llt L, llt k){
    llt ans = L&1 ? 0 : 2; // 绿色为0的方案数
    for(llt i=1;i<=k;++i){ // 绿色为i的方案数
        ans += powerMod(2, i) * (C(L-i, i) + C(L-i-1, i-1)) % MOD;
    }
    return ans % MOD;
}

llt proc(llt n, llt k){
    llt i=1, ans = 0LL;
    for(;i*i<n;++i){ // 循环节长度为i以及n/i的方案数
        if(n%i) continue;
        addAssMul(ans, f(n, i, min(k*i/n, i/2)), Euler[n/i]);
        addAssMul(ans, f(n, n/i, min(k/i, n/i/2)), Euler[i]);
    }
    if(i*i==n){
        addAssMul(ans, f(n, i, min(k/i, i/2)), Euler[i]);
    }
    return ans * Inv[n] % MOD;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    initFac();
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%lld\n", proc(n, k));
    }
    return 0;
}