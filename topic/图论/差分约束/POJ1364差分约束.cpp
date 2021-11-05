/*
    给定一个序列ai
    再给定一些条件ai,n,o,k，其中o是小于号或者大于号
    表示 ai + a(i+1) + ... + a(i+n) o k
    问所有条件是否满足
    很明显的差分约束
    令 Si = a1 + a2 + ... + ai
    条件等价于：Sn - S(i-1) o k
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
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 10000;
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
    N = getUnsigned();
    if ( 0 == N ) return false;
    M = getUnsigned();

    initGraph(N+2);//从0到N，每个+1映射为图的顶点标号

    int a,n,k;
    char o[5];
    for(int i=0;i<M;++i){
        scanf("%d%d%s%d",&a,&n,o,&k);
        ++a;

        if ( 'g' == *o ){//相当于S(a+n)-S(a-1) > k，等价于S(a-1)-S(a+n) <= -k-1
            mkEdge(a+n,a-1,-k-1);
        }else{//相当于S(a+n)-S(a-1) < k
            mkEdge(a-1,a+n,k-1);
        }
    }
    
    //建立超级源点
    for(int i=1;i<=N+1;++i) mkEdge(N+2,i,0);
    return true;
}

int D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ){
        printf(spfa(N+2,N+2,D,Flag,Cnt)?"lamentable kingdom\n":"successful conspiracy\n");
    }
    return 0;
}
