/*
    ����2^N֧���飬�Լ�����֮��Ļ�ʤ���ʣ��ʴ���̭���ƣ�˭���п��ܻ�ʤ
    ÿһ�ֽ�ʣ�µĶ��鰴�������������У�Ȼ������������
    ����DP
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int N,N2;
double P[130][130];
bool read(){
    scanf("%d",&N);
    if ( N < 0 ) return false;

    N2 = 1 << N;
    for(int i=0;i<N2;++i)for(int j=0;j<N2;++j){
        scanf("%lf",P[i]+j);
    }
    return true;
}

//Dij��ʾ��i�ֵ�j֧����Ӯ�ĸ���
//Dij = D(i-1,j) * SIGMA( D(i-1,k) * P[j][k] )
double D[8][130];
int dp(){
    //��һ��Ӯ��ĸ���
    for(int i=0;i<N2;i+=2){
        D[1][i] = P[i][i+1];
        D[1][i+1] = P[i+1][i];
    }

    for(int i=2;i<=N;++i){
        for(int j=0;j<N2;++j){
            D[i][j] = 0.0;

            int t = j / ( 1 << i );//��һ������
            int tt = ( j / ( 1 << (i-1) )  ) & 1;//Ϊ0������һ���ǰһ��

            //ÿһ���Ϊ���룬ǰһ��ͺ�һ�뻥Ϊ���ܵĶ���
            int pos = t * ( 1 << i ) + ( tt ^ 1 ) * ( 1 << (i-1) );
            for(int k=0;k<(1<<(i-1));++k,++pos){
                D[i][j] += D[i-1][pos] * P[j][pos];
            }

            D[i][j] *= D[i-1][j];
        }
    }

    return max_element(D[N],D[N]+N2) - D[N] + 1;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%d\n",dp());
    }
    return 0;
}
