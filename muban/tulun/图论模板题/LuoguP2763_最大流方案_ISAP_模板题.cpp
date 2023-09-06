#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 101;
#else
int const SZ = 110;
#endif

struct MaxFlow_ISAP{

enum{INF = 0x7F7F7F7FFFFFFFFF};

#ifndef ONLINE_JUDGE
enum{SIZE_OF_VERTICES = 120};
enum{SIZE_OF_edgesS = 120 << 2};
#else
enum{SIZE_OF_VERTICES = 100020};
enum{SIZE_OF_edgesS = 1200000 << 2};
#endif

using weight_t = long long;

struct edges_t{
    int to;
    weight_t cap;//容量
    weight_t flow;//流量
    int next;
}edges[SIZE_OF_edgesS];
int ECnt;

int n;
int Vertex[SIZE_OF_VERTICES];

//初始化
inline void init(int n){
    ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
    fill(Vertex,Vertex+(this->n=n)+1,0);
}

//生成边
inline void mkDirectEdge(int a,int b,weight_t w){
    edges[ECnt].to = b;
    edges[ECnt].cap = w;
    edges[ECnt].flow = 0;
    edges[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    edges[ECnt].to = a;
    edges[ECnt].cap = 0;//有向图的反向边为0，无向图的反向边同正向边
    edges[ECnt].flow = 0;
    edges[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int __D[SIZE_OF_VERTICES];//Di表示i到汇的距离
int __Cnt[SIZE_OF_VERTICES];//Cnti表示距离为i的顶点的个数
int Queue[SIZE_OF_VERTICES];//辅助队列

//反向BFS，搜索各点到汇的距离，t为汇，n为顶点总数
void bfs(int t){
    fill(__D,__D+n+1,-1);
    fill(__Cnt,__Cnt+n+1,0);

    int u,v, head = 0, tail = 0;
    __Cnt[ __D[ Queue[tail++]=t ] = 0 ] = 1;

    while(head != tail){
        for(int p = Vertex[ u = Queue[head++] ]; p ; p = edges[p].next){
            if ( -1 == __D[ v = edges[p].to ] ){
                ++ __Cnt[ __D[ Queue[tail++]=v ] = __D[u] + 1 ];
            }
        }
    }
}

int Cur[SIZE_OF_VERTICES];//当前弧
int Stack[SIZE_OF_VERTICES];//辅助栈

//Improved shortest argument path algorithm
//s为源，t为汇
weight_t maxflow(int s,int t){
    bfs(t);
    copy(Vertex,Vertex+n+1,Cur);

    weight_t ans = 0;
    int u = s, top = 0;

    while(__D[s] < n){
        if(u == t){//找到一条增广路
            int inser;
            weight_t wtmp,flow = INF;
            for(int i=0;i<top;++i)if( flow > ( wtmp = edges[Stack[i]].cap - edges[Stack[i]].flow ) ){
                flow = wtmp, inser = i;
            }
            for(int i=0;i<top;++i){
                edges[Stack[i]].flow += flow;  //正向边
                edges[Stack[i]^1].flow -= flow;//反向边
            }
            ans += flow;
            top = inser;
            u = edges[Stack[top]^1].to;
            continue;
        }

        //查找可行弧
        int v, ava = 0;
        for(int p=Cur[u];p;p=edges[p].next){
            if(edges[p].cap > edges[p].flow && __D[ v = edges[p].to ] + 1 == __D[u]){
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
        for(int p=Vertex[u];p;p=edges[p].next)
        if( edges[p].cap > edges[p].flow && __D[edges[p].to] < tmpd ){
            tmpd = __D[edges[p].to];
            Cur[u] = p;
        }
        --__Cnt[__D[u]];

        if(!__Cnt[__D[u]])return ans;

        ++__Cnt[ __D[u] = tmpd + 1 ];

        if(u != s) u = edges[Stack[--top]^1].to;
    }

    return ans;
}

void forEachUsed(function<void(int p, weight_t usedw)> f){
    for(int p=2;p<ECnt;p+=2){
        if(edges[p].flow > 0){
            f(p, edges[p].flow);
        }
    }
    return;
}


};

int K, N;
int M;
MaxFlow_ISAP ISAP;

void proc(){
    auto ans = ISAP.maxflow(N + K + 1, N + K + 2);
    if(ans != M) return (void)(cout << "No Solution!" << endl);

    vvi results(K + 1, vi());
    ISAP.forEachUsed([&](int index, MaxFlow_ISAP::weight_t usedw){
        int from = ISAP.edges[index ^ 1].to;
        int to = ISAP.edges[index].to;
        if(1 <= from and from <= K and K + 1 <= to and to <= N + K){
            assert(usedw == 1);
            results[from].push_back(to - K);
        }
    });
    for(int i=1;i<=K;++i){
        sort(results[i].begin(), results[i].end());
        cout << i << ":";
        for(int j : results[i]) cout << " " << j;
        cout << endl;
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> K >> N;

    M = 0;
    ISAP.init(N + K + 2);
    for(int a,i=1;i<=K;++i){
        cin >> a;
        ISAP.mkDirectEdge(N + K + 1, i, a);
        M += a;
    }
    
    for(int i=1;i<=N;++i){
        int p; cin >> p;
        for(int type,j=0;j<p;++j){
            cin >> type;
            ISAP.mkDirectEdge(type, K + i, 1);
        }
        ISAP.mkDirectEdge(K + i, N + K + 2, 1);
    }

    proc();
    return 0;
}