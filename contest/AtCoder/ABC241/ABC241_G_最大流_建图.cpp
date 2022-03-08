/**
 * N个人两两进行比赛，已经打了M场，有结果。问所有N个人中，哪些人有可能成为严格胜者
 * 所谓严格胜者就是胜场比别人多。N在50.
 * 规模比较小，可以考虑挨个判定，即问第u个人是否能够成为严格胜者。
 * 记录下已有结果，并且令剩下u的比赛全赢，看其余人的胜场是否均不超过这个数即可。
 * 感觉应该有别的方法。
 * 这是一个比较典型的匹配，左边为比赛，右边为选手，一场比赛可能与两个选手有关，但是最终只能连一条边，即只能与胜者连边
 * 由于选手那边可以有多场，所以是一个多重匹配。考虑使用最大流
 * 设当前考虑的选手为u，则已知比赛和u的比赛结果均已知，从比赛到胜者连一条边，容量为1
 * 未知比赛到参赛双方分别连一条边，容量为1
 * 源到每场比赛连一条边容量为1
 * u选手到汇连一条边，容量为N-1-Cnt[u]，其中Cnt[u]是负场数，已知
 * 其余选手到汇连一条边，容量为N-2-Cnt[u]
 * 跑最大流，如果能跑到N*(N-1)/2，说明u选手OK
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef int llt;

llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 55;
#endif  

typedef int weight_t;

int const SIZE_OF_VERTICES = 3500;//点数的最大值
int const SIZE_OF_EDGES = 1500*100;//边数的最大值
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

typedef pair<int, int> pii;
int N, M;
vector<pii> Already;
bool Flag[SIZE][SIZE] = {0};
int Cnt[SIZE] = {0};

inline int tr(int a, int b){if(a>b)swap(a,b);return --a * N + (--b) + 1;}
inline int tr(int a){return N*N+a;}

/// idx是否可能成为严格胜者
bool proc(int idx){
    int vn = N + N*N+2;
    int t = vn, s = vn - 1;
    
    initGraph(vn);
    /// 已有的比赛结果
    for(const auto &p: Already){
        int a = p.first, b = p.second;
        mkEdge(tr(a, b), tr(a), 1);
    }
    /// 对idx的所有没有比的比赛
    for(int i=1;i<=N;++i)if(i!=idx&&!Flag[idx][i]){
        mkEdge(tr(idx, i), tr(idx), 1);
    }
    /// 对所有的比赛
    for(int i=1;i<=N;++i)for(int j=i+1;j<=N;++j){
        mkEdge(s, tr(i, j), 1);
        /// 所有剩下的比赛
        if(idx==i||idx==j||Flag[i][j]) continue;
        mkEdge(tr(i, j), tr(i), 1);
        mkEdge(tr(i, j), tr(j), 1);
    }
    /// 终点
    for(int i=1;i<=N;++i){
        if(i == idx) mkEdge(tr(i), t, N-Cnt[i]-1);
        else mkEdge(tr(i), t, N-Cnt[idx]-2);
    }

    auto ans = isap(s, t, vn);
    if(ans == N*(N-1)/2) return true;
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
    for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
        Already.emplace_back(a, b);
        Flag[a][b] = Flag[b][a] = true;
        ++Cnt[b]; // 记录负的次数
    }
    vector<int> ans;
    for(int i=1;i<=N;++i){
        if(proc(i)) ans.push_back(i);
    }
    for(auto i: ans)printf("%d ", i);
    puts("");
    return 0;
}

