/**
   最少添加多少条边使得为强连通图
   首先求出KDAG，然后求出入度和出度为零的数量即可
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair

typedef pair<int, int> pii;
struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 20100;
int const SIZE_OF_EDGES = 300010;

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
        }
        if(Belong[u]!=SCCCnt) ++SCCSize[Belong[u]=SCCCnt];
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
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int InDeg[SIZE_OF_VERTICES],OutDeg[SIZE_OF_VERTICES];
int main(){
    //freopen("1.txt","r",stdin);
    while(2==scanf("%d%d",&N,&M)){
        initGraph(N);
        for(int a,i=0;i<M;++i){
            a = getUnsigned();
            mkEdge(a, getUnsigned());
        }

        Nuutila(N);

        if(1==SCCCnt){
            puts("0");
            continue;
        }
        //求出KDAG，实际上不用求，只要求零度即可
        fill(InDeg,InDeg+SCCCnt+1,0);
        fill(OutDeg,OutDeg+SCCCnt+1,0);
        //for(int i=1;i<=SCCCnt;++i)Kdag[i].clear();
        for(int a,b,i=2;i<ECnt;++i){
            if((a=Belong[Edge[i].from])!=(b=Belong[Edge[i].to])){
                ++InDeg[b];++OutDeg[a];
            }
        }

        int acnt = 0, bcnt = 0;
        for(int i=1;i<=SCCCnt;++i){
            if(!InDeg[i]) ++acnt;
            if(!OutDeg[i]) ++bcnt;
        }
        printf("%d\n",max(acnt, bcnt));
    }
    return 0;
}
