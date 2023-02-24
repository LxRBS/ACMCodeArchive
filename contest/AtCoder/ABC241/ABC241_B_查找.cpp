/**
 * 给定长度为N的数组A，再给定长度为M的数组B
 * 一共操作M次，第i次在A中查找是否存在Bi，找不到就失败
 * 找到了就从A中删除Bi，并继续。
 * 排序，或者做一个set都可以。
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
int const SIZE = 10030;
#endif  

int N, M;
vector<int> A, B;

bool proc(){
	if(M > N) return false;
	sort(A.begin(), A.end());
	for(auto i: B){
		auto it = lower_bound(A.begin(), A.end(), i);
		if(it == A.end() || *it != i) return false;
		A.erase(it);
	}
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	A.assign(N, 0); B.assign(M, 0);
	for(int i=0;i<N;++i) A[i] = getInt();
	for(int i=0;i<M;++i) B[i] = getInt();
	puts(proc()?"Yes":"No");
    return 0;
}
