/**
   无向图求最小点割，即最少删除多少个点后剩下的点不连通
   图规模在50个点
   对每个点拆点，然后枚举ST，取最小值
   注意ST本身的容量为INF，其他点为1
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 120;
int const SIZE_OF_EDGES = 2520000;
int const INF = 0x3F3F3F3F;

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
	ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
	fill(Vertex,Vertex+n+1,0);
}

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

int __L[SIZE_OF_VERTICES];//层次图
int Queue[SIZE_OF_VERTICES];//队列
//建立残留网络从源s到汇t的层次图，n为顶点总数
bool bfs(int s,int t,int n){
	fill(__L+1,__L+n+1,-1);

	int u,v,head,tail = 0;
	__L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//寻找还有残量的边
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //如果有残量又没有被搜索过的，则标记层次
			if ( Edge[p].weight > 0 && -1 == __L[v = Edge[p].to] ){
                __L[Queue[tail++]=v] = __L[u] + 1;
			}
		}
	}

	return -1 != __L[t];
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

		if ( __L[u] + 1 == __L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//正向边减去可行流量
			Edge[p^1].weight += f;//反向边加上
			tf += f;
		}
	}
	if ( 0 == tf ) __L[u] = -1;//修改层次图
	return tf;
}

//Dinic算法，s为源，t为汇，n为图顶点总数
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//第一步建立分层图
		weight_t ans;
		//第二步在分层图上查找一条增广路径的可行流量
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}

vector<vector<int> > Vec;

int f(int idx,int jdx,int n){
    int vn = n + n;
    initGraph(vn);
    int s = idx+1, t = jdx+n+1;
    //建图
    for(int i=1;i<=n;++i){
        //拆点
        mkEdge(i,i+n,1);
        vector<int>const&v = Vec[i-1];
        for(vector<int>::const_iterator it=v.begin();it!=v.end();++it){
            mkEdge(i+n,*it+1,INF);
        }
    }
    mkEdge(s,s+n,INF);
    mkEdge(t-n,t,INF);
    return Dinic(s,t,vn);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    int a,b,n,m,nofkase = getUnsigned();
    while(nofkase--){
        Vec.assign(n=getUnsigned(),vector<int>());
        m = getUnsigned();
        for(int i=0;i<m;++i){
            a = getUnsigned();
            Vec[a].push_back(b=getUnsigned());
            Vec[b].push_back(a);
        }
        //特判
        if(0==m){
            if(1==n)puts("1");
            else puts("0");
            continue;
        }
        int ret = INF;
        for(int i=0;i<n;++i)for(int j=i+1;j<n;++j){
            ret = min(ret,f(i,j,n));
        }
        printf("%d\n",ret>=INF?n:ret);
    }
    return 0;
}
