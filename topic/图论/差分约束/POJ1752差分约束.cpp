/*
    每个人至少要看到K个广告板
    第i个人能够看到[Ai,Bi]之间的广告板
    问最少要多少个广告板
    且要其中一个解
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
int const SIZE_OF_VERTICES = 20000+10;
int const SIZE_OF_EDGES = 50000;
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

int N,K;
bool read(){
    while( EOF == scanf("%d%d",&K,&N) ) return false;

    initGraph(20002);//从-10001到10000之间，+10002对应图的顶点标号

    int a,b;
    for(int i=0;i<N;++i){
        scanf("%d%d",&a,&b);
        a += 10002, b += 10002;
        if ( a > b ) swap(a,b);
        //xb - x(a-1) >= K
        mkEdge(a-1,b,min(K,b-a+1));
    }

    for(int i=1;i<20002;++i){
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
        spfa(1,20002,D,Flag,Cnt);
        printf("%d\n",D[20002]);
        for(int i=2;i<=20002;++i){
            if ( D[i] != D[i-1] ){
                printf("%d\n",i-10002);
            }
        }
    }
    return 0;
}
