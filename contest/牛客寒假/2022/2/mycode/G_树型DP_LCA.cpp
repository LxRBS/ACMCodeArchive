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
int const SIZE = 11;
#else
int const SIZE = 1000001;
#endif

typedef long long llt;
typedef vector<int> IntVecTy;
typedef pair<int, int> PiiTy;

struct pair_hash{
	inline size_t operator()(const PiiTy&p)const{
		return p.first * 1331 + p.second;
	}	
};

typedef IntVecTy I2VecMapTy[SIZE];
typedef unordered_map<PiiTy, int, pair_hash> MapTy;

IntVecTy G[SIZE];

int N, M;
llt A[SIZE];
llt X[SIZE]; 
llt Y[SIZE];

I2VecMapTy Qs, IQ;
MapTy Q2I;
llt Ans[SIZE];

//Pij表示第i个节点的2^j级别的祖先
//例如Pi0就是i的父节点
int Parent[SIZE][22];
int Depth[SIZE];//根节点的深度是1
//Log2[i]就是以2为底i的对数加1，取整，需要预先算出来
int Log2[SIZE];

void dfs(int u,int parent){
    Parent[u][0] = parent;
    Depth[u] = Depth[parent] + 1;
    //确定u的各级祖先
    for(int i=1,n=Log2[Depth[u]];i<=n;++i){
        Parent[u][i] = Parent[Parent[u][i-1]][i-1];
    }
    for(auto v: G[u]){
		if(v == parent) continue;
		if(A[v] <= A[u]){
			X[v] = X[u];
			Y[v] = Y[u] + A[u] - A[v];
		}else{
			X[v] = X[u] + A[v] - A[u];
			Y[v] = Y[u];
		}		
		dfs(v, u);
	}
}

int lca(int x,int y){
    if(Depth[x]<Depth[y]) swap(x,y);
    //把x和y调整到一个深度区间内
    while(Depth[x]>Depth[y]) x = Parent[x][Log2[Depth[x]-Depth[y]]-1];
    if(x==y) return x;
    //一起往上跳
    for(int k=Log2[Depth[x]]-1;k>=0;--k){
        if(Parent[x][k]!=Parent[y][k]){
            x = Parent[x][k];
            y = Parent[y][k];
        }
    }
    return Parent[x][0];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	M = getInt();
    //初始化
    for(int i=1;i<=N;++i){
        Log2[i] = Log2[i-1] + ( (1 << Log2[i-1])==i?1:0 );
    }	
	for(int i=1;i<=N;++i) A[i] = getInt();
	for(int a,b,i=1;i<N;++i){
		a = getInt();
		b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	X[1] = Y[1] = 0;
	dfs(1, 0);
	for(int r,a,b,i=1;i<=M;++i){
		a = getInt();
		b = getInt();
        r = lca(a, b);
		printf("%lld\n", A[a]+Y[a]-Y[r]+X[b]-X[r]);
	}    
    return 0;
}
