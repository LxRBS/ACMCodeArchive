/**
    求割点，模板题
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE_OF_VERTICES = 20010;
int const SIZE_OF_EDGES = 220010;

struct edge_t{
    int from,to;
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

inline void initGraph(int n){
    ECnt = 2;
    fill(Vertex,Vertex+n+1,0);
}

//双向边
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int TimeStamp;
int Dfn[SIZE_OF_VERTICES],Low[SIZE_OF_VERTICES];
int AddBlocks[SIZE_OF_VERTICES];//ABi表示删除i点之后多出来的块数
bool IsBridge[SIZE_OF_EDGES];//边i是否为桥
bool IsCut[SIZE_OF_VERTICES];//点i是否为割点
bool IsVisited[SIZE_OF_EDGES];//边的标记数组，有重边时有用
int BridgeCnt;//桥的数量

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    int v,son = 0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            //*
            //桥
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
                ++BridgeCnt;
            }
            //*/

            //*
            //符合割点的条件2
            if ( u != pre && Dfn[u] <= Low[v] ){
                IsCut[u] = true;
                ++AddBlocks[u];
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //符合割点的条件1
    if ( u == pre && son > 1 ) IsCut[u] = true;
    if ( u == pre ) AddBlocks[u] = son - 1;
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(AddBlocks,AddBlocks+vn+1,0);
    fill(IsCut,IsCut+vn+1,false);
    fill(IsBridge,IsBridge+ECnt,false);
    fill(IsVisited,IsVisited+ECnt,false);
    TimeStamp = BridgeCnt = 0;

    for(int i=1;i<=vn;++i)if(0==Dfn[i])dfs(i,i);
}


int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    int n = getUnsigned();
    int m = getUnsigned();
    while(m--)mkEdge(getUnsigned(),getUnsigned());
    Tarjan(n);

    printf("%d\n",accumulate(IsCut+1,IsCut+n+1,0));
    for(int i=1;i<=n;++i)if(IsCut[i])printf("%d ",i);
    printf("\n");
    return 0;
}
