/*
    ��N���ӹ��豸��ÿ���豸����ĳ�ְ��Ʒ�������ĳ�ְ��Ʒ
    ������Ʒ��P�����ֹ��ɣ����Ʒ����������ĳЩ���ֹ���
    ÿ���ӹ��豸ͬʱ���ӹ�Q����Ʒ
    ����ô���ţ�ʹ��������ˮ�߼ӹ���󣬲����������
    ��������
*/
#include <stdio.h>
#include <limits.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;
weight_t const INF = 2000000000;

//just as its names
int const SIZE_OF_VERTICES = 500;
int const SIZE_OF_EDGES = 50000;

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
	ECnt = 2;//ECnt��2��ʼ����ָ����0��ʾ���������^1����
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;//����ߵ�����Ϊ0
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int L[SIZE_OF_VERTICES];//���ͼ
int Queue[SIZE_OF_VERTICES];//����
//�������������Դs����t�Ĳ��ͼ��nΪ��������
bool bfs(int s,int t,int n){
	fill(L+1,L+n+1,-1);

	int u,v,head,tail = 0;
	L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//Ѱ�һ��в����ı�
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //����в�����û�б��������ģ����ǲ��
			if ( Edge[p].weight > 0 && -1 == L[v = Edge[p].to] ){
                L[Queue[tail++]=v] = L[u] + 1;
			}
		}
	}

	return -1 != L[t];
}

//�ڲ��ͼ����������·���������Ͼ��������������������
//��������Ǹ���֮����������Сֵ
//uΪ��ǰ�ڵ㣬cfΪ�Ѿ��������Ľ����tΪ���
weight_t dfs(int u,weight_t cf,int t){
	if ( u == t ) return cf;

	weight_t tf = 0;//tf��¼u����һ����ܿ�������
	for(int p=Vertex[u];p;p=Edge[p].next){
		int v = Edge[p].to;
		weight_t c = Edge[p].weight;

		if ( L[u] + 1 == L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//����߼�ȥ��������
			Edge[p^1].weight += f;//����߼���
			tf += f;
		}
	}
	if ( 0 == tf ) L[u] = -1;//�޸Ĳ��ͼ
	return tf;
}

//Dinic�㷨��sΪԴ��tΪ�㣬nΪͼ��������
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//��һ�������ֲ�ͼ
		weight_t ans;
		//�ڶ����ڷֲ�ͼ�ϲ���һ������·���Ŀ�������
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}

int P,N;
int In[55][12],Out[55][12];
int const SOUT[12] = {0};
int const TIN[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
int S,T;//Դ��

bool f(int const out[],int const in[]){
    for(int i=1;i<=P;++i){
        if ( in[i] != 2 && in[i] != out[i] ) return false;
    }
    return true;
}

bool read(){
    if ( EOF == scanf("%d%d",&P,&N) ) return false;

    S = N + N + 1;
    initGraph(T=N+N+2);

    int q;
    for(int i=1;i<=N;++i){
        scanf("%d",&q);
        mkEdge(i,i+N,q);//���

        for(int j=1;j<=P;++j)scanf("%d",In[i]+j);
        for(int j=1;j<=P;++j)scanf("%d",Out[i]+j);
    }

    for(int i=1;i<=N;++i){
        if ( f(SOUT,In[i]) ) mkEdge(S,i,INF);
        if ( f(Out[i],TIN) ) mkEdge(i+N,T,INF);

        for(int j=i+1;j<=N;++j){
            if ( f(Out[i],In[j]) ) mkEdge(i+N,j,INF);
            if ( f(Out[j],In[i]) ) mkEdge(j+N,i,INF);
        }
    }

    return true;
}

int A[100],B[100],W[100];
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        int ret = Dinic(S,T,T);
        int v, cnt = 0;

        //������еķ����
        for(int i=1;i<=N;++i)for(int next=Vertex[i];next;next=Edge[next].next){
            if ( Edge[next].weight && N < (v=Edge[next].to) && v <= N+N && v!=i+N ){
                A[cnt] = v-N;
                B[cnt] = i;
                W[cnt++] = Edge[next].weight;
            }
        }

        printf("%d %d\n",ret,cnt);
        for(int i=0;i<cnt;++i)printf("%d %d %d\n",A[i],B[i],W[i]);
    }
    return 0;
}
