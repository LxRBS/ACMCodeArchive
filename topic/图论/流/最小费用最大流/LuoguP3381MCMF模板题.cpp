/**
    最小费用最大流，模板题
*/
#include <bits/stdc++.h>
using namespace std;


typedef int weight_t;

int const SIZE_OF_VERTICES = 6500;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    int s = getUnsigned();
    int t = getUnsigned();

    initGraph(n);
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        int w = getUnsigned();
        mkEdge(a,b,w,getUnsigned());
    }
    pair<int,int> ans = mcmf(s,t,n,D,Pre,Flag);
    printf("%d %d\n",ans.first,ans.second);
    return 0;
}
