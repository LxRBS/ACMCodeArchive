/**
 * 给定一个树，要求给节点赋权值。满足：
 * 删除任意一个点，原树分成的若干个部分，每个部分的权值和都一样
 * 把图二分染色，黑色赋权值为度数，白色赋权值为负度数
 * 实际上连通子图的点权和就是边权和，而完整的边权值是0
 * 所以如果删掉的点是黑色，则剩下部分全是-1
 * 删掉白色，剩下的全是1
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
int const SIZE = 10;
#else
int const SIZE = 1E5+5;
#endif

typedef long long llt;
typedef pair<int, int> pii;
typedef vector<int> vi;
vi G[SIZE];
int N;
int Flag[SIZE];
int Deg[SIZE];

void dfs(int u, int p){
	Deg[u] = 1;
    for(int v: G[u]){
		if(v == p) continue;
		Flag[v] = Flag[u] ^ 1;
		dfs(v, u);
		++Deg[u];
	}
}

void proc(){
	fill(Flag, Flag+N+1, 0);
	fill(Deg, Deg+N+1, 0);
	Flag[1] = 2;
	dfs(1, 0);
	--Deg[1];
	for(int i=1;i<=N;++i){
		if(2 == Flag[i]){
			printf("%d ", Deg[i]);
		}else{
			printf("%d ", -Deg[i]);
		}
	}
	
	return (void)puts("");
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=1;i<=N;++i) G[i].clear();
        for(int a,b,i=1;i<N;++i){
            a = getInt(); b = getInt();
			G[a].push_back(b);
			G[b].push_back(a);
		}
		proc();
	}
    return 0;
}
