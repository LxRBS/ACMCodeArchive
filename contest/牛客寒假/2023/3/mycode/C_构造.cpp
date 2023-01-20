/**
 * 构造一个N长度的排列，对每个ai满足 2 <= |ai - i| <= 3
 * i从1到N。
 * 手工构造较小的一些数，发现可以用4作为循环节
 * 对于对于前面循环节，按照(3,4,1,2)的顺序填充即可
 * 将余数和最后一整节和在一起，构成4,5,6，均可以简单手推出来
 * 7是一个特殊的，7本身不满足。但是之后形如4k+3的均可。
 * 用了一个二分匹配构造出11的情况，按照最后7个的对应关系构造即可。
 * 7以下特判。
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
int const SIZE = 130;
#else
int const SIZE = 1e7+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>; 

int N;
vi A;

bool test(){
	vi cnt(N+1, 0);
	for(int i=0;i<N;++i){
		auto j = i + 1;
        auto aj = A[i];
		if(++cnt[aj] > 1) return false;
		if(2 <= abs(aj - j) && abs(aj - j) <= 3) continue;
		return false;
	}
	return true;
}

void proc(){
	int left = N % 4;
	int beishu = N / 4;
    int k = 4;

	if(N <= 3) return (void)printf("-1\n");
	if(4 == N){
		A = {3, 4, 1, 2};
		goto L;
	}
	if(5 == N){
		A = {3, 4, 5, 1, 2};
		goto L;
	}
    if(6 == N){
		A = {3, 5, 1, 6, 2, 4};
		goto L;
	}
	if(7 == N){
		return (void)printf("-1\n");
	}

	A[0] = 3; A[1] = 4; A[2] = 1; A[3] = 2;

    
	for(int i=2;i<beishu;++i){
		A[k] = A[k - 4] + 4; ++k;
		A[k] = A[k - 4] + 4; ++k;
		A[k] = A[k - 4] + 4; ++k;
		A[k] = A[k - 4] + 4; ++k;
	}
	if(0 == left){
		A[N-4] = A[N-8] + 4;
		A[N-3] = A[N-7] + 4;
		A[N-2] = A[N-6] + 4;
		A[N-1] = A[N-5] + 4;
	}else if(1 == left){
        A[N - 5] = N - 2;
		A[N - 4] = N - 1;
		A[N - 3] = N;
		A[N - 2] = N - 4;
		A[N - 1] = N - 3;
	}else if(2 == left){
        A[N - 6] = N - 3;
		A[N - 5] = N - 1;
		A[N - 4] = N - 5;
		A[N - 3] = N;
		A[N - 2] = N - 4;
		A[N - 1] = N - 2; 
	}else if(3 == left){
        A[N - 11] = N - 8;
		A[N - 10] = N - 6;
		A[N - 9] = N - 5;
		A[N - 8] = N - 10;
		A[N - 7] = N - 9;
		A[N - 6] = N - 7;
		A[N - 5] = N - 1;
		A[N - 4] = N;
		A[N - 3] = N - 4;
		A[N - 2] = N - 3;
		A[N - 1] = N - 2;
	}

L:
	assert(test());
	for(int i : A) printf("%d ", i);
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif


	while(cin >> N){
		A.assign(N, 0);
		proc();
	}
    return 0;
}