#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int int_t;

struct Hash{
    typedef int_t key_t;
    typedef int_t value_t;
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
int_t bsgs(int_t a,int_t b,int_t n){
    if ( 1 == b ) return 0;

    Map.clear();
    int_t m = sqrt(n+0.5);
    int_t x = 1, p = 1;
    for(int_t i=0;i<m;++i,p=p*a%n) Map.insert(p*b%n,i);

    int_t j;
    for(int_t i=m;i<=n;i+=m)if(-1!=(j=Map.find(x=x*p%n)))return i-j;

    return -1;
}

int main(){
    int a,b,n;
    while(EOF!=scanf("%d%d%d",&n,&a,&b)){
        int_t ans = bsgs(a,b,n);
        if ( -1 == ans ) printf("no solution\n");
        else printf("%lld\n",ans);
    }
    return 0;
}

