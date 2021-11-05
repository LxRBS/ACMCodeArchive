/**
    一个图，要求：
    1 每条边染一个颜色，一共有100500种颜色
    2 每种颜色最多染两条边
    3 每个点最多与k中颜色的边相连
    点数和边数在600，因此颜色数量可以认为是无穷，k在点数以内
    对每一个点，如果度数超过2k，则必然失败
    如果度数小于等于k，则根本无需考虑
    对于度数在(k, 2k]的点，必然有i-k对边颜色是相同的，成对出现，且只出现在这个点
    所以对于每个点，要与2*(i-k)条边匹配
    所以是一个多重匹配问题，可以用最大流解决
    如果能够跑出最大流，则匹配的边每一对染一种颜色，剩下的边依次染不同颜色即可
    ISAP直接用正向边即可判断最大流时用了哪些边
*/
#include <bits/stdc++.h>
using namespace std;

typedef int llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int weight_t;

int const SIZE_OF_VERTICES = 100010;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int from, to;
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
    Edge[ECnt].cap = 0;//有向图的反向边为0，无向图的反向边同正向边
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
            int inser;
            weight_t wtmp,flow = INF;
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

typedef pair<int,int> pii;
int N,M,K;
int Degree[610];
vector<int> Dian;
vector<int> E[610];
vector<int> Ans[610];

bool f_degree(){
    for(int i=1,k2=K+K;i<=N;++i){
        if(Degree[i]>k2) return false;
        if(Degree[i]>K) Dian.push_back(i);
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        K = getUnsigned();

        fill(Degree,Degree+N+1,0);
        for(int i=1;i<=N;++i){
            E[i].clear();
            Ans[i].clear();
        }
        Dian.clear();

        for(int a,b,i=1;i<=M;++i){
            ++Degree[a = getUnsigned()];
            ++Degree[b = getUnsigned()];
            E[a].push_back(i);
            E[b].push_back(i);
        }

        ///统计点的度数
        if(!f_degree()){//无解
            printf("0");
            for(int i=1;i<M;++i)printf(" 0");
            printf("\n");
            continue;
        }

        ///建图
        int vn = N + M + 2;
        int s = vn - 1, t = vn;
        initGraph(vn);
        ///对每一个点
        int tmp = 0;
        for(auto i: Dian){
            ///对每一个与其相连的边
            for(auto j: E[i]){
                mkEdge(i, j+N, 1);
            }
            ///起点到点有一条边
            mkEdge(s, i, (Degree[i]-K)*2);
            tmp += (Degree[i]-K)*2;
        }
        ///每条边到终点有一条边
        for(int i=1;i<=M;++i){
            mkEdge(i+N, t, 1);
        }
        ///跑一个最大流
        weight_t ans = isap(s, t, vn);
        if(ans!=tmp){//无解
            printf("0");
            for(int i=1;i<M;++i)printf(" 0");
            printf("\n");
            continue;
        }
        ///有解，检查反向边，看用的哪一条
        for(auto i: Dian){
            ///对与i相关的每一条正向向边，检查是否使用了流量
            for(int p=Vertex[i];p;p=Edge[p].next)if(!(p&1)){
                if(Edge[p].flow==1){
                    Ans[i].push_back(Edge[p].to-N);
                }
            }
        }
        ///输出
        int c[610]={0},cc=0;
        for(auto i: Dian){
                /*
            printf("%d %d\n",i, (int)Ans[i].size());
            for(auto j: Ans[i]){
                printf("%d ",j);
            }
            printf("\n");//*/
            int tmp = 2*(Degree[i]-K);

            for(unsigned j=0,n=Ans[i].size();j<n;j+=2){
                if(j<tmp){
                    c[Ans[i][j]] = ++cc;
                    c[Ans[i][j+1]] = cc;
                }
            }
        }
        ///剩下的
        for(int i=1;i<=M;++i)if(0==c[i])c[i] = ++cc;
        printf("%d", c[1]);
        for(int i=2;i<=M;++i)printf(" %d",c[i]);
        printf("\n");
    }
    return 0;
}
