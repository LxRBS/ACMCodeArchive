//����ͼ�������˫��ͨ���������Դ����رߣ���Ȼ����û���ر�
#include <stdio.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

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

//˫���
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

int Stack[SIZE_OF_VERTICES],StackTop;//����ջ
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
//bool IsBridge[SIZE_OF_EDGES];//��i�Ƿ�Ϊ��
bool IsVisited[SIZE_OF_EDGES];//�ߵı�����飬���ر�ʱ���ô���������ж�
int Belong2BiCC[SIZE_OF_VERTICES];//��i���ڵ�Bi��˫��ͨ��������1��ʼ
int Represent[SIZE_OF_VERTICES];//Ri��ʾ��i����˫�Ĵ���Ҳ���Ǳ����С���Ǹ���
int BiCCCnt;//˫��ͨ����������

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    //��ջ
    Stack[StackTop++] = u;

    //��u��ÿһ����
    int v,son=0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            /*//��
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    if ( Low[u] == Dfn[u] ){//u�����ϵĵ���ͬһ��������
        Represent[Belong2BiCC[u] = ++BiCCCnt] = u;
        do{
            Belong2BiCC[v=Stack[--StackTop]] = BiCCCnt;
            if ( v < Represent[BiCCCnt] ) Represent[BiCCCnt] = v;
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+vn+1,0);
    fill(IsVisited,IsVisited+ECnt,false);
    //fill(IsBridge,IsBridge+ECnt,false);
    BiCCCnt = StackTop = 0;

    TimeStamp = 0;

    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
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

    initGraph(n);
    for(int i=0;i<m;++i){
        mkEdge(getUnsigned(),getUnsigned());//������˫���
    }

    Tarjan(n);
    printf("%d\n%d",BiCCCnt,Represent[Belong2BiCC[1]]);
    for(int i=2;i<=n;++i)printf(" %d",Represent[Belong2BiCC[i]]);
    printf("\n");
    return 0;
}
