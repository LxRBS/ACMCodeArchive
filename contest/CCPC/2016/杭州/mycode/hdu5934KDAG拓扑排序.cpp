/*
   平面上有N个炸弹，有各自的起爆费用
   如果爆炸范围内有其他炸弹，则这些炸弹也会引爆
   问引爆所有炸弹所需的最小费用
   显然如果A能引爆B，则A到B有一条边
   节点A引爆后，其所有可达后继都会引爆，因此要引爆入度为0的点
   但也有可能是一个强连通分量，因此要缩点，得到DAG
   再把所有入度为0的点的费用加起来
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[1100*1100];
int ECnt;
int Vertex[1100];

inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}
int Stack[1100], StackTop;//辅助栈
bool IsInStack[1100];

int TimeStamp;
int Dfn[1100], Low[1100];

int SCCCnt;//连通分量的总数量
int Belong[1100];//第i个顶点属于第Belong[i]个强连通分量
int SCCSize[1100];//第i个连通分量的大小，下标从1开始

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //入栈
    IsInStack[ Stack[StackTop++] = u ] = true;

    //对u的每一条边
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //找到一个SCC
    if ( Dfn[u] == Low[u] ){
        ++SCCCnt;
        do{
            IsInStack[ v = Stack[--StackTop] ] = false;
            ++SCCSize[ Belong[v] = SCCCnt ];
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(IsInStack,IsInStack+vn+1,false);
    fill(SCCSize,SCCSize+vn+1,0);

    TimeStamp = SCCCnt = StackTop = 0;

    for(int i=1;i<=vn;++i){
        if ( 0 == Dfn[i] ){
            dfs(i);
        }
    }
}

int Cost[1100];
int X[1100],Y[1100],R[1100];
int N;

//idx到jdx有一条边
bool f(int idx,int jdx){
    long long int x = X[idx] - X[jdx];
    long long int y = Y[idx] - Y[jdx];
    long long int r = R[idx];
    return x*x+y*y<=r*r;
}

void read(){
    initGraph(N = getInt());

    for(int i=1;i<=N;++i){
        X[i] = getInt();
        Y[i] = getInt();
        R[i] = getInt();
        Cost[i] = getInt();
        for(int j=1;j<i;++j){
            if(f(i,j)) mkEdge(i,j);
            if(f(j,i)) mkEdge(j,i);
        }
    }
}

int Degree[1100];
int Ans[1100];
int proc(){
    //求强连通分量
    Tarjan(N);

    //求每一个强连通分量的最小权值
    fill(Ans,Ans+SCCCnt+1,1000000);
    for(int i=1;i<=N;++i){
        if(Cost[i]<Ans[Belong[i]]){
            Ans[Belong[i]] = Cost[i];
        }
    }
    //建立KDAG，记录度数即可
    int from,to;
    fill(Degree,Degree+SCCCnt+1,0);
    for(int i=2;i<ECnt;++i){
        //from到to有一条边
        if ( (from=Belong[Edge[i].from]) != (to=Belong[Edge[i].to]) ){
                ++Degree[to];
        }
    }
    //将入度为0的累加
    int ret = 0;
    for(int i=1;i<=SCCCnt;++i){
        if(0==Degree[i]){
            ret += Ans[i];
        }
    }
    return ret;
}

int main(){
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case #%d: %d\n",kase,proc());
    }
    return 0;
}
