/*
    ����ͼ��ֻ���һ���ߣ�ʹ�üӱ��Ժ��ͼ���ŵ���������
    �����˫��ͨ�����Ժ����㣬ԭͼ���һ����
    �������Զ��������֮����ӱߣ���ʣ�µı�˫�϶����٣�Ҳ�����ŵ���������
    Ҳ�������������ֱ�����ټ�һ��
    ���رߣ����жϵ�ʱ���ܵ㣬��Ӧ��Ϊ�߿�һ���������
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 200010;
int const SIZE_OF_EDGES = 1000010<<1;

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
int Belong2BiCC[SIZE_OF_VERTICES];//��i���ڵ�Bi��˫��ͨ��������1��ʼ
int BiCCCnt;//˫��ͨ����������
bool IsVisited[SIZE_OF_EDGES];//�ߵı������

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
        Belong2BiCC[u] = ++BiCCCnt;
        do{
            Belong2BiCC[v=Stack[--StackTop]] = BiCCCnt;
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

int N,M;
bool read(){
    N = getUnsigned();
    M = getUnsigned();
    if ( 0 == N && 0 == M ) return false;

    initGraph(N);
    for(int i=0;i<M;++i){
        mkEdge(getUnsigned(),getUnsigned());//������˫���
    }
    return true;
}

int D[SIZE_OF_VERTICES];
int T;
vector<vector<int> >Tree;
void dfs(int u){
    int v;
    for(vector<int>::iterator it=Tree[u].begin();it!=Tree[u].end();++it)if(-1==D[v=*it]){
        D[v] = D[u] + 1;
        if ( D[T] < D[v] ) T = v;
        dfs(v);
    }
}

int proc(){
    Tarjan(N);
    Tree.assign(BiCCCnt+1,vector<int>());
    int a,b;
    for(int i=2;i<ECnt;++i){
        if ( (a=Belong2BiCC[Edge[i].from]) != (b=Belong2BiCC[Edge[i].to]) ){
            Tree[a].push_back(b);
            Tree[b].push_back(a);
        }
    }

    fill(D,D+BiCCCnt+1,-1);
    D[T=1] = 0;
    dfs(1);

    fill(D,D+BiCCCnt+1,-1);
    D[T] = 0;
    dfs(T);

    return BiCCCnt - D[T] - 1;
}
int main(){
    //freopen("1.txt","r",stdin);
    while(read())printf("%d\n",proc());
    return 0;
}
