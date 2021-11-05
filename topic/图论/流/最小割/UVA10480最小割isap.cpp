/*
    求最小割
    要求出哪些边属于割集
*/
#include <stdio.h>
#include <limits.h>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE_OF_VERTICES = 100010;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int from,to;
    weight_t cap;//容量
    weight_t flow;//流量
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
inline void mkEdge(int a,int b,weight_t w){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].from = b;
    Edge[ECnt].to = a;
    Edge[ECnt].cap = w;//有向图的反向边为0，无向图的反向边同正向边
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int __D[SIZE_OF_VERTICES];//Di表示i到汇的距离
int __Cnt[SIZE_OF_VERTICES];//Cnti表示距离为i的顶点的个数
int Queue[SIZE_OF_VERTICES];//辅助队列

//反向BFS，搜索各点到汇的距离，t为汇，n为顶点总数
void bfs(int t,int n){
    fill(__D,__D+n+1,-1);
    fill(__Cnt,__Cnt+n+1,0);

    int u,v, head = 0, tail = 0;
    __Cnt[ __D[ Queue[tail++]=t ] = 0 ] = 1;

    while(head != tail){
        for(int p = Vertex[ u = Queue[head++] ]; p ; p = Edge[p].next){
            if ( -1 == __D[ v = Edge[p].to ] ){
                ++ __Cnt[ __D[ Queue[tail++]=v ] = __D[u] + 1 ];
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

    while(__D[s] < n){
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
            if(Edge[p].cap - Edge[p].flow && __D[ v = Edge[p].to ] + 1 == __D[u]){
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
        if( Edge[p].cap - Edge[p].flow && __D[Edge[p].to] < tmpd ){
            tmpd = __D[Edge[p].to];
            Cur[u] = p;
        }
        --__Cnt[__D[u]];

        if(!__Cnt[__D[u]])return ans;

        ++__Cnt[ __D[u] = tmpd + 1 ];

        if(u != s) u = Edge[Stack[--top]^1].to;
    }

    return ans;
}

int N,M;
bool read(){
    scanf("%d%d",&N,&M);
    if ( 0 == N && 0 == M ) return false;

    initGraph(N);

    int a,b,w;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&w);
        mkEdge(a,b,w);
    }

    return true;
}

struct ufs_t{
    enum{UF_SIZE=110};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int main(){
    //freopen("1.txt","r",stdin);

    while(read()){
        isap(1,2,N);

        //检查哪些边为满流
        UF.init(N);
        for(int i=2;i<ECnt;i+=2){
            if ( ( 0 <= Edge[i].flow && Edge[i].flow < Edge[i].cap )
              || ( 0 <= Edge[i+1].flow && Edge[i+1].flow < Edge[i+1].cap ) )
                UF.unite(Edge[i].from,Edge[i].to);
        }

        //检查哪些边可以被割除
        for(int i=2;i<ECnt;i+=2){
            if ( ( UF.find(1) == UF.find(Edge[i].from) && UF.find(1) != UF.find(Edge[i].to) )
                || ( UF.find(1) == UF.find(Edge[i].to) && UF.find(1) != UF.find(Edge[i].from) ) ){
                printf("%d %d\n",Edge[i].from,Edge[i].to);
            }
        }
        putchar('\n');
    }
    return 0;
}
