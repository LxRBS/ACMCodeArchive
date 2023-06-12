/**
   n条蛇，长度分别是1/2/3...n，问能否构成一个矩形
   要求奇数有奇数个拐弯，偶数有偶数个拐弯
   问能否成立，且给出方案。
   例如3时：
   312
   332
   4时：
   34412
   33442
   5时：
   55522
   54433
   54413
   很容易利用因子分解可知
   N是奇数时：(N+1)/2行×N列
   N是偶数时：N/2行×(N+1)列
   从2开始，如果是偶数，将其排成2列，接在后面即可
   如果是奇数，直接放在最后一行，然后再把最后一个N与左上方的数换一个位置即可
   但是按照上述规则当N==5时4是不对的，所以5及以前作为特殊值
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

char const X5[] = {
    "3 4\n1 4 1 5\n2 4 2 5 3 5\n2 2 2 3 3 3 3 2\n3 1 2 1 1 1 1 2 1 3\n"
};

int N,R,C;
int main(){
    //freopen("1.txt","w",stdout);
    while(EOF!=scanf("%d",&N)){
        N&1?(R=(N+1)>>1,C=N):(R=N>>1,C=N+1);
        printf("%d %d\n",R,C);

        if(1==N){//直接打印
            printf("1 1\n");
            continue;
        }

        if(2==N){
            printf("1 1\n1 2 1 3\n");
            continue;
        }

        if(3==N){
            printf("1 1\n1 3 2 3\n2 1 2 2 1 2\n");
            continue;
        }

        if(4==N){
            printf("1 1\n1 3 2 3\n2 1 2 2 1 2\n1 4 2 4 2 5 1 5\n");
            continue;
        }

        if(5==N){
            printf("%s",X5);
            continue;
        }

        //当N为其他值时
        printf("%s",X5);
        for(int i=6;i<=N;++i){
            if(i&1){//奇数，直接塞在最后一行
                int lastr = (i+1)>>1;
                for(int j=1;j<i;++j){
                    printf("%d %d ",lastr,j);
                }
                //最后一个要与左上换位置
                printf("%d %d",lastr-1,i-1);
            }else{//偶数，放在最后2列
                int lastr = i>>1;
                //如果不是最后一个偶数，则需要把第1列最后一个数换地方
                if(i==N){//不换地方，从第1列开始打
                    printf("%d %d",lastr,i);
                    //第一列
                    for(int j=(i>>1)-1;j>=1;--j){
                        printf(" %d %d",j,i);
                    }
                    //第二列
                    for(int j=1;j<=(i>>1);++j){
                        printf(" %d %d",j,i+1);
                    }
                }else{//要换地方，从第二列开始打
                    printf("%d %d",lastr+1,i+1);
                    for(int j=(i>>1);j>=1;--j){
                        printf(" %d %d",j,i+1);
                    }
                    for(int j=1;j<(i>>1);++j){
                        printf(" %d %d",j,i);
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}