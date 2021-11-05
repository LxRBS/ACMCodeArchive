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

int const SIZE = 1001000;
inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int N, M;
int St[SIZE<<2];
int Lazy[SIZE<<2];

inline void _pushUp(int t){
    St[t] = min(St[lson(t)], St[rson(t)]);
}

inline void _pushDown(int t){
    if(0==Lazy[t]) return;

    int &lazy = Lazy[t];
    St[lson(t)] += lazy;
    Lazy[lson(t)] += lazy;
    St[rson(t)] += lazy;
    Lazy[rson(t)] += lazy;
    lazy = 0;
}

void build(int t, int s, int e){
    if(s==e){
        St[t] = getUnsigned();
        return;
    }
    int mid = (s+e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t);
}

int query(int t, int s, int e, int a, int b){
    if(a<=s&&e<=b){
        return St[t];
    }
    _pushDown(t);
    int mid = (s+e) >> 1;
    int ans = INT_MAX;
    if(a<=mid) ans = min(ans, query(lson(t), s, mid, a, b));
    if(mid<b) ans = min(ans, query(rson(t), mid+1, e, a, b));
    return ans;
}

void modify(int t, int s, int e, int a, int b, int delta){
    if(a<=s&&e<=b){
        Lazy[t] += delta;
        St[t] += delta;
        return;
    }
    _pushDown(t);
    int mid = (s+e) >> 1;
    if(a<=mid) modify(lson(t), s, mid, a, b, delta);
    if(mid<b) modify(rson(t), mid+1, e, a, b, delta);
    _pushUp(t);
}

int D[SIZE], S[SIZE], T[SIZE];

void proc(){
    for(int i=1;i<=M;++i){
        modify(1, 1, N, S[i], T[i], -D[i]);
        if(query(1, 1, N, S[i], T[i])<0){
            printf("-1\n%d\n", i);
            return;
        }
    }
    printf("0\n");
}

int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    M = getUnsigned();
    build(1, 1, N);
    for(int i=1;i<=M;++i){
        D[i] = getUnsigned();
        S[i] = getUnsigned();
        T[i] = getUnsigned();
    }
    proc();
    return 0;
}
