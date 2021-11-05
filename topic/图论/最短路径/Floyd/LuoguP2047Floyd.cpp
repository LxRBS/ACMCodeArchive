/**
    无向连通图，对每一个节点v，求
    SIGMA( (经过v的s、t最短路数量)/(s、t最短路数量) )

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
llt const INF = 1E16;

llt G[110][110];
llt Cnt[110][110];
double Ans[110];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    for(int i=1;i<=n;++i){
        fill(G[i],G[i]+n+1,INF);
        G[i][i] = 0;
    }
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        G[a][b] = G[b][a] = min(G[a][b],(llt)getUnsigned());
        Cnt[a][b] = Cnt[b][a] = 1;
    }
    //Floyd
    llt tmp;
    for(int k=1;k<=n;++k){
        for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){
            if((tmp=G[i][k]+G[k][j])>=INF) continue;
            if(G[i][j]>tmp){
                G[i][j] = tmp;
                Cnt[i][j] = Cnt[i][k] * Cnt[k][j];
            }else if(G[i][j]==tmp){
                Cnt[i][j] += Cnt[i][k] * Cnt[k][j];
            }
        }
    }

    //计算过v的最短路径数量，顺便计算答案
    for(int v=1;v<=n;++v){
        for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)if(v!=i&&v!=j&&G[i][j]==G[i][v]+G[v][j]){
            Ans[v] += (double)Cnt[i][v] * (double)Cnt[v][j] / (double)Cnt[i][j];
        }
        printf("%.3f\n",Ans[v]);
    }
    return 0;
}
