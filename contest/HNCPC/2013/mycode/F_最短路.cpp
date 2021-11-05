/**
 * 无向图，每条边有abw，意思是a秒开放、b秒关闭、w秒经过，从0开始即时
 * 问从S到T最短需要多少时间，不可达输出-1
 * 简单的最短路，标程似乎用的Bellman-Ford算法，因为点数最多300
 * 这里用的SPFA
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 10;
#else
int const SIZE = 310;
#endif

#define pb push_back
typedef tuple<int,int,int,int> edge_t;
typedef vector<edge_t> AdjTy;

int const INF = 0x3FFFFFFF;

AdjTy G[SIZE];
int N, M, S, T;

int D[SIZE];
bool Flag[SIZE];

inline int calc(int u, const edge_t &e){
    int tu = D[u];
    int a = get<1>(e), b = get<2>(e), w = get<3>(e);
    
    int left = tu % (a + b);
    if(a>=left+w){ // 可以即时出发
        return w;
    }

    /// 否则只能等下一次通道打开
    return (a + b - left) + w;
}

int proc(){
    if(S == T) return 0;
    fill(D+1, D+N+1, INF);
    fill(Flag+1, Flag+N+1, false);

    D[S] = 0;
    Flag[S] = true;
    
    queue<int> q;
    q.push(S);

    while(!q.empty()){
        int h = q.front();q.pop();
        Flag[h] = false;

        int tmp, v;
        for(edge_t e: G[h]){
            if((tmp=calc(h, e)+D[h]) < D[v=get<0>(e)]){
                D[v] = tmp;                
                if(!Flag[v]){
                    Flag[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return D[T] != INF ? D[T] : -1;
}

int main(){
    // freopen("2.txt","w",stdout);
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    for(int kase=1;4==scanf("%d%d%d%d", &N, &M, &S, &T);++kase){
        for(int i=1;i<=N;++i) G[i].clear();

        for(int u,v,a,b,t,i=0;i<M;++i){
            scanf("%d%d%d%d%d", &u, &v, &a, &b, &t);
            if(a>=t) G[u].pb({v, a, b, t});
        }

        printf("Case %d: %d\n", kase, proc());
    }
    return 0;
}
