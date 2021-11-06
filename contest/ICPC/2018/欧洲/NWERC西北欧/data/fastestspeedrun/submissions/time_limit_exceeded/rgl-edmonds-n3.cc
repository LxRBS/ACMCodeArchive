#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://en.wikipedia.org/wiki/Edmonds%27_algorithm

int levels=0;

struct Graph{
  int n;

  vector<vector<int64_t>> edge;
  vector<int> pi;

  Graph(int n): n(n) {edge.assign(n,vector<int64_t>(n,1ll<<40ll));}

  void add_edge(int a,int b,int64_t w){
    edge[a][b]=min(edge[a][b],w);
  }

  void find_pi(){
    pi.resize(n);
    for (int i=n; i-->1;)
      for (int j=n; j-->0;)
        if (i!=j and edge[j][i]<edge[pi[i]][i])
          pi[i]=j;
  }

  vector<int> find_cycle(){
    vector<int> visited(n,-1);
    visited[0]=0;

    for (int i=n; i--;){
      if (~visited[i]) continue;

      int x=i;
      while (!~visited[x]){
        visited[x]=i;
        x=pi[x];
      }

      if (visited[x]==i){
        vector<int> res={x};
        for (int j=pi[x]; j!=x; j=pi[j]) res.push_back(j);
        return res;
      }
    }
    return {};
  }

  int64_t solve(){
    find_pi();
    vector<int> cycle=find_cycle();

    ++levels;

    if (cycle.empty()){
      int64_t res=0;
      for (int i=n; i-->1;){
        res+=edge[pi[i]][i];
      }
      return res;
    }

    vector<int> keep(n,0);
    for (auto i: cycle) keep[i]=-1;
    for (int i=0,j=0; i<n; i++) if (~keep[i]) keep[i]=j++;

    int64_t res=0;
    {
      Graph gp(n+1-cycle.size());
      int const sink=gp.n-1;
      for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
          if (keep[i]==-1 and keep[j]==-1){
            if (pi[j]==i) res+=edge[i][j];
          } else if (keep[i]!=-1 and keep[j]!=-1){
            gp.edge[keep[i]][keep[j]]=edge[i][j];
          } else if (keep[i]!=-1 and keep[j]==-1){
            gp.add_edge(keep[i],sink,edge[i][j]-edge[pi[j]][j]);
          } else if (keep[i]==-1 and keep[j]!=-1){
            gp.add_edge(sink,keep[j],edge[i][j]);
          }
        }
      }
      n=gp.n;
      edge=gp.edge;
      pi=gp.pi;
    }

    return res+solve();
  }
};

int main(){
  int n; cin>>n;
  Graph g(n+1);

  for (int i=1; i<=n; i++){
    int x,t; cin>>x>>t;
    for (int j=0; j<=n; j++){
      cin>>g.edge[j][i];
    }
    if (x!=i){
      g.edge[x][i]=t;
    }
  }

  cout<<g.solve()<<endl;
  cerr<<"used "<<levels<<" levels"<<endl;
}
