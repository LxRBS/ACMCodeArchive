/**
  给定N,A,B，要生成交替由.和#构成的矩形
  整个尺寸为(N*A)*(N*B)，小矩形的尺寸为A*B
  例如给定5 1 5，则答案为:
  .....#####.....#####.....
  #####.....#####.....#####
  .....#####.....#####.....
  #####.....#####.....#####
  .....#####.....#####.....  
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

int N, A, B;
char T[3] = "#.";

char Out[150][150];

void output(int r, int c, char ch){
    int x = r * A;
	int y = c * B;
	for(int i=x;i<x+A;++i)for(int j=y;j<y+B;++j){
		Out[i][j] = ch;
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    cin>>N>>A>>B;
	int t = 0;
    for(int i=0;i<N;++i){
		t ^= 1;
		int u = t;
		for(int j=0;j<N;++j){
            output(i, j, T[u]);
			u ^= 1;
		}
	}
	for(int i=0;i<N*A;++i) puts(Out[i]);
    return 0;
}
