#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N;
int A[210],B[210];
int D[210][210];

int dp(int s,int e){
    if ( -1 != D[s][e] ) return D[s][e];
    if ( e <= s+1 ) return D[s][e] = 0;

    int&r = D[s][e];
    r = 2000000000;

    for(int k=s+1;k<e;++k){
        r = min(r,dp(s,k)+dp(k,e)+A[k]+B[s]+B[e]);
    }

    return r;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&N);
        for(int i=1;i<=N;++i)scanf("%d",A+i);
        for(int i=1;i<=N;++i)scanf("%d",B+i);
        A[N+1] = B[N+1] = 0;

        memset(D,-1,sizeof(D));
        printf("Case #%d: %d\n",kase,dp(0,N+1));
    }
    return 0;
}
