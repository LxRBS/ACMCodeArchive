/**
 * 给定一个数组，允许进行一种操作：如果相邻数之和是奇数就能够进行交换
 * 问能否经过任意次操作将数组变的有序
 * 很显然，如果相邻数奇偶性相同，就不能交换，所以如果要有序就得原来就有序
 * 因此分别检查奇数和偶数是否有序即可
 * 其他的通过不限次的交换肯定能够变为有序
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
int const SIZE = 7;
#else
int const SIZE = 100010;
#endif

int N, A[SIZE];

int B[SIZE], C[SIZE];

bool proc(){
	if(1 == N) return true;

	auto f = [](const int a[], int n)->bool{
        for(int i=1;i<n;++i){
			if(a[i-1] <= a[i]) continue;
			return false;
		}
		return true;
	};

    if([&]()->bool{
		for(int i=2;i<=N;++i){
			if(A[i-1] <= A[i]) continue;
			return false;
		}
		return true;
	}()) return true;

	int b = 0, c = 0;
	for(int i=1;i<=N;++i){
		if(A[i]&1) B[b++] = A[i];
		else C[c++] = A[i];
	}
	return f(B, b) && f(C, c);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		for(int i=1;i<=N;++i)A[i]=getInt();
		puts(proc()?"Yes":"No");
    }
    return 0;
}
