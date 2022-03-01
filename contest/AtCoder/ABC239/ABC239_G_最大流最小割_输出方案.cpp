/**
 * 给定一个无向图，节点上有权。删除若干节点，使得1到N不可达
 * 删点的代价即给定的点权。问如何操作使得代价最小，要求给出方案
 * 显然是拆点最大流。对边ab，a+N到b有一条边，容量INF，b+N到a有边INF，
 * 对每个点，从a到a+N有边，容量即点权
 * 从1跑到N+N即可
 * 考虑方案输出，不能直接输出残量为0的边。
 * 因为假设输入为，1->2->3->4，则拆出来的2边和3边都跑完了。但是显然不需要全用上2和3
 * 最大流以后，从1开始做一个简单的搜索，跑出仍然和1连接的点，注意正向边反向边都要用到。
 * 然后对每个a和a+N，左边连1，右边不连的即可选为方案。
 * 由于只有100，也可以用O(V^3)的最小割算法，但是不会输出方案。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 17;
#else
int const SIZE = 210;
#endif

typedef long long int weight_t;
weight_t INF = 0x3FFFFFFFFFFFFFFF;

struct edge_t{
	int from,to;
	weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE*SIZE];
int ECnt;
int Vertex[SIZE];

inline void initGraph(int n){
	ECnt = 2;//
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int __L[SIZE];//层次图
int Queue[SIZE];//队列

bool bfs(int s,int t,int n){
	fill(__L+1,__L+n+1,-1);

	int u,v,head,tail = 0;
	__L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
			if ( Edge[p].weight > 0 && -1 == __L[v = Edge[p].to] ){
                __L[Queue[tail++]=v] = __L[u] + 1;
			}			
		}
	}

	return -1 != __L[t];
}

weight_t dfs(int u,weight_t cf,int t){
	if ( u == t ) return cf;

	weight_t tf = 0;//
	for(int p=Vertex[u];p;p=Edge[p].next){
		int v = Edge[p].to;
		weight_t c = Edge[p].weight;

		if ( __L[u] + 1 == __L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//
			Edge[p^1].weight += f;//
			tf += f;
		}
	}
	if ( 0 == tf ) __L[u] = -1;//
	return tf;
}

//
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//
		weight_t ans;
		//
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}


int N, M;
int W[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	initGraph(N+N);

	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		mkEdge(a+N, b, INF); mkEdge(b+N, a, INF);
	}

	for(int c,i=1;i<=N;++i){
		mkEdge(i, i+N, W[i] = getInt());
	}

	mkEdge(1, N+1, INF);
	mkEdge(N, N+N, INF);

	weight_t tmp = Dinic(1, N+N, N+N);
    bool flag[SIZE] = {0};
	function<void(int)> dfs = [&](int u){
        flag[u] = 1;
		for(int v,p=Vertex[u];p;p=Edge[p].next){
			// if(p&1) continue;
			if(flag[v=Edge[p].to]) continue;
            if(Edge[p].weight) dfs(v);
		}
	};
	dfs(1);
	vector<int> ans;
	for(int i=2;i<N;++i)if(flag[i]&&!flag[i+N])ans.push_back(i);
	cout<<tmp<<endl<<ans.size()<<endl;
	cout<<*ans.begin();
	for(int i=1,n=ans.size();i<n;++i)cout<<" "<<ans[i];
	cout<<endl;
    return 0;
}
