#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int const DIMENSION = 2;
int const DIM_SQUARE = DIMENSION * DIMENSION;//4乘4的数独
char Input[4][5];//原始输入

//以下为DLX
int const ROWSIZE = DIM_SQUARE*DIM_SQUARE*DIM_SQUARE + 10;
int const COLSIZE = DIM_SQUARE*DIM_SQUARE*4+10;
//上下左右
int Up[ROWSIZE*COLSIZE],Down[ROWSIZE*COLSIZE],Left[ROWSIZE*COLSIZE],Right[ROWSIZE*COLSIZE];
//所在行列
int Rth[ROWSIZE*COLSIZE],Cth[ROWSIZE*COLSIZE];
int toUsed;

//每一行的头指针
int RHead[ROWSIZE];
//每一列元素的个数
int CCnt[COLSIZE];
//结果
int Ans[ROWSIZE];
int ACnt;
//分别记录数独上对应的行列数
int MRow[ROWSIZE],MCol[ROWSIZE],Su[ROWSIZE];

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

    int tmp = ROWSIZE;
    int col;
    for(int i=Right[0];i!=0;i=Right[i]){
        //printf("(%d,%d)\n",i,CCnt[i]);
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

vector<int> V789;
vector<int> Candidate[DIM_SQUARE*DIM_SQUARE];
int TotalRow = 0;

//r行c列有一个数k，r、c、k的范围均为[0,DIM_SQUARE)
inline void set(int r,int c,int k){
    MRow[TotalRow] = r;
    MCol[TotalRow] = c;
    Su[TotalRow] = k;//记录数据

    link(TotalRow,1+r*DIM_SQUARE+c);//表明r行c列有一个数
    link(TotalRow,DIM_SQUARE*DIM_SQUARE+1+r*DIM_SQUARE+k);//表明第r行放置了数k
    link(TotalRow,DIM_SQUARE*DIM_SQUARE*2+1+c*DIM_SQUARE+k);//表明第c列放置了数k
    link(TotalRow,DIM_SQUARE*DIM_SQUARE*3+1+(r/DIMENSION*DIMENSION+c/DIMENSION)*DIM_SQUARE+k);//表明对应宫放置了数k
    ++TotalRow;
}

//构建01矩阵
void build(){
    TotalRow = 1;
    fill(Candidate,Candidate+DIM_SQUARE*DIM_SQUARE,vector<int>());

    for(int i=0;i<DIM_SQUARE;++i){
        for(int j=0;j<DIM_SQUARE;++j){
            int idx = i * DIM_SQUARE + j;
            if ('*'!=Input[i][j]){
                int k = Input[i][j] - '1';
                set(i,j,k);
            }else{
                vector<int>&v = Candidate[idx];
                v.assign(V789.begin(),V789.end());
                //搜索行
                for(int c=0;c<DIM_SQUARE;++c){
                    if ('*'!=Input[i][c]){
                        int const kk = Input[i][c] - '1';
                        for(vector<int>::iterator it=v.begin();it!=v.end();++it){
                            if ( kk == *it ){
                                v.erase(it);
                                break;
                            }
                        }
                    }
                }

                if ( 1 == v.size() ){
                    set(i,j,v.front());
                    continue;
                }

                //搜索列
                for(int r=0;r<DIM_SQUARE;++r){
                    if ('*'!=Input[r][j]){
                        int const kk = Input[r][j] - '1';
                        for(vector<int>::iterator it=v.begin();it!=v.end();++it){
                            if ( kk == *it ){
                                v.erase(it);
                                break;
                            }
                        }
                    }
                }

                if ( 1 == v.size() ){
                    set(i,j,v.front());
                    continue;
                }

                for(vector<int>::iterator it=v.begin();it!=v.end();++it){
                    set(i,j,*it);
                }
            }
        }
    }


}

int main(){
    //freopen("1.txt","w",stdout);
    for(int i=0;i<DIM_SQUARE;++i) V789.push_back(i);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        //input
        scanf("%s",Input[0]);scanf("%s",Input[1]);
        scanf("%s",Input[2]);scanf("%s",Input[3]);

        init(DIM_SQUARE*DIM_SQUARE*DIM_SQUARE,DIM_SQUARE*DIM_SQUARE*4);
        build();
        //disp("row");
        dlx();

        for(int i=0;i<ACnt;++i){
            int& t = Rth[Ans[i]];
            Input[MRow[t]][MCol[t]] = Su[t] + '1';
        }

        printf("Case #%d:\n%s\n%s\n%s\n%s\n",kase,Input[0],Input[1],Input[2],Input[3]);

    }
    return 0;
}

