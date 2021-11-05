/*
    给定M条信息
    P A B X：表示A在B北边X距离
    V A B：表示A在B北边，距离至少为1
    问这M条消息整体是否可靠
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
int const SIZE_OF_EDGES = 500000;
weight_t const INF = 2000000000;

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

int N,M;
bool read(){
    while( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N+1);//

    int a,b,x;
    char cmd[5];

    for(int i=0;i<M;++i){
        scanf("%s%d%d",cmd,&a,&b);
        if ( 'P' == *cmd ){
            x = getUnsigned();
            //A - B == x等价于A-B<=X且A-B>=X
            mkEdge(b,a,x);
            mkEdge(a,b,-x);
        }else{
            //A-B>=1
            mkEdge(a,b,-1);
        }
    }

    //建立超级源点
    for(int i=1;i<=N;++i){
        mkEdge(N+1,i,0);
    }

    return true;
}

int D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ){
        printf(spfa(N+1,N+1,D,Flag,Cnt)?"Reliable\n":"Unreliable\n");
    }
    return 0;
}
