/**
 * 从坐标(000)移动到坐标(XYZ)，每次只能向8邻域移动一个单位
 * 问恰好N步到达，一共有多少种不同的方法
 * 首先很容易判断是否不能到达，以下仅考虑能到的情况，其次将XYZ全部变成正数
 * 考虑一维情况，假设n步到x，则必须有(n+x)/2的正方向移动，剩下的为负方向，算一个组合数即可
 * 再考虑二维情况，n步到(x,y)，为了方便陈述令n=x+y+2k，于是可以肯定总的负方向的步数为k
 * 假设x正方向需要x+i步，则负方向要i步，y正方向需要y+k-i步，负方向要k-i步
 * 因此总的方案数为SIGMA{C(n,k)C(n-k,x+i)C(k,i),i=0到k}
 * 其含义就是首先从n步中选出k个负步，其余为正；
 * 再从n-k个正步中选出x+i个给与x正，剩下的自然给y正
 * 最后从k个负步中选出i个给x负，剩下的自然给y负，这一项可以变成C(k,k-i)
 * 第一项是常数不考虑，考虑后两项，其实就是总数为n，
 * 分两堆，一堆n-k，一堆k，然后各取x+i和k-i个，i要遍历，
 * 因此效果就是从总的n个中取x+k个，所以就是C(n,x+k)，这样就消除了i的循环
 * 因此二维情况的结果为C(n,k)C(n,x+k)
 * 考虑三维情况，令t是分配给z的步数，则n-t是分配给xy的步数，所以答案是
 * SIGMA{C(n,t)C(t,(t-z)/2)*(n-t步走到xy的答案),t=z到n-x-y}
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 323;
#else
int const SIZE = 1E7+5;
#endif

typedef long long llt;
llt const MOD = 998244353LL;

llt power(llt a, llt n){
    llt ret = 1LL; a %= MOD;
    while(n){
        if(n & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ret;
}

inline llt inv(llt a){return power(a, MOD-2);}

llt Fac[SIZE], IFac[SIZE];

void init(int n){
    Fac[0] = Fac[1] = 1LL;
    for(int i=2;i<=n;++i) Fac[i] = Fac[i-1] * i % MOD;
    IFac[n] = inv(Fac[n]);
    for(int i=n-1;i>=0;--i) IFac[i] = IFac[i+1] * (i+1) % MOD;
    assert(IFac[1] == 1 && IFac[0] == 1);
}

/// 组合数， n里面选m个, 保证m在范围以内
inline llt C(llt n, llt m){
    return Fac[n] * IFac[m] % MOD * IFac[n-m] % MOD;
}

llt N, X, Y, Z;

llt proc(){
    if(X+Y+Z > N) return 0;
    if((X+Y+Z-N)&1) return 0;

    llt a = Z;
    llt b = N - X - Y;
    llt ans = 0;
    for(llt tmp,i=a;i<=b;i+=2){
        tmp = 1LL;
        (tmp *= C(N, i)) %= MOD;
        (tmp *= C(i, (i-Z)/2)) %= MOD;
        (tmp *= C(N-i, (N-i-X-Y)/2)) %= MOD;
        (tmp *= C(N-i, (N-i-X+Y)/2)) %= MOD;
        (ans += tmp) %= MOD;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    llt a[3];
    cin>>N>>a[0]>>a[1]>>a[2];
    init(N);
    for(int i=0;i<3;++i)if(a[i]<0)a[i]=-a[i];
    sort(a, a+3);
    X=a[0], Y=a[1], Z=a[2];
    cout<<proc()<<endl;
    return 0;
}
