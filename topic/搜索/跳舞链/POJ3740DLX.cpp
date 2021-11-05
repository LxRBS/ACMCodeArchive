//精确覆盖
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int const SIZE = 1100;

//上下左右
int Up[SIZE*SIZE],Down[SIZE*SIZE],Left[SIZE*SIZE],Right[SIZE*SIZE];
//所在行列
int Rth[SIZE*SIZE],Cth[SIZE*SIZE];
int toUsed;

//每一行的头指针
int RHead[SIZE];
//每一列元素的个数
int CCnt[SIZE];
//结果
int Ans[SIZE];
int ACnt;

/////////////////////////////////显示
void dispNode(int node){
    printf("%d:(%d,%d)(%d,%d,%d,%d)\n",node,Rth[node],Cth[node],Up[node],Down[node],Left[node],Right[node]);
}
void dispRow(int row){
    int h = RHead[row];
    dispNode(h);
    for(int r=Right[h];r!=h;r=Right[r]){
        dispNode(r);
    }
}
void dispCol(int col){
    dispNode(col);
    for(int c=Down[col];c!=col;c=Down[c]){
        dispNode(c);
    }
}
void disp(char const* p){
    printf("cross:\n");
    if ('r' == *p){
        for(int r=0;RHead[r]!=-1;++r){
            dispRow(r);
        }
    }else if ('c' == *p){
        dispNode(0);
        for(int i=Right[0];i;i=Right[i]){
            dispCol(i);
        }
    }else{
        ;
    }
}
/////////////////////////////////////////////////////////////////

//01矩阵的行列
void init(int row,int cols){
    fill(CCnt,CCnt+cols+1,0);

    for(int i=0;i<=cols;++i){
        Up[i] = Down[i] = i;//上下都指向自己
        Left[i+1] = i;
        Right[i] = i + 1;
        Cth[i] = i;//确定列
    }
    Left[0] = cols;
    Right[cols] = 0;//指回头结点
    toUsed = cols + 1;

    RHead[0] = 0;
    fill(RHead+1,RHead+row+2,-1);//-1表示头指针为空，即该行为空，多设置1个-1用于显示的时候终止条件判断

    ACnt = 0;//
}

//将列号为col的块加入行row
inline void link(int row,int col){
    ++CCnt[Cth[toUsed]=col];//指定所在列，并将该列元素个数加1

    Down[toUsed] = Down[col];
    Up[Down[col]] = toUsed;
    Up[toUsed] = col;
    Down[col] = toUsed;//将节点插入列链表，本质就是链表的头插入

    if ( RHead[row] < 0 ){
        RHead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    }else{
        int& h = RHead[row];
        Right[toUsed] = Right[h];
        Left[Right[h]] = toUsed;
        Left[toUsed] = h;
        Right[h] = toUsed;//将节点插入行链表，本质就是链表的头插入
    }

    Rth[toUsed++] = row;//记录toUsed所在的行号
}


int N,M;
bool read(){//M行N列
    if (EOF == scanf("%d%d",&M,&N)) return false;

    init(M,N);

    for(int i=1;i<=M;++i){
        for(int j=1;j<=N;++j){
            int t;
            scanf("%d",&t);
            if (t) link(i,j);
        }
    }
    return true;
}

void remove(int node){
    Right[Left[node]] = Right[node];
    Left[Right[node]] = Left[node];//将node从行链表中摘除

    for(int i=Down[node];i!=node;i=Down[i]){//往下
        for(int j=Right[i];j!=i;j=Right[j]){//往右
            Up[Down[j]] = Up[j];
            Down[Up[j]] = Down[j];//将j从列链表中摘除
            --CCnt[Cth[j]];//列元素个数减一
        }
    }
}

void resume(int node){
    Right[Left[node]] = Left[Right[node]] = node;//将node放回行链表
    for(int i=Up[node];i!=node;i=Up[i]){
        for(int j=Left[i];j!=i;j=Left[j]){
            ++CCnt[Cth[Up[Down[j]]=Down[Up[j]]=j]];//将j放回列链表，列元素个数加1
        }
    }
}

bool dlx(){
    if ( 0 == Right[0] ){//说明只剩头结点，成功
        return true;
    }

    int tmp = SIZE;
    int col;
    for(int i=Right[0];i!=0;i=Right[i]){
        if ( CCnt[i] < tmp ){
            tmp = CCnt[col=i];//找出元素个数最少的列
            if (1 == tmp) break;
        }
    }

    remove(col);//删除

    for(int i=Down[col];i!=col;i=Down[i]){
        Ans[ACnt++] = i;//可能为答案
        for(int j=Right[i];j!=i;j=Right[j]){
            remove(Cth[j]);//与i行元素有关的列全部删除
        }

        if ( dlx() ){//递归
            return true;
        }

        for(int j=Left[i];j!=i;j=Left[j]){
            resume(Cth[j]);//还原
        }
        --ACnt;//还原
    }
    resume(col);//还原
    return false;
}

int main(){
    while( read() ) {
        printf(dlx()?"Yes, I found it\n":"It is impossible\n");
    }
    return 0;
}
