/*
    ��(1,1)��(n,m)һ���ж������߷���
    ֻ����������
    ÿ��һ������һ������
    �ߵ�ĳ��ʱ�������õ��ø�����������������ۼ�
    
    ��Ŀ��Χ������200
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N,M;
int A[210][210];
int D[210][210];

//��λ��(r,c)�ϣ�������e���ܵ�����Щ��
void f(int r,int c,int e){
    for(int i=0;i<=e;++i)for(int j=0;j<=e-i;++j)if(i||j)
        D[r+i][c+j] = ( D[r+i][c+j] + D[r][c] ) % 10000;
}

int dp(){
    memset(D,0,sizeof(D));

    D[1][1] = 1;

    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
        f(i,j,A[i][j]);
    }

    return D[N][M];
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j) scanf("%d",A[i]+j);

        printf("%d\n",dp());
    }
    return 0;
}
