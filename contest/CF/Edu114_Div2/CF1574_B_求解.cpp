/**
  a个字母A，b个字母B，c个字母C，要求构造成一个字符串，
  该字符串中恰好有m对相邻字母保持一致，问能否构造
  一个简单的判断，m超过N，则肯定不能构造，当然N并非可构造的确界
  将a、b、c连续排列，可以得到最大的可行的m
  设c是最大的，将a、c和b、c轮流安排，可以得到最小的可行m
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
int const SIZE = 100100;
#endif

int A, B, C, M, N;

void sort(){
	int mmax = max(A, max(B, C));
	int mmin = min(A, min(B, C));
	int mmid = N - mmax - mmin;
	A = mmin, B = mmid, C = mmax;
}

bool proc(){
    N = A + B + C;
	if(M > N - 3) return false;

	sort();
	int t = C - A - B - 1;
	if(M < t) return false;

	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        A = getUnsigned();
		B = getUnsigned();
		C = getUnsigned();
		M = getUnsigned();
		puts(proc() ? "YES" : "NO");
    }
    return 0;
}
