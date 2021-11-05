/*
     求区间[a,b]之间的质数的个数
     区间长度最多为10万
     但a可能很大
     筛法
*/
#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

//线性筛法
int const SIZE = 65536;//一般只筛到30000+即可
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

typedef long long llt;
bool Flag[100010];

//筛[a,b]之间的质数
int proc(int a,int b){
    fill(Flag,Flag+b-a+1,false);
    for(int i=0;i<PCnt&&(llt)P[i]*P[i]<=b;++i){
        llt start = (llt)P[i] * P[i];
        if ( start < a ) start = 0 == a % P[i] ? a : (llt)a / P[i] * P[i] + P[i];
        //从start开始筛
        for(llt j=start;j<=b;j+=P[i])Flag[j-a]=true;
    }
    int ans=0;
    for(int i=a;i<=b;++i)if(!Flag[i-a])++ans;
    return 1==a?ans-1:ans;
}

int main(){
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("Case %d: %d\n",kase,proc(a,b));
    }
    return 0;
}