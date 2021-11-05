//3148ms, it is slower than Dijkstra
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 2000010;
int const SIZE_OF_EDGES = 6000010;
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

//s is the source
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//di records the shortest distance from s to i
//pre records the previous vertex of i in the shortest path
//flag is auxiliary array
bool spfa(int s,int vn,weight_t d[],int pre[],bool flag[],int cnt[]){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);
	//fill(cnt,cnt+vn+1,0);
	//fill(pre,pre+vn+1,0);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	//pre[s] = 0;
	d[s] = 0;
	//cnt[s] = 1;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t t = d[u] + Edge[next].weight;

			if ( t < d[v] ){
				d[v] = t;
				//pre[v] = u;
				if ( !flag[v] ){
					//++cnt[v];
					//if ( cnt[v] > vn ) return false;

					flag[v] = true;
					q.push(v);
				}
			}
		}
	}

	return true;
}

int N,M,S,T;
bool Flag[SIZE_OF_VERTICES];
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

bool read(){
    scanf("%d%d",&N,&M);

    if ( 1 == N ){
        int t = INF;
        int w;
        for(int i=1;i<M;++i){
            scanf("%d",&w);
            if ( w < t ) t = w;
        }
        printf("%d\n",INF==t?0:t);
        return true;
    }

    if ( 1 == M ){
       int t = INF;
        int w;
        for(int i=1;i<N;++i){
            scanf("%d",&w);
            if ( w < t ) t = w;
        }
        printf("%d\n",t);
        return true;
    }

    S = ( N - 1 ) * ( M - 1 ) * 2 + 1;
    T = S + 1;
    initGraph(T);

    int a,b,w;
    //the first row of horizontal edges
    for(int i=1;i<=M-1;++i){
        scanf("%d",&w);
        mkEdge(T,i,w);
    }

    for(int i=2;i<N;++i){
        a = ( 2 * ( i - 1 ) - 1 ) * ( M - 1 ) + 1;
        b = a + M - 1;

        for(int j=1;j<=M-1;++j){
            scanf("%d",&w);
            mkEdge(a++,b++,w);
        }
    }

    //the last row of horizontal edges
    b = ( M - 1 ) * ( 2 * N - 3 ) + 1;
    for(int i=1;i<=M-1;++i){
        scanf("%d",&w);
        mkEdge(S,b++,w);
    }

    //vertical edges
    for(int i=2;i<=N;++i){
        b = ( 2 * i - 3 ) * ( M - 1 ) + 1;
        scanf("%d",&w);
        mkEdge(S,b,w);

        ++b;
        a = b - M;
        for(int j=1;j<M-1;++j){
            scanf("%d",&w);
            mkEdge(a++,b++,w);
        }

        scanf("%d",&w);
        mkEdge(T,a,w);
    }

    //diagonal edges
    for(int i=2;i<=N;++i){
        b = (2*i-3)*(M-1) + 1;
        a = b - M + 1;
        for(int j=1;j<=M-1;++j){
            scanf("%d",&w);
            mkEdge(a++,b++,w);
        }
    }

    //Dijkstra(S,T,D,Pre,Flag);
    spfa(S,T,D,Pre,Flag,Cnt);
    printf("%d\n",D[T]);

    return true;
}

int main()
{
    //freopen("1.txt","r",stdin);
    read();
    return 0;
}

