/**
  给定一个数组A，再给定一个W，问从1到W中，
  有多少个数可以表示为最多三个不同的Ai之和。
  A只有300，直接暴力即可。
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

struct Point{
	llt x, y;
};


int N;
int W;
llt A[SIZE];
bool F[1000100] = {0};

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); W = getInt();
	for(int i=0;i<N;++i) A[i] = getInt();
	sort(A, A+N);
	int n = N;
	// int n = unique(A, A+N) - A;

	int ans = 0;
	for(int i=0;i<n;++i){
		if(A[i] <= W && !F[A[i]]){
			++ans;
			F[A[i]] = true;
		}
		for(int j=i+1;j<n;++j){
			llt tmp = A[i] + A[j];
			if(tmp > W) continue;
			if(!F[tmp]){
				F[tmp] = true;
				++ans;				
			}
			for(int k=j+1;k<n;++k){
				llt tmp = A[i] + A[j] + A[k];
				if(tmp > W) continue;
				if(!F[tmp]){
					F[tmp] = true;
					++ans;
				} 
			}
		}
	}
	cout<<ans<<endl;
    return 0;
}
