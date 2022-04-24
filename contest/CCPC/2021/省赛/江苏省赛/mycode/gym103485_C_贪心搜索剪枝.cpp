/**
 * 0~9的十种数字，每种给定若干个，构成一个最小的整数，满足:
 * 1 没有前导0，除非本身就是0
 * 2 给定的数字全都要用上
 * 3 相邻数字不相同
 * 深搜剪枝，搜的时候从小往大搜，所以搜到的第一个就是最小的
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
int const SIZE = 33;
#else
int const SIZE = 100100;
#endif

int A[10];
char B[SIZE];
int Total;

bool dfs(int depth){
	if(Total == depth){
		return true;
	}

    int const prev = B[depth-1] - '0';
	for(int i=0;i<10;++i){
		if(0 == A[i] || prev == i) continue;
        
		B[depth] = i + '0';
		--A[i];
        /// 只加了这一个剪枝,就过了
        int left = Total - depth - 1;
		int mmax = *max_element(A, A+10);
		if(mmax + mmax > left + 1){
			++A[i]; continue;
		}

		if(dfs(depth+1)) return true;
		++A[i];
	}
	return false;
}

bool proc(){
	B[Total] = '\0';    
	if(1 == Total){
		for(int i=0;i<10;++i){
			if(A[i]){
				B[0] = i + '0';
				return true;
			}
		}
	}
	for(int i=1;i<10;++i){
		if(A[i]){
			B[0] = i + '0';
			--A[i];
			if(dfs(1)) return true;
			++A[i];
		}
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        Total = 0;
		for(int i=0;i<10;++i){
			Total += A[i] = getInt();
		}
		puts(proc()?B:"-1");
	}
    return 0;
}
