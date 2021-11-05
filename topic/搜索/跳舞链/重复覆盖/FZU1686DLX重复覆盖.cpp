/*
    大矩阵上有若干个怪物
    每次攻击可以攻击到一个小矩阵，
    问最少要攻击多少次

    把每一次攻击看作是一行，该行中有若干个1表示源矩阵中的怪物
    最少选择多少行可以把所有的1都盖住
    重复覆盖
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int SIZE = 300;
const int INF = 1000000000;

//上下左右
int Up[SIZE*SIZE],Down[SIZE*SIZE],Right[SIZE*SIZE],Left[SIZE*SIZE];
//所在行列
int Rth[SIZE*SIZE],Cth[SIZE*SIZE];
//每一行的头指针
int RHead[SIZE];
//每一列元素的个数
int CCnt[SIZE];
int toUsed;
int Ans;

//初始化，01矩阵的大小为rows×cols
void init(int rows,int cols){
    fill(CCnt,CCnt+cols+1,0);
    for(int i = 0;i <= cols;++i){
        Up[i] = Down[i] = i;//上下都指向自己
        Left[i+1] = i;
        Right[i] = i+1;
    }
    Right[cols] = 0; Left[0] = cols;
    toUsed = cols;

    RHead[0] = 0;
    fill(RHead+1,RHead+rows+2,-1);
    Ans = INF;
}

//将位置(row,cols)设为1
inline void link(int row,int col){
    ++CCnt[Cth[++toUsed]=col];//指定所在列，并将该列元素个数加1
    Rth[toUsed] = row;        //指定所在行

    Down[toUsed] = Down[col];
    Up[Down[col]] = toUsed;
    Up[toUsed] = col;
    Down[col] = toUsed;  //将节点插入列链表，本质就是链表的头插入

    if(RHead[row] < 0){
        RHead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    }else{
        int const&h = RHead[row];
        Right[toUsed] = Right[h];
        Left[Right[h]] = toUsed;
        Right[Left[toUsed] = h] = toUsed;//将节点插入行链表，本质就是链表的头插入
    }
}

//删除node节点的同列节点
void remove(int node){
    for(int i = Down[node];i != node;i = Down[i])
        Left[Right[i]] = Left[i], Right[Left[i]] = Right[i];
}

//恢复node节点的同列节点
void resume(int node){
    for(int i = Up[node];i != node;i = Up[i])
        Left[Right[i]] = Right[Left[i]] = i;
}

bool Flag[SIZE] = {false};

//评价函数，至少还要删多少次，
int f(){
    int ret = 0;
    //标题行上仍然存在的节点置为true
    for(int i = Right[0]; i != 0;i = Right[i])Flag[i] = true;

    //对于标题行中的每一个节点
    for(int i = Right[0]; i != 0;i = Right[i])if(Flag[i]){
        ret++;
        Flag[i] = false;

        //同一列的行全部置为false，不计数
        for(int j = Down[i];j != i;j = Down[j])for(int k = Right[j];k != j;k = Right[k])
            Flag[Cth[k]] = false;
    }

    return ret;
}

//d已经删除的行数
void dlx(int d){
    if(d + f() >= Ans)return;
    if(Right[0] == 0){
        if(d < Ans)Ans = d;
        return;
    }

    //找列元素最少的列
    int col,tmp = INF;
    for(int i=Right[0];i!=0;i=Right[i]){
        if ( CCnt[i] < tmp && 1 == (tmp = CCnt[col=i]) ) break;
    }

    //对第col列的每一行
    for(int i = Down[col];i != col;i = Down[i]){
        //删除i所在行的全部节点
        remove(i);
        for(int j = Right[i];j != i;j = Right[j])remove(j);

        dlx(d+1);

        //恢复
        for(int j = Left[i];j != i;j = Left[j])resume(j);
        resume(i);
    }
}

int N,M,NN,MM;
int A[20][20];
//int id[20][20];

bool read(){
    if ( 2 != scanf("%d%d",&N,&M) ) return false;

    int sz = 0;
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        scanf("%d",A[i]+j);
        if( 1 == A[i][j] ) A[i][j] = (++sz);
    }
    scanf("%d%d",&NN,&MM);

    init((N-NN+1)*(M-MM+1),sz);

    sz = 1;
    for(int i=0;i<=N-NN;++i)for(int j=0;j<=M-MM;++j){
        for(int x=i,n=i+NN;x<n;++x)for(int y=j,m=j+MM;y<m;++y){
            if(A[x][y]) link(sz,A[x][y]);
        }
        sz++;
    }

    return true;
}

int main(){
    while( read() ){
        dlx(0);
        printf("%d\n",Ans);
    }
    return 0;
}
