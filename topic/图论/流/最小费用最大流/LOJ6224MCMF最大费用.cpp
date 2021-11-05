/**
    一个网格，条边上有一个权值
    有若干个机器人可以从某些点出发，然后某些点作为终点
    机器人只能向右或者向上走
    问最多能够获得的权值和是多少
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef llt weight_t;
typedef pair<int, weight_t> pii;

int const SIZE_OF_VERTICES = 100010;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
weight_t const INF = 2000000000000000LL;

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

int VN;
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

llt const M3 = 1000000000LL;

int main(){
    //freopen("1.txt","r",stdin);
    int a = getUnsigned();
    int b = getUnsigned();
    int p = getUnsigned();
    int q = getUnsigned();

    ///初始化
    initGraph(VN=(p+1)*(q+1)+2);
    int s = VN - 1, t = VN; //起点终点

    ///图中的点从水平开始编号
    ///1,2,3,...,q+1
    ///(q+1)+1,(q+1)+2,...,(q+1)+q+q
    ///(q+1)*p+1,(q+1)*p+2,...,(q+1)*p+q+1

    ///栅格中水平边的权值，一共是(p+1)*q个
    for(int i=0;i<p+1;++i){
        ///每行q个整数
        for(int j=1;j<=q;++j){
            int w = getUnsigned();
            int idx = (q+1)*i+j;
            mkEdge(idx,idx+1,1,-w);
            mkEdge(idx,idx+1,10000,0);
        }
    }

    ///栅格中竖直边的权值，一共是(q+1)*p个
    for(int i=1;i<=q+1;++i){
        for(int j=0;j<p;++j){
            int w = getUnsigned();
            int idx = (q+1)*j+i;
            int jdx = idx + q + 1;
            mkEdge(idx,jdx,1,-w);
            mkEdge(idx,jdx,10000,0);
        }
    }

    ///超级源到a个起点
    for(int i=0;i<a;++i){
        int k = getUnsigned();
        int y = getUnsigned();
        int x = getUnsigned();
        mkEdge(s,y*(q+1)+x+1,k,M3);
    }

    ///b个终点到超级汇
    for(int i=0;i<b;++i){
        int r = getUnsigned();
        int y = getUnsigned();
        int x = getUnsigned();
        mkEdge(y*(q+1)+x+1,t,r,0);
    }

    pii ans = mcmf(s,t,VN,D,Pre,Flag);
    //cout<<M3<<endl;
    //cout<<ans.first<<" "<<ans.second<<endl;
    cout<<M3*ans.first-ans.second<<endl;
    return 0;
}
