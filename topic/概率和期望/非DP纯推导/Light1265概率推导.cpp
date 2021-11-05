/*
    有t个老虎，d个鹿，再加上你。
    每次随机选2个东西。
    如果是老虎和你，你死了。
    如果是老虎和鹿，鹿死了。
    如果是老虎和老，都死了。
    如果是鹿和鹿，nothing happens
    如果是你和鹿，你可以根据如何让生存机会最大来决定是否杀死鹿
    问，最后生存的概率是多少。

    实际上生存与否只与老虎的数量有关，奇数个老虎肯定完蛋，偶数个老虎则有一定机会生存，生存几率就是老虎死光的概率

*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
using namespace std;

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int t,d;
        scanf("%d%d",&t,&d);
        if ( t & 1 ){
            printf("Case %d: 0\n",kase);
            continue;
        }

        double ans = 1.0;
        for(int i=t;i;i-=2){
            ans *= (double)(i-1) / ( i + 1 );
        }
        printf("Case %d: %.10f\n",kase,ans);
    }
    return 0;
}

