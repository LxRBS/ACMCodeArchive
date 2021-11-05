/*
    N头牛按顺序站成一排
    每一头牛都有喜欢名单，与喜欢的牛的距离不超过给定值
    每一头牛都有讨厌名单，与讨厌的牛的距离不小于给定值
    问1到N的最大距离
*/

#include <stdio.h>
#include <queue>
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
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 50000;
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

			if ( t < d[v] ){
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

int N,ML,MD;
bool read(){
    if ( EOF == scanf("%d%d%d",&N,&ML,&MD) ) return false;

    initGraph(N);

    for(int i=1;i<N;++i){
        //必须满足 x(i+1)-xi >= 0
        mkEdge(i+1,i,0);
    }

    int a,b,d;
    for(int i=0;i<ML;++i){
        a = getUnsigned();
        b = getUnsigned();
        d = getUnsigned();

        //相当于 xb - xa <= d
        mkEdge(a,b,d);
    }

    for(int i=0;i<MD;++i){
        a = getUnsigned();
        b = getUnsigned();
        d = getUnsigned();

        //相当于 xb - xa >= d， 即 xa - xb <= -d
        mkEdge(b,a,-d);
    }
    return true;
}

int D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        bool b = spfa(1,N,D,Flag,Cnt);

        if ( !b ){
            printf("-1\n");
        }else if ( INF == D[N] ){
            printf("-2\n");
        }else{
            printf("%d\n",D[N]);
        }
    }
    return 0;
}
