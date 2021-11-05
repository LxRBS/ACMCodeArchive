/**
    无向图最小环，
    改造一下Floyd，令Dijk是i到j且途中的最大顶点不超过k的最短路径则：
    Dijk = min( Di,j,k-1, Di,k,k-1 + Dk,j,k-1 )
    则Dijk+Wik+Wkj就是一个环，求其最小值

*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long llt;
llt const INF = 100000000000000LL;
llt G[110][110];
llt D[110][110];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    for(int i=1;i<=n;++i){
        fill(G[i],G[i]+n+1,INF);
        fill(D[i],D[i]+n+1,INF);
        G[i][i] = D[i][i] = 0;
    }
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        llt w = getUnsigned();
        D[a][b] = D[b][a] = G[a][b] = G[b][a] = min(G[a][b],w);
    }

    //Floyd
    llt ans = INF;
    for(int k=1;k<=n;++k){
        for(int i=1;i<k;++i)for(int j=i+1;j<k;++j){
            ans = min(ans,D[i][j]+G[i][k]+G[k][j]);
        }
        for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){
            D[i][j] = min(D[i][j],D[i][k]+D[k][j]);
        }
    }
    if(ans>=INF)puts("No solution.");
    else printf("%d\n",ans);
    return 0;
}
