/**
 * 给定一个01串，将其划分成若干子串，
 * 使得这些子串的mex和最小
 * 显然1直接扔掉，而每一段0贡献1
 * 整串的mex是2。所以看0的段数有多少，超过1段答案就是2
 * 否则就是0的段数。
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

char A[SIZE];
int proc(){
    int cnt = 0;
	int k = 0;
	int n = strlen(A);

	while(1){
		while(k<n && '1'==A[k]) ++k;
		if(k==n) break;

        if(++cnt > 1) break;
		while(k<n && '0'==A[k]) ++k;
	}

	return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%s", A);
		printf("%d\n", proc());
	}
	return 0;
}