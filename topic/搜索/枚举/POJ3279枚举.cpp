/*
    M×N的格子，每个格子有黑白两色
    初始有一个状态
    每翻一个格子会同时翻动其四邻域
    问怎么翻才能将所有格子都变成白色
    如果有多解，输出字典序小的

    高斯消元法可以判断解的数量，但是很难确定字典序小的解
    实际上格子是相互关联的
    如果能确定第一行是如何翻转的，那么下面每一行的翻转都确定了
    所以穷举第一行的所有可能的翻转情况
    使用状态压缩来表示翻转情况
*/

#include <stdio.h>
#include <string.h>

int M,N;
int A[17][17];
int B[17][17];
int C[17][17];
int Ans;

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

void flip(int r,int c){
    A[r][c] ^= 1;
    for(int i=0;i<4;++i){
        int dr = r + DR[i];
        int dc = c + DC[i];
        if ( 0 <= dr && dr < M && 0 <= dc && dc < N ) A[dr][dc] ^= 1;
    }
}

void proc(int status){
    //把B拷贝到A
    memcpy(A,B,sizeof(B));

    int tmp[17][17] = {0};

    int cnt = 0;

    //首先处理第0行
    for(int i=0;i<N;++i){
        if ( (1<<i) & status ){
            flip(0,i);
            tmp[0][i] = 1;
            ++cnt;
        }
        if ( Ans <= cnt ) return;
    }

    //1~M-1行
    for(int i=1;i<M;++i){
        //每一列
        for(int j=0;j<N;++j){
            if ( A[i-1][j] ){
                flip(i,j);
                tmp[i][j] = 1;
                ++cnt;
            }
        }
        if ( Ans <= cnt ) return;
    }

    //检查最后一行
    for(int i=0;i<N;++i)if(A[M-1][i]) return;
    Ans = cnt;
    memcpy(C,tmp,sizeof(tmp));
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&M,&N);
    for(int i=0;i<M;++i)for(int j=0;j<N;++j)scanf("%d",B[i]+j);

    //对每一个状态i，1代表翻转
    //搜索的顺序就符合字典序
    Ans = 3000;
    for(int i=0;i<(1<<N);++i){
        proc(i);
    }

    //输出答案
    if ( 3000 == Ans ){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    //printf("%d\n",Ans);
    for(int i=0;i<M;++i){
        printf("%d",C[i][0]);
        for(int j=1;j<N;++j)printf(" %d",C[i][j]);
        putchar('\n');
    }
    return 0;
}
