/**
 * 2×n的01矩阵，划分成若干个2×t的子矩阵（t为正数）
 * 问怎么划分，使得这些子矩阵的mex和最大
 * 如果上下两行是01或者10，显然可以贡献最大的mex2，因此可以单独划出来
 * 如果是连续的11，则毫无价值，划不划都一样
 * 如果11和00相邻，则需要划在一起。因为分开只有1，而合在一起有2
 * 因此，如果11和00相邻，就合在一起，其他情况都单独成列即可。
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
int const SIZE = 10;
#else 
int const SIZE = 100100;
#endif

char A[2][SIZE];
int N;

inline bool is01(int idx){
    return '0' == A[0][idx] && '1' == A[1][idx]
	    || ('0' == A[1][idx] && '1' == A[0][idx]);
}

inline bool is00(int idx){
	return '0' == A[0][idx] && '0' == A[1][idx];
}

inline bool is11(int idx){
	return '1' == A[0][idx] && '1' == A[1][idx];
}

int proc(){
    int ans = 0;
	int k = 0;
	while(1){
		if(is01(k)){
			ans += 2;
			++k;
		}else if(is00(k)){
			if(k+1<N&&is11(k+1)){
				ans += 2;
				k += 2;
			}else{
				++ans;
				++k;
			}
		}else if(is11(k)){
			while(k<N && is11(k)) ++k;
			if(k==N) break;
			if(is00(k)){
				ans += 2;
				++k;
			}else if(is01(k)){
				ans += 2;
				++k;
			}else{
				throw runtime_error("XX");
			}
		}else{
			throw runtime_error("YYY");
		}

        if(k==N) break;
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%d%s%s", &N, A[0], A[1]);
		printf("%d\n", proc());
	}
	return 0;
}