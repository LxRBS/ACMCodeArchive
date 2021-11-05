/**
   给定一个点的矩阵，上面用*画出若干个"V"字，位置和长度各有不同。
   问给定的矩阵是否是由这样的规则构造出来的
   矩阵大小只有10×20，直接暴力测试
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t unordered_map

typedef long long int llt;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vp;

double const EPS = 1E-8;
inline int sgn(double x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(double x){return 0==sgn(x);}
inline bool isEq(double x,double y){return is0(x-y);}
inline double myasin(double x){if(x>1)x=1.;else if(x<-1)x=-1.;return asin(x);}
inline double myacos(double x){if(x>1)x=1.;else if(x<-1)x=-1.;return acos(x);}

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

llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

bool getUnsigned(llt&ret){
    char ch;
    do{
        if(EOF==(ch=__hv007())) return false;
    }while( ch < '0' || ch > '9' );

	ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return true;
}

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 22;
#endif

int N, M, K;
char A[SIZE][SIZE];
int B[SIZE][SIZE];

bool test(int r, int c, int k){
	if(r-k < 0 || c-k < 0 || c+k >=M) return false;
	for(int i=1;i<=k;++i){
		--r;
		if('*'!=A[r][c-i] || '*'!=A[r][c+i]) return false;
	}
	return true;
}

void test(int r, int c){
    if(!test(r, c, K)) return;

    int c1 = c, c2 = c;
	while(1){
        B[r][c1] = B[r][c2] = 1;
		--r; --c1; ++c2;
		if(r<0 || c1 <0 || c2>=M) break;
		if('*'!=A[r][c1] || '*'!=A[r][c2]) break;
	}
}

bool proc(){
	for(int i=N-1;i>=0;--i)for(int j=0;j<M;++j){
        if('*'==A[i][j]){
			test(i, j);
			if(!B[i][j]) return false;
		}
	}
	for(int i=0;i<N;++i)for(int j=0;j<M;++j){
		if('*' == A[i][j] && 0 == B[i][j]) return false;
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%d", &N, &M, &K);
		for(int i=0;i<N;++i){scanf("%s", A[i]);fill(B[i],B[i]+M,0);}
		puts(proc() ? "YES" : "NO");
    }
    return 0;
}