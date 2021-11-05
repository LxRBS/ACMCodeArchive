/**
   给定一个数组，每次操作允许将一个连续的子空间做一个循环移位操作。
   问能否在不超过N次操作下将数组变成有序。
   每次将一个数排到指定位置即可，最多只要N次。 
   第i次只要找到当前排名第i的数的位置，设为pi，则取出子区间[i, pi]做一个循环移位即可，将pi位置上的数移到i位置
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
int const SIZE = 110;
#endif

int N;
int A[SIZE];
vector<vector<int> > Buzhou;

int find(int a, int start){
	for(int i=start;i<=N;++i)if(a==A[i])return i;
	return 0;
}

void proc(){
    Buzhou.clear();
	vector<int> vec(A+1, A+N+1);
	sort(vec.begin(), vec.end());

	for(int i=1;i<=N;++i){
        int pos = find(vec[i-1], i);
		if(pos>i){
			Buzhou.push_back({i, pos, pos-i});
			rotate(A+i, A+pos, A+pos+1);
		}else if(pos==i){

		}else if(0==pos){
			throw runtime_error("XXX");
		}	
	}

	printf("%d\n", Buzhou.size());
	if(!Buzhou.empty())for(auto const &v: Buzhou){
		printf("%d %d %d\n", v[0], v[1], v[2]);
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
		for(int i=1;i<=N;++i){
			A[i] = getInt();
		}
		proc();
    }
    return 0;
}