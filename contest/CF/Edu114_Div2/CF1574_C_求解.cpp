/**
  给N个数，A1到AN。再给两个数X和Y。
  要求从N个数中选取一个，命名为Ai，使得Ai>=X，且剩下的数之和>=Y。
  如果不能满足的话，允许给这N个数增加数值，问：
  问了满足条件，最少加多少
  首先找最接近X的Ai，如果Ai==X，则看剩下的数之和与Y的关系即可
  否则，只有两种可能，一种是用最接近X的但是比X小的Ai，一种是用最接近X的但是比X大的Ai
  都计算一遍即可
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
int const SIZE = 22;
#else
int const SIZE = 200100;
#endif

int N, M;
llt A[SIZE], S;
llt X, Y;

llt proc(){
    int t = lower_bound(A+1, A+N+1, X) - A;
    if(t > N){
		llt ans = X - A[N];
		if(S - A[N] >= Y) return ans;
		return ans + Y + A[N] - S;
	}
	if(A[t] == X){
		if(S-A[t] >= Y) return 0LL;
		return Y + A[t] - S;
	}
	if(1 == t){
		llt ans = 0LL;
		if(S - A[1] >= Y) return ans;
		return ans + Y + A[1] - S;
	}
	
	llt ans1 = X - A[t-1];
	if(S-A[t-1] >= Y) ;
	else ans1 += Y - (S-A[t-1]);
	
	llt ans2 = 0LL;
	if(S-A[t] >= Y) ;
	else ans2 += Y - (S-A[t]);
	return min(ans1, ans2);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = 1;
    while(nofkase--){
		S = 0LL;
        N = getUnsigned();
		for(int i=1;i<=N;++i) S += A[i] = getULL();
		sort(A+1, A+N+1);

		M = getUnsigned();
		for(int i=1;i<=M;++i){
			X = getULL();
			Y = getULL();
			printf("%lld\n", proc());
		}
    }
    return 0;
}
