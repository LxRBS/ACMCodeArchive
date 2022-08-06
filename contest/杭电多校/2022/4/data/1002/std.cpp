#include <cstdio>
#include <algorithm>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#define MN 100000
 
using std::min;
using std::max;
using std::function;
using std::greater;
using std::swap;
using std::stack;
using std::queue;
using std::priority_queue;
using std::vector;
 
using ll = long long;
 
const ll INF = 1e18;
 
struct Edge{
    int v,w1,w2;
};
 
namespace GetSpg{
    ll dis[MN+5];
    vector<Edge> e[MN+5];
    
    void clear(int n){
        for(int i=1;i<=n;i++){
            e[i].clear();
        }
    }
    
    void addEdge(int u,int v,int w1,int w2){
        e[u].push_back({v,w1,w2});
    }
    
    void dijkstra(int n,int S){
        using pii = std::pair<ll,int>;
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        for(int i=1;i<=n;i++){
            dis[i] = INF;
        }
        pq.push({dis[S]=0,S});
        while(!pq.empty()){
            int u = pq.top().second;
            ll d = pq.top().first;
            pq.pop();
            if(d!=dis[u]) continue;
            for(Edge edge:e[u]){
                int v = edge.v;
                int w = edge.w1;
                if(dis[u]+w<dis[v]){
                    dis[v] = dis[u]+w;
                    pq.push({dis[v],v});
                }
            }
        }
    }
    
    void solve(int n,function<void(int,int,int,int)> addEdge){
        dijkstra(n,1);
        for(int u=1;u<=n;u++){
            if(dis[u]==INF) continue;
            for(Edge edge:e[u]){
                if(dis[u]+edge.w1==dis[edge.v]){
                    addEdge(u,edge.v,edge.w1,edge.w2);
                }
            }
        }
    }
    
}
 
namespace GetDag{
    vector<Edge> e[MN+5];
    
    stack<int> s;
    bool ins[MN+5];
    int low[MN+5],dfn[MN+5],scc[MN+5];
    int dfnCnt=0,sccCnt=0;
    
    void clear(int n){
        for(int i=1;i<=n;i++){
            e[i].clear();
            ins[i] = false;
            dfn[i] = low[i] = scc[i] = 0;
        }
        dfnCnt = 0;
        sccCnt = 0;
        while(!s.empty()) s.pop();
    }
    
    void addEdge(int u,int v,int w1,int w2){
        e[u].push_back({v,w1,w2});
    }
    
    void tarjan(int u){
        dfn[u] = ++dfnCnt;
        low[u] = dfn[u];
        s.push(u);
        ins[u] = true;
        for(Edge edge:e[u]){
            int v = edge.v;
            if(dfn[v]){
                if(ins[v]){
                    low[u] = min(low[u],dfn[v]);
                }
            }else{
                tarjan(v);
                low[u] = min(low[u],low[v]);
            }
        }
        if(low[u]==dfn[u]){
            int v;
            ++sccCnt;
            do{
                v = s.top();
                s.pop();
                ins[v] = false;
                scc[v] = sccCnt;
            }while(u!=v);
        }
    }
    
    void solve(int& n,function<void(int,int,int,int)> addEdge,bool isLoop[]){
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        for(int u=1;u<=n;u++){
            for(Edge edge:e[u]){
                int v = edge.v;
                if(scc[u]==scc[v]){
                    if(edge.w2>0){
                        isLoop[scc[u]] = true;
                    }
                }else{
                    addEdge(scc[u],scc[edge.v],edge.w1,edge.w2);
                }
            }
        }
    }
    
}
 
namespace GetLp{
    int din[MN+5];
    bool isLoop[MN+5];
    vector<Edge> e[MN+5];
    
    struct Dis{
        ll d;
        Dis(ll d=0){
            this->d = d;
        }
        Dis operator + (const Dis& that)const{
            if(d==-INF||that.d==-INF) return Dis(-INF);
            if(d==INF||that.d==INF) return Dis(INF);
            return Dis(d+that.d);
        }
        bool operator < (const Dis& that)const{
            return this->d < that.d;
        }
    };
    
    Dis f[MN+5];
    
    void clear(int n){
        for(int i=1;i<=n;i++){
            din[i] = 0;
            isLoop[i] = false;
            e[i].clear();
        }
    }
    
    void addEdge(int u,int v,int w1,int w2){
        e[u].push_back({v,w1,w2});
        din[v]++;
    }
 
    void solve(int n,int S){
        for(int i=1;i<=n;i++){
            f[i] = -INF;
        }
        f[S] = 0;
        queue<int> q;
        for(int i=1;i<=n;i++){
            if(din[i]==0) q.push(i);
        }
        while(!q.empty()){
            int u = q.front();
            q.pop();
            if(isLoop[u]) f[u] = f[u]+INF;
            for(Edge edge:e[u]){
                int v = edge.v;
                int w = edge.w2;
                f[v] = max(f[v],f[u]+w);
                if(--din[v]==0){
                    q.push(v);
                }
            }
        }
    }
}
 
void solve(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w1,w2;
        scanf("%d%d%d%d",&u,&v,&w1,&w2);
        GetSpg::addEdge(u,v,w1,w2);
    }
    GetSpg::solve(n,GetDag::addEdge);
    GetDag::solve(n,GetLp::addEdge,GetLp::isLoop);
    GetLp::solve(GetDag::sccCnt,GetDag::scc[1]);
    printf("%lld %lld\n",GetSpg::dis[n],GetLp::f[GetDag::scc[n]].d);
    GetSpg::clear(n);
    GetDag::clear(n);
    GetLp::clear(n);
}
 
int main(){
    int T;
    scanf("%d",&T);
    while(T--) solve();
}
