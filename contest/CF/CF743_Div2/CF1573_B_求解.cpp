/**
 * 两个数组，A是1,3,5,...,2n-1
 * B是2,4,6,...,2n
 * 先只允许在各自数组内部做两两交换操作
 * 问最少要多少步使得A数组的字典序小于B数组
 * 只需要对每一个bi，找到第一个小于它的aj，然后计算i+j-2的最小值即可
 * 直接计算是N^2的。考虑树状数组上二分，同时要变化迭代顺序
 * 令i从N到1，则相对应B数组中有2i，A数组中有2i-1
 * 对每一个i，取出器PosB，并找到第一个比它小的PosA，计算PosBi+PosAi-2的最小值即可
 * 令P数组为PosA数组的前缀和，则i-Pi必然是不降的，只要找到第一个为1的位置即可。 
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 10;
#else 
int const SIZE = 100100;
#endif

int N, NN;
int A[SIZE], B[SIZE], C[SIZE];
int PosA[SIZE], PosB[SIZE];
int Flag[SIZE];

inline int lowbit(int x){return x & -x;}
void modify(int x){for(;x<=N;x+=lowbit(x))C[x] += 1;};
int query(int x){int ans=0;for(;x;x-=lowbit(x))ans+=C[x];return ans;}

int f(){
    int left = 1, right = N, mid;
    do{
         mid = (left + right) >> 1;
         if(query(mid) == mid) left = mid + 1;
         else right = mid - 1;
    }while(left<=right);
    return left;
}

int proc(){
    fill(C, C+N+1, 0);
    int ans = N - 1;
    for(int t,i=N;i;--i){
        t = f();
        ans = min(ans, PosB[i]-1+t-1);
        modify(PosA[i]);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
        N = getUnsigned();
		for(int i=1;i<=N;++i)PosA[((A[i] = getUnsigned())+1)>>1] = i;
		for(int i=1;i<=N;++i)PosB[(B[i] = getUnsigned())>>1] = i;
		printf("%d\n", proc());
	}
	return 0;
}