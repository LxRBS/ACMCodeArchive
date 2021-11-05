/**
    一个无向图，每个点有一个权值ai。将其所有边定一个方向，改成有向图。
    最小化SIGMA(max(0, di-ai))，其中di是入度
    显然对ai比较大的点应该多加入边，而一条边的两个邻点只能选一个点进入
    建一个费用流，假设第i条边的邻点是u和v，则i到u和i到v分别有一条边，容量为1，费用为0
    S到i有一条边，容量为1费用为0
    对原图上的每个节点u，到T有2条边，分别是(au, 0)和(INF, 1)
    这样的话优先走0那条边，走完以后再走1那条边，每条边付出一个费用
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

typedef int weight_t;

int const SIZE_OF_VERTICES = 1550;//点数的最大值
int const SIZE_OF_EDGES = 15000;//边数的最大值
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int from,to;
    weight_t cap;//容量
    weight_t cost;//费用
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;

int Vertex[SIZE_OF_VERTICES];

//初始化
inline void initGraph(int n){
    ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
    fill(Vertex,Vertex+n+1,0);
}

//生成边
inline void mkEdge(int a,int b,weight_t capa,weight_t cost){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].cap = capa;
    Edge[ECnt].cost = cost;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].from = b;
    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;
    Edge[ECnt].cost = -cost;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

//s表示源，vn为顶点数量，其余为辅助数组
void spfa(int s,int vn,weight_t d[],int pre[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);
    fill(pre,pre+vn+1,0);

    queue<int> q;
    q.push(s);

    d[s] = 0;
    flag[s] = true;

    int u,v;
    weight_t tmp;
    while( !q.empty() ){
        flag[ u = q.front() ] = false;
        q.pop();

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( Edge[p].cap > 0 && ( tmp = d[u] + Edge[p].cost ) < d[ v=Edge[p].to ] ){
                d[v] = tmp;pre[v] = p;
                if ( !flag[v] ) q.push(v), flag[v] = true;
            }
        }
    }
}

//最小费用最大流，s为源，t为汇，vn为总点数
//其余为辅助数组
pair<weight_t,weight_t> mcmf(int s,int t,int vn,weight_t d[],int pre[],bool flag[]){
    weight_t miniCost = 0;
    weight_t maxFlow = 0;
    while(1){
        spfa(s,vn,d,pre,flag);
        //说明找不到增广路
        if ( INF == d[t] ) break;

        //找出该增广路上的可行流
        weight_t curFlow = INF;
        for(int p=pre[t];p;p=pre[Edge[p].from])if(curFlow>Edge[p].cap)curFlow = Edge[p].cap;

        //变动流量
        for(int p=pre[t];p;p=pre[Edge[p].from]){
            Edge[p].cap -= curFlow;
            Edge[p^1].cap += curFlow;
        }

        //更新流量和费用
        miniCost += d[t] * curFlow;
        maxFlow += curFlow;
    }

    return make_pair(maxFlow,miniCost);
}

#define mp make_pair
#define fi first
#define se second

typedef pair<int,int> pii;

int N,M,S,T;
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        initGraph(T=N+M+2);
        S = T - 1;

        /// 点到T有一条边
        for(int ai,i=1;i<=N;++i){
            mkEdge(i, T, getUnsigned(), 0);
            mkEdge(i, T, INF, 1);
        }

        /// 第i条边到节点有边
        for(int u,v,i=1;i<=M;++i){
            u = getUnsigned();
            v = getUnsigned();
            mkEdge(N+i, u, 1, 0);
            mkEdge(N+i, v, 1, 0);
        }

        /// S到第一条边有一条边
        for(int i=N+1;i<=N+M;++i){
            mkEdge(S, i, 1, 0);
        }

        pii pp = mcmf(S, T, T, D, Pre, Flag);
        printf("%d\n", pp.se);
        /// 输出每条边的朝向，边序号从2开始
        for(int u,v,i=2+4*N;i<2+4*N+4*M;i+=4){
            u = i ^ 1;     // 查看反向边比较好
            v = (i+2) ^ 1;
            if(Edge[u].cap+Edge[v].cap!=1){
                throw runtime_error("not 1");
            }
            if(Edge[u].cap){ // 说明u用了，指向u
                putchar('1');
            }else if(Edge[v].cap){
                putchar('0');
            }else{
                throw runtime_error("XXXX");
            }
        }
        puts("");
    }
    return 0;
}
