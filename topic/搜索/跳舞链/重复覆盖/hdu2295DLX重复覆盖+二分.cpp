/*
    N个城市M个可能的雷达站位置，
    但是最多只能建造K个雷达
    问雷达的最短探测半径，使得N个城市都在范围之内

    将问题改成判定性问题：
    对于给定的半径R，能否用最多K个雷达覆盖所有城市

    将雷达当做行，城市当作列
    第i个雷达能够覆盖第j个城市，表示(i,j)为1
    然后做一个重复覆盖，看最少要多少行可以覆盖整个列
    如果这个答案小于等于K即表示该半径可以

    最后做一个二分搜索
    半径1000显然是答案，0显然不是答案，找一个满足条件的最小值
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

double const EPS = 1E-9;
inline bool is0(double x){return -EPS<x&&x<EPS;}
//x<y返回-1，x==y返回0，x>y返回1
inline int cmp(double x,double y){
    if ( is0(x-=y) ) return 0;
    return x > EPS ? 1 : -1;
}

int const SIZE = 60;
int const INF = 1000000;

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

inline double dist2(double x1,double y1,double x2,double y2){
    double x = x1 - x2;
    double y = y1 - y2;
    return x * x + y * y;
}

int N,M,K;
double XC[60],YC[60];
double XR[60],YR[60];
bool read(){
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<=N;++i)scanf("%lf%lf",XC+i,YC+i);
    for(int i=1;i<=M;++i)scanf("%lf%lf",XR+i,YR+i);
    return true;
}

//radius为雷达的探测半径
bool check(double radius){
    //初始化十字链表
    init(M,N);//行代表雷达，列代表城市

    radius *= radius;
    //对每一个雷达，看在半径radius的情况下，能够覆盖哪些城市
    for(int i=1;i<=M;++i){
        for(int j=1;j<=N;++j){
            if ( 1 != cmp(dist2(XR[i],YR[i],XC[j],YC[j]),radius) ){
                link(i,j);
            }
        }
    }

    //搜索
    dlx(0);

    return Ans <= K;
}

double proc(){
    double left = 0.0, right = 1000.0, mid;
    do{
        mid = left + ( right - left ) * 0.5;
        if ( check(mid) ) right = mid - EPS;
        else left = mid + EPS;
    }while( right - left > EPS );
    return left;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        printf("%.6f\n",proc());
    }
    return 0;
}

