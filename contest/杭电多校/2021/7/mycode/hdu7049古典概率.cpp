/**
   从原点发射一个速度为v0的东西，方向为均匀分布。
   要t时间后，东西与原点的距离大于r。重力加速度取10
   就是一个斜抛运动公式，设与水平面夹角为theta，
   可解出sintheta的条件，而sintheta的条件就表明了球面上满足条件的面积
   除以整个球面的面积就得到概率
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
    char ch = __hv007();
    while( ch < '0' || ch > '9' ) ch = __hv007();

    int ret = (int)(ch-'0');
    while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
    return ret;
}

typedef long long llt;
llt const MOD = 1000000007LL;

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

llt inv(llt a){
    a %= MOD;
    llt ret = 1;
    llt n = MOD - 2;

    while( n ){
        if ( n & 1 ) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}

llt T, V, R;

void proc(){
    llt fenzi = 4*V*V*T*T + 100LL*T*T*T*T - 4*R*R;
    llt fenmu = 40*V*T*T*T;
     
    if(0 == fenzi){
        printf("500000004\n");
        return;
    }

    if(fenzi > 0){
        if(fenzi>=fenmu){
            printf("1\n");
            return;
        }

        fenzi += fenmu;
        fenmu <<= 1;
        llt g = gcd(fenzi, fenmu);
        fenzi /= g;
        fenmu /= g;
        printf("%lld\n", fenzi%MOD*inv(fenmu)%MOD);
        return;
    }

    fenzi = -fenzi;
    if(fenzi>=fenmu){
        printf("0\n");
        return;
    }

    fenzi = fenmu - fenzi;
    fenmu <<= 1;
    llt g = gcd(fenzi, fenmu);
    fenzi /= g;
    fenmu /= g;
    printf("%lld\n", fenzi%MOD*inv(fenmu)%MOD);
}

int main(){
    // freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        T = getUnsigned();
        V = getUnsigned();
        R = getUnsigned();
        proc();
    } 
   
    return 0; 
}