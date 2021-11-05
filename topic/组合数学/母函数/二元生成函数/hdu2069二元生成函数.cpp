//求方案总数，除了限制了硬币总数，与UVA674完全一样
//既要满足金额数，又要满足硬币数量
//使用二元生成函数,x^i*y^j表示金额为i、硬币数量为j
//1分的生成函数为SIGMA{ x^i * y^i }
//5分的生成函数为SIGMA{ x^(5i) * y^i }
//...

//该题数据较小，其实可以暴力

#include <cstdio>
#include <cstring>
#include <numeric>
#include <algorithm>
using namespace std;

int A[251][101];//Aij表示x^i*y^j的系数
int B[251][101];//临时数组
int S[251];
void init(){
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));

    //首先是1分的系数
    for(int i=0;i<101;++i) A[i][i] = 1;

    //依次是5/10/25/50
    int c[] = {5,10,25,50};
    for(int i=0;i<4;++i){
        //x的系数
        for(int j=0;j<251;++j){
            //y的系数
            for(int k=0;k<101;++k){
                //下一个生成函数的每一项
                for(int w=0;j+w*c[i]<251&&w+k<101;++w){
                    B[j+w*c[i]][k+w] += A[j][k];
                }
            }
        }

        //倒腾
        memcpy(A,B,sizeof(B));
        memset(B,0,sizeof(B));
    }

    //预处理求和
    for(int i=0;i<251;++i) S[i] = accumulate(A[i],A[i]+101,0);
}
int main(){
    init();

    int n;
    while( EOF != scanf("%d",&n) ){
        printf("%d\n",S[n]);
    }
    return 0;
}
