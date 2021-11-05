/**
   m个实验，n台仪器，每个实验要用到其中一些仪器
   每个仪器的费用是ci，每个实验的收益是pi
   问如何做实验能够让净收益最大
   这是一个最大权闭合子图问题
   左边为正权点，右边为负权点，求最大点权和
   S到正权点有一条边，容量为权
   负权点到T有条边，容量为负负权
   正负权点之间有一条边，容量为无穷大
   最大点权和=所有正权之和－最大流
   最后输出方案，输出与s相连的点即可
   即最后一次分层图上大于0的点
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

int main(){
    //freopen("1.txt","r",stdin);
    int m,n,vn,s,t;
    int sum = 0;
    string str;
    cin>>m>>n;getline(cin,str);
    s = ( vn = t = n + m + 2 ) - 1;
    initGraph(vn);
    for(int i=1;i<=m;++i){//m个实验
        getline(cin,str);
        stringstream ss(str);
        int a;
        ss>>a;
        sum+=a;
        mkEdge(s,i,a);
        while(ss>>a){//每个实验要用到的仪器编号
            mkEdge(i,a+m,INF);
        }
    }
    for(int i=m+1,nn=n+m;i<=nn;++i){
        int a;
        cin>>a;
        mkEdge(i,t,a);
    }
    int ret = Dinic(s,t,vn);
    //输出实验
    for(int i=1;i<=m;++i)if(__L[i]>0){
        cout<<i<<" ";
    }
    cout<<endl;
    //输出仪器
    for(int i=1+m,nn=m+n;i<=nn;++i)if(__L[i]>0){
        cout<<i-m<<" ";
    }
    cout<<endl;
    cout<<sum-ret<<endl;
    return 0;
}
