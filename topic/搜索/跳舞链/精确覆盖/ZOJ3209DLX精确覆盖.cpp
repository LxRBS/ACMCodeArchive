/*
    给定一个大的长方形
    再给定若干个小长方形，
    问最少选择多少个小长方形，可以恰好覆盖大长方形
    精确覆盖
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLS = 1010;
int const SIZE_OF_ROWS = 510;
int const INF = 1000000000;

//上下左右
int Up[SIZE_OF_ROWS*SIZE_OF_COLS];
int Down[SIZE_OF_ROWS*SIZE_OF_COLS];
int Right[SIZE_OF_ROWS*SIZE_OF_COLS];
int Left[SIZE_OF_ROWS*SIZE_OF_COLS];
//节点i所在的行列
int Rth[SIZE_OF_ROWS*SIZE_OF_COLS];
int Cth[SIZE_OF_ROWS*SIZE_OF_COLS];
//行链表的头指针
int RHead[SIZE_OF_ROWS];
//每一列的元素的个数
int CCnt[SIZE_OF_COLS];

int toUsed;
int Ans;

//初始化DLX矩阵的标题行，1 based
void init(int rows,int cols){
    fill(CCnt,CCnt+cols+1,0);

    for(int i=0;i<=cols;++i){
        Up[i] = Down[i] = i;//上下都指向自己
        Right[Left[i+1] = i] = i+1;
        Cth[i] = i;         //确定列
    }

    Right[Left[0] = cols] = 0;
    toUsed = cols;

    fill(RHead+1,RHead+rows+2,-1);
    Ans = -1;
}

//将位置(row,col)设为1
inline void link(int row,int col){
    Rth[++toUsed] = row;
    ++CCnt[Cth[toUsed]=col];//确定行列

    Up[Up[Down[toUsed] = Down[col]] = toUsed] = col;
    Down[col] = toUsed;//将节点插入列链表，本质就是链表的头插入

    if( RHead[row] < 0 ){
        RHead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    }else{
        int const & h = RHead[row];
        Left[Left[Right[toUsed] = Right[h]] = toUsed] = h;
        Right[h] = toUsed;//将节点插入列链表，本质就是链表的头插入
    }
}

void remove(int node){
    Left[Right[Left[node]] = Right[node]] = Left[node];//将node从行链表中摘除

    //对每一个与node同列的节点i
    for(int i=Down[node];i!=node;i=Down[i]){
        //对每一个与节点i同行的节点j
        for(int j=Right[i];j!=i;j=Right[j]){
            Down[Up[Down[j]] = Up[j]] = Down[j];//将j从列链表中摘除
            --CCnt[Cth[j]];
        }
    }
}

void resume(int node){
    Left[Right[node]] = Right[Left[node]] = node;
    for(int i=Up[node];i!=node;i=Up[i])for(int j=Left[i];j!=i;j=Left[j])
        ++CCnt[ Cth[ Up[Down[j]] = Down[Up[j]] = j ] ];
}

//d是当前删除的行数
void dlx(int d){
    if(Ans != -1 && Ans <= d)return;

    if(Right[0] == 0){
        Ans = d;
        return;
    }

    int col, tmp = INF;
    //找到列元素最少的列
    for(int i=Right[0];i!=0;i=Right[i])
        if( CCnt[i] < tmp && 1 == ( tmp = CCnt[col=i] ) ) break;

    remove(col);

    //从第col列中，选择某一节点所在行进行删除
    for(int i=Down[col];i!=col;i=Down[i]){
        for(int j=Right[i];j!=i;j=Right[j])remove(Cth[j]);
        dlx(d+1);
        for(int j=Left[i];j!=i;j=Left[j])resume(Cth[j]);
    }

    resume(col);
}

int N,M,P;
void read(){
    scanf("%d%d%d",&N,&M,&P);

    init(P,N*M);

    int x1,y1,x2,y2;
    for(int i=1;i<=P;++i){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        for(int x=x1;x<x2;++x)for(int y=y1;y<y2;++y){
            link(i,y*N+x+1);
        }
    }
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        dlx(0);
        printf("%d\n",Ans);
    }
    return 0;
}
