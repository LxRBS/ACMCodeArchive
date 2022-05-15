/**
  有一个环，每条边有一个边权，要求选一些边将所有的点都覆盖，
  问最小边权和是多少
  设Di为选中第i条边的从开头到点i全覆盖的最小和，则
  Di = min(D[i-1], D[i-2]) + Ai
  由于是环，所以要用不同的起点计算，以边为单位进行计算
  因此要分别用三个起点计算，两个会wa
*/
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

using llt = long long;

llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 3E5+15;
#endif

using llt = long long;
using Real = long double;
using vi = vector<int>;
using pii = pair<int, int>;

llt N;
llt A[SIZE];

llt U[SIZE];

llt proc(){
    U[0] = A[0];
	U[1] = A[0] + A[1];
	for(int i=2;i<N;++i){
		U[i] = min(U[i-1], U[i-2]) + A[i];
	}    
	llt ans = U[N-2];

	A[N] = A[0];
	U[1] = A[1];
	U[2] = A[1] + A[2];
	for(int i=3;i<=N;++i){
		U[i] = min(U[i-1], U[i-2]) + A[i];
	}
	ans = min(ans, U[N-1]);

	A[N+1] = A[1];
	U[2] = A[2];
	U[3] = A[2] + A[3];
	for(int i=4;i<=N;++i){
		U[i] = min(U[i-1], U[i-2]) + A[i];
	}
	ans = min(ans, U[N]);

	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
	for(int i=0;i<N;++i) A[i] = getInt();
	cout<<proc()<<endl;
    return 0;
}
