#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool active[5001];

bool cycle[5001];
int root[5001];
int p[5001];

int cost[5001][5001];

int dfs(int x){
  if (active[x]){
    root[x]=x;
  }else if (root[p[x]]!=-1){
    root[x]=root[p[x]];
  }else{
    active[x]=true;
    root[x]=dfs(p[x]);
    if (active[root[x]]) cycle[x]=true;
    active[x]=false;
  }
  return root[x];
}

int main(){
  int n; cin>>n; ++n;
  ll res=0;

  for (int i=1; i<n; i++){
    ll t; cin>>p[i]>>t; res+=t;
    for (int j=0; j<n; j++){
      cin>>cost[j][i]; cost[j][i]-=t;
    }
  }

  memset(root,-1,sizeof root);
  for (int i=n; i--;)
    if (root[i]==-1)
      root[i]=dfs(i);

  for (int i=1; i<n; i++)
    if (root[i]==i){
      int x=i;
      for (int j=n; j--;)
        if (root[j]==i and cycle[j] and cost[n-1][j]<cost[n-1][x])
          x=j;

      auto const rcost=cost[n-1][x]; res+=rcost;
      for (int j=n; j--;)
        if (root[j]==i and cycle[j])
          for (int k=n; k--;)
            cost[k][j]-=rcost;
    }

  for (int i=n; i--;)
    for (int j=n; j--;)
      if (i==p[j] or root[i]==root[j] and cycle[i])
        cost[i][j]=0;

  priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> todo;
  todo.emplace(0ll,0);
  while (not todo.empty()){
    int x=todo.top().second; ll w=todo.top().first; todo.pop();
    if (active[x]) continue; else active[x]=true;
    for (int y=n; y--;) todo.emplace(w+cost[x][y],y);
    cost[0][x]=w;
  }
  cout<<cost[0][n-1]+res<<endl;
}
