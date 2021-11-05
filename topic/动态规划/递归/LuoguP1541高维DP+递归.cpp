#include <bits/stdc++.h>
using namespace std;

int N,M;
int A[420];
int D[42][42][42][42];
int C[4];

int dfs(int a,int b,int c,int d){
    if(D[a][b][c][d]) return D[a][b][c][d];

    int n = a+b*2+c*3+d*4 + 1;
    int ans = 0;

    if(a>0)ans = max(ans,dfs(a-1,b,c,d));
    if(b>0)ans = max(ans,dfs(a,b-1,c,d));
    if(c>0)ans = max(ans,dfs(a,b,c-1,d));
    if(d>0)ans = max(ans,dfs(a,b,c,d-1));
    return D[a][b][c][d] = ans + A[n];
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)scanf("%d",A+i);
    for(int i=0;i<M;++i){
        int x;
        scanf("%d",&x);
        ++C[x-1];
    }

    D[0][0][0][0] = A[1];
    printf("%d\n",dfs(C[0],C[1],C[2],C[3]));
	return 0;
}
