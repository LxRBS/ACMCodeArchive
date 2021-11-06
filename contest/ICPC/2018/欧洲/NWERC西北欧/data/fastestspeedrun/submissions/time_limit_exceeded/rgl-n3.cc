#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool edge[5001][5001];
ll cost[5001][5001];

#define f(i) for (int i=n; i--;)
#define f2(i,j) f(i) f(j)
#define f3(i,j,k) f(i) f(j) f(k)

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

  f3(i,j,k) edge[j][k]|=edge[j][i]&edge[i][k];
  f2(i,j) if (edge[i][j]) f(k) cost[i][k]=min(cost[i][k],cost[j][k]);
  f2(i,j) if (edge[i][j]) cost[i][j]=0;

  for (int i=1; i<n; i++){
    bool is_root=true;
    f(j) is_root&=edge[i][j] and make_pair(cost[n-1][i],i)<=make_pair(cost[n-1][j],j) or not edge[j][i];
    if (is_root){
      auto const rcost=cost[n-1][i]; res+=rcost;
      f2(j,k) if (edge[i][j] and edge[j][i]) cost[k][j]-=rcost;
    }
  }

  f2(i,j) if (edge[i][j]) cost[i][j]=0;
  f3(i,j,k) cost[j][k]=min(cost[j][k],cost[j][i]+cost[i][k]);
  cout<<cost[0][n-1]+res<<endl;
}
