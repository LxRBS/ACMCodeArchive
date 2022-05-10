/**
  给定一个数组A，给定若干个交换操作，问操作以后的数组A
  直接模拟即可
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
int const SIZE = 13;
#else
int const SIZE = 2e5+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>;
 
Real const EPS = 1E-12;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}

int N, Q;

int A[SIZE];
int Pos[SIZE];


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); Q = getInt();
	for(int i=1;i<=N;++i){
		Pos[A[i] = i] = i;
	}
	for(int p,q=1;q<=Q;++q){
        p = getInt();
		if(A[N] == p){
            Pos[p] = N - 1;
			Pos[A[N-1]] = N;
			swap(A[N], A[N-1]);
		}else{
            int t = Pos[p];
			Pos[A[t]] = t + 1;
			Pos[A[t+1]] = t;
			swap(A[t], A[t+1]);
		}
	}
	for(int i=1;i<=N;++i)printf("%d ", A[i]);puts("");
    return 0;
}
