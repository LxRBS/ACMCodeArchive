/**
 * 给定一个数组A，问存在多少个长度为K+1的子数组满足：
 * 将子数组分别乘以1,2,4,8,...的等比数列以后是严格递增的
 * 无论如何，只需要判断A[i-1] < A[i] * 2即可
 * 因此做一个扫描即可，只需一次循环
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
int const SIZE = 18;
#else
int const SIZE = 2E5+13;
#endif

int N, K;
int A[SIZE];

int proc(){
    int ans = 0;
    int cur = 1;
    while(1){
        int k = cur + 1;
        while(k <= N && (A[k-1]) < (A[k] << 1)) ++k;

        if(k - 1 - cur >= K) ans += k - cur - K;
        if((cur = k) >= N) break;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); K = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        printf("%d\n", proc());
    }
    return 0;
}
