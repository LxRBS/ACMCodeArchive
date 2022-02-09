/**
 * 有蓝色彗星与红色彗星，每个彗星持续时间为T，一共N个。N、T都在1E5
 * 给定每个彗星的开始时刻，问一共有多少时间可以看到蓝色且看不到红色
 * 线段树求和
 * 先把蓝色彗星的时间段都刷1，再把红色时间段刷0
 * 最后返回整个的和即可
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
int const SIZE = 11;
#else
int const SIZE = 200110;
#endif

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int St[SIZE<<2] = {0};
int Lazy[SIZE<<2] = {0};

inline void _pushUp(int t){St[t]=St[lson(t)]+St[rson(t)];}

inline void _pushDown(int t, int s, int e){
	int& lazy = Lazy[t];
	if(0 == lazy) return;
    
	int mid = (s+e) >> 1;
	if(1 == lazy){
	    int son = lson(t);
		St[son] = mid - s + 1;
		Lazy[son] = 1;

		son = rson(t);
		St[son] = e - mid;
		Lazy[son] = 1;
	}else if(-1 == lazy){
        St[lson(t)] = St[rson(t)] = 0;
		Lazy[lson(t)] = Lazy[rson(t)] = -1;
	}else{
		throw runtime_error("XX");
	}

	lazy = 0; 
}

void modify(int t, int s, int e, int a, int b, int newValue){
	if(a<=s&&e<=b){
		St[t] = (e-s+1) * newValue;
		Lazy[t] = newValue ? 1 : -1;
		return;
	}
	
	_pushDown(t, s, e);
	int mid = (s+e) >> 1;
	if(a<=mid) modify(lson(t),s,mid,a,b,newValue);
	if(mid<b) modify(rson(t),mid+1,e,a,b,newValue);
	_pushUp(t);
}

int query(int t, int s, int e, int a, int b){
	if(a<=s&&e<=b){
		return St[t];
	}

	_pushDown(t, s, e);
	int mid = (s+e) >> 1;
	int ans = 0;
	if(a<=mid) ans += query(lson(t),s,mid,a,b);
	if(mid<b) ans += query(rson(t),mid+1,e,a,b);
	return ans;
}

int N, T;
int A[SIZE];
char B[SIZE];
int Total;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d%d%s", &N, &T, B);
	for(int i=0;i<N;++i)scanf("%d", A+i);
    
	--T;
	Total = *max_element(A, A+N);
	Total += T;
	for(int i=0;i<N;++i){
        if('B' == B[i]){
			modify(1, 1, Total, A[i], A[i]+T, 1);
		}
	}
	for(int i=0;i<N;++i){
		if('R' == B[i]){
			modify(1, 1, Total, A[i], A[i]+T, 0);
		}
	}
	printf("%d\n", query(1, 1, Total, 1, Total));
    return 0;
}
