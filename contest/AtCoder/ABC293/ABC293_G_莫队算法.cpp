/**
 * 莫队算法模板题。问区间内有多少个三元组(i,j,k)满足 i < j < k 且 Ai == Aj == Ak
 * 记录一个全局答案，每次添加的元素值记作x,其加之前的数量记作c，则此次操作添加的三元组数量就是 C(c, 2)
 * 对于删除操作，令删除之后的数量是c，则此次减少的数量也是 C(C, 2)
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

char getChar(){
	char ch = __hv007();
	while(ch != 'R' and ch != 'B') ch = __hv007();
	return ch;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;

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

int N, Q;
vi A;
vector<_t> B;
vector<llt> Ans;
llt Global = 0;
vi Cnt;

inline void insert(int c){
    Global += (Cnt[c] - 1LL) * Cnt[c] / 2LL;
	++Cnt[c];
}

inline void remove(int c){    
	--Cnt[c];
	Global -= (Cnt[c] - 1LL) * Cnt[c] / 2LL;
}

void proc(){
    Ans.assign(Q, 0LL);
	Cnt.assign(200000 + 1, 0);

	int curLeft = 1;
	int curRight = 0;
	for(int i=0;i<Q;++i){
		while(curRight < B[i].e) insert(A[++curRight]);
        while(curLeft > B[i].s) insert(A[--curLeft]);
        while(curRight > B[i].e) remove(A[curRight--]);
        while(curLeft < B[i].s) remove(A[curLeft++]);	
		Ans[B[i].idx] = Global;			
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
	N = getInt();
    A.assign(N + 1, 0);
	Q = getInt();
	for(int i=1;i<=N;++i) A[i] = getInt();
    B.assign(Q, {});
	for(int i=0;i<Q;++i)B[i].s = getInt(), B[i].e = getInt(), B[i].idx = i;
	sort(B.begin(), B.end());
	proc();
	for(auto i : Ans) printf("%lld\n", i);
	// printf("\n");
    return 0; 
}


