/**
 * 给一个数字串，允许两种操作：删除任意一个数字，在最右端添加一个数字
 * 问最少几次操作，可以将给定字符串变成2的幂
 * 数字串在1E9，则可能的目标在1E18以内，即2^57
 * 令d为某个2的幂，将s变为d，最少步骤用贪心法即可
 * 例如s为410777，d为4096，则s中4和0保留，其余全删掉，再在右边添加96即可
 * 对所有2的幂计算结果，取最小的即可
 * 后来发现贪心其实是有问题的，应该求出输入与指定2幂的最长公共子序列，不过长度较短，肯定也可以实现
 * 后来又发现贪心是没有问题的???
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 100100;
#endif

char const G[58][23] = {
	"1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024"
	, "2048", "4096", "8192", "16384", "32768", "65536", "131072"
	, "262144", "524288", "1048576", "2097152", "4194304", "8388608"
	, "16777216", "33554432", "67108864", "134217728", "268435456"
	, "536870912", "1073741824", "2147483648", "4294967296"
	, "8589934592", "17179869184", "34359738368", "68719476736"
	, "137438953472", "274877906944", "549755813888", "1099511627776"
	, "2199023255552", "4398046511104", "8796093022208", "17592186044416"
	, "35184372088832", "70368744177664", "140737488355328", "281474976710656"
	, "562949953421312", "1125899906842624", "2251799813685248", "4503599627370496"
	, "9007199254740992", "18014398509481984", "36028797018963968"
	, "72057594037927936", "144115188075855872"
};
int L[58];

char A[15];
int N;

int proc(int idx){
    int t = 0;
	char const *pa = A;
	char const *pb = G[idx];
	while(*pa && *pb){
		if(*pa == *pb){
			++pa; ++pb; ++t;
		}else{
			++pa;
		}
	}   
    int m = L[idx];
	return N - t + m - t;
}

int proc(){
	N = strlen(A);
    int ans = N + 1;
	for(int i=0;i<58;++i){
		ans = min(ans, proc(i));
	}
	return ans;
}

int main(){
	for(int i=0;i<58;++i) L[i] = strlen(G[i]);
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