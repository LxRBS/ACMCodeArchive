/*
    ����ͼ��N���㣬ָ��һ��X��
    Ҫ������N-1���㵽XȻ���ٴ�X���أ������·��
    ����N-1�����·��������Ƕ���

    ��һ����Ŀ�����·��������һ����Դ���·��
    ���߰ѱ�ȡ���������ε�Դ���·��
*/
#include <stdio.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 200100;
weight_t const INF = 1000000000;

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
	ECnt = 2;//������2���������ֳ�����ߺͷ����
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

//this is for heap
struct dijkstra_t{
    int u;
    weight_t w;
    dijkstra_t(int a,weight_t b):u(a),w(b){}
};
//����Ҫ��һ�£�ʹ�����ѣ�����Dijkstra�㷨ʵ����ʹ�õ�����С��
bool operator < (dijkstra_t const&lhs,dijkstra_t const&rhs){
    return rhs.w < lhs.w || ( lhs.w == rhs.w && rhs.u < lhs.u );
}

//s is the source
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//di records the shortest distance from s to i
//pre records the previous vertex of i in the shortest path
//flag is auxiliary array
//1����ʹ������ߣ�2����ʹ�÷����
void Dijkstra(int s,int vn,weight_t d[],bool flag[],int orient){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,INF));

    //pre[s] = 0;
    d[s] = 0;

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int v,u = head.u;
        weight_t tmp;
        flag[u] = true;

        for(int next=Vertex[u];next;next=Edge[next].next){
            if ( ((next&1)^orient) && !flag[v = Edge[next].to] && (tmp=d[u]+Edge[next].weight) < d[v] ){
            	//pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int N,M,X;
bool read(){
    if ( 3 != scanf("%d%d%d",&N,&M,&X) ) return false;

    initGraph(N);

    int a,b,w;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&w);
        mkEdge(a,b,w);
    }
    return true;
}
bool Flag[SIZE_OF_VERTICES];
weight_t D[2][SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        //���������һ�����·
        Dijkstra(X,N,D[0],Flag,1);
        //�÷������һ�����·
        Dijkstra(X,N,D[1],Flag,0);

        int ans = D[0][1] + D[1][1];
        for(int i=2;i<=N;++i)if(ans<D[0][i]+D[1][i])ans=D[0][i]+D[1][i];
        printf("%d\n",ans);
    }
    return 0;
}

