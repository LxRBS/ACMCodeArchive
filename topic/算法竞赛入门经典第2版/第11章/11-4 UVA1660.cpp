//��������ͼ������С��
//��ÿ�����������ҵ㣬֮��������Ϊ1�ı����ӣ�ԭ������ΪINF
//�����������С��
//���ǲ�֪����������2���㲻��ͨ�������Ҫö��

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <vector>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

weight_t const INF = 100000000;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 30000;

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
	ECnt = 2;//Cnt��2��ʼ����ָ����0��ʾ���������^1����
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
	Edge[ECnt].weight = 0;
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

int N,M;
vector<pair<int,int> >Vec;

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N+N);

    for(int i=1;i<=N;++i)mkEdge(i,i+N,1);

    Vec.clear();
    int a,b;
    for(int i=0;i<M;++i){
        scanf(" (%d,%d)",&a,&b);
        ++a,++b;
        mkEdge(a+N,b,INF);
        mkEdge(b+N,a,INF);//ԭ��ת��Ϊ2����
        Vec.push_back(make_pair(a,b));
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        if ( 0 == N || 1 == N ){
            printf("%d\n",N);
            continue;
        }

        if ( 0 == M ){
            printf("0\n");
            continue;
        }

        int ret = INF;

        for(int i=2;i<=N;++i){
            initGraph(N+N);

            for(int j=1;j<=N;++j)mkEdge(j,j+N,1);

            for(vector<pair<int,int> >::iterator it=Vec.begin();it!=Vec.end();++it){
                int a = it->first, b = it->second;
                mkEdge(a+N,b,INF);
                mkEdge(b+N,a,INF);//ԭ��ת��Ϊ2����
            }

            int t = Dinic(1+N,i,N+N);
            if ( t < ret ) ret = t;
        }
        printf("%d\n",ret==INF?N:ret);
    }
    return 0;
}
