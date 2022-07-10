/**
 * 两种操作，区间开根，区间求和
 * 考虑到开根少许次数，数值就会变为1，此时就再也不用开根。
 * 因此对开根操作，使用类似单点操作，一直往下修改。除非整个区间均为1
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
int const SIZE = 13;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long int;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

llt St[SIZE<<2];
llt Peak[SIZE<<2];

inline void _pushUp(int t){
    St[t] = St[lson(t)] + St[rson(t)];
	Peak[t] = max(Peak[lson(t)], Peak[rson(t)]);
}

/// 对[a, b]区间开根号
void modify(int t, int s, int e, int a, int b){
	if(1 == Peak[t]) return;
    
	if(s == e){
		Peak[t] = St[t] = sqrt(Peak[t]);
		return;
	}
	int mid = (s + e) >> 1;
	if(a <= mid) modify(lson(t), s, mid, a, b);
	if(mid < b) modify(rson(t), mid+1, e, a, b);
	_pushUp(t);
}

llt query(int t, int s, int e, int a, int b){
	if(a <= s && e <= b){
		return St[t];
	}

	int mid = (s + e) >> 1;
	llt ans = 0;
	if(a <= mid) ans += query(lson(t), s, mid, a, b);
	if(mid < b) ans += query(rson(t), mid+1, e, a, b);
	return ans;
}

void build(int t, int s, int e){
    if(s == e){
		Peak[t] = St[t] = getInt();
		return;
	}
	int mid = (s + e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid+1, e);
	_pushUp(t);
}

int N, M;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
	build(1, 1, N);
	for(int op,a,b,q=1;q<=M;++q){
        if(1 == (op=getInt())){
            a = getInt(); b = getInt();
			modify(1, 1, N, a, b);
		}else{
            a = getInt(); b = getInt();
			printf("%lld\n", query(1, 1, N, a, b));
		}
	}   
    return 0;
}