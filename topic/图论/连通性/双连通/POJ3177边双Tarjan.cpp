/*
    ����ͼ������Ӷ������߿���ʹ������������������ͬ��·��
    ʵ���Ͼ�������Ӷ�������ʹ�ñ��˫��ͨͼ
    ������б�˫��ͨ������Ȼ�����㣬ԭͼ���һ����
    ������Ҷ�������������ɣ�Ҳ����(Ҷ����+1)/2
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
bool IsBridge[SIZE_OF_EDGES];//��i�Ƿ�Ϊ��
int Belong2BiCC[SIZE_OF_VERTICES];//��i���ڵ�Bi��˫��ͨ��������1��ʼ
int BiCCCnt;//˫��ͨ����������

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    //��ջ
    Stack[StackTop++] = u;

    //��u��ÿһ����
    int v,son=0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( (v=Edge[next].to) != pre ){
        if ( 0 == Dfn[v] ){
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

int Deg[SIZE_OF_VERTICES],IV[SIZE_OF_VERTICES];//��¼�����Ժ�Ķ����������㣬Deg�ӵ�2�Ͳ����ٹ��� 
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
