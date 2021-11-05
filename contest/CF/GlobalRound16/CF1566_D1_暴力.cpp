/**
 * 1×M个座位，编号从左到右依次为1~M
 * M个人，每个人有ai的属性
 * 要求从第1个人到第M个人依次去坐座位，满足大ai就要坐大编号的座位
 * 求每个人去坐座位的过程中跨过的人数之和
 * 例如如果A是：1，2
 * 则第1个人就要坐第1个座位，第2个人去座位的时候就要跨过1个人，因此答案是1
 * 而如果A是：2，1
 * 则第1个人就要坐第2个座位，第2个人坐第1个，不会跨过任何人，答案是0
 * 对每一个ai，实际上就是看之前比它小的数有多少个，M只有300
 * 暴力即可
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

int N, M;
int A[SIZE];
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

llt proc(){
	llt ans = 0;
	for(int i=1;i<=M;++i){
        ans += f(A[i]);
		insert(A[i]);
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
		Vec.clear();
		N = getUnsigned();
		M = getUnsigned();
		for(int i=1;i<=M;++i) A[i] = getUnsigned();
		printf("%lld\n", proc());
	}
	return 0;
}