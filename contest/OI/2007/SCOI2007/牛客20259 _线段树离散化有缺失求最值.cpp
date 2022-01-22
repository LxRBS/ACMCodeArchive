/**
 * 给定若干年份的降雨量，询问(X, Y)是否满足：
 * X的降雨量比Y不大，且中间年的降雨量都小于X
 * 首先离散化
 * 然后注意询问有可能是缺失的年份，需要考虑清楚每一种可能性
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
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
int const SIZE = 12<<2;
#else
int const SIZE = 500010<<2;
#endif

typedef unordered_map<int, int> Int2IntMapTy;
Int2IntMapTy Map;
int N, M;
int Year[SIZE];

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int St[SIZE];

inline void _pushUp(int t){
    St[t] = max(St[lson(t)], St[rson(t)]);
}

int query(int t,int s, int e, int a, int b){
    if(a<=s&&e<=b){
        return St[t];
    }

    int mid = (s + e) >> 1;
    int ans = 0;
    if(a<=mid) ans = max(query(lson(t), s, mid, a, b), ans);
    if(mid<b) ans = max(query(rson(t), mid+1, e, a, b), ans);
    return ans;
}

void build(int t, int s, int e){
    if(s==e){
        Map[Year[s] = getInt()] = s;
        St[t] = getInt();
        return;
    }

    int mid = (s + e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t);
}

char const Output[3][15] = {
    "false", "true", "maybe"
};

int proc(int a, int b){
    if(a >= b) return 0; // 显然false

    int ia = lower_bound(Year+1, Year+N+1, a) - Year;
    int ib = lower_bound(Year+1, Year+N+1, b) - Year;

    if(Year[ib] != b && Year[ia] != a){
        return 2; // 两个年份的降雨量都未知
    }
    
    if(Year[ia] != a){ // 起点年份未知
        if(ia == ib) return 2;
        int t1 = query(1, 1, N, ia, ib-1);
        int t2 = query(1, 1, N, ia, ib);
        return t2 <= t1 ? 0 : 2;
    }

    if(Year[ib] != b){ // 终点年份未知
        if(ib - 1 == ia) return 2;
        int t1 = query(1, 1, N, ia, ib-1);
        int t2 = query(1, 1, N, ia+1, ib-1);
        return t1 <= t2 ? 0 : 2; 
    }

    int ta = query(1, 1, N, ia, ia);
    int tb = query(1, 1, N, ib, ib);

    if(b - a == 1){ // 相邻的两个年份
        return tb <= ta ? 1 : 0;
    }

    if(tb > ta) return 0; // 终点超过了起点

    int tt = query(1, 1, N, ia+1, ib-1);
    if(tt >= tb) return 0;
    if(ib - ia != b - a) return 2;
    return 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    build(1, 1, N=getInt());
    M = getInt();
    for(int a,b,q=1;q<=M;++q){
        a = getInt();
        b = getInt();
        puts(Output[proc(a, b)]);
    }
    return 0;
}

