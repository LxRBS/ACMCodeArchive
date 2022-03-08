/**
 * 给定一个数组A，每次询问问：[L, R]之间能组成多少对？
 * 成对的条件就是两个位置的元素值相等即可
 * N在1E5，莫队算法模板题，记录全局Cnt数组
 * 当某个Cnt[c]加成了偶数，即多了一对
 * 减成了奇数，即少了一对。
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
int const SIZE = 33;
#else
int const SIZE = 100001;
#endif

int const BLOCK_SIZE = 300;

struct _t{
	int s, e;
	int idx;
};

bool operator < (const _t&a, const _t&b){
	int ln = a.s / BLOCK_SIZE;
	int rn = b.s / BLOCK_SIZE;
	if(ln != rn) return ln < rn;
	if(a.e != b.e) return a.e < b.e;
	return a.idx < b.idx;
}

int A[SIZE];
_t B[SIZE*10];
int Ans[SIZE*10];
int Cnt[SIZE] = {0};
int N, Q;
int Global = 0;

inline void insert(int c){
	if(!(++Cnt[c] & 1)){
		++Global;
	}
}

inline void remove(int c){
	if(--Cnt[c] & 1) {
		--Global;
	}
}

void proc(){
	sort(B, B+Q);

	int curLeft = 1;
	int curRight = 0;
	for(int i=0;i<Q;++i){
		while(curRight < B[i].e) insert(A[++curRight]);
        while( curLeft > B[i].s ) insert(A[--curLeft]);
        while( curRight > B[i].e ) remove(A[curRight--]);
        while( curLeft < B[i].s ) remove(A[curLeft++]);	
		Ans[B[i].idx] = Global;	
	}
	
	for(int i=0;i<Q;++i){
		printf("%d\n", Ans[i]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int i=1;i<=N;++i) A[i] = getInt();
	Q = getInt();
	for(int i=0;i<Q;++i){
		B[B[i].idx = i].s = getInt();
		B[i].e = getInt();
	}	
	proc();
    return 0;
}