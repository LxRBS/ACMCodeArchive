#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool edge[5001][5001];
ll cost[5001][5001];

#define f(i) for (int i=n; i--;)

int main(){
  int n; cin>>n; ++n;
  ll res=0;

  for (int i=1; i<n; i++){
    int x; ll t; cin>>x>>t; res+=t;
    edge[i][i]=edge[x][i]=true;
    for (int j=0; j<n; j++){
      cin>>cost[j][i]; cost[j][i]-=t;
    }
  }

  f(i) f(j) f(k) edge[j][k]|=edge[j][i]&edge[i][k];

  for (int i=1; i<n; i++)
    for (int j=1; j<i; j++)
      if (edge[i][j] and edge[j][i])
        for (int k=0; k<n; k++)
          cost[i][k]=min(cost[i][k],cost[j][k]);

  for (int i=1; i<n; i++){
    bool is_root=true;
    f(j) is_root&=(j<=i and edge[i][j]) or not edge[j][i];
    if (is_root){
      res+=cost[n-1][i];
      for (int j=0; j<n; j++) cost[j][i]-=cost[n-1][i];
    }
  }

  f(i) f(j) if (edge[i][j]) cost[i][j]=0;
  f(i) f(j) f(k) cost[j][k]=min(cost[j][k],cost[j][i]+cost[i][k]);

  cout<<cost[0][n-1]+res<<endl;
}
