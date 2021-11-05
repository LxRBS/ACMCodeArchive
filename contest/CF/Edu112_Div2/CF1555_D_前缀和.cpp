/**
 * 一个字符串如果不含长度2及以上的回文子串，称为beautiful
 * 给定一个字符串，只含a/b/c三种字母
 * 每次操作可以改变其中一个字母，给定[s, e]
 * 问最少要几次操作，可以将[s, e]子串改为beautiful
 * 有多次询问。
 * 因为只有三种字母，发现必须是一个排列，才能满足条件
 * 所以每个[s, e]只有6种可能的改法，
 * 即要统计[s, e]与abcabc、acbacb、bacbac、bcabca、...不同字母的数量
 * 可以预处理整个字符串，用前缀和记录。
 * O(1)回答查询 
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 200010;
#endif

int N, M;
char A[SIZE] = {0};
int B[6][SIZE] = {0};

int proc(int s, int e){
	int ans = N;
	for(int i=0;i<6;++i){
		ans = min(ans, B[i][e] - (s?B[i][s-1]:0));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%s", &N, &M, A);
	char t[] = "abc";
	int k = 0;
	do{
		B[k][0] = t[0] != A[0] ? 1 : 0;
        for(int i=1;i<N;++i){
			B[k][i] = B[k][i-1] + (t[i%3]!=A[i]?1:0);
		}
		++k;
	}while(next_permutation(t, t+3));

    for(int a, b, i=1;i<=M;++i){
		scanf("%d%d", &a, &b);
		printf("%d\n", proc(--a, --b));
	}
    return 0;
}