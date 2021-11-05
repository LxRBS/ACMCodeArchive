/*
给定N个任务，完成每个任务需要执行p天，其可行的时间段在[s,e]之间
只有M个机器用于执行任务
问是否可行
*/
#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE_OF_VERTICES = 2000;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int to;
    weight_t cap;//容量
    weight_t flow;//流量
    int next;
}Edge[SIZE_OF_EDGES];//注意是MAXM
int ECnt;

int Vertex[SIZE_OF_VERTICES];

//初始化
inline void initGraph(int n){
    ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
    fill(Vertex,Vertex+n+1,0);
}

//生成边
inline void mkEdge(int a,int b,weight_t w){
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;//反向边
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int D[SIZE_OF_VERTICES];//Di表示i到汇的距离
int Cnt[SIZE_OF_VERTICES];//Cnti表示距离为i的顶点的个数
int Queue[SIZE_OF_VERTICES];//辅助队列

//反向BFS，搜索各点到汇的距离，t为汇，n为顶点总数
void bfs(int t,int n){
    fill(D,D+n+1,-1);
    fill(Cnt,Cnt+n+1,0);

    int u,v, head = 0, tail = 0;
    Cnt[ D[ Queue[tail++]=t ] = 0 ] = 1;

    while(head != tail){
        for(int p = Vertex[ u = Queue[head++] ]; p ; p = Edge[p].next){
            if ( -1 == D[ v = Edge[p].to ] ){
                ++ Cnt[ D[ Queue[tail++]=v ] = D[u] + 1 ];
            }
        }
    }
}

int Cur[SIZE_OF_VERTICES];//当前弧
int Stack[SIZE_OF_VERTICES];//辅助栈

//Improved shortest argument path algorithm
//s为源，t为汇，n为顶点个数
weight_t isap(int s,int t,int n){
    bfs(t,n);
    copy(Vertex,Vertex+n+1,Cur);

    weight_t ans = 0;
    int u = s, top = 0;

    while(D[s] < n){
        if(u == t){//找到一条增广路
            int inser,flow = INF;
            weight_t wtmp;
            for(int i=0;i<top;++i)if( flow > ( wtmp = Edge[Stack[i]].cap - Edge[Stack[i]].flow ) ){
                flow = wtmp, inser = i;
            }
            for(int i=0;i<top;++i){
                Edge[Stack[i]].flow += flow;  //正向边
                Edge[Stack[i]^1].flow -= flow;//反向边
            }
            ans += flow;
            top = inser;
            u = Edge[Stack[top]^1].to;
            continue;
        }

        //查找可行弧
        int v, ava = 0;
        for(int p=Cur[u];p;p=Edge[p].next){
            if(Edge[p].cap - Edge[p].flow && D[ v = Edge[p].to ] + 1 == D[u]){
                Cur[u] = ava = p;
                break;
            }
        }

        if(ava){//找到可行弧以后，推进
            Stack[top++] = Cur[u];
            u = v;
            continue;
        }

        //找不到可行弧，回溯
        int tmpd = n;
        for(int p=Vertex[u];p;p=Edge[p].next)
        if( Edge[p].cap - Edge[p].flow && D[Edge[p].to] < tmpd ){
            tmpd = D[Edge[p].to];
            Cur[u] = p;
        }
        --Cnt[D[u]];

        if(!Cnt[D[u]])return ans;

        ++Cnt[ D[u] = tmpd + 1 ];

        if(u != s) u = Edge[Stack[--top]^1].to;
    }

    return ans;
}

int N,M;
int SRC,DST;
int TotalDays;
void read(){
    scanf("%d%d",&N,&M);

    initGraph(N+500+2);

    SRC = N+500+1;
    DST = SRC + 1;
    TotalDays = 0;

    //从每一天到汇建一条边
    for(int i=1;i<=500;++i) mkEdge(i+N,DST,M);

    int p,s,e;
    for(int i=1;i<=N;++i){
        scanf("%d%d%d",&p,&s,&e);
        TotalDays += p;

        //对每个任务，从源建立一条边
        mkEdge(SRC,i,p);

        //每个任务到执行的时间段建立一条边
        for(int j=s;j<=e;++j) mkEdge(i,j+N,1);
    }

}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: ",kase);
        printf(isap(SRC,DST,N+500+2)==TotalDays?"Yes\n\n":"No\n\n");
    }
    return 0;
}
