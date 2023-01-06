/**
 * 给定一个树，再给定两个点，x是起点，y是终点，除此之外还有K个点
 * 从x出发，要先访问K个点每个点至少一次，最后到达y点，问最少走几步？
 * 以x为根，首先搜一遍，对某个节点，如果其子树上没有任何有用的点，则该点没用，否则就是有用的节点
 * 然后再求出x到所有有用节点的边长的两倍，这就是从x出发再回到x需要的最小步数
 * 再减去x到y的距离即可
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
int const SIZE = 13;
#else
int const SIZE = 2e5+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>; 

int N, K;
int X, Y;
int A[SIZE];
vi G[SIZE];
int B[SIZE];
bool Flag[SIZE];


int dfs(int u, int p){
    int ans = 0;
	if(Flag[u]||u==X||u==Y) ans = 1;

	for(int i: G[u]){
		if(i == p) continue;
        ans += dfs(i, u);
	}
    if(0 == ans) B[u] = 1;
	else B[u] = 2;
	return ans;
}

int f(){
	if(X == Y) return 0;

	int ans = 0;
	queue<int> q; q.push(X);
	vi tmp(N+1, 0); tmp[X] = 1;
	while(!q.empty()){
		int sz = q.size();
		++ans;
		while(sz--){
			int h = q.front();q.pop();
			for(int i: G[h]){
				if(i == Y) return ans;
				if(tmp[i]) continue;
				tmp[i] = 1;
				q.push(i);
			}
		}
	}
	return ans;
}

llt g(int u, int p){
	llt ans = 0;
    for(int i: G[u]){
		if(i == p) continue;
		if(B[i] & 1) continue;
		ans += 1 + g(i, u);
	}
	return ans;
}

llt proc(){
	fill(B, B+N+1, 0);
    dfs(X, 0);

	int left = f();
	llt ans = g(X, 0);
	ans = ans * 2;
	ans -= left;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); K = getInt();
		X = getInt(); Y = getInt();
		fill(Flag, Flag+N+1, false);
		for(int i=1;i<=N;++i) G[i].clear();
		for(int i=1;i<=K;++i) Flag[getInt()] = true;
		for(int u,v,i=1;i<N;++i){
            u = getInt(); v = getInt();
			G[u].push_back(v);
			G[v].push_back(u);
		}
		printf("%lld\n", proc());
    }
    return 0;
}