/**
    ��չ�Ĵ�С���㷨��ģ����
*/
#include <stdio.h>
#include <math.h>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

typedef long long llt;

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
//��ⷽ��a^x%n=b������a,n���ʣ���֤�н�
//������С�Ǹ��⣬�������-1����ʾ�޽�
llt bsgs(llt a,llt b,llt n){
	a %= n, b %= n;
    //a�����0��bҲ��0�����Ϊ1��b��Ϊ0���޽�
    if ( 0 == a ) return b?-1:1;
    //bΪ1�����Ϊ0
    if ( 1 == b ) return 0;

    Map.clear();
    llt m = sqrt(n+0.5);
    llt x = 1, p = 1;
    for(llt i=0;i<m;++i,p=p*a%n) Map.insert(p*b%n,i);

    llt j;
    for(llt i=m;i<=n+m;i+=m)if(-1!=(j=Map.find(x=x*p%n)))return i-j;

    return -1;
}

//iteration implementation
llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}


//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
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

//returns the inverse of a mod p satisfied with 1 == ax%p
//it will be success only when a and p are co-prime
inline llt inv(llt a,llt p){
    llt x,y;
    llt r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

//��չ��BSGS�㷨
//��ⷽ��a^x%n=b������a,n��һ�����ʣ���һ���н�
//������С�Ǹ��⣬�������-1����ʾ�޽�
llt exBSGS(llt a,llt b,llt n){
    a%=n, b%=n;
    //a�����0��bҲ��0�����Ϊ1��b��Ϊ0���޽�
    if ( 0 == a ) return b?-1:1;
    //bΪ1�����Ϊ0
    if ( 1 == b ) return 0;
    //gcd
    llt g = gcd(a,n);
    if(1==g) return bsgs(a,b,n);
    //b����g�ı������޽�
    if(b%g) return -1;
    //�ݹ�
    return (1 + exBSGS(a,b/g*inv(a/g,n/g),n/g))%n;
}
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
int main(){
    //freopen("1.txt","r",stdin);
    while(1){
        llt a,p,b;
        scanf("%lld%lld%lld",&a,&p,&b);
        if(!a&&!p&&!b) break;
        llt ret = exBSGS(a,b,p);
        if(-1==ret)printf("No Solution\n");
        else printf("%lld\n",ret);
    }
    return 0;
}
