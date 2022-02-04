/**
 * 给定一个长度为N的字符串，分成K个非空子序列，不一定要用到所有字母，即某些字母可以不在这K个子序列中
 * K个子序列内部可以互相交换相邻位置任意次，最后均要变成回文
 * 现在要求这K个子序列的最短长度最长，问这个最短最长是多少
 * 相邻交换任意次其实就是可以任意排列，因此只需选字母即可
 * 要形成回文，显然要成对成对选，最后单一个即可
 * 因此统计对数即可，最后判断以下
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 200010;
#endif

int N, K;
char A[SIZE];

int proc(){
    int cnt[256] = {0};
	for(int i=0;i<N;++i) ++cnt[A[i]];

	int two = 0, one = 0;
	for(int i='a';i<='z';++i){
		two += cnt[i] / 2;
		one += (cnt[i] & 1);
	}
	if(two < K) return 1;
	int t = two / K;
	int left = two % K;
	if(left + left + one >= K) return t + t + 1;
	return t + t;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%d%d%s", &N, &K, A);	
		printf("%d\n", proc());
	}
    return 0;
}
