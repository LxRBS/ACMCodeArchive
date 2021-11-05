/**
 * 对每一排的每一个ai，要求出之前比它小的数有多少个
 * 离散化以后用树状数组
 * 但M其实只有300，所以不如直接暴力法快
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

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

bool getUnsigned(int&ret){
    char ch;
    do{
        if(EOF==(ch=__hv007())) return false;
    }while( ch < '0' || ch > '9' );

	ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return true;
}

typedef long long llt;

llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t unordered_map

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vp;

double const EPS = 1E-8;
inline int sgn(double x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(double x){return 0==sgn(x);}
inline bool isEq(double x,double y){return is0(x-y);}
inline double myasin(double x){if(x>1)x=1.;else if(x<-1)x=-1.;return asin(x);}
inline double myacos(double x){if(x>1)x=1.;else if(x<-1)x=-1.;return acos(x);}

#ifndef ONLINE_JUDGE
int const SIZE = 20;
#else 
int const SIZE = 100100;
#endif

int C[SIZE] = {0};

int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

int BTN;
void modify(int idx,int v){
	while( idx <= BTN ){
	    C[idx] += v;
		idx += lowbit(idx);
	}
}

int query(int x){
    int s = 0;
	while( x > 0 ){
	    s += C[x];
		x -= lowbit(x);
	}
    return s;
}

inline int query(int s,int e){
	return query(e) - query(s-1);
}

int N, M, Total;
struct _t{
    int a;
    int idx;
    bool operator < (const _t&rhs)const{
        if(a != rhs.a) return a < rhs.a;
        return idx < rhs.idx;
    }
}A[SIZE];

bool cmp(const _t&a, const _t&b){
    return a.idx < b.idx;
}

vi Vec;

int f(int a){
    auto it = lower_bound(Vec.begin(), Vec.end(), a);
	return it - Vec.begin();
}

void insert(int a){
	auto it = Vec.begin();
	while(it != Vec.end() && *it < a) ++it;
	Vec.insert(it, a);
}

llt proc(int row){
    sort(A+(row-1)*M+1, A+row*M+1, cmp);
    fill(C, C+BTN+1, 0);
    
    llt ans = 0;
    Vec.clear();
    for(int i=(row-1)*M+1,n=row*M;i<=n;++i){
        ans += query(A[i].a-1);
        modify(A[i].a, 1);
    }
    return ans;
}

llt proc(){
    sort(A+1, A+Total+1);

    llt ans = 0;
    for(int i=1;i<=N;++i){
        ans += proc(i);
    }
    return ans;
}

int B[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
		Vec.clear();
		N = getUnsigned();
		M = getUnsigned();
        Total = N * M;
		for(int i=1;i<=Total;++i) B[i] = A[A[i].idx=i].a = getUnsigned();
        sort(B+1, B+Total+1);
        BTN = unique(B+1, B+Total+1) - B;
        for(int i=1;i<=Total;++i){
            A[i].a = lower_bound(B+1, B+BTN, A[i].a) - B;
        }
        sort(A+1, A+Total+1);
		printf("%lld\n", proc());
	}
	return 0;
}