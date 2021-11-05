/*
    N�����ӣ�ÿһ��ȸ��ʣ�ÿ����ai�����
    N�浱����M��������ģ�����M������֮һ�Ϳ�������һ�飬
    ������M��֮һ�ֿ�������һ�顭��
    ��һ����Ϸ�õ��Ľ������
    ������ΪE
    E = SIGMA( P(������M��) * ��Ӧ��Ľ�� ) + SIGMA( P(M��) * ( ��Ӧ��Ľ�� + E ) )
    ���� E = ����/N + E * M/N
    ���� E = ���� / ( N - M )
*/
#include <stdio.h>
#include <numeric>
#include <algorithm>
using namespace std;

int N,M,S;
int main(){
    int a;
    while( EOF != scanf("%d",&N) ){
        S = 0;
        for(int i=0;i<N;++i){
            scanf("%d",&a);
            S += a;
        }

        scanf("%d",&M);
        for(int i=0;i<M;++i) scanf("%d",&a);

        if ( 0 == S ) printf("0.00\n");
        else if( N == M ) printf("inf\n");
        else printf("%.2f\n",(double)S/(N-M));
    }
    return 0;
}
