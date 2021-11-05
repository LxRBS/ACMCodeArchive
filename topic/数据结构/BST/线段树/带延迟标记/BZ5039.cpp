/*
    3种操作：
    区间乘
    区间加
    区间求和
    先打乘法标记，而且无延迟时乘法标记应该为1
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long llt;

int const SIZE = 100010;
llt MOD;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

llt ST[SIZE<<2];
llt MLazy[SIZE<<2];//乘法的延迟
llt DLazy[SIZE<<2];//加法的延迟

void _pushUp(int t){ST[t]=(ST[lson(t)]+ST[rson(t)])%MOD;}

void _pushDown(int t,int s,int e){
    //先打乘法标记
    if ( MLazy[t] != 1LL ){
        llt&lazy = MLazy[t];
        lazy %= MOD;

        int son = lson(t);
        ST[son] = lazy * ST[son] % MOD;
        MLazy[son] = lazy * MLazy[son] % MOD;
        DLazy[son] = lazy * DLazy[son] % MOD;

        son = rson(t);
        ST[son] = lazy * ST[son] % MOD;
        MLazy[son] = lazy * MLazy[son] % MOD;
        DLazy[son] = lazy * DLazy[son] % MOD;

        lazy = 1LL;
    }

    if ( DLazy[t] ){
        llt &lazy = DLazy[t];
        lazy %= MOD;

        int son = lson(t);
        int mid = ( s + e ) >> 1;
        ST[son] = ( ST[son] + ( mid - s + 1 ) * lazy % MOD ) % MOD;
        DLazy[son] = ( DLazy[son] + lazy ) % MOD;

        son = rson(t);
        ST[son] = ( ST[son] + ( e - mid ) * lazy % MOD ) % MOD;
        DLazy[son] = ( DLazy[son] + lazy ) % MOD;

        lazy = 0LL;
    }
}

void modifyMulti(int t,int s,int e,int a,int b,llt mul){
    if ( a <= s && e <= b ){
        ST[t] = ( ST[t] * mul ) % MOD;
        MLazy[t] = ( MLazy[t] * mul ) % MOD;
        DLazy[t] = ( DLazy[t] * mul ) % MOD;
        return;
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modifyMulti(lson(t),s,mid,a,b,mul);
    if ( mid < b ) modifyMulti(rson(t),mid+1,e,a,b,mul);
    _pushUp(t);
}

void modifyDelta(int t,int s,int e,int a,int b,llt delta){
    if ( a <= s && e <= b ){
        ST[t] = ( ST[t] + ( e - s + 1 ) * delta % MOD ) % MOD;
        DLazy[t] = ( DLazy[t] + delta ) % MOD;
        return;
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modifyDelta(lson(t),s,mid,a,b,delta);
    if ( mid < b ) modifyDelta(rson(t),mid+1,e,a,b,delta);
    _pushUp(t);
}

llt query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ) return ST[t];

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    llt ans = 0LL;
    if ( a <= mid ) ans = ( ans + query(lson(t),s,mid,a,b) ) % MOD;
    if ( mid < b ) ans = ( ans + query(rson(t),mid+1,e,a,b) ) % MOD;
    return ans;
}

void build(int t,int s,int e){
    MLazy[t] = 1LL;
    DLazy[t] = 0LL;
    if ( s == e ){
        ST[t] = getUnsigned()%MOD;
        return;
    }

    int mid = ( s + e ) >> 1;
    build(lson(t),s,mid);
    build(rson(t),mid+1,e);
    _pushUp(t);
}

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    MOD = getUnsigned();
    build(1,1,n);

    int m = getUnsigned();
    int cmd,a,b,d;
    while(m--){
        cmd = getUnsigned();
        a = getUnsigned();
        b = getUnsigned();
        if ( 1 == cmd ){
            modifyMulti(1,1,n,a,b,getUnsigned()%MOD);
        }else if ( 2 == cmd ){
            modifyDelta(1,1,n,a,b,getUnsigned()%MOD);
        }else{
            printf("%lld\n",query(1,1,n,a,b));
        }
    }
    return 0;
}
