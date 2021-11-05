//LIS
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int const SIZE = 100005;
int A[SIZE];
int N;
int DP[SIZE];//DP[i]记录的是以Ai结尾的LIS的长度
int Aux[SIZE];//辅助数组，Aux[i]记录的是长度为i的LIS的结尾元素

//最长上升子序列,O(nlogn)
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

