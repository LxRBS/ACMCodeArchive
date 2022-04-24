/// 区间增加，区间求和
#include <bits/stdc++.h>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef long long int value_t;

int const SIZE_OF_SEGMENT_TREE = 100010;//TODO

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

value_t ST[SIZE_OF_SEGMENT_TREE<<2];
value_t Lazy[SIZE_OF_SEGMENT_TREE<<2];

inline void _pushUp(int t){
    ST[t] = ST[lson(t)] + ST[rson(t)];
}

inline void _pushDown(int s,int e,int t){
    if ( 0 == Lazy[t] ) return;

    value_t& lazy = Lazy[t];

    int m = (s+e) >> 1;

    int son = lson(t);
    ST[son] += (m-s+1)*lazy ;
    Lazy[son] += lazy;

    son = rson(t);
    ST[son] += (e-m)*lazy ;
    Lazy[son] += lazy;

    lazy = 0;
}

void build(int t,int s,int e){
    Lazy[t] = 0;

    if ( s == e ){
        ST[t] = getInt();
        return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t);
}

void modify(int t,int s,int e,int a,int b,value_t delta){
    if ( a <= s && e <= b ){
        ST[t] += (e-s+1)*delta;
        Lazy[t] += delta;
        return;
    }

    _pushDown(s,e,t);
    int m = ( s + e ) >> 1;
    if ( a <= m ) modify(lson(t),s,m,a,b,delta);
    if ( m < b ) modify(rson(t),m+1,e,a,b,delta);
    _pushUp(t);
}

value_t query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        return ST[t];
    }

    _pushDown(s,e,t);
    int m = ( s + e ) >> 1;
    value_t ret = 0LL;
    if ( a <= m ) ret += query(lson(t),s,m,a,b);
    if ( m < b ) ret += query(rson(t),m+1,e,a,b);
    return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int m = getInt();
    build(1,1,n);

    while(m--){
        int cmd = getInt();
        int x = getInt();
        int y = getInt();
        if(1==cmd){
            modify(1,1,n,x,y,getInt());
        }else{
            printf("%lld\n",query(1,1,n,x,y));
        }
    }
    return 0;
}