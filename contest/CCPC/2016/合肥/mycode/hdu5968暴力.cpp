/**
  长度为N的数组，给定M个x，对每一个x，
  要求找到数组中的连续子序列，使得异或和与x最接近
  如果有多个答案，取最长的
  N在100以内，所以暴力
*/

#include <stdio.h>
using namespace std;

int A[110];
int B[110][110];

inline int abs(int n){
    return n>=0?n:-n;
}

int f(int n, int x){
    int cha = 1000000000;
    int ans = 0;
    for(int len=n;len>0;--len){
        for(int i=0;i<n-len+1;++i){
            int t = abs(x-B[i][i+len-1]);
            if(t<cha) cha=t,ans=len;
        }
    }
    return ans;
}

int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n,m;
        scanf("%d",&n);
        for(int i=0;i<n;++i)scanf("%d",A+i);

        //预处理
        for(int i=0;i<n;++i){
            B[i][i] = A[i];
            for(int j=i+1;j<n;++j){
                B[i][j] = B[i][j-1] ^ A[j];
            }
        }

        scanf("%d",&m);
        while(m--){
            int x;
            scanf("%d",&x);
            printf("%d\n",f(n,x));
        }
        printf("\n");
    }
    return 0;
}