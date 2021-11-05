/*
    有N个路由构成的网络，从0往N-1发数据，一个字节一个字节的发，一共需要发S个字节
    每个链路有一个成功率。N-1位置每收到一个字节就发一个回执，回执一定成功。
    发送和应答都需要K分钟。
    问发送S个字节的时间期望是多少
    每个字节是独立的，只需要计算1个字节即可。令时间期望为T，则
    T = 2K * P + ( 1 - P ) * ( 2K + T )
    所以 T = 2K / P
    其中P是从0到N-1的最大概率
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef double weight_t;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 20010;
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
	ECnt = 1;
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

//s is the source id
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//d[i] records the shortest distance from s to i
//pre[i] records the previous node of i in the shortest path
//flag and cnt are auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[]){
	fill(d,d+vn+1,0.0);
	fill(flag,flag+vn+1,false);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	d[s] = 1.0;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t t = d[u] * Edge[next].weight;

			if ( t > d[v] ){
				d[v] = t;
				if ( !flag[v] ){
					flag[v] = true;
					q.push(v);
				}
			}
		}
	}

	return true;
}

int N,M,S,K;
void read(){
    scanf("%d%d%d%d",&N,&M,&S,&K);

    initGraph(N);

    int u,v,p;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&u,&v,&p);
        mkEdge(u+1,v+1,p/100.0);
    }
}

double D[110];
bool Flag[110];

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        spfa(1,N,D,Flag);


        printf("Case %d: %.10f\n",kase,S / D[N] * 2 * K);
    }
    return 0;
}

