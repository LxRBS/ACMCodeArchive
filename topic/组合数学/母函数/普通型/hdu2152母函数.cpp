//N�ֶ�����ÿһ�ֵĸ���������[A,B]֮�䣬�����M���ķ�������
#include <cstdio>
#include <algorithm>
using namespace std;

int N,M;
int A[110],B[110];

int D[110];
int T[110];

int dp(){
    //��ʼ��
    fill(D,D+M+1,0);
    fill(T,T+M+1,0);
    fill(D+A[0],D+B[0]+1,1);

    //��ÿһ��ˮ��
    for(int i=1;i<N;++i){
        for(int j=0;j<=M;++j){
            for(int k=A[i];k+j<=M&&k<=B[i];++k)
                T[j+k] += D[j];
        }

        //����
        copy(T,T+M+1,D);
        fill(T,T+M+1,0);
    }
    return D[M];
}
int main(){
    while ( EOF != scanf("%d%d",&N,&M) ){
        for(int i=0;i<N;++i)scanf("%d%d",A+i,B+i);

        printf("%d\n",dp());
    }
    return 0;
}
