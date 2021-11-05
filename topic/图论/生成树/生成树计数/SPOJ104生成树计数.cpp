/*
    求不同生成树的个数
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMNS = 13;

typedef double real_t;

real_t const EPS = 1E-6;
int sign(real_t x){
    if ( -EPS < x && x < EPS ) return 0;
    return x < 0 ? -1 : 1;
}

//a is the determinant to be calculated
//n is n, the valid index is from 0 to n-1
real_t determinant(real_t (*a)[SIZE_OF_COLUMNS],int const n){
    real_t ret = 1;
    int sgn = 0;

    for(int i=0,j,k;i<n;++i){
        if ( 0 == sign(a[i][i]) ){
            for(j=i+1;j<n;++j){
                if ( sign(a[j][i]) ) break;
            }

            if ( n == j ) return 0;

            for(k=i;k<n;++k) swap(a[i][k],a[j][k]);

            ++sgn;
        }

        ret *= a[i][i];
        for(k=i+1;k<n;++k) a[i][k] /= a[i][i];

        for(j=i+1;j<n;++j)for(k=i+1;k<n;++k){
            a[j][k] -= a[j][i] * a[i][k];
        }
    }

    if ( sgn & 1 ) ret = -ret;
    return ret;
}

bool G[13][13];
real_t A[13][SIZE_OF_COLUMNS];
int N,M;
bool read(){
    for(int i=0;i<13;++i)fill(G[i],G[i]+13,false);

    scanf("%d%d",&N,&M);
    for(int i=0;i<M;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        --a,--b;
         G[a][b] = G[b][a] = true;
    }


    return true;
}

void proc(){
    if ( 1 == N ){
        printf("1\n");
        return;
    }

    for(int i=0;i<N;++i)fill(A[i],A[i]+N,0.0);

    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
        if ( i != j && G[i][j] ){
            ++ A[i][i];
            A[i][j] = -1;
        }
    }

    double ret = determinant(A,N-1);
    if ( ret < 0 ) ret = -ret;
    printf("%.0f\n",ret);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while( nofkase-- ){
        read();
        proc();
    }
    return 0;
}
