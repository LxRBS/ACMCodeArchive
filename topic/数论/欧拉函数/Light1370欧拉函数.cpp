/*
    竹子的价格等于phi(竹子的长度)
    phi是欧拉函数
    每个人有一个lucky number

    为每个人买一根柱子
    同时要求花费大于等于该人的幸运数字

    问N个人最少要花费多少

    定理：欧拉函数大于等于x的数就是x+1后的第一个质数
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//线性筛法
int const SIZE = 1000100;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int main(){
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int a,n;
        scanf("%d",&n);

        long long int ans = 0;
        for(int i=0;i<n;++i){
            scanf("%d",&a);
            pair<int*,int*> pp = equal_range(P,P+PCnt,a+1);
            ans += *pp.first;
        }

        printf("Case %d: %lld Xukha\n",kase,ans);
    }
    return 0;
}
