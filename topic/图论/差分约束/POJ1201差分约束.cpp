/*
    给定ai、bi、ci
    表示区间[ai,bi]内至少要选ci个整点
    问满足条件最少要选多少个点

    令xi表示区间[0,i]要选定的数量，则
    xbi - x(ai-1) >= ci
    注意到还有一个约束：0<=xi<=i+1
    这个约束实际等价于：0 <= x(i+1)-xi <= 1
    要求最小值等价于求最长路
*/

#include <stdio.h>
#include <queue>
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
int const SIZE_OF_VERTICES = 50010;
int const SIZE_OF_EDGES = 250000;
weight_t const INF = -2000000000;

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

//
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

//s is the source id
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//d[i] records the shortest distance from s to i
//pre[i] records the previous node of i in the shortest path
//flag and cnt are auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[],int cnt[]){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);
	fill(cnt,cnt+vn+1,0);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	d[s] = 0;
	cnt[s] = 1;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t t = d[u] + Edge[next].weight;

			if ( t > d[v] ){
				d[v] = t;
				if ( !flag[v] ){
					++cnt[v];
					if ( cnt[v] > vn ) return false;

					flag[v] = true;
					q.push(v);
				}
			}
		}
	}

	return true;
}

struct _t{
    int h;
    int idx;
}H[SIZE_OF_VERTICES];
bool operator < (_t const&lhs,_t const&rhs){
    return lhs.h < rhs.h;
}

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(50002);//从-1到50000，每个+2映射为图的顶点标号

    int a,b,c;
    for(int i=0;i<N;++i){
        a = getUnsigned()+2;
        b = getUnsigned()+2;
        c = getUnsigned();

        //xbi - x(ai-1) >= ci
        mkEdge(a-1,b,c);
    }

    for(int i=1;i<50002;++i){
        // 0 <= x(i+1)-xi <= 1
        mkEdge(i+1,i,-1);
        mkEdge(i,i+1,0);
    }
    return true;
}

int D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ){
        spfa(1,50002,D,Flag,Cnt);
        printf("%d\n",D[50002]);
    }
    return 0;
}
