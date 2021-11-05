/*
    有向图上，每个点有一个权值
    求一条从1出发的路径使得点权和最大

    如果是DAG的话：
    Di = max{Dj|ji右边} +W[i]

    首先求出核心DAG，然后即可
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef long long weight_t;

//just as its names
int const SIZE_OF_VERTICES = 20010;
int const SIZE_OF_EDGES = 200110;

struct edge_t{
	int from,to;
	//weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}


inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int Stack[SIZE_OF_VERTICES], StackTop;//辅助栈
bool IsInStack[SIZE_OF_VERTICES];

int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
int Low2Node[SIZE_OF_VERTICES];//Low2Node[i]表示Low值为i的节点编号
int SCCCnt;//连通分量的总数量
int Belong[SIZE_OF_VERTICES];//第i个顶点属于第Belong[i]个强连通分量
int SCCSize[SIZE_OF_VERTICES];//第i个连通分量的大小，下标从1开始
vector<int> TopoOrder;//拓扑排序的结果
weight_t W[SIZE_OF_VERTICES],WW[SIZE_OF_VERTICES];

void dfs(int u){
    Low2Node[Dfn[u] = Low[u] = ++TimeStamp] = u;

    //对u的每一条边
    int v, tmplow, &low = Low[u];
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < low ) low = Low[v];
        }else if (!Belong[Low2Node[tmplow=Low[v]]] && tmplow < low){
            low = tmplow;
        }
    }

    //找到一个SCC
    if ( Dfn[u] == low ){
        ++SCCCnt;
        while(Low[v=Stack[StackTop-1]]>=low){
            ++SCCSize[Belong[v]=SCCCnt];
            --StackTop;
            IsInStack[v] = false;
            Low[v] = low;
            WW[SCCCnt] += W[v];
        }
        if(Belong[u]!=SCCCnt) ++SCCSize[Belong[u]=SCCCnt], WW[SCCCnt]+=W[u];
        //TopoOrder.push_back(u); //记录拓扑排序的结果
    }else if(!IsInStack[u]){
        IsInStack[Stack[StackTop++] = u] = true;
    }
}

//Nuutila算法求SCC
//Tarjan算法改进，减少了节点的入栈次数
void Nuutila(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(IsInStack,IsInStack+vn+1,false);
    fill(SCCSize,SCCSize+vn+1,0);
    fill(Belong,Belong+vn+1,0);
    fill(WW,WW+vn+1,0LL);

    TimeStamp = SCCCnt = 0;
    Stack[StackTop=1] = 0;
    Low[0] = -10000;//栈里放一个绝对最小值
    //TopoOrder.clear(); //记录拓扑排序，有需要可以用

    for(int i=1;i<=vn;++i){
        if ( 0 == Dfn[i] ){
            dfs(i);
        }
    }
}

int N,M;

bool read(){
    if ( scanf("%d%d",&N,&M) == EOF ) return false;

    initGraph(N);
    for(int i=1;i<=N;++i)scanf("%lld",W+i);

    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }
    return true;

}

vector<int> KDag[SIZE_OF_VERTICES];
weight_t D[SIZE_OF_VERTICES];
int Queue[SIZE_OF_VERTICES],Head,Tail;
bool Flag[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        Nuutila(N);

        //建立核心DAG
        for(int i=1;i<=SCCCnt;++i) KDag[i].clear();
        int from,to;
        for(int i=2;i<ECnt;++i){
            if ( (from=Belong[Edge[i].from]) != (to=Belong[Edge[i].to]) ){
                KDag[from].push_back(to);
            }
        }

        int u,v;
        //DP
        fill(D,D+SCCCnt+1,0LL);
        fill(Flag,Flag+SCCCnt+1,false);
        Flag[ u = Belong[1] ] = true;
        D[u] = WW[u];

        Head = Tail = 0;
        Queue[Head++] = u;

        while( Head != Tail ){
            Flag[ u = Queue[Tail++] ] = false;
            for(vector<int>::const_iterator it=KDag[u].begin();it!=KDag[u].end();++it){
                int v = *it;
                D[v] = max(D[v],D[u]+WW[v]);
                if ( !Flag[v] ) Flag[ Queue[Head++] = v ] = true;
            }
        }

        printf("%lld\n",*max_element(D+1,D+SCCCnt+1));
    }
    return 0;
}
