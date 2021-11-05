/*
    ������ٵı�ʹ��ͼ���ǿ��ͨ��
    ��ǿ��ͨ������Ȼ�����㣬��������DAG��
    ��DAG�ϣ������Ϊ0�ĵ�����Ϊa������Ϊ0�ĵ������Ϊb����Ϊmax(a,b)
    ע�⵱ͼ�������ǿ��ͨ�ģ���Ϊ0
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 10010;
int const SIZE_OF_EDGES = 300010;

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
int SCCSize[SIZE_OF_VERTICES];//��i����ͨ�����Ĵ�С���±��1��ʼ

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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M;
void read(){
    N = getUnsigned();
    M = getUnsigned();

    initGraph(N);
    int a,b;
    for(int i=0;i<M;++i){
        a = getUnsigned();
        mkEdge(a,getUnsigned());
    }
}

int InDeg[SIZE_OF_EDGES];
int OutDeg[SIZE_OF_EDGES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        read();
        Tarjan(N);

        //����
        fill(InDeg,InDeg+SCCCnt+1,0);
        fill(OutDeg,OutDeg+SCCCnt+1,0);
        int a,b;
        for(int i=2;i<ECnt;++i){
            if ( (a=Belong[Edge[i].from]) != (b=Belong[Edge[i].to]) ){
                ++OutDeg[a];
                ++InDeg[b];
            }
        }

        a = b = 0;
        for(int i=1;i<=SCCCnt;++i){
            if ( 0 == InDeg[i] ) ++a;
            if ( 0 == OutDeg[i] ) ++b;
        }

        printf("%d\n",1==SCCCnt?0:max(a,b));
    }
    return 0;
}
