/**
    求次短路，如果最短路有多条，次短路就是最短路。
    首先求出最短路，然后去掉每条边，跑最短路，求最小值
*/
#include <bits/stdc++.h>
using namespace std;

typedef double weight_t;

double const EPS = 1E-4;
inline bool is0(double x){return fabs(x)<=EPS;}

//just as its names
int const SIZE_OF_VERTICES = 300;
int const SIZE_OF_EDGES = 110000;
weight_t const INF = 1E10;

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
bool spfa(int s,int vn,weight_t d[],bool flag[],int pre[],int uu,int vv){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);
	fill(pre,pre+vn+1,0);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	pre[s] = 0;
	d[s] = 0;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			if(u==uu&&v==vv||(u==vv&&v==uu)) continue;//这里改造一下

			weight_t t = d[u] + Edge[next].weight;

			if ( t < d[v] ){
				d[v] = t;
				pre[v] = u;
				if ( !flag[v] ){
					flag[v] = true;
					q.push(v);
				}
			}
		}
	}

	return true;
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int X[210],Y[210];
double dist(int idx,int jdx){
    int x = X[idx]-X[jdx];
    int y = Y[idx]-Y[jdx];
    return sqrt((double)(x*x+y*y));
}

weight_t D[210];
bool Flag[210];
int Pre[210],PPre[210];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int m = getInt();
    for(int i=1;i<=n;++i)X[i]=getInt(),Y[i]=getInt();
    initGraph(n);
    while(m--){
        int a = getInt();
        int b = getInt();
        mkEdge(a,b,dist(a,b));
    }
    spfa(1,n,D,Flag,Pre,0,0);
    if(is0(D[n]-INF)){
        puts("-1");
        return 0;
    }
    //删除每条边，跑最短路
    weight_t ans = INF;
    for(int next,i=n;Pre[i];i=Pre[i]){
        //将i和pre边删除
        spfa(1,n,D,Flag,PPre,i,Pre[i]);
        ans = min(ans,D[n]);
    }
    if(ans>=INF-EPS){
        puts("-1");
        return 0;
    }
    printf("%.2f\n",ans);
    return 0;
}
