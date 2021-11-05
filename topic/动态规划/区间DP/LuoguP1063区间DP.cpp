//区间DP
//环状结构，直接两倍
#include <bits/stdc++.h>
using namespace std;

int N;
int D[210][210];
int A[210];

int dfs(int s,int e){
    if(D[s][e]) return D[s][e];

    int &ans = D[s][e];
    for(int i=s;i<e;++i){
        int tmp = dfs(s,i) + dfs(i+1,e);
        tmp += A[s] * A[i+1] * A[e+1];
        ans = max(ans,tmp);
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;++i)scanf("%d",A+i),A[i+N]=A[i];
    A[N<<1] = A[0];

    for(int i=0,n=N<<1;i<n-1;++i){
        D[i][i+1] = A[i]*A[i+1]*A[i+2];
    }

    int ans = 0;
    for(int i=0;i<N;++i){
        ans = max(ans,dfs(i,i+N-1));
    }
    printf("%d\n",ans);
	return 0;
}
