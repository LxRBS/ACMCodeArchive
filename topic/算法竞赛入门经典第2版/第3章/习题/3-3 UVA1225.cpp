#include <cstdio>

int const SIZE = 10010;
int A[10][SIZE] = {0};//A[i][n]表示前n个整数中、数字i一共出现了多少次
void init(){          //一口气把所有可能的答案都算出来
    for(int i=1;i<SIZE;++i){
        for(int j=0;j<10;++j){   //根据i-1的答案计算i的答案
            A[j][i] = A[j][i-1];
        }

        int n = i;
        while(n){
            ++A[n%10][i];
            n /= 10;
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);

    init();
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n;
        scanf("%d",&n);

        printf("%d",A[0][n]);  //注意输出的格式，每两个数之间用一个空格，而最后一个数之后没有空格
        for(int i=1;i<10;++i)printf(" %d",A[i][n]);
        printf("\n");
    }
    return 0;
}
