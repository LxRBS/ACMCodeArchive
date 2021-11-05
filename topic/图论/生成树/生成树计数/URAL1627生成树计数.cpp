/*
    给定一个N×M的格子
    两个打点的格子如果互相出在四邻域可以相连
    问连接的方法总数
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int const SIZE_OF_COLUMNS = 120;

//a is the determinant to be calculated which will be changed during calculation
//n is n, the valid index is from 0 to n-1
llt determinant(llt (*a)[SIZE_OF_COLUMNS],int const n,llt const mod){
    llt ret = 1;

    for(int i=0;i<n;++i){
    	for(int j=i+1;j<n;++j){
    		while( a[j][i] ){
    			llt t = a[i][i] / a[j][i];
    			for(int k=i;k<n;++k){
    				a[i][k] = ( a[i][k] - t * a[j][k] ) % mod;
				}
				for(int k=i;k<n;++k) swap(a[i][k],a[j][k]);
				ret = -ret;
			}
		}

		if ( 0 == a[i][i] ) return 0;

		ret = ret * a[i][i] % mod;
	}

	if ( ret < 0 ) ret += mod;
    return ret;
}

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

llt const MOD = 1000000000LL;
int N,M;
char A[33][33];
llt G[120][120];
int Map[120];

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    for(int i=0;i<N;++i)scanf("%s",A[i]);

    memset(G,0,sizeof(G));
    int cnt = 0;

    for(int i=0;i<N;++i)for(int j=0;j<M;++j)if('.'==A[i][j]){
        int ki = i * M + j;
        Map[ki] = cnt ++;
    }

    for(int i=0;i<N;++i)for(int j=0;j<M;++j)if('.'==A[i][j])for(int o=0;o<4;++o){
        int di = i + DR[o];
        int dj = j + DC[o];
        if ( 0 <= di && di < N && 0 <= dj && dj < M && '.' == A[di][dj] ){
            int ki = Map[i * M + j];
            int kj = Map[di * M + dj];
            ++G[ki][ki];
            --G[ki][kj];
        }
    }
    N = cnt;
    return true;
}

void proc(){
    llt ans = determinant(G,N-1,MOD);
    printf("%lld\n",ans);
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}
