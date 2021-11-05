#include <cstdio>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

struct edge_t{
    int node;
    int weight;
};

edge_t Graph[501][501];
int Degree[501];

int Dist[501];
bool Flag[501];
int Cnt[501];

//带判断的spfa,s是源点，n是点的数量
bool spfa(int s,int n){
    fill(Dist+1,Dist+n+1,INT_MAX);
    Dist[s] = 0;

    fill(Flag+1,Flag+n+1,false);
    Flag[s] = true;

    fill(Cnt+1,Cnt+n+1,0);
    Cnt[s] = 1;

    queue<int> q;
    q.push(s);

    while( !q.empty() ){
        int u = q.front();
        q.pop();
        Flag[u] = false;

        for(int i=0;i<Degree[u];++i){
            int v = Graph[u][i].node;
            int tmp = Dist[u] + Graph[u][i].weight;
            if ( tmp < Dist[v] ){
                Dist[v] = tmp;
                if ( !Flag[v] ){
                    q.push(v);
                    Flag[v] = true;
                    ++Cnt[v];
                    if ( Cnt[v] >= n ) return false;
                }
            }
        }
    }
    return true;
}

int main(){
    int kase;
    scanf("%d",&kase);
    while(kase--){
        int n,m,w;
        scanf("%d%d%d",&n,&m,&w);

        fill(Degree+1,Degree+n+1,0);

        for(int i=0;i<m;++i){
            int a,b,t;
            scanf("%d%d%d",&a,&b,&t);

            Graph[a][Degree[a]].node = b;
            Graph[a][Degree[a]].weight = t;
            ++Degree[a];

            Graph[b][Degree[b]].node = a;
            Graph[b][Degree[b]].weight = t;
            ++Degree[b];
        }

        for(int i=0;i<w;++i){
            int a,b,t;
            scanf("%d%d%d",&a,&b,&t);

            Graph[a][Degree[a]].node = b;
            Graph[a][Degree[a]].weight = - t;
            ++Degree[a];
        }

        printf( !spfa(1,n) ? "YES\n" : "NO\n" );
    }
    return 0;
}
