/**
   N头牛P个牧场C条路
   N头牛分布在牧场中
   要在所有牧场中找到一个牧场，使得
   牛到达该牧场的路程总和最小
   枚举每个牧场跑一遍最短路，累加求最小值
*/
#include <bits/stdc++.h>
using namespace std;


//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 2100;
int const SIZE_OF_EDGES = 100010<<1;
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
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	d[s] = 0;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t t = d[u] + Edge[next].weight;

			if ( t < d[v] ){
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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


weight_t D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cow[510];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int p = getUnsigned();
    int c = getUnsigned();
    for(int i=1;i<=n;++i)Cow[i]=getUnsigned();
    initGraph(p);
    while(c--){
        int a = getUnsigned();
        int b = getUnsigned();
        mkEdge(a,b,getUnsigned());
    }
    int ans = INF;
    for(int i=1;i<=p;++i){
        spfa(i,p,D,Flag);
        int sum = 0;
        for(int j=1;j<=n;++j)sum+=D[Cow[j]];
        ans = min(ans,sum);
    }
    printf("%d\n",ans);
    return 0;
}
