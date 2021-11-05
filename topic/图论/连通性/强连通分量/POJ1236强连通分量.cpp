/*
    ���ɸ�ѧУ��������ͼ
    ÿ��ѧУ�õ�һ������󣬾�������ѧУ����
    �ʳ�ʼ��������ٸ�ѧУ�������
    ����������Ӽ����ߣ�ʹ��������һ��ѧУ���ţ�����Ҷ��ܹ���
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 20010;

struct edge_t{
	int from,to;
	weight_t weight;
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

int Stack[SIZE_OF_VERTICES], StackTop;//����ջ
bool IsInStack[SIZE_OF_VERTICES];

int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];

int SCCCnt;//��ͨ������������
int Belong[SIZE_OF_VERTICES];//��i���������ڵ�Belong[i]��ǿ��ͨ����
int SCCSize[SIZE_OF_VERTICES];//��i����ͨ�����Ĵ�С����1��ʼ

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //��ջ
    IsInStack[ Stack[StackTop++] = u ] = true;

    //��u��ÿһ����
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //�ҵ�һ��SCC
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

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(N);
    int b;
    for(int i=1;i<=N;++i){
        while( scanf("%d",&b),b ){
            mkEdge(i,b);
        }
    }
    return true;

}

int G[110][110];
int InDeg[110],OutDeg[110];
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        //�������SCC
        Tarjan(N);

        //����SCC������ͼ����DAG
        memset(G,0,sizeof(G));
        memset(InDeg,0,sizeof(InDeg));
        memset(OutDeg,0,sizeof(OutDeg));

        int from,to;
        for(int i=2;i<ECnt;++i){
            if ( (from=Belong[Edge[i].from]) != (to=Belong[Edge[i].to]) && 0 == G[from][to] ){
                G[from][to] = 1;
                ++OutDeg[from];
                ++InDeg[to];
            }
        }

        int ans1 = 0,ans2 = 0;
        for(int i=1;i<=SCCCnt;++i){
            if ( 0 == InDeg[i] ) ++ans1;
            if ( 0 == OutDeg[i] ) ++ans2;
        }

        printf("%d\n%d\n",0==ans1?1:ans1,1==SCCCnt?0:max(ans1,ans2));
    }
    return 0;
}
