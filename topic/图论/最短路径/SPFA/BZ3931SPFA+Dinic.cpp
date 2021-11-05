//先跑最短路，再根据最短路的结果建图跑Dinic
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef long long int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 5000;
int const SIZE_OF_EDGES = 500000;
weight_t const INF = 1LL<<60;

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

//建立单向边
inline void mkEdge(int a,int b,weight_t w){
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
//flag is auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[]){
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


int L[SIZE_OF_VERTICES];//层次图
int Queue[SIZE_OF_VERTICES];//队列
//建立残留网络从源s到汇t的层次图，n为顶点总数
bool bfs(int s,int t,int n){
	fill(L+1,L+n+1,-1);

	int u,v,head,tail = 0;
	L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//寻找还有残量的边
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //如果有残量又没有被搜索过的，则标记层次
			if ( Edge[p].weight > 0 && -1 == L[v = Edge[p].to] ){
                L[Queue[tail++]=v] = L[u] + 1;
			}
		}
	}

	return -1 != L[t];
}

//在层次图上搜索增广路径，本质上就是搜索可以增广的流量
//这个流量是各层之间流量的最小值
//u为当前节点，cf为已经搜索出的结果，t为汇点
weight_t dfs(int u,weight_t cf,int t){
	if ( u == t ) return cf;

	weight_t tf = 0;//tf记录u往下一层的总可行流量
	for(int p=Vertex[u];p;p=Edge[p].next){
		int v = Edge[p].to;
		weight_t c = Edge[p].weight;

		if ( L[u] + 1 == L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//正向边减去可行流量
			Edge[(p&1)?p+1:p-1].weight += f;//反向边加上
			tf += f;
		}
	}
	if ( 0 == tf ) L[u] = -1;//修改层次图
	return tf;
}

//Dinic算法，s为源，t为汇，n为图顶点总数
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//第一步建立分层图
		weight_t ans;
		//第二步在分层图上查找一条增广路径的可行流量
		while( ans = dfs(s,INF,t) )
			ret += ans;
	}
	return ret;
}


int N,M;
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int A[SIZE_OF_EDGES],B[SIZE_OF_EDGES];
weight_t AB[SIZE_OF_EDGES];
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N);

    weight_t d;
    for(int i=0;i<M;++i){
        scanf("%d%d%lld",A+i,B+i,AB+i);
        mkEdge(A[i],B[i],AB[i]);mkEdge(B[i],A[i],AB[i]);
    }

    //最短路
    spfa(N,N,D,Flag);

    initGraph(N+N);
    //如果边在最短路上，则加入
    for(int i=0;i<M;++i){
        if ( D[A[i]] + AB[i] == D[B[i]] ){
            mkEdge(B[i]+N,A[i],INF);
            mkEdge(A[i],B[i]+N,0LL);
        }else if ( D[B[i]] + AB[i] == D[A[i]] ){
            mkEdge(A[i]+N,B[i],INF);
            mkEdge(B[i],A[i]+N,0LL);
        }
    }

    //对每个点的吞吐量进行拆点
    for(int i=1;i<=N;++i){
        scanf("%lld",&d);
        mkEdge(i,i+N,1==i||N==i?INF:d);
        mkEdge(i+N,i,0LL);
    }

    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    read();
    printf("%lld\n",Dinic(1,N+N,N+N));
    return 0;
}
