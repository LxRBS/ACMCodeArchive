/// 两种延迟，倍乘和增加
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000+1];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
    int sgn = 1;
    char ch = __hv007();
    while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
    if ( '-' == ch ) {sgn = 0;ch=__hv007();}

    int ret = (int)(ch-'0');
    while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
    return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 7;
#else
int const SIZE = 1e5+7;
#endif

using llt = long long;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

llt St[SIZE<<2];
llt Lazy[SIZE<<2][2];

int N, M;
llt MOD;

inline void _pushUp(int t){
    St[t] = (St[lson(t)] + St[rson(t)]) % MOD;
}

inline void _pushDown(int t, int s, int e){
    llt &k = Lazy[t][0];
    llt &d = Lazy[t][1];
    if(1 == k && 0 == d) return;

    int mid = (s + e) >> 1;
    int son = lson(t);
    (((St[son] *= k) %= MOD) += (mid - s + 1) * d % MOD) %= MOD;
    (Lazy[son][0] *= k) %= MOD;
    (((Lazy[son][1] *= k) %= MOD) += d) %= MOD;
    

    son = rson(t);
    (((St[son] *= k) %= MOD) += (e - mid) * d % MOD) %= MOD;
    (Lazy[son][0] *= k) %= MOD;
    (((Lazy[son][1] *= k) %= MOD) += d) %= MOD;

    k = 1; d = 0;
    return;
}

void build(int t, int s, int e){
    Lazy[t][0] = 1;
    if(s == e){
        St[t] = getInt() % MOD;
        return;
    }
    int mid = (s + e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t);
}

llt query(int t, int s, int e, int a, int b){
    if(a<=s && e<=b){
        return St[t];
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    llt ans = 0;
    if(a <= mid) (ans += query(lson(t), s, mid, a, b)) %= MOD;
    if(mid < b) (ans += query(rson(t), mid+1, e, a, b)) %= MOD;
    return ans;
}

void modifyM(int t, int s, int e, int a, int b, llt k){
    if(a<=s && e<=b){
        (Lazy[t][0] *= k) %= MOD;
        (Lazy[t][1] *= k) %= MOD;
        (St[t] *= k) %= MOD;
        return;
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    if(a <= mid) modifyM(lson(t), s, mid, a, b, k);
    if(mid < b) modifyM(rson(t), mid+1, e, a, b, k);
    _pushUp(t);
    return;
}

void modifyD(int t, int s, int e, int a, int b, llt d){
    if(a<=s && e<=b){
        (Lazy[t][1] += d) %= MOD;
        (St[t] += (e - s + 1) * d % MOD) %= MOD;
        return;
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    if(a <= mid) modifyD(lson(t), s, mid, a, b, d);
    if(mid < b) modifyD(rson(t), mid+1, e, a, b, d);
    _pushUp(t);
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt(); MOD = getInt();
    build(1, 1, N);
    for(int op,x,y,q=1;q<=M;++q){
        op = getInt(); x = getInt(); y = getInt();
        switch(op){
            case 1:modifyM(1, 1, N, x, y, getInt()); break;
            case 2:modifyD(1, 1, N, x, y, getInt()); break;
            case 3:printf("%d\n", query(1, 1, N, x, y));break;
            default: throw runtime_error("XXXX");
        }
    }
    return 0;
}