/**
 * 给定数组A，每次做如下操作，将Ai减2，A[i-1]和A[i+1]减1，如果有的话
 * 问要将A中的两个元素减为0，最少需要几次操作
 * 分情况讨论，令目标元素为a和b
 * 最简单的情况就是ab互不干扰，各减各的，此情况下只需选择A中的前二小的元素即可
 * 另一种情况是ab相邻，这样用一个贪心可将其减到0，用O(N)可以遍历选出最小的一对
 * 还有一种情况是ab隔一个位置，这样也可能有影响，同样用贪心枚举每一对即可
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
 
Real const EPS = 1E-12;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}

int N;
int A[SIZE];

int f0(){
    auto f = [](int a, int b){
		if(a < b) swap(a, b);
		if(2 == a && 1 == b) return 1;
		int t = a - b;
		if(b < t) return (a+1) / 2;
		b -= t;
		int left = b % 3;
		return t + b / 3 * 2 + left;
	};
    int ans = 1E7;
	for(int i=1;i<N;++i){
        ans = min(ans, f(A[i], A[i+1]));
	}
	return ans;
}

int f1(){
    auto f = [](int a, int b){
        if(a < b) swap(a, b);
		int ans = b;
		return ans + (a - b + 1) / 2;
	};
	int ans = 1E7;
	for(int i=1;i<N-1;++i){
		ans = min(ans, f(A[i], A[i+2]));
	}
	return ans;
}

int f2(){
	int m1 = -1, m2 = -1;
	for(int i=1;i<=N;++i){
		if(-1 == m1 || A[i] < m1){
			m2 = m1;
			m1 = A[i];
		}else if(-1 == m2 || A[i] < m2){
			m2 = A[i];
		}
	}
	return (m1 + 1) / 2 + (m2 + 1) / 2;
}

int proc(){
	int ans = f0();
	ans = min(ans, f1());
	ans = min(ans, f2());
	return ans;
}
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
	for(int i=1;i<=N;++i) A[i] = getInt();
	cout<<proc()<<endl;
    return 0;
}