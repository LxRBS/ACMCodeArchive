/*
    成段修改，区间求和
*/
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long llt;
int const SIZE = 100010;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

llt ST[SIZE<<2];
llt Lazy[SIZE<<2];

void _pushUp(int t){
    ST[t] = ST[lson(t)] + ST[rson(t)];
}

void _pushDown(int t,int s,int e){
    if ( 0LL == Lazy[t] ) return;

    llt& a = Lazy[t];
    int mid = ( s + e ) >> 1;

    Lazy[lson(t)] += a;
    ST[lson(t)] += a * ( mid - s + 1);

    Lazy[rson(t)] += a;
    ST[rson(t)] += a * ( e - mid );

    a = 0LL;
}

void build(int t,int s,int e){
    Lazy[t] = 0LL;
    if ( s == e ){
        scanf("%lld",ST+t);
        return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);

    _pushUp(t);
}

void modify(int t,int s,int e,int a,int b,llt d){
    if ( a <= s && e <= b ){
        ST[t] += d * ( e - s + 1 );
        Lazy[t] += d;
        return;
    }

    _pushDown(t,s,e);
    int m = ( s + e ) >> 1;
    if ( a <= m ) modify(lson(t),s,m,a,b,d);
    if ( m < b ) modify(rson(t),m+1,e,a,b,d);
    _pushUp(t);
}

llt query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        return ST[t];
    }

    _pushDown(t,s,e);
    int m = ( s + e ) >> 1;

    llt ret = 0LL;
    if ( a <= m ) ret += query(lson(t),s,m,a,b);
    if ( m < b ) ret += query(rson(t),m+1,e,a,b);
    return ret;
}

int N,Q;
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&Q);
    build(1,1,N);

    char cmd[3];
    int a,b,c;
    while(Q--){
        scanf("%s%d%d",cmd,&a,&b);
        if ( 'Q' == *cmd ){
            printf("%lld\n",query(1,1,N,a,b));
        }else{
            scanf("%d",&c);
            modify(1,1,N,a,b,c);
        }
    }
    return 0;
}
