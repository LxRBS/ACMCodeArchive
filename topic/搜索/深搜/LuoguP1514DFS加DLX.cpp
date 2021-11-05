/**
   N×M的矩形。在第一行选取若干个点建立蓄水池
   水可自动的向低处流去，目标是使得最后一行有水
   问最后一行是否能全部都有水，如果是，问最少的蓄水池数量
   如果否，问没有水的格子最少是多少
   以每个目标为起点进行搜索，看能否连接到源头，很容已得到否定情况下的答案
   对于肯定情况下，就是求一个最小覆盖
   也可以用DP，因为每一个源头覆盖的目标必然是连续的
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


const int SIZE = 501;
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

//初始化，01矩阵的大小为rows×cols,1 based
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

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M;
int A[510][510];
int CurCol;
bool Used[501][500];
bool IsOK;

void dfs(int r,int c){
    Used[r][c] = true;

    if(0==r){//找到一个源头
        //第c个源头可以覆盖第CurCol个目标
        link(c+1,CurCol+1);
        IsOK = true;
    }

    for(int i=0;i<4;++i){
        int nr = r + DR[i];
        int nc = c + DC[i];
        if(0<=nr&&nr<N&&0<=nc&&nc<M&&!Used[nr][nc]&&A[r][c]<A[nr][nc]){
            dfs(nr,nc);
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    M = getUnsigned();
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        A[i][j] = getUnsigned();
    }

    init(M,M);

    int cnt = 0;
    //从终点开始搜索，看能从哪里引水
    for(CurCol=0;CurCol<M;++CurCol){
        memset(Used,0,sizeof(Used));
        IsOK = false;
        dfs(N-1,CurCol);
        if(!IsOK) ++cnt;
    }

    if(cnt){
        printf("0\n%d\n",cnt);
        return 0;
    }

    dlx(0);
    printf("1\n%d\n",Ans);

    return 0;
}
