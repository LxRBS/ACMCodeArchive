/**
 * 给定一个数组A，从后往前对每个Ai将其放入B数组的中间，B初始为空
 * 如果当时B有奇数个元素，则Ai有两个位置可供选择。
 * 所有Ai都放入B以后，再依次将B的中间元素拿出放入C，C初始为空
 * 如果当时B有偶数个元素，则有两种选法
 * 问这样操作后，C是否能够有序
 * 假设A的长度是偶数，如此操作以后，实际上就是将A中的成对元素放入C的相应位置
 * 每对元素内部可以交换位置。因此判断一下即可。对奇数做一个简单处理也可如此处理。
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
int A[SIZE], B[SIZE];

bool proc(){
    copy(A, A+N, B);
	sort(B, B+N);
	int from = 0;
	if(N&1){
		if(A[0] != B[0]) return false;
		++from;
	}
	for(int i=from;i<N;i+=2){
		if((A[i] == B[i] && A[i+1] == B[i+1]) || (A[i] == B[i+1] && A[i+1] == B[i])) continue;;
	    return false;
	}
	return true;
}
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		for(int i=0;i<N;++i)A[i] = getInt();
		puts(proc()?"YES":"NO");
    }
    return 0;
}