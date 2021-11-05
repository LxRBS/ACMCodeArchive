//LIS
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int const SIZE = 100005;
int A[SIZE];
int N;
int DP[SIZE];//DP[i]��¼������Ai��β��LIS�ĳ���
int Aux[SIZE];//�������飬Aux[i]��¼���ǳ���Ϊi��LIS�Ľ�βԪ��

//�����������,O(nlogn)
int lis(int const a[],int n){
    fill(DP,DP+n,0);
    fill(Aux,Aux+n+1,0);
    DP[0] = 1;
    Aux[1] = a[0];

    int k = 1;
    for(int i=1;i<n;++i){
        int t;
        if ( Aux[k] < a[i] ){
            Aux[++k] = a[i];
        }else{
            *lower_bound(Aux+1,Aux+k+1,a[i]) = a[i];
        }
    }
    return k;
}

int main()
{
    while(EOF!=scanf("%d",&N)){
        for(int i=0;i<N;++i)scanf("%d",A+i);

        printf("%d\n",lis(A,N));
    }
    return 0;
}

