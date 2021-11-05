#include <bits/stdc++.h>
using namespace std;

int N;
int Pos[20];
int Ans = 0;
bool Flag[4][40] = {false};

//depth������depth���ʺ�Ҫ����
void dfs(int depth){
    //��N-depth���ʺ�ֱ�ӷ���N-depth��
    if(0==depth){
        ++Ans;
        if(Ans <= 3){
            //���
            printf("%d",Pos[0]);
            for(int i=1;i<N;++i)printf(" %d",Pos[i]);
            printf("\n");
        }
        return;
    }

    for(int i=0;i<N;++i){
        //����С����Խ��ߡ��ζԽ���
        if(Flag[1][i]||Flag[2][N-depth-i+N]||Flag[3][N-depth+i]) continue;

        //�仯
        Pos[N-depth] = i + 1;
        Flag[1][i] = Flag[2][N-depth-i+N] = Flag[3][N-depth+i] = true;
        //�ݹ�
        dfs(depth-1);
        //��ԭ
        Flag[1][i] = Flag[2][N-depth-i+N] = Flag[3][N-depth+i] = false;
    }
}

int main(){
    scanf("%d",&N);
    dfs(N);
    printf("%d\n",Ans);
    return 0;
}
