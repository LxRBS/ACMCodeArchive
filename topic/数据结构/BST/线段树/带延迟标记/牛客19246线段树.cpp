/**
   四种操作
   成段增加，成段倍乘
   成段和，成段平方和
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long llt;
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

int const SIZE = 10100;
int N,M;

llt Sum[SIZE<<2];
llt S2[SIZE<<2];
llt Lazy[SIZE<<2][2];

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

inline void _pushUp(int t){
    Sum[t] = Sum[lson(t)] + Sum[rson(t)];
    S2[t] = S2[lson(t)] + S2[rson(t)];
}

/// 根据lazy计算准确值
inline void _f(const llt lazy[], int t, int s, int e){
    S2[t] = lazy[0] * lazy[0] * S2[t] + 2 * lazy[0] * lazy[1] * Sum[t] + (e-s+1) * lazy[1] * lazy[1];
    Sum[t] = lazy[0] * Sum[t] + (e-s+1) * lazy[1];
}

inline void _pushDown(int t, int s, int e){
    if(1==Lazy[t][0]&&0==Lazy[t][1]) return;

    int mid = (s + e) >> 1;

    int son = lson(t);
    _f(Lazy[t], son, s, mid);
    Lazy[son][0] *= Lazy[t][0];
    (Lazy[son][1] *= Lazy[t][0]) += Lazy[t][1];

    son = rson(t);
    _f(Lazy[t], son, mid+1, e);
    Lazy[son][0] *= Lazy[t][0];
    (Lazy[son][1] *= Lazy[t][0]) += Lazy[t][1];

    Lazy[t][Lazy[t][0] = 1] = 0;
}

void build(int t, int s, int e){
    Lazy[t][Lazy[t][0] = 1] = 0;
    if(s == e){
        Sum[t] = getInt();
        S2[t] = Sum[t] * Sum[t];
        return;
    }

    int mid = (s + e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t);
}

llt query(int t, int s, int e, int a, int b, int op){
    if(a<=s && e<=b){
        return 1==op ? Sum[t] : S2[t];
    }
    _pushDown(t, s , e);
    int mid = (s +  e) >> 1;
    llt ans = 0;
    if(a<=mid) ans += query(lson(t), s, mid, a, b, op);
    if(mid<b) ans += query(rson(t), mid+1, e, a, b, op);
    return ans;
}

void modify(int t, int s, int e, int a, int b, int op, llt delta){
    if(a<=s && e<=b){
        if(3==op){
            Sum[t] *= delta;
            S2[t] *= delta * delta;
            Lazy[t][0] *= delta;
            Lazy[t][1] *= delta;
        }else if(4==op){
            S2[t] += 2 * delta * Sum[t] + (e-s+1) * delta * delta;
            Sum[t] += (e-s+1) * delta;
            Lazy[t][1] += delta;
        }else{
            throw runtime_error("wrong op");
        }
        return;
    }

    _pushDown(t, s, e);
    int mid = (s +  e) >> 1;
    if(a<=mid) modify(lson(t), s, mid, a, b, op, delta);
    if(mid<b) modify(rson(t), mid+1, e, a, b, op, delta);
    _pushUp(t);
}

int main(){
    //freopen("1.txt","r",stdin);
    N = getInt();
    M = getInt();
    build(1, 1, N);
    for(int cmd,a,b,kase=1;kase<=M;++kase){
        cmd = getInt();
        a = getInt();
        b = getInt();
        switch(cmd){
        case 1:
        case 2:printf("%lld\n", query(1, 1, N, a, b, cmd));break;
        case 3:
        case 4:modify(1, 1, N, a, b, cmd, getInt());break;
        default:throw runtime_error("wrong cmd");
        }
    }
    return 0;
}
