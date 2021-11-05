#include <bits/stdc++.h>
using namespace std;

int N;
int Pos[20];
int Ans = 0;
bool Flag[4][40] = {false};

//depth代表还有depth个皇后要放置
void dfs(int depth){
    //第N-depth个皇后直接放在N-depth行
    if(0==depth){
        ++Ans;
        if(Ans <= 3){
            //输出
            printf("%d",Pos[0]);
            for(int i=1;i<N;++i)printf(" %d",Pos[i]);
            printf("\n");
        }
        return;
    }

    for(int i=0;i<N;++i){
        //检查列、主对角线、次对角线
        if(Flag[1][i]||Flag[2][N-depth-i+N]||Flag[3][N-depth+i]) continue;

        //变化
        Pos[N-depth] = i + 1;
        Flag[1][i] = Flag[2][N-depth-i+N] = Flag[3][N-depth+i] = true;
        //递归
        dfs(depth-1);
        //还原
        Flag[1][i] = Flag[2][N-depth-i+N] = Flag[3][N-depth+i] = false;
    }
}

int main(){
    scanf("%d",&N);
    dfs(N);
    printf("%d\n",Ans);
    return 0;
}
