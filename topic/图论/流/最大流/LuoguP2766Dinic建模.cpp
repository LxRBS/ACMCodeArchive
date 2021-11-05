/**
   给定n个正整数序列，求：
   1 最长不降子序列的长度s
   2 每个元素只用一次，求能取出多少个长度为s的不降子序列
   3 头尾元素可以重复使用，问可以取出多少个不同的长度为s的不降子序列
   令Di是以i开头的最长不降子序列长度
   则Di=max{Dj+1,if Di<=Dj，同时i到j有一条边}
   每个点只能用一次，典型的拆点，中间边容量为1
   建立一个超级S和T，要保证长度为s，则需要将Di=s的那些点与S相连
   对于第3问，只需将中间边放开容量即可
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 2200;
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

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;//反向边的容量为0
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
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int A[SIZE_OF_VERTICES],D[SIZE_OF_VERTICES];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    initGraph(n+n+2);
    for(int i=1;i<=n;++i){
        A[i]=getUnsigned();
        //拆点建图，容量为1
        mkEdge(i,i+n,1);
    }

    if(1==n){
        printf("1\n1\n1\n");
        return 0;
    }

    //求D以及建图
    D[n] = 1;
    for(int i=n-1;i;--i){
        int tmp = 0;
        for(int j=i+1;j<=n;++j)if(A[i]<=A[j]){
            tmp = max(tmp,D[j]);
        }
        D[i] = tmp + 1;
    }
    //求最长
    int s = *max_element(D+1,D+n+1);
    for(int i=1;i<=n;++i){
        if(D[i]==s){
            mkEdge(n+n+1,i,1);
        }
        if(D[i]==1){//注意s可能就是1
            mkEdge(i+n,n+n+2,1);
        }
        for(int j=i+1;j<=n;++j)if(A[i]<=A[j]&&D[j]+1==D[i]){
            mkEdge(i+n,j,1);
        }
    }
    //最大流
    int ans2 = Dinic(n+n+1,n+n+2,n+n+2);
    //第1个点和第n个点可以随便用
    if(D[1]==s)mkEdge(n+n+1,1,INF),mkEdge(1,1+n,INF);
    mkEdge(n,n+n,INF);mkEdge(n+n,n+n+2,INF);
    int ans3 = Dinic(n+n+1,n+n+2,n+n+2);
    printf("%d\n%d\n%d\n",s,ans2,ans2+ans3);
    return 0;
}