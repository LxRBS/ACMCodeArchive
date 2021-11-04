/**
  ����һ�������޻�ͼ���ٵȸ��ʸ���һ�����������P
  ��P1��Pn���δ������Pi���ھ�û�б�ѡ�������Piѡ����
  �����ѡ�����ļ��ϵĳ��������Ƕ���
  �ٸ���򵥵����ӣ�����xֻ��y�бߣ�����x��ѡ�����ϵ��ܴ����Ƕ��٣�
  ���x��ѡ�еĲ�ͬ�����������
  C(n, 2) * 1! * (n-2)!
  ��һ��ģ�����x�Ķ�����d����x��ѡ�еĲ�ͬ���������
  C(n, d+1) * d! * (n-d-1)!
  ûѡ��һ�γ���+1����˴�1��N�ۼ������ٳ���n!
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
    /// Ԥ����׳˺���
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
