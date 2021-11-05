/**
   数均大于1
   A集合有m个数，B集合有n个数
   每次从AB各取1个且不互质
   问最多能取多少对？
   表面上可以用二分匹配，
   但是确定边的过程就需要n^2log(value)，超时
   将质因子求出来设为pi
   ai到pi有一条边，pi到bi有一条边
   再设定一个虚拟ST，跑最大流
   1000w以内的质数有66w+
   开启O2优化可过，或者把图的点数弄少一点
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 720000;
int const SIZE_OF_EDGES = 2520000;


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

//线性筛法
int const SIZE = 1E7 + 2;
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[700000];//P[i]为第i个素数，i从0开始，1000w以内的质数是66w+
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
int Index[SIZE];
void sieve(){
    for(long long int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[Index[i]=PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    //首先筛质数
    sieve();
    int vn,s,t;
    int nofkase = getUnsigned();
    while(nofkase--){
        int m = getUnsigned();
        int n = getUnsigned();
        int a,tmp = n + m;
        int tmp2 = tmp + tmp + 1;
        //建图
        initGraph(vn=n+n+m+m+PCnt+2);
        s = (t=vn) - 1;
        //读入并且连边
        for(int i=1;i<=m;++i){
            a = getUnsigned();
            for(int j=0;j<PCnt&&P[j]*P[j]<=a;++j){
                if(0==a%P[j]){
                    do a/=P[j];while(0==a%P[j]);
                    //i到Pj有一条边
                    mkEdge(i+tmp,j+tmp2,1);
                }
            }
            if(a!=1){//a也是一个质因子
                mkEdge(i+tmp,Index[a]+tmp2,1);
            }
            //拆点
            mkEdge(i,i+tmp,1);
            //S到i有一条边
            mkEdge(s,i,1);
        }
        for(int i=m+1,nn=n+m;i<=nn;++i){
            a = getUnsigned();
            for(int j=0;j<PCnt&&P[j]*P[j]<=a;++j){
                if(0==a%P[j]){
                    do a/=P[j];while(0==a%P[j]);
                    //Pj到i有一条边
                    mkEdge(j+tmp2,i,1);
                }
            }
            if(a!=1)mkEdge(Index[a]+tmp2,i,1);
            //拆点
            mkEdge(i,i+tmp,1);
            //i到t有一条边
            mkEdge(i+tmp,t,1);
        }

        printf("%d\n",Dinic(s,t,vn));
    }
    return 0;
}
