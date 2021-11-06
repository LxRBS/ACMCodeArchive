/**
    有若干个人，从某个x坐标从某个时刻开始走，速度恒定为1，可以向x正方向也可以负方向
    现在给若干个采样(t,x)，表示在t时刻x坐标至少有一个人
    问至少要多少个人才能满足这样的采样

    很明显，如果多个采样点在一条45°直线上，或者一条负45°直线上，可以由一个人完成
    因此原题变为用两类直线去覆盖点，用最少的直线进行覆盖
    典型的最小点覆盖问题，跑一个最大匹配即可
    也可以跑一个最大流，isap比HopcroftKarp慢一点点
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

vector<int> G[100010];

int N;
llt X[100010],T[100010];
int A[100010][2];

unordered_map<llt,int> BZ,BF;
unordered_map<llt,int>::iterator USIt;

void read(){
    N = getUnsigned();
    for(int i=1;i<=N;++i){
        T[i] = getUnsigned();
        X[i] = getUnsigned();
        G[i].clear();
    }

    BZ.clear();
    BF.clear();

    //依次每个点
    for(int i=1;i<=N;++i){
        llt bz = X[i] - T[i];
        if((USIt=BZ.find(bz))!=BZ.end()){
            A[i][0] = USIt->second;
        }else{
            A[i][0] = BZ.size() + 1;
            BZ.insert(make_pair(bz,A[i][0]));
        }

        llt bf = X[i] + T[i];
        if((USIt=BF.find(bf))!=BF.end()){
            A[i][1] = USIt->second;
        }else{
            A[i][1] = BF.size() + 1;
            BF.insert(make_pair(bf,A[i][1]));
        }
    }
}
typedef int weight_t;

int const SIZE_OF_VERTICES = 200010;//点数的最大值
int const SIZE_OF_EDGES = 200010<<2;//边数的最大值
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int to;
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
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

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

void proc(){
    //建图
    int na = BZ.size();
    int nb = BF.size();
    initGraph(na+nb+2);

    int s = na+nb+1;
    int t = na+nb+2;

    //建边
    for(int i=1;i<=N;++i){
        mkEdge(A[i][0],A[i][1]+na,1);
    }
    for(int i=1;i<=na;++i)mkEdge(s,i,1);
    for(int i=1;i<=nb;++i)mkEdge(i+na,t,1);

    printf("%d\n",isap(s,t,t));
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        read();
        proc();
    }
    return 0;
}
