/**
  给定数组A和B，长度在2E5，再给定2E5个询问，每次询问：x, y
  即问集合A[1...x]是否等于集合B[1...y]
  有4s时间，因此用了一个类似于莫队算法的分块做法。
  将所有询问排序，然后来回移动即可。
  标程有O(QlogN)以及O(N+Q)的做法
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
int const SIZE = 2e5+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>;
 
Real const EPS = 1E-12;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}

int N, A[SIZE], B[SIZE];
int C[SIZE+SIZE];

int Q;
struct _t{
	int x, y;
	int idx;
}T[SIZE];

int FA = 0, FB = 0;
int PosA[SIZE] = {0};
int PosB[SIZE] = {0};
int Ans[SIZE];

void insertA(int n){
	if(1 == ++PosA[n]){
		if(0 == PosB[n]) ++FA;
		else --FB;
	}
}

void insertB(int n){
    if(1 == ++PosB[n]){
		if(0 == PosA[n]) ++FB;
		else --FA;
	}
}

void removeA(int n){
	if(0 == --PosA[n]){
		if(0 == PosB[n]) --FA;
		else ++FB;
	}
}

void removeB(int n){
	if(0 == --PosB[n]){
		if(0 == PosA[n]) --FB;
		else ++FA;
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
	for(int i=1;i<=N;++i)C[i-1] = A[i] = getInt();
	for(int i=1;i<=N;++i)C[i-1+N] = B[i] = getInt();
    sort(C, C+N+N);
	int n = unique(C, C+N+N) - C;
	for(int i=1;i<=N;++i) A[i] = lower_bound(C, C+n, A[i]) - C;
	for(int i=1;i<=N;++i) B[i] = lower_bound(C, C+n, B[i]) - C;

	Q = getInt();
    for(int q=1;q<=Q;++q){
		T[q].x = getInt();
		T[q].y = getInt();
		T[q].idx = q;
	}
    sort(T+1, T+Q+1, [](const _t&a, const _t&b){
		static int const sz = 500;
		int as = a.x / sz, bs = b.x / sz;
		if(as != bs) return as < bs;
		if(a.y != b.y) return a.y < b.y;
		return a.idx < b.idx;
	});

    int curLeft = 0, curRight = 0;
	for(int i=1;i<=Q;++i){
        while(curRight < T[i].x) insertA(A[++curRight]); 
		while(curLeft < T[i].y) insertB(B[++curLeft]);
		while(curRight > T[i].x) removeA(A[curRight--]);
		while(curLeft > T[i].y) removeB(B[curLeft--]);
        Ans[T[i].idx] = (0 == FA && 0 == FB) ? 1 : 0;
	}
	for(int i=1;i<=Q;++i)puts(Ans[i]?"Yes":"No");
    return 0;
}
