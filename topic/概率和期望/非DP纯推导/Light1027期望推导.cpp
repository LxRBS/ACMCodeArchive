/*
    有N个门，等概率的被选择。
    其中有些门选中以后，会在xi分钟后离开迷宫
    另外一些门则会在yi分钟后回到原点
    每次选择都不受上一次的影响
    问出门的平均期望时间
    设答案为E，则 E = SIGMA( Xi / n ) + SIGMA( yi/n + E )
*/

#include <stdio.h>

int N;
int A[110];

int gcd(int a,int b){
    while( b ){
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int sum = 0, cnt = 0;

        scanf("%d",&N);
        for(int i=0;i<N;++i){
            scanf("%d",A+i);
            if ( A[i] > 0 ) sum += A[i], ++cnt;
            else sum += -A[i];
        }

        printf("Case %d: ",kase);
        if ( 0 == cnt ) printf("inf\n");
        else {
            int g = gcd(sum,cnt);
            printf("%d/%d\n",sum/g,cnt/g);
        }
    }
    return 0;
}

