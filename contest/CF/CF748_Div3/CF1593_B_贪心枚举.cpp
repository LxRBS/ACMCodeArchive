/**
 * 给定一个数字串，每次操作可以删除一个数字（以及由此形成的前导0）
 * 问最少多少次操作，使得数字被25整除
 * 首先确定贪心，只需从后往前考虑进行删除即可
 * 其次枚举，被25整除末尾只有4种情况
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

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 22;
#endif

int N;
char A[SIZE];

int f00(){
	int fi = -1, se = -1;
	for(int i=N-1;i>=0;--i){
		if('0' == A[i]){
			if(-1 == fi){
				fi = i;
			}else if(-1 == se){
				se = i;
				break;
			}
		}
	}

	if(-1 == se) return N;
	return N - se - 2;
}

int f25(){
	int fi = -1, se = -1;
	for(int i=N-1;i>=0;--i){
	    if(-1 == fi){
			if('5' == A[i]){
				fi = i;
			}
		}else if(-1 == se){
			if('2' == A[i]){
				se = i;
				break;
			}
		}
	}

	if(-1 == se) return N;
	return N - se - 2;	
}

int f50(){
	int fi = -1, se = -1;
	for(int i=N-1;i>=0;--i){
	    if(-1 == fi){
			if('0' == A[i]){
				fi = i;
			}
		}else if(-1 == se){
			if('5' == A[i]){
				se = i;
				break;
			}
		}
	}

	if(-1 == se) return N;
	return N - se - 2;	
}

int f75(){
	int fi = -1, se = -1;
	for(int i=N-1;i>=0;--i){
	    if(-1 == fi){
			if('5' == A[i]){
				fi = i;
			}
		}else if(-1 == se){
			if('7' == A[i]){
				se = i;
				break;
			}
		}
	}

	if(-1 == se) return N;
	return N - se - 2;	
}

int proc(){
	N = strlen(A);
	int ans = N;
	ans = min(ans, f00());
	ans = min(ans, f25());
	ans = min(ans, f50());
	ans = min(ans, f75());
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%s", A);
		printf("%d\n", proc());
	}
    return 0;
}