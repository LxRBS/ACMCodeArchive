/**
 * 给定NMAB，要求构造一个N×M的01矩阵，使得每一行都有A个1，每一列都有B个1，其余全是0
 * 首先N*A要等于M*B，否则不可能。
 * 拆点，每一行两个点，中间边容量为A；每一列拆出来，中间边容量为B
 * 起点要每一行有边，容量无穷；列到终点有边，无穷。
 * 每一行到每一列有边，容量为1
 * 跑出的最大流要等于N*A，然后检查正向边或者反向边均可。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 500;
int const SIZE_OF_EDGES = 50000;

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

int N, M, A, B;

void proc(int vn){
    if(N*A != M*B){
        puts("NO");
        return;        
    }
    int ret = Dinic(vn-1, vn, vn);
    if(ret != N*A || ret != M*B){
        puts("NO");
        return;
    }

    puts("YES");

    char a[55][55] = {0};
    for(int i=0;i<N;++i)fill(a[i], a[i]+M, '0');

    for(int v,u=N+1,i=0;i<N;++i,++u){
        for(int p=Vertex[u];p;p=Edge[p].next){
            if(p&1) continue; // 反向边
            if(!Edge[p].weight){
                v = Edge[p].to;
                a[i][v-N-N-1] = '1';
            }
        } 
    }

    for(int i=0;i<N;++i)puts(a[i]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        A = getUnsigned();
        B = getUnsigned();

        int vn = N + N + M + M + 2;
        initGraph(vn);
        for(int i=1;i<=N;++i){
            mkEdge(vn-1, i, 0x3F3F3F3F);
            mkEdge(i, i+N, A);
        }
        for(int i=N+N+1;i<=N+N+M;++i){
            mkEdge(i, i+M, B);
            mkEdge(i+M, vn, 0x3F3F3F3F);
        }
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
            mkEdge(N+i, N+N+j, 1);
        }
        proc(vn);
    }
    return 0;
}
