/**
 * N张牌，其中M张是大王，K个人，K一定是N的倍数
 * 拿到最多大王的人获胜，且得分为最多数量减去剩下的人的最多数量
 * 如果有多个人均拿到了最多的大王，则积分为0
 * 给定NMK，问最多可能的积分是多少
 * 显然某个人全拿大王，剩下的人平分剩下的即可
 * 还要处理一些特殊情况
*/
#include <bits/stdc++.h>
using namespace std;

int N, M, K;

int proc(){
	if(M<=N/K) return M;
    
	int m = M - N / K;
	int t = m / (K - 1);
	if(m % (K-1)) ++t;
	return N/K - t;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%d%d%d", &N, &M, &K);
		printf("%d\n", proc());
	}
	return 0;
}
