#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int N,M;
int P[100010];
double D[100010];//Di表示从位置i到N需要的期望次数

void dp(){
    D[N] = 0.0;
    for(int i=N-1;i>=0;--i){
        if ( D[i] ) continue;

        if ( P[i] ){
            D[i] = D[P[i]];
            continue;
        }

        D[i] = 1.0;
        for(int j=1;j<=6;++j){
            int n = i + j;
            if ( n > N ) n = N;

            D[i] += D[n] / 6.0;
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    while( scanf("%d%d",&N,&M) ){
        if ( 0 == N && 0 == M ) return 0;

        fill(P,P+N+1,0);
        fill(D,D+N+1,0.0);

        int x,y;
        for(int i=0;i<M;++i){
            scanf("%d%d",&x,&y);
            P[x] = y;
        }

        dp();
        printf("%.4f\n",D[0]);
    }
}
