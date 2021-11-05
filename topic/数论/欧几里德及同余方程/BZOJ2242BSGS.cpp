/**
    三种操作
    给定yzp，求y^z%p,快速幂取模
    给定yzp，求x满足xy%p=z，扩展的欧
    给定yzp，求x满足y^x%p=z，大步小步
*/
#include <stdio.h>
#include <math.h>
#include <map>
#include <algorithm>
using namespace std;

typedef long long llt;

//returns a^n%mod
llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}

llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

typedef long long int llt;

struct Hash{
    typedef llt key_t;
    typedef llt value_t;
    enum{MOD=0x1FFFFF};

    key_t keys[MOD+1];
    value_t values[MOD+1];

    int head[MOD+1];
    int next[MOD+1];

    int toUsed;

    Hash():toUsed(0){fill(head,head+MOD+1,-1);}

    void clear(){toUsed=0;fill(head,head+MOD+1,-1);}

    void insert(key_t const&key,value_t const&value){
        int k = key & MOD;
        keys[toUsed] = key;
        values[toUsed] = value;
        next[toUsed] = head[k];
        head[k] = toUsed++;
    }

    value_t find(key_t const&key)const{
        int k = key & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i] == key ) return values[i];
        }
        return -1;
    }
};

Hash Map;
//求解方程a^x%n=b，其中a,n互质，保证有解
//返回最小非负解，如果返回-1，表示无解
llt bsgs(llt a,llt b,llt n){
    a %= n, b %= n;
    //a如果是0，b也是0，则解为1；b不为0则无解
    if ( 0 == a ) return b?-1:1;
    //b为1，则解为0
    if ( 1 == b ) return 0;

    Map.clear();
    llt m = sqrt(n+0.5);
    llt x = 1, p = 1;
    for(llt i=0;i<m;++i,p=p*a%n) Map.insert(p*b%n,i);

    llt j;
    for(llt i=m;i<=n+m;i+=m)if(-1!=(j=Map.find(x=x*p%n)))return i-j;

    return -1;
}

void f1(llt y,llt z,llt p){
    printf("%lld\n",powerMod(y,z,p));
}

void f2(llt y,llt z,llt p){
    llt ans,tmp;
    llt ret = exEuclid(y,p,ans,tmp);
    if(z%ret){
        printf("Orz, I cannot find x!\n");
        return;
    }

    llt beishu = z / ret;
    llt t = p / ret;
    ans *= beishu;
    ans %= t;
    if(ans<0)ans+=t;
    printf("%lld\n",ans);
}

void f3(llt y,llt z,llt p){
    llt ret = bsgs(y%p,z%p,p);
    if(-1==ret){
        printf("Orz, I cannot find x!\n");
    }else{
        printf("%lld\n",ret);
    }
}


typedef void (*pf_t)(llt,llt,llt);
pf_t PF[] = {NULL,f1,f2,f3};

int main(){
    //freopen("1.txt","r",stdin);
    int t,k;
    L:
    if(EOF==scanf("%d%d",&t,&k)) return 0;
    while(t--){
        llt y,z,p;
        scanf("%lld%lld%lld",&y,&z,&p);
        PF[k](y,z,p);
    }
    goto L;
    return 0;
}
