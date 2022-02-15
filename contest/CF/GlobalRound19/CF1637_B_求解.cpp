/**
 * 给一个数组，将其做一个完备划分，并且定义该划分的花费为：
 * 划分的数量+SIGA{每个划分的mex}
 * 再定义数组的值为所有划分中最大的那个花费
 * 现在给定数组，求其所有子数组的值之和
 * 首先解决值的问题
 * 给定任意非零元素[a1, a2]，很明显将其拆开，花费要更大
 * 对于全零序列[0, 0]，显然拆开的花费更大
 * 对于含零序列[a1, 0]，同样拆开的花费会更大
 * 因此对一个数组而言，其值就是全拆开的花费，也就是长度加零的数量
 * 现在考虑问题，对一个数组而言，显然长度为N的子数组只有1个，长度为N-1的子数组有2个，……
 * 再考虑零的问题，零一共会出现几次？假设零左边有left个数，右边有right个数，
 * 则含该0的子数组一共有(left+1)*(right+1)个。
 * 注意，因为方案是把每个零都拆开，所以零零之间互补不影响。
 * 两部分加起来即可
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
int const SIZE = 10010;
#endif

typedef long long llt;

int N, A[SIZE];

llt proc(){
    llt ans = 0;
    for(int i=0;i<N;++i){
        ans += (1+i)*(N-i);
    }
    for(int i=0;i<N;++i){
        if(A[i]) continue;
        ans += (i+1) * (N-i);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        for(int i=0;i<N;++i) A[i] = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}
