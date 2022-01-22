/**
 * 三种操作：1 倍乘；2 增加；3 求和
 * 使用矩阵延迟的思想可以实现多种延迟操作
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

#ifndef ONLINE_JUDGE
int const SIZE = 10<<2;
#else
int const SIZE = 100100<<2;
#endif

typedef long long llt;
llt MOD;

inline llt add(llt a, llt b){return (a+b)%MOD;}
inline void mul(llt &a, llt b){(a*=b)%=MOD;}
inline void mulAdd(llt&v, llt k, llt b){(((v*=k)%=MOD)+=b)%=MOD;}

int N;

llt St[SIZE];
llt Lazy[SIZE][2]; // 倍乘，增加

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

inline void _pushUp(int t){
    St[t] = add(St[lson(t)], St[rson(t)]);
}

inline void _pushDown(int t, int s, int e){
    llt &k = Lazy[t][0];
    llt &b = Lazy[t][1];

    int mid = (s + e) >> 1;
    int son = lson(t);
    mulAdd(St[son], k, b*(mid-s+1)%MOD);
    mul(Lazy[son][0], k);
    mulAdd(Lazy[son][1], k, b);

    son = rson(t);
    mulAdd(St[son], k, b *(e-mid)%MOD);
    mul(Lazy[son][0], k);
    mulAdd(Lazy[son][1], k, b);

    k = 1;
    b = 0;
}

void modifyM(int t, int s, int e, int a, int b, llt multiple){
    if(a<=s&&e<=b){
        mul(St[t], multiple);
        mul(Lazy[t][0], multiple);
        mul(Lazy[t][1], multiple);
        return;
    }

    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    if(a<=mid) modifyM(lson(t), s, mid, a, b, multiple);
    if(mid<b) modifyM(rson(t), mid+1, e, a, b, multiple);
    _pushUp(t);
}

void modifyD(int t, int s, int e, int a, int b, llt delta){
    if(a<=s&&e<=b){
        (St[t] += (e-s+1)*delta % MOD) %= MOD;
        (Lazy[t][1] += delta) %= MOD;
        return;
    }

    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    if(a<=mid) modifyD(lson(t), s, mid, a, b, delta);
    if(mid<b) modifyD(rson(t), mid+1, e, a, b, delta);
    _pushUp(t);
}

llt query(int t, int s, int e, int a, int b){
    if(a<=s&&e<=b){
        return St[t];
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    llt ans = 0;
    if(a<=mid) (ans += query(lson(t), s, mid, a, b)) %= MOD;
    if(mid<b) (ans += query(rson(t), mid+1, e, a, b)) %= MOD;
    return ans;
}

void build(int t, int s, int e){
    Lazy[t][Lazy[t][1] = 0] = 1;
    if(s==e){
        St[t] = getUnsigned();
        return;
    }

    int mid = (s + e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    N = getUnsigned();
    MOD = getUnsigned();
    build(1, 1, N);
    int M = getUnsigned();
    for(int cmd,a,b,q=1;q<=M;++q){
        cmd = getUnsigned();
        a = getUnsigned();
        b = getUnsigned();

        switch(cmd){
            case 1:{
                modifyM(1, 1, N, a, b, getUnsigned());
            }break;
            case 2:{
                modifyD(1, 1, N, a, b, getUnsigned());  
            }break;
            case 3:{   
                printf("%lld\n", query(1, 1, N, a, b));
            }break;
            default: throw runtime_error("XXX");
        }
    }
    return 0;
}

