//选k个不同的质数，使其和洽为n，求方案总数，可以看做是01背包
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

//普通筛法
int const SIZE = 1130;
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数

void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( isComp[i] ) continue;

        P[PCnt++] = i;
        for(int j=i*i;j<SIZE;j+=i){//i*i可能超范围
            isComp[j] = true;
        }
    }
}

int D[15][1121];//Dkin表示前i个质数选k个和为n的数量，其中i用滚动数组优化掉
void dp(){
    fill(D[0],D[0]+1121,0);
    D[0][0] = 1;
    for(int i=0;i<PCnt;++i){
        for(int n=1120;n>=P[i];--n){
            for(int k=1;k<15;++k){
                D[k][n] += D[k-1][n-P[i]];//仿照01背包，求方案数量和
            }
        }
    }
}

int main(){
    sieve();
    dp();
    int n,k;
    while(scanf("%d%d",&n,&k)&&n&&k){
        printf("%d\n",D[k][n]);
    }
    return 0;
}

