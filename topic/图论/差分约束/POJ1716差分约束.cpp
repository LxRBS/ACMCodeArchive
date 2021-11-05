/*
    给定若干个区间[a,b]
    问每个区间都至少选择2个点，一共最少要多少个点

    令xi为[0,i]包含的点数
    xb - x(a-1) >= 2
    此外：0 <= x(i+1)-xi <= 1
    求最小值等价于最长路，同POJ1201
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
int const SIZE_OF_VERTICES = 10000+10;
int const SIZE_OF_EDGES = 100000;
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

int N,M;
bool read(){
    while( EOF == scanf("%d",&N) ) return false;

    initGraph(10002);//从-1到10000，每个+2映射为图的顶点标号

    int a,b;
    for(int i=0;i<N;++i){
        a = getUnsigned()+2;
        b = getUnsigned()+2;
        //xb-x(a-1)>=2
        mkEdge(a-1,b,2);
    }
    for(int i=1;i<10002;++i){
        //0 <= x(i+1)-xi <= 1
        mkEdge(i,i+1,0);
        mkEdge(i+1,i,-1);
    }
    return true;
}

int D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ){
        spfa(1,10002,D,Flag,Cnt);
        printf("%d\n",D[10002]);
    }
    return 0;
}
