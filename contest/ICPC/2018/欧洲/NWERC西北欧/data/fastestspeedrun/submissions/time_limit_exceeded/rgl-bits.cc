#include <bits/stdc++.h>
using namespace std;

#define MAXN 28
uint32_t cost[5001][5001];

int main(){
  int n; cin>>n;
  for (int i=1; i<=n; i++){
    uint32_t x,t; cin>>x>>t;
    for (int j=0; j<=n; j++){
      cin>>cost[j][i];
    }
    cost[x][i]=min(cost[x][i],t);
  }

  map<uint64_t,uint32_t> dp;
  dp[0]=0;
  for (uint64_t mask=0; mask<(1llu<<(uint64_t)n); mask++){
    for (uint64_t y=1; y<=n; y++) if (!(mask&(1ll<<(y-1))))
      for (uint64_t x=0; x<=n; x++) if (x==0 or (mask&(1ll<<(x-1))))
        if (not dp.count(mask|(1ll<<(y-1))) or dp[mask|(1ll<<(y-1))]>dp[mask]+cost[x][y])
          dp[mask|(1ll<<(y-1))]=dp[mask]+cost[x][y];
  }

  cout<<dp[(1<<n)-1]<<endl;
}
