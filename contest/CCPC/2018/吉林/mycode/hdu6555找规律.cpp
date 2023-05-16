/**
  [x]表示小于x的最大整数
  给定n，问SIGMA(n/i)的奇偶性
  n小于等于10亿
  把100以内的暴力算一下，发现每一段偶数有如下规律：
  起点是4×i×i，长度是4×i+1
  例如第1段偶数就是从4到8，第2段偶数就是从16到24
  所以，对给定n如果是偶数需要满足
  4×i×i≤n≤4×i×i+4×i
  有整数解，即[(sqrt(1+n)-1)/2,sqrt(n)/2]之间恰好有整数
*/

#include <stdio.h>
#include <math.h>

char const A[2][100] = {
    "odd",
    "even"
};

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);
        int t1 = (sqrt(1.0+n)-1)*0.5;
        int t2 = sqrt((double)n)*0.5;
        printf("Case %d: %s\n",kase,A[4*t1*(t1+1)==n||1==t2-t1]);
    }
    return 0;
}
