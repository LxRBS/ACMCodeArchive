#include <bits/stdc++.h>
using namespace std;

int N;
char A[110][110];
int F[256] = {0};
bool G[110][110] = {false};//为真表示ij位置的字母需要保留

bool f(int r,int c,int dr,int dc){
    //递归结束条件
    if('g'==A[r][c]) {
        G[r][c] = true;
        return true;
    }

    int nr = r + dr;
    int nc = c + dc;
    if(nr<0||nr>=N||nc<0||nc>=N)return false;

    bool flag = false;
    if(F[A[r][c]] == A[nr][nc]) flag = f(nr,nc,dr,dc);
    if(flag) G[r][c] = true;
    return flag;
}

int main(){
    //freopen("1.txt","r",stdin);
    F['y']='i';
    F['i']='z';
    F['z']='h';
    F['h']='o';
    F['o']='n';
    F['n']='g';
    F['g']=1;

    scanf("%d",&N);
    for(int i=0;i<N;++i)scanf("%s",A[i]);

    //先做一个预处理
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if(!F[A[i][j]])A[i][j] = '*';

    //对每一个点做8个方向的搜索
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if('y'==A[i][j]){
        bool flag = false;
        flag |= f(i,j,-1,0);//上
        flag |= f(i,j,1,0);//下
        flag |= f(i,j,0,-1);//左
        flag |= f(i,j,0,1);//右
        flag |= f(i,j,-1,-1);//左上
        flag |= f(i,j,1,-1);//左下
        flag |= f(i,j,-1,1);//右上
        flag |= f(i,j,1,1);//右下
        G[i][j] = flag;
    }

    //做一个后处理
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if(!G[i][j])A[i][j]='*';
    //输出
    for(int i=0;i<N;++i)printf("%s\n",A[i]);
    return 0;
}
