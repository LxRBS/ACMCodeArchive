/*
    在菱形地图上问从最顶端走到最底端所能获得的最大权值和
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int const SIZE = 101;

//Dij表示从最顶端走到位置(i,j)所能得到的最大值
int D[SIZE+SIZE][SIZE] = {0};
int A[SIZE+SIZE][SIZE];
int N;

int dp(int row,int col){
    if ( -1 != D[row][col] ) return D[row][col];
    int dc = row <= N ? -1 : +1;
    return D[row][col] = A[row][col] + max(dp(row-1,col),dp(row-1,col+dc));
}

void read(){
    scanf("%d",&N);
    for(int i=1;i<=N;++i)for(int j=1;j<=i;++j)scanf("%d",A[i]+j),D[i][j]=-1;
    for(int i=N-1;i>=1;--i)for(int j=1;j<=i;++j)scanf("%d",A[N+N-i]+j),D[N+N-i][j]=-1;
    D[1][1] = A[1][1];
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,dp(N+N-1,1));
    }
    return 0;
}

