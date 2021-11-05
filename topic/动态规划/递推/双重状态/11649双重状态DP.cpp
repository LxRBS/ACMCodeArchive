#include <cstdio>
#include <algorithm>
using namespace std;

int N,K;
int W[210][2];
bool read(){
    scanf("%d%d",&N,&K);
    if ( 0 == N && 0 == K ) return false;
    for(int i=1;i<=N;++i) scanf("%d%d",W[i],W[i]+1);
    return true;
}

int D[210][2][210];//Drck��ʾ�رշ���rc�ҹر���k�䣬�ܹ��õ������ֵ
int U[210][210];//Urk��ʾǰr�йر�k�䷿�ܹ��õ������ֵ
/*
Drck = max{Wro+Dr-1,c,k-1;Wrc+Wro+Ur-2,k-1}
Urk = max{Drck;Drok;Wro+Wrc+Ur-1,k}
*/
int dp(){
    //��ʼ��
    fill(U[0],U[0]+K+1,0);
    int ta = 0, tb = 0;
    for(int i=1;i<=N;++i){
        ta += W[i][0];
        tb += W[i][1];
        U[i][0] = ta + tb;
        U[i][i] = ta > tb ? ta : tb;
        D[i][0][i] = tb;
        D[i][1][i] = ta;
    }

    //�ӵ�2�п�ʼ
    for(int r=2;r<=N;++r){
        //�ر�1�䵥����
        D[r][0][1] = W[r][1] + U[r-1][0];
        D[r][1][1] = W[r][0] + U[r-1][0];
        U[r][1] = max( max(D[r][0][1],D[r][1][1]),W[r][1]+W[r][0]+U[r-1][1] );

        //���ر�r-1��
        for(int k=2;k<r&&k<=K;++k){
            D[r][0][k] = W[r][1] + max(D[r-1][0][k-1],W[r-1][0]+W[r-1][1]+U[r-2][k-1]);
            D[r][1][k] = W[r][0] + max(D[r-1][1][k-1],W[r-1][0]+W[r-1][1]+U[r-2][k-1]);
            U[r][k] = max( max(D[r][0][k],D[r][1][k]),W[r][1]+W[r][0]+U[r-1][k] );
        }
    }

    return U[N][K];
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        if ( K > N ){
            printf("0\n");
        }else{
            printf("%d\n",dp());
        }
    }
    return 0;
}

