#include <bits/stdc++.h>
using namespace std;

constexpr int64_t infinity=(1llu<<60llu);
typedef pair<int64_t,int> E;
vector<vector<E>> e,r;

int main(){
  int64_t stime,etime; cin>>stime>>etime;
  int n,m; cin>>n>>m;
  e.resize(n);
  r.resize(n);
  while (m--){
    int a,b; int64_t c; cin>>a>>b>>c; --a,--b;
    e[a].emplace_back(c,b);
    r[b].emplace_back(c,a);
  }

  auto sshpath=[n](vector<vector<E>> const &g,int s){
    priority_queue<E,vector<E>,greater<E>> djk;
    vector<int64_t> d(n,infinity);
    djk.emplace(d[s]=0,s);
    while (not djk.empty()){
      int x=djk.top().second; int64_t c=djk.top().first; djk.pop();
      if (c==d[x])
        for (auto y: g[x])
          if (d[x]+y.first<d[y.second])
            djk.emplace(d[y.second]=d[x]+y.first,y.second);
    }
    return d;
  };
  auto const dist=sshpath(e,0);
  auto const potential=sshpath(r,n-1);

  if (stime==etime){
    cout<<max((int64_t)0,dist[n-1]-stime)<<endl;
    return 0;
  }

  int64_t lef=-1;
  for (int64_t rad=(1ll<<40ll); rad; rad>>=1ll){
    int64_t mid=(lef+rad);

    // Make a reduced graph with only legal vertices and edges.
    vector<bool> reachable(n);
    stack<int> dfs;
    for (int i=0; i<n; i++){
      if (dist[i]+potential[i]<=stime+mid){
        reachable[i]=true;
        dfs.push(i);
      }
    }
    while (not dfs.empty()){
      int x=dfs.top(); dfs.pop();
      for (auto y: e[x])
        if (y.first+potential[y.second]<=mid and not reachable[y.second])
          reachable[y.second]=true, dfs.push(y.second);
    }

    // An edge is legal if its length + end potential <= mid.
    decltype(e) e2(n);
    vector<int> r2(n,0);
    for (int i=0; i<n; i++)
      if (reachable[i])
        for (auto y: e[i])
          if (y.first+potential[y.second]<=mid)
            e2[i].emplace_back(y),
            r2[y.second]++;

    // Find longest path.
    // path[x] = latest we can arrive at x and still always arrive in time.
    queue<int> bfs;
    vector<int64_t> path(n,-infinity);
    for (int i=0; i<n; i++){
      if (dist[i]+potential[i]<=stime+mid)
        path[i]=(stime+mid)-potential[i];
      if (not r2[i])
        bfs.push(i);
    }
    while (not bfs.empty()){
      int x=bfs.front(); bfs.pop();
      for (auto y: e2[x]){
        path[y.second]=max(path[y.second],path[x]+y.first);
        if (not --r2[y.second])
          bfs.push(y.second);
      }
    }
    bool possible=(path[n-1]>=etime);

    // Check for reachable cycles.
    bool cycle=false;
    for (int i=n; i--;)
      if (path[i]>=0 and r2[i])
        cycle=true,
        possible=true;

    if (not possible) lef=mid;
  }

  int64_t res=min(lef+1,potential[0]);
  cout<<res<<endl;
}
