/*
    无向图，问添加多少条边可以使得任意两点有两条不同的路径
    实际上就是问添加多少条边使得变成双连通图
    求出所有边双连通分量，然后缩点，原图变成一个树
    把所有叶子两两相连即可，也就是(叶子数+1)/2
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 5100;
int const SIZE_OF_EDGES = 30000;

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

//双向边
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int Stack[SIZE_OF_VERTICES],StackTop;//辅助栈
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
bool IsBridge[SIZE_OF_EDGES];//边i是否为桥
int Belong2BiCC[SIZE_OF_VERTICES];//点i属于第Bi个双连通分量，从1开始
int BiCCCnt;//双连通分量的数量

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    //入栈
    Stack[StackTop++] = u;

    //对u的每一条边
    int v,son=0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( (v=Edge[next].to) != pre ){
        if ( 0 == Dfn[v] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            /*//桥
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    if ( Low[u] == Dfn[u] ){//u和其上的点在同一个分量中
        Belong2BiCC[u] = ++BiCCCnt;
        do{
            Belong2BiCC[v=Stack[--StackTop]] = BiCCCnt;
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+vn+1,0);
    //fill(IsBridge,IsBridge+ECnt,false);
    BiCCCnt = StackTop = 0;

    TimeStamp = 0;

    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
}

int Deg[SIZE_OF_VERTICES],IV[SIZE_OF_VERTICES];//记录缩点以后的度数即关联点，Deg加到2就不用再管了 
int main(){
    //freopen("1.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    initGraph(n);
    int a,b;
    for(int i=0;i<m;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }

    Tarjan(n);

    for(int i=2;i<ECnt;++i){
        if ( (a=Belong2BiCC[Edge[i].from]) == (b=Belong2BiCC[Edge[i].to]) ) continue;

        if ( 0 == IV[a] ){
            ++Deg[a];IV[a] = b;
        }else if ( 1 == Deg[a] && b != IV[a] ){
            ++Deg[a];
        }

        if ( 0 == IV[b] ){
            ++Deg[b];IV[b] = a;
        }else if ( 1 == Deg[b] && a != IV[b] ){
            ++Deg[b];
        }
    }

    int ans = 0;
    for(int i=1;i<=BiCCCnt;++i)if(1==Deg[i])++ans;
    printf("%d\n",(ans+1)>>1);
    return 0;
}
