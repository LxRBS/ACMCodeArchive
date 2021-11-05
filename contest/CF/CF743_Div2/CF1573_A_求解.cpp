/**
 * 一个数字串，一共两种操作。
 * 1 将最低位减一（必须非零）
 * 2 交换两个数字
 * 问最少要几次操作，将整个数字串全变为0
 * 显然加起来，然后再看需要几个交换操作即可
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 33;
#else 
int const SIZE = 1010;
#endif

int N;
char A[SIZE];

int proc(){
	int ans = 0, cnt = 0;
	for(int i=0;i<N;++i){
		if(A[i]!='0'){
			ans += A[i] - '0';
			++cnt;
		}
	}
	if(A[N-1]!='0') --cnt;
	return ans + cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%d%s", &N, A);
		printf("%d\n", proc());
	}
	return 0;
}