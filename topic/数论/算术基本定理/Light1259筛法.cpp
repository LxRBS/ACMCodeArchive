/*
    给定n，问有多少组(a,b)满足
    a+b=n且a、b均为质数
    筛质数即可
    将标记数组开到一千万直接判断
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

//线性筛法
int const SIZE = 1E7+5;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[665000];//1E7以内的质数为664000+
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
    //freopen("1.txt","r",stdin);
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);

        int ans = 0;
        int n2 = n >> 1;
        for(int i=0;P[i]<=n2&&i<PCnt;++i)if(!isComp[n-P[i]])++ans;
        printf("Case %d: %d\n",kase,ans);
    }
    return 0;
}