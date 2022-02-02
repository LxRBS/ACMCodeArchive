/**
 * 给定N，要求求出一个0到N-1的排列，使得 argmin{max{P[i-1]^Pi},i从1到N-1}
 * 首先令N减减，简单的暴力发现答案可能是2^k，其中k是N的最高位位置
 * 考虑构造方案：显然0和2^k放在一起即可得到答案，比2^k大的数不能放在0左边
 * 比2^k大的数放在右边即可，因为异或出来肯定小于2^k
 * 同理小的数放在左边即可
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
int const SIZE = 15;
#else
int const SIZE = 200010;
#endif

int N;
int A[SIZE];

void proc(){
	int k = 30;
	--N;
	while(0 == ((1<<k)&N)) --k;
	for(int i=N,n=1<<k;i>=n;--i) printf("%d ", i);
	printf("0");
	for(int i=1,n=1<<k;i<n;++i) printf(" %d", i);
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		proc();
	}
    return 0;
}
