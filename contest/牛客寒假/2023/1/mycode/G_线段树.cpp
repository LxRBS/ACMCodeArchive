/**
 * 一个数组，M个操作，每次操作：
 * 1 s e k, 对[s, e]范围内的Ai操作k次，每次令Ai = round(10 * sqrt(Ai))
 * 2, 求数组总和
 * 很显然，对每个Ai只要少数操作之后，后续操作就不起作用了。
 * 但是要注意Ai的不动点有3个：0, 99, 100。
 * 经典的线段树。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 100010;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;
using mvi = map<int, vi>;

struct _t{
    llt data;
    int flag;
}St[SIZE<<2];


int N, M;

inline int lson(int x) {return x << 1;}
inline int rson(int x) {return lson(x) | 1;}

inline void _pushUp(int t){
    auto & p = St[t];
    const auto & son1 = St[lson(t)];
    const auto & son2 = St[rson(t)];
    p.data = son1.data + son2.data;
    p.flag = son1.flag + son2.flag;
}


void build(int t, int s, int e){
    if(s == e){
        St[t].data = getInt();
        St[t].flag = 1;
        return;
    }
    int mid = (s + e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t);
}

void modify(int t, int s, int e, int a, int b, int k){
    if(s == e){
        auto & v = St[t].data;
        if(0 == v) {
            St[t].flag = 0;
            return;
        }
        for(int i=0;i<k;++i){
            v = (llt)(10.0 * sqrt(v) + 0.5);
            if(100 == v || 99 == v) {
                St[t].flag = 0;
                break;
            }
        }
        return;
    }
    if(a <= s && e <= b && St[t].flag == 0){
        return;
    }

    int mid = (s + e) >> 1;
    if(a <= mid) modify(lson(t), s, mid, a, b, k);
    if(mid < b) modify(rson(t), mid+1, e, a, b, k);
    _pushUp(t);
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    M = getInt();
    build(1, 1, N);

    for(int cmd,q=1;q<=M;++q){
        cmd = getInt();
        if(2 == cmd){
            printf("%lld\n", St[1].data);
        }else{
            int a = getInt();
            int b = getInt();
            int k = getInt();
            modify(1, 1, N, a, b, k);
        }
    }
    return 0;
}


